#define BYTES_PER_PIXEL 2
#define LINES 25
#define COLUMNS 80
#define LIGHT_GREY 0x07
#define VIDEO_MEMORY_START 0xb8000
#define BLANCK_CHAR ' '
#define SCREENSIZE BYTES_PER_PIXEL * COLUMNS * LINES


#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08


#define ENTER_KEY_CODE 0x1C

extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);



unsigned int current_cursor_location = 0;


char *vidptr = (char*)VIDEO_MEMORY_START;



struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];


void cmain(void) {

    const char *str = "Hello world from my first kernel";
	unsigned int i = 0;
	unsigned int j = 0;

    /* clear the screen */
    while(j < SCREENSIZE) {
		/* blank character */
		vidptr[j] = BLANCK_CHAR;

		/* attribute-byte - light grey on black screen */
		vidptr[j+1] = LIGHT_GREY; 		
		j += BYTES_PER_PIXEL;
	}

	j = 0;

    /* this loop writes the string to video memory */
	while(str[j] != '\0') {
		/* the actual character in ascii */
		vidptr[i] = str[j];

		/* the color of the previos char */
		vidptr[i+1] = LIGHT_GREY;
		j++;
		i += BYTES_PER_PIXEL;
	}

	return;
}