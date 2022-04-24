# [Upgraded] From Multiboot1 to fit Multiboot2 Specifications
# Relevant multiboot2 documentation:
# https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html

# Multiboot tags
.set TAG_END,          0
.set TAG_FRAMEBUFFER,  5

# Multiboot flags
.set TAG_REQUIRED,     0
.set TAG_OPTIONAL,     1

# Multiboot2 header constants
.set MAGIC,            0xE85250D6
.set ARCH,             0
.set HEADER_LEN,       (multiboot_end - multiboot_start)
.set CHECKSUM,         -(MAGIC + ARCH + HEADER_LEN)


# Multiboot header
.section .multiboot
multiboot_start:
    # Magic
    .align 8
    .long MAGIC
    .long ARCH
    .long HEADER_LEN
    .long CHECKSUM

    # Graphics tag (Removing this section disables graphics mode)
     .align 8
     .short TAG_FRAMEBUFFER
     .short TAG_REQUIRED # 0 for linear, 1 for textmode
     .long 20
    # Resolution (run "videoinfo" in Linux to get a list of available resolutions)
    # Run the OS at 480p
     .long 640 # width
     .long 480 # Height
     .long 32 # Depth(BPP)

    # End tag
    .align 8
    .short TAG_END
    .short TAG_REQUIRED
    .long 8
multiboot_end:

# Reserve a stack for the initial thread.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
    .skip 16384 # 16 KiB
stack_top:

.section .data

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:

    # We are now in 32-bit protected mode.
    # Transfer control to the main kernel.
    # Pass the multiboot header adress and magic number,
    # See https://www.gnu.org/software/grub/manual/multiboot/html_node/Machine-state.html
    pushl %eax
    pushl %ebx

    cli # disable until we setup handlers
    call kmain
    add $12, %esp # cleanup the stack. useless here

    # Hang if kernel_main unexpectedly returns.
    cli
.hang:
    hlt
    jmp .hang
