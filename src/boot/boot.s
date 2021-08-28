.set MAGIC,    0x1BADB002
.set FLAGS,	0
.set CHECKSUM, -(MAGIC + FLAGS)
.section .multiboot

# define type to long for each data defined as above
.long MAGIC
.long FLAGS
.long CHECKSUM

# set the stack bottom 
stackBottom:

# define the maximum size of stack to 512 bytes
.skip 1024


# set the stack top which grows from higher to lower
stackTop:

.section .text
.global _start
.type _start, @function


_start:

  # assign current stack pointer location to stackTop
	mov $stackTop, %esp

  # call the kernel main source
	call kernel_entry

	cli


# put system in infinite loop
hltLoop:

	hlt
	jmp hltLoop

.size _start, . - _start

.global _timestamp_edx
.global _timestamp_eax

_timestamp_edx: 
    rdtsc
    movl %edx,%eax
    ret

_timestamp_eax: 
    rdtsc
    ret

