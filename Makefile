obj-m	:=myrt_process.o
KDIR	:=/lib/modules/$(shell uname -r)/build
PWD	:=$(shell pwd)
EXTRA_CFLAGS := -I/usr/realtime/include -I/usr/include -ffast-math -mhard-float
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
