obj-m := enable-cycle-cnt-regs.o

KVERSION := $(shell uname -r)
KERNEL_SRC  ?= /lib/modules/$(KVERSION)/build

SRC   := $(shell pwd)

.PHONY: all clean modules_install

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) clean

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

