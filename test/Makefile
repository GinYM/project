ifneq ($(KERNELRELEASE),)
obj-m := modulename.o

else
	KDIR ?= /lib/modules/`uname -r'/build
default:
$(MAKE) -C $(KDIR) M=$$PWD

endif
