# Matidigo
A base kernel that prints a simple string at screen

Create object from the kernel.asm
```bash
nasm -f elf32 kernel.asm -o kasm.o
```

Create the object from the kernel.c
```bash
gcc -m32 -c kernel.c -o kc.o
```

Link the two objects files
```bash
ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
```
