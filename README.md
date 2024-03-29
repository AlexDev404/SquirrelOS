# SquirrelOS
My third attempt at OSDev. The fourth attempt is https://github.com/AlexDev404/Sapphire
<!-- <img src="https://raw.githubusercontent.com/AlexDev404/SquirrelOS/main/previewImg/CapturePreview4.PNG"/> -->
<img src="https://raw.githubusercontent.com/AlexDev404/SquirrelOS/main/previewImg/CapturePreview5.png"/>
A simple DOS like OS made in Assembly and C with a ported version of Stephen Brennan's [LSH](https://github.com/brenns10/lsh) Shell.

## Build

Run `sudo ./build.sh`.

## Run

To run the OS, you can download VM software.
A pre-built ISO image is in the `./out/` directory.

### Recommended:

- [Virtualbox](https://www.virtualbox.org/wiki/Downloads)
- [VMware](https://my.vmware.com/web/vmware/downloads/info/slug/desktop_end_user_computing/vmware_fusion/12_0)
- [QEMU](https://www.qemu.org)
- [BOCHS](https://bochs.sourceforge.io/)
- Hyper-V

### Running with VMWARE/Virtualbox

To run with this, simply insert the iso image outputted in `./out/`, and make sure to choose the `other` option.

### Running with qemu

Run with `qemu-system-x86_64 iso/MyOS.iso`.

## Source Tree
<!--
```shell
.
|-- OLDFILES
|   |-- shell.c
|   `-- shell.h
|-- boot
|   |-- boot.s
|   |-- grub.cfg
|   |-- grubconf
|   |   `-- boot
|   |       |-- MyOS.bin
|   |       `-- grub
|   |           `-- grub.cfg
|   `-- linker.ld
|-- build.sh
|-- cpu
|   `-- cpuid
|       |-- cpuid.c
|       `-- cpuid.h
|-- drivers
|   |-- acpi
|   |   |-- acpi.c
|   |   `-- acpi.h
|   |-- ata
|   |   |-- ata.c
|   |   `-- ata.h
|   |-- keyboard
|   |   |-- keyboard.c
|   |   |-- keyboard.h
|   |   `-- keycodes.h
|   |-- mouse
|   |   |-- mouse.c
|   |   `-- mouse.h
|   |-- pci
|   |   |-- pci.c
|   |   `-- pci.h
|   |-- ports
|   |   |-- ports.c
|   |   `-- ports.h
|   |-- rtc
|   |   |-- rtc.c
|   |   `-- rtc.h
|   |-- screen
|   |   |-- screen.c
|   |   `-- screen.h
|   |-- serial
|   |   |-- serial.c
|   |   `-- serial.h
|   |-- sound
|   |   `-- pcspeaker
|   |       |-- pcspeaker.c
|   |       `-- pcspeaker.h
|   `-- timer
|       |-- timer.c
|       `-- timer.h
|-- fs
|   |-- fs.c
|   |-- fs.h
|   |-- initrd
|   |   |-- initrd.c
|   |   `-- initrd.h
|   |-- tar.c
|   |-- tar.h
|   |-- vfs.c
|   `-- vfs.h
|-- gdt
|   |-- gdt.c
|   |-- gdt.h
|   `-- load_gdt.s
|-- idt
|   |-- idt.c
|   |-- idt.h
|   |-- isr.c
|   |-- isr.h
|   `-- load_idt.s
|-- include
|   |-- math
|   |   |-- math.c
|   |   `-- math.h
|   |-- printf.c
|   |-- printf.h
|   |-- stdarg.h
|   |-- types
|   |   `-- types.h
|   |-- utils.c
|   `-- utils.h
|-- isodir
|   `-- boot
|       `-- grub\r
|-- kernel
|   |-- apps
|   |   |-- apps.c
|   |   |-- apps.h
|   |   |-- calculator
|   |   |   |-- calculator.c
|   |   |   `-- calculator.h
|   |   |-- cowsay
|   |   |   |-- cowsay.c
|   |   |   `-- cowsay.h
|   |   |-- man
|   |   |   |-- man.c
|   |   |   `-- man.h
|   |   |-- serialapp
|   |   |   |-- serialapp.c
|   |   |   `-- serialapp.h
|   |   |-- slang
|   |   |   |-- slang.c
|   |   |   `-- slang.h
|   |   `-- textedit
|   |       |-- textedit.c
|   |       `-- textedit.h
|   |-- fonts
|   |   `-- font.h
|   |-- kernel.c
|   |-- multiboot.h
|   |-- panic.c
|   |-- panic.h
|   |-- pic
|   |   |-- pic.c
|   |   `-- pic.h
|   `-- shell
|       |-- lshell.c
|       `-- lshell.h
|-- out
|   `-- MyOS.iso

```
-->

```shell
.
|-- OLDFILES
|   |-- kernel.c
|   |-- shell.c
|   `-- shell.h
|-- boot
|   |-- boot.s
|   |-- grub.cfg
|   `-- linker.ld
|-- build
|-- cpu
|   `-- cpuid
|       |-- cpuid.c
|       `-- cpuid.h
|-- drivers
|   |-- acpi
|   |   |-- acpi.c
|   |   `-- acpi.h
|   |-- ata
|   |   |-- ata.c
|   |   `-- ata.h
|   |-- keyboard
|   |   |-- keyboard.c
|   |   |-- keyboard.h
|   |   `-- keycodes.h
|   |-- mouse
|   |   |-- mouse.c
|   |   `-- mouse.h
|   |-- pci
|   |   |-- pci.c
|   |   `-- pci.h
|   |-- ports
|   |   |-- ports.c
|   |   `-- ports.h
|   |-- rtc
|   |   |-- rtc.c
|   |   `-- rtc.h
|   |-- screen
|   |   |-- screen.c
|   |   `-- screen.h
|   |-- serial
|   |   |-- serial.c
|   |   `-- serial.h
|   |-- sound
|   |   `-- pcspeaker
|   |       |-- pcspeaker.c
|   |       `-- pcspeaker.h
|   `-- timer
|       |-- timer.c
|       `-- timer.h
|-- fs
|   |-- fs.c
|   |-- fs.h
|   |-- initrd
|   |   |-- initrd.c
|   |   `-- initrd.h
|   |-- tar.c
|   |-- tar.h
|   |-- vfs.c
|   `-- vfs.h
|-- gdt
|   |-- gdt.c
|   |-- gdt.h
|   `-- load_gdt.s
|-- idt
|   |-- idt.c
|   |-- idt.h
|   |-- isr.c
|   |-- isr.h
|   `-- load_idt.s
|-- include
|   |-- exit.c
|   |-- exit.h
|   |-- limits.h
|   |-- math
|   |   |-- math.c
|   |   `-- math.h
|   |-- printf.c
|   |-- printf.h
|   |-- stdarg.h
|   |-- types
|   |   `-- types.h
|   |-- utils.c
|   `-- utils.h
|-- kernel
|   |-- apps
|   |   |-- apps.c
|   |   |-- apps.h
|   |   |-- calculator
|   |   |   |-- calculator.c
|   |   |   `-- calculator.h
|   |   |-- cowsay
|   |   |   |-- cowsay.c
|   |   |   `-- cowsay.h
|   |   |-- man
|   |   |   |-- man.c
|   |   |   `-- man.h
|   |   |-- serialapp
|   |   |   |-- serialapp.c
|   |   |   `-- serialapp.h
|   |   |-- slang
|   |   |   |-- slang.c
|   |   |   `-- slang.h
|   |   |-- textedit
|   |   |   |-- textedit.c
|   |   |   `-- textedit.h
|   |   |-- xander
|   |   |   |-- xander.c
|   |   |   `-- xander.h
|   |   `-- xgui
|   |       |-- xgui.c
|   |       `-- xgui.h
|   |-- fonts
|   |   |-- ChunkyMonkey
|   |   |   |-- Atari8
|   |   |   |   `-- Chunky\ Monkey.fnt
|   |   |   |-- BBC
|   |   |   |   |-- Chunky\ Monkey.bbc
|   |   |   |   `-- Preview-DFS.ssd
|   |   |   |-- C64
|   |   |   |   |-- Chunky\ Monkey.bin
|   |   |   |   |-- Chunky\ Monkey.both.64c
|   |   |   |   `-- Chunky\ Monkey.upper.64c
|   |   |   |-- Chunky\ Monkey.png
|   |   |   |-- PC
|   |   |   |   |-- Chunky\ Monkey.bdf
|   |   |   |   |-- Chunky\ Monkey.psf
|   |   |   |   |-- Chunky\ Monkey.ttf
|   |   |   |   |-- Chunky\ Monkey.woff
|   |   |   |   |-- Chunky\ Monkey.woff2
|   |   |   |   `-- font.o
|   |   |   |-- README.md
|   |   |   `-- Spectrum
|   |   |       |-- Chunky\ Monkey.ch8
|   |   |       |-- Chunky\ Monkey.fzx
|   |   |       |-- Chunky\ Monkey.tap
|   |   |       `-- Chunky\ Monkey.z80.asm
|   |   |-- font.h
|   |   |-- fontdriver
|   |   |   |-- fontdriver.c
|   |   |   `-- fontdriver.h
|   |   `-- ibmfont.h
|   |-- kernel.c
|   |-- multiboot.h
|   |-- panic.c
|   |-- panic.h
|   |-- pic
|   |   |-- pic.c
|   |   `-- pic.h
|   `-- shell
|       |-- lshell.c
|       `-- lshell.h
|-- out
|   `-- MyOS.iso

```


## Contact Info

- Have any questions/requests/issues? Feel free to contact me at:
  [alexdev404@protonmail.com](mailto:alexdev404@protonmail.com).
  
  
## Contributing

I'm looking to extend it with additional features at this time.  So I will be accepting any pull requests
that are related to bug fixes and additional features that could be implemented.
