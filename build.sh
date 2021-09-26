# SQUIRRELOS BUILD SCRIPT v0.1

# BOOT
#assemble boot.s file
as --32 boot/boot.s -o boot.o
as --32 gdt/load_gdt.s -o load_gdt.o
as --32 idt/load_idt.s -o load_idt.o


# CPU

gcc -m32 -c cpu/cpuid/cpuid.c -o cpuid.o -std=gnu99 -ffreestanding -w -I.

# DRIVERS
gcc -m32 -c drivers/acpi/acpi.c -o acpi.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/ata/ata.c -o ata.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/keyboard/keyboard.c -o keyboard.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/mouse/mouse.c -o mouse.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/pci/pci.c -o pci.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/ports/ports.c -o ports.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/rtc/rtc.c -o rtc.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/screen/screen.c -o screen.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/serial/serial.c -o serial.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/sound/pcspeaker/pcspeaker.c -o pcspeaker.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c drivers/timer/timer.c -o timer.o -std=gnu99 -ffreestanding -w -I.

# FS
gcc -m32 -c fs/initrd/initrd.c -o initrd.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c fs/fs.c -o fs.o -std=gnu99 -ffreestanding -I.
gcc -m32 -c fs/tar.c -o tar.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c fs/vfs.c -o vfs.o -std=gnu99 -ffreestanding -w -I.

# GDT
gcc -m32 -c gdt/gdt.c -o gdt.o -std=gnu99 -ffreestanding -w -I.

# IDT
gcc -m32 -c idt/idt.c -o idt.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c idt/isr.c -o isr.o -std=gnu99 -ffreestanding -I.

# INCLUDE
gcc -m32 -c include/math/math.c -o math.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c include/utils.c -o utils.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c include/printf.c -o printf.o -std=gnu99 -ffreestanding -w -I.

# KERNEL

# KERNEL - APPLICATIONS

gcc -m32 -c kernel/apps/apps.c -o apps.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c kernel/apps/cowsay/cowsay.c -o cowsay.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c kernel/apps/textedit/textedit.c -o textedit.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c kernel/apps/calculator/calculator.c -o calculator.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c kernel/apps/serialapp/serialapp.c -o serialapp.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c kernel/apps/slang/slang.c -o slang.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c kernel/apps/man/man.c -o man.o -std=gnu99 -ffreestanding -w -I.

# OLDSHELL
# gcc -m32 -c kernel/shell.c -o shell.o -std=gnu99 -ffreestanding -w -I.

gcc -m32 -c kernel/pic/pic.c -o pic.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c kernel/shell/lshell.c -o lshell.o -std=gnu99 -ffreestanding -w -I.
gcc -m32 -c kernel/panic.c -o panic.o -std=gnu99 -ffreestanding -w -I.

# KERNEL ENTRY

gcc -m32 -c kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -w -I.

ld -m elf_i386 -T boot/linker.ld kernel.o screen.o utils.o keyboard.o ports.o lshell.o apps.o man.o cowsay.o cpuid.o load_idt.o gdt.o idt.o isr.o vfs.o initrd.o serial.o panic.o pci.o rtc.o mouse.o pic.o ata.o fs.o acpi.o textedit.o math.o calculator.o serialapp.o slang.o tar.o printf.o pcspeaker.o timer.o boot.o load_gdt.o -o MyOS.bin -nostdlib --allow-multiple-definition

# Check MyOS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot MyOS.bin

# Build The ISO Disk Image File
rm -r out
mkdir out
mkdir -p boot/grubconf/boot/grub

cp MyOS.bin boot/grubconf/boot/MyOS.bin
cp boot/grub.cfg boot/grubconf/boot/grub/grub.cfg
grub-mkrescue -o out/MyOS.iso boot/grubconf

# Remove Files Created While Building Source
# rm -rf isodir
rm -rf *.o
rm -rf *.bin
