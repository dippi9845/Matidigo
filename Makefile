OBJECT_DIR=objects
SRC=./
EXE_DIR=exe

GCC=gcc
ASSMB=nasm
LINKER=ld

${EXE_DIR}/kernel : ${OBJECT_DIR}/kc.o ${OBJECT_DIR}/kasm.o
	${LINKER} -m elf_i386 -T link.ld -o ${EXE_DIR}/kernel ${OBJECT_DIR}/kc.o ${OBJECT_DIR}/kasm.o

${OBJECT_DIR}/kc.o : kernel.c
	${GCC} -fno-stack-protector -m32 -c kernel.c -o ${OBJECT_DIR}/kc.o

${OBJECT_DIR}/kasm.o : kernel.asm
	${ASSMB} -f elf32 kernel.asm -o ${OBJECT_DIR}/kasm.o

clean :
	rm ${OBJECT_DIR}/* ${EXE_DIR}/*

.PHONY: clean