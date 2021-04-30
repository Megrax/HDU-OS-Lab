obj-m := show_all_kt.o
KDIR := /lib/modules/$(shell uname -r)/build
# 当前路径
PWD := $(shell pwd)
default:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
