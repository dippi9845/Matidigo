#define BYTES_PER_PIXEL 2
#define LINES 25
#define COLUMNS 80
#define LIGHT_GREY 0x07
#define VIDEO_MEMORY_START 0xb8000
#define BLANCK_CHAR ' '

void cmain(void) {

    const char *str = "Hello world from my first kernel";
	char *vidptr = (char*)VIDEO_MEMORY_START;
	unsigned int i = 0;
	unsigned int j = 0;

    /* clear the screen */
    while(j < COLUMNS * LINES * BYTES_PER_PIXEL) {
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