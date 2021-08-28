# SquirrelOS
A simple DOS like OS made in Assembly and C with a ported version of Stephen Brennan's [LSH](https://github.com/brenns10/lsh) Shell.

## Build
CD into `src/` and run `sudo ../build.sh`. 

## Run
To run the OS, you can download VM software.
The iso Image is in the `iso` folder.

### Recommended:
- [Virtualbox](https://www.virtualbox.org/wiki/Downloads)
- [VMware](https://my.vmware.com/web/vmware/downloads/info/slug/desktop_end_user_computing/vmware_fusion/12_0)
- [QEMU](https://www.qemu.org)
- Hyper-V

### Running with VMWARE/Virtualbox
To run with this, simply insert the iso image outputted in `src/out/`, and make sure to choose the `other` option.

### Running with qemu
Run with `qemu-system-x86_64 iso/MyOS.iso`.

## Source
The source is in the `src/` Directory

