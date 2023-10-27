#define BYTES_PER_PIXEL 2
#define LINES 25
#define COLUMNS 80
#define LIGHT_GREY 0x07
#define VIDEO_MEMORY_START 0xb8000
#define BLANCK_CHAR ' '
#define SCREENSIZE BYTES_PER_PIXEL * COLUMNS * LINES


unsigned int current_cursor_location = 0;


char *vidptr = (char*)VIDEO_MEMORY_START;

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void CallConstructors() {
	for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


void kprint(const char *str)
{
	unsigned int i = 0;
	while (str[i] != '\0') {
		vidptr[current_cursor_location++] = str[i++];
		vidptr[current_cursor_location++] = 0x07;
	}
}

void kprint_newline(void)
{
	unsigned int line_size = BYTES_PER_PIXEL * COLUMNS;
	current_cursor_location = current_cursor_location + (line_size - current_cursor_location % (line_size));
}

void clear_screen(void)
{
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
}

void CMain(void) {
	const char *str = "my first kernel with keyboard support";
	clear_screen();
	kprint(str);
	kprint_newline();
	kprint_newline();
}