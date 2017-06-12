#include "qemu/osdep.h"
#include "hw/hw.h"
#include "hw/sysbus.h"
#include "trace.h"
#include "qemu/error-report.h"
#include "qemu/main-loop.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include "pqueuedef.h"

#define REGISTER_DATA 0x100
#define TYPE "mydevice"
#define MY_DEVICE_REGISTER(obj) OBJECT_CHECK(MydeviceState, (obj), TYPE)

static void assert_internal(const char* file, int line);
static void assert_good(void);


static pthread_t thread1;
static pthread_t thread2;

struct mq_attr my_mq_attr,my_mq_attr2;
mqd_t my_mq,my_mq2;

static void thread1_main(void);
static void thread2_main(void);
static void mq_queue_init(void);

unsigned int counter = 10;
unsigned int pb_id = 0; 

static void assert_internal(const char* file, int line) {
   printf("Hit ASSERT in file %s, line %d. Aborting\n", file, line);
   exit(1);
}

static void assert_good(void) {
   return;
}

static void sig_handler(int signum) {
    if (signum != SIGINT) {
        printf("Received invalid signum = %d in sig_handler()\n", signum);
        ASSERT(signum == SIGINT);
    }

    printf("Received SIGINT. Exiting Application\n");

    pthread_cancel(thread1);
    pthread_cancel(thread2);

    mq_close(my_mq);
    mq_unlink(MY_MQ_NAME);

    exit(0);
}

struct MydeviceState {
    SysBusDevice parent_obj;
    MemoryRegion iomem;
    QEMUBH *bh;
    qemu_irq irq;
    uint32_t data;
    uint32_t regs;
};
typedef struct MydeviceState MydeviceState;


static void register_write(void *opaque, hwaddr addr,
                        uint64_t value, unsigned size)
{
    MydeviceState *s = opaque;

    s->regs = value;
    if(s->regs == 0x1) mq_queue_init();
    printf("WRITE");
    
}

static uint64_t register_read(void *opaque, hwaddr addr, unsigned size)
{
    MydeviceState *s = opaque;
    uint32_t r = 0;
    r = s->regs;
    //r = 0x1;
    if(r == 0x1) mq_queue_init();
    printf("READ");
    return r;
}

 static void mq_queue_init(void)
{
    pthread_attr_t attr;
    int status;
    counter =10;
    signal(SIGINT, sig_handler);
    my_mq_attr.mq_maxmsg = 10;
    my_mq_attr.mq_msgsize = sizeof(counter);
    my_mq_attr2.mq_maxmsg = 10;
    my_mq_attr2.mq_msgsize = sizeof(counter2);
    
    my_mq = mq_open(MY_MQ_NAME,O_CREAT | O_EXCL | O_RDWR | O_NONBLOCK,0666,&my_mq_attr);  //Exclsive with name
    pb_id = 1;
    counter = 100;
    if(my_mq == -1)
    {
        printf("Mq with name %s exists \n", MY_MQ_NAME);
        my_mq2 = mq_open(MY_MQ_NAME2,O_CREAT  | O_RDWR | O_NONBLOCK,0666,&my_mq_attr2); //Only once
        pb_id = 2;
        counter = 200;
    }
    //my_mq2 = mq_open(MY_MQ_NAME2,O_CREAT | O_RDWR | O_NONBLOCK,0666,&my_mq_attr2);
    //ASSERT(my_mq != -1);
    //ASSERT(my_mq2 != -1);

    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 1024*1024);
   
    printf("Creating thread1\n");
    status = pthread_create(&thread1, &attr, (void*)&thread1_main, NULL);
    if (status != 0) {
        printf("Failed to create thread1 with status = %d\n", status);
        ASSERT(status == 0);
    }    

    printf("Creating thread2\n");
    status = pthread_create(&thread2, &attr, (void*)&thread2_main, NULL);
    if (status != 0) {
        printf("Failed to create thread2 with status = %d\n", status);
        ASSERT(status == 0);
    }    

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sig_handler(SIGINT);

  }

static void thread1_main(void) {
    unsigned int exec_period_usecs;
    int status;

    exec_period_usecs = 1000000; /*in micro-seconds*/

    printf("Thread 1 started. Execution period = %d uSecs\n",\
                                           exec_period_usecs);
    
                                            
    
    while(1) {
        if(pb_id == 1)
        {
            status = mq_send(my_mq, (const char*)&counter, sizeof(counter), 1);
            ASSERT(status != -1);
            printf("SEND : Device 1:  %d\n",counter);
        }
        else if(pb_id == 2)
        {
            status = mq_send(my_mq2, (const char*)&counter, sizeof(counter), 1);
            ASSERT(status != -1);
            printf("SEND : Device 2:  %d\n",counter);
        }
        usleep(exec_period_usecs);
    }
}


static void thread2_main(void) {
    unsigned int exec_period_usecs;
    int status;
    int recv_counter;   
    
    exec_period_usecs = 10000; /*in micro-seconds*/
    
    printf("Thread 2 started. Execution period = %d uSecs\n",\
                                           exec_period_usecs);

    while(1) {
        if(pb_id == 1)
        {
            my_mq2 = mq_open(MY_MQ_NAME2,O_RDWR | O_NONBLOCK,0666,&my_mq_attr2);
            status = mq_receive(my_mq2, (char*)&recv_counter, \
                                sizeof(recv_counter), NULL);

            if (status > 0) {
                printf("RECVd MSG in THRD_2:Device 1: %d\n", recv_counter);
            
            }
            else
            {
                //printf("PB_ID = %d; status = %x", pb_id, status);
            }
        }
        else if(pb_id == 2)
        {
            my_mq = mq_open(MY_MQ_NAME,O_RDWR | O_NONBLOCK,0666,&my_mq_attr);
            status = mq_receive(my_mq, (char*)&recv_counter, \
                                sizeof(recv_counter), NULL);

            if (status > 0) {
                printf("RECVd MSG in THRD_2:Device 2: %d\n", recv_counter);
            
            }
            else
            {
                //printf("PB_ID = %d; status = %x", pb_id, status);
            }
        }
 
        usleep(exec_period_usecs);
    }
}

static const VMStateDescription vmstate_my_device_class = {
    .name = "mydevice",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(data, MydeviceState),
        VMSTATE_END_OF_LIST()
    }
};
static Property my_device_class_properties[] = {
    DEFINE_PROP_UINT32("Register", MydeviceState,data,REGISTER_DATA),
    DEFINE_PROP_END_OF_LIST(),
};


static void my_device_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->vmsd = &vmstate_my_device_class;
    dc->props = my_device_class_properties;
}


static const MemoryRegionOps my_device_ops = {
    .read = register_read,
    .write = register_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static void my_device_init(Object *obj)
{
    MydeviceState *s = MY_DEVICE_REGISTER(obj);
    SysBusDevice *dev = SYS_BUS_DEVICE(obj);

    sysbus_init_irq(dev, &s->irq);

    memory_region_init_io(&s->iomem, obj, &my_device_ops, s,"mydevice",4);
    sysbus_init_mmio(dev, &s->iomem);
}

static const TypeInfo my_device_info = {
    .name          = TYPE,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(MydeviceState),
    .instance_init = my_device_init,
    .class_init    = my_device_class_init,
};

static void my_device_register_types(void)
{
    type_register_static(&my_device_info);
}

type_init(my_device_register_types)
