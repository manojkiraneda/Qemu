extern unsigned int counter;
extern unsigned int counter2;
#define MY_MQ_NAME "/my_mq"
#define MY_MQ_NAME2 "/my_mq2"
#define ASSERT(test) (test) ? assert_good():assert_internal(__FILE__, __LINE__);
extern struct mq_attr my_mq_attr,my_mq_attr2;
extern mqd_t my_mq,my_mq2;
