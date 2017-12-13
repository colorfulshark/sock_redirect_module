KDIR=../../kernel/huawei-mate8-kernel-source

obj-m += sock_redirect_module.o

FLAGS = ARCH=arm64 CROSS_COMPILE=$(KDIR)/android-ndk-r14b/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-

module:
	make $(FLAGS) -C $(KDIR) M=$(CURDIR) modules

push:
	adb push sock_redirect_module.ko /sdcard/modules

clean:
	make $(FLAGS) -C $(KDIR) M=$(CURDIR) clean
