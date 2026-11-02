# normal makefile
ARCH ?= arm
CROSS_COMPILE ?= arm-linux-gnueabihf-

KDIR ?= /home/popovych-milana/repos/linux-stable

default:
	$(MAKE) -C $(KDIR) M=$$PWD ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
clean:
	$(MAKE) -C $(KDIR) M=$$PWD ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean
