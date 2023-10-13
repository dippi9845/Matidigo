OBJECT_DIR=objects
SRC=src
EXE_DIR=exe

GCC=gcc
ASSMB=nasm
LINKER=ld

.PHONY: clean all

all : ${EXE_DIR}/kernel


${EXE_DIR}/kernel : ${OBJECT_DIR}/kc.o ${OBJECT_DIR}/kasm.o
	${LINKER} -m elf_i386 -T ${SRC}/link.ld -o ${EXE_DIR}/kernel ${OBJECT_DIR}/kc.o ${OBJECT_DIR}/kasm.o

${OBJECT_DIR}/kc.o : ${SRC}/kernel.c
	${GCC} -fno-stack-protector -m32 -c ${SRC}/kernel.c -o ${OBJECT_DIR}/kc.o

${OBJECT_DIR}/kasm.o : ${SRC}/kernel.asm
	${ASSMB} -f elf32 ${SRC}/kernel.asm -o ${OBJECT_DIR}/kasm.o

clean :
	-rm ${OBJECT_DIR}/* ${EXE_DIR}/*
