
#lesson 01
GPPPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-leading-underscore -Wwrite-strings
ASPARAMS = --32
LDPARAMS = -melf_i386
#CFLAGS = -Wl,-Bdynamic -lgcc_s
objects = obj/loader.o \
	obj/gdt.o \
	obj/memorymanagerment.o\
	obj/drivers/driver.o \
	obj/hardwarecommunication/port.o \
	obj/hardwarecommunication/interrupts.o \
	obj/hardwarecommunication/interruptstubs.o \
	obj/multitasking.o\
	obj/drivers/amd_am79c973.o\
	obj/hardwarecommunication/pci.o \
	obj/drivers/ata.o\
	obj/drivers/keyboard.o \
	obj/drivers/mouse.o\
	obj/drivers/vga.o\
	obj/gui/widget.o\
	obj/gui/window.o\
	obj/gui/destop.o\
	obj/kernel.o 
	
	
obj/%.o:src/%.cpp
	#g++ $(GPPPARAMS) $(CFLAGS)-o $@ -c $^
	mkdir -p $(@D)
	g++ $(GPPPARAMS) -o $@ -c $^

obj/%.o:src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $^

mykernel.bin:linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin 
	sudo cp $< /boot/mykernel.bin


#lesson 03 制作iso
mykernel.iso:mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $^ iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	#echo 'menuentry "My Operatoring System" {' >> iso/boot/grub/grub.cfg
	echo 'menuentry "mmyyooss" {' >> iso/boot/grub/grub.cfg
	echo 'multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo 'boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg

	grub-mkrescue --output=$@ iso
	rm -rf iso

#使用VB虚拟机后台运行,已经在运行时会报错，解决如下
run:mykernel.iso
	(killall VirtualBox && sleep 1) || true
	#VirtualBox --startvm "My Operatoring System" &
	VirtualBox --startvm "mmyyooss" &

.PHONY: clean
clean: 
	#rm -rf $(objects) mykernel.bin mykernel.iso
	rm -rf obj mykernel.bin mykernel.iso