# NextOS - a simple x86 operating system

NextOS is an attempt to write a simple operating system for computers running
on x86 (and compatible) processors. It's currently in experimental state and
still misses a lot of crucial functionality. Contributions are welcome.

## The current state

That's just a list of stuff that currently works or seems to work:

- booting from a CD or a USB stick using the GRUB bootloader
- switching between common A modes
- running minimal C programs
- printing some text on the screen
  
![img_1045](https://github.com/tzuntar/next-os/assets/35228139/e545d0f4-e68e-4282-8a0d-1ab37844dd1d)

## What has to be done

Well, there's a lot to be done but a few currently important things are:

- set up a proper interrupt support (eg. one that is usable by more than one part of the code)
- actual text scrolling instead of rewriting it when the screen is full
- basic command-line UI
- port of the base C library
- filesystem support

## Compiling

Use the supplied Makefile to compile the OS and pack it into an ISO:

```bash
make
```

You can then use that ISO in VirtualBox or burn it to a CD-ROM. To clean the up
the current working tree just run

```bash
make clean
```
