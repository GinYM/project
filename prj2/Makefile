obj-m := ptree.o
KID := ~/kernel/goldfish
export KBUILD_BUILDHOST := $(SUBARCH)
ARCH ?= arm
CROSS_COMPILE?=arm-linux-androideabi-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld

all:
	make -C $(KID) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) M=$(shell pwd) modules

clean:
	rm -rf *.k0 *.0 *.mod.c *.order *.sysvers
