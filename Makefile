OBJECT_DIR=objects
SRC=src
EXE_DIR=exe

# Remove starndard library functions
# -fno-use-cxa-atexit
#	This flag disables the use of __cxa_atexit from the C++ ABI runtime. This function is used to register exit functions for global objects in C++.
#	Disabling it is useful when developing a program without support for global objects with constructors or destructors in C++.

# -nostdlib
#	This flag tells the compiler not to use the C standard library during linking.
#	This is useful when writing embedded programs or a kernel for the operating system,
#	where you often need more fine-grained control over the libraries used.

# -fno-builtin
#	This flag disables the use of compiler-built-in functions.
#	Built-in functions are compiler optimizations applied automatically.
#	Disabling this option prevents the compiler from applying these automatic optimizations.

# -fno-exceptions
#	This flag disables C++ exception support. 
#	Exceptions are error-handling mechanisms in C++.
#	Disabling this option removes support for exceptions,
#	which can be useful in embedded systems or when you want to reduce code complexity and size.
CPP_NO_DEFAULT=-fno-builtin -nostdlib -fno-use-cxa-atexit -fno-exceptions

# -m32
# 	This flag specifies the target processor architecture as 32-bit.
#	It instructs the compiler to generate code intended for a 32-bit architecture.
#	It's useful when you want to compile a program to run on 32-bit systems.

# -fno-rtti
#	This flag disables Run-Time Type Information (RTTI) support in C++.
#	RTTI is used to obtain type information during program execution.
#	Turning it off reduces the generated code size and can be useful in embedded systems or where RTTI is not needed.

# -fno-leading-underscore
#	This flag specifies that function names should not start with an underscore character.
#	On some architectures, the compiler may add a prefix or underscore to function names.
#	This flag prevents the addition of such a prefix.
CPP_FLAGS=-m32 -fno-rtti -fno-leading-underscore

GCC=gcc ${CPP_FLAGS} ${CPP_NO_DEFAULT}

# Specify the output format as 32-bit ELF
ASS_FLAGS=-f elf32

ASSMB=nasm ${ASS_FLAGS}

# Specify the ELF 386 output
LINK_FLAGS=-m elf_i386
LINK_FILE=-T ${SRC}/link.ld

LINKER=ld ${LINK_FLAGS}

CKERNEL_OBJ=${OBJECT_DIR}/kc.o
AKERNEL_OBJ=${OBJECT_DIR}/kasm.o

.PHONY: clean all

all : ${EXE_DIR}/kernel


${EXE_DIR}/kernel : ${CKERNEL_OBJ} ${AKERNEL_OBJ}
	${LINKER} ${LINK_FILE} -o ${EXE_DIR}/kernel ${CKERNEL_OBJ} ${AKERNEL_OBJ}

${CKERNEL_OBJ} : ${SRC}/kernel.c
	${GCC} -c ${SRC}/kernel.c -o ${CKERNEL_OBJ}

${AKERNEL_OBJ} : ${SRC}/kernel.asm
	${ASSMB} ${SRC}/kernel.asm -o ${AKERNEL_OBJ}

clean :
	-rm ${OBJECT_DIR}/* ${EXE_DIR}/*
