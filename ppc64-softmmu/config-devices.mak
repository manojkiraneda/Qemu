# Default configuration for ppc64-softmmu

CONFIG_VIRTIO_VGA=y
CONFIG_ESCC=y
CONFIG_M48T59=y
CONFIG_SERIAL=y
CONFIG_PARALLEL=y
CONFIG_I8254=y
CONFIG_PCKBD=y
CONFIG_FDC=y
CONFIG_I8257=y
CONFIG_I82374=y
CONFIG_OPENPIC=y
CONFIG_PREP_PCI=y
CONFIG_I82378=y
CONFIG_PC87312=y
CONFIG_MACIO=y
CONFIG_PCSPK=y
CONFIG_CUDA=y
CONFIG_ADB=y
CONFIG_MAC_NVRAM=y
CONFIG_MAC_DBDMA=y
CONFIG_HEATHROW_PIC=y
CONFIG_GRACKLE_PCI=y
CONFIG_UNIN_PCI=y
CONFIG_DEC_PCI=y
CONFIG_PPCE500_PCI=y
CONFIG_IDE_ISA=y
CONFIG_IDE_CMD646=y
CONFIG_IDE_MACIO=y
CONFIG_NE2000_ISA=y
CONFIG_PFLASH_CFI01=y
CONFIG_PFLASH_CFI02=y
CONFIG_PTIMER=y
CONFIG_I8259=y
CONFIG_XILINX=y
CONFIG_XILINX_ETHLITE=y
CONFIG_PSERIES=y
CONFIG_POWERNV=y
CONFIG_PREP=y
CONFIG_MAC=y
CONFIG_E500=y
CONFIG_OPENPIC_KVM=$(and $(CONFIG_E500),$(CONFIG_KVM))
CONFIG_PLATFORM_BUS=y
CONFIG_ETSEC=y
CONFIG_LIBDECNUMBER=y
# For pSeries
CONFIG_XICS=$(CONFIG_PSERIES)
CONFIG_XICS_SPAPR=$(CONFIG_PSERIES)
CONFIG_XICS_KVM=$(and $(CONFIG_PSERIES),$(CONFIG_KVM))
# For PReP
CONFIG_SERIAL_ISA=y
CONFIG_MC146818RTC=y
CONFIG_ISA_TESTDEV=y
CONFIG_MEM_HOTPLUG=y
CONFIG_RS6000_MC=y
CONFIG_PCI=y
# For now, CONFIG_IDE_CORE requires ISA, so we enable it here
CONFIG_ISA_BUS=y
CONFIG_VIRTIO_PCI=y
CONFIG_VIRTIO=y
CONFIG_USB_UHCI=y
CONFIG_USB_OHCI=y
CONFIG_USB_EHCI=y
CONFIG_USB_XHCI=y
CONFIG_NE2000_PCI=y
CONFIG_EEPRO100_PCI=y
CONFIG_PCNET_PCI=y
CONFIG_PCNET_COMMON=y
CONFIG_AC97=y
CONFIG_HDA=y
CONFIG_ES1370=y
CONFIG_LSI_SCSI_PCI=y
CONFIG_VMW_PVSCSI_SCSI_PCI=y
CONFIG_MEGASAS_SCSI_PCI=y
CONFIG_MPTSAS_SCSI_PCI=y
CONFIG_RTL8139_PCI=y
CONFIG_E1000_PCI=y
CONFIG_E1000E_PCI=y
CONFIG_VMXNET3_PCI=y
CONFIG_IDE_CORE=y
CONFIG_IDE_QDEV=y
CONFIG_IDE_PCI=y
CONFIG_AHCI=y
CONFIG_FOO=y
CONFIG_ESP=y
CONFIG_ESP_PCI=y
CONFIG_SERIAL=y
CONFIG_SERIAL_ISA=y
CONFIG_SERIAL_PCI=y
CONFIG_IPACK=y
CONFIG_WDT_IB6300ESB=y
CONFIG_PCI_TESTDEV=y
CONFIG_NVME_PCI=y
CONFIG_SD=y
CONFIG_SDHCI=y
CONFIG_EDU=y
CONFIG_VGA=y
CONFIG_VGA_PCI=y
CONFIG_IVSHMEM=$(CONFIG_EVENTFD)
CONFIG_ROCKER=y
CONFIG_SB16=y
CONFIG_ADLIB=y
CONFIG_GUS=y
CONFIG_CS4231A=y
CONFIG_USB=y
CONFIG_USB_TABLET_WACOM=y
CONFIG_USB_STORAGE_BOT=y
CONFIG_USB_STORAGE_UAS=y
CONFIG_USB_STORAGE_MTP=y
CONFIG_USB_SMARTCARD=y
CONFIG_USB_AUDIO=y
CONFIG_USB_SERIAL=y
CONFIG_USB_NETWORK=y
CONFIG_USB_BLUETOOTH=y
