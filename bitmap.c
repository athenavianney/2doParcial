#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define CABEZERA_INCORRECTA 1

typedef struct fileheader {
	uint16_t type;
	uint32_t size;
	unsigned short int reserved1, reserved2;
	unsigned int offset;
} FileHeader;

typedef struct bmp {
	FileHeader fileHeader;
	unsigned int size;
	int width, height;
	unsigned short int planes;
	unsigned short int bits;
	unsigned int compression;
	unsigned int imagesize;
	int xresolution, yresolution;
	unsigned int ncolours;
	unsigned int importantcolours;

	void* memory;
} BMP;

typedef struct Color {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} Color;

FileHeader readFileHeader(FILE* source) {
	FileHeader header;

	fread(&header.type, sizeof(header.type), 1, source);
	fread(&header.size, sizeof(header.size), 1, source);
	fread(&header.reserved1, sizeof(header.reserved1), 1, source);
	fread(&header.reserved2, sizeof(header.reserved2), 1, source);
	fread(&header.offset, sizeof(header.offset), 1, source);

	return header;
}

void writeFileHeader(FileHeader header, FILE* dest) {
	fwrite(&header.type, sizeof(header.type), 1, dest);
	fwrite(&header.size, sizeof(header.size), 1, dest);
	fwrite(&header.reserved1, sizeof(header.reserved1), 1, dest);
	fwrite(&header.reserved2, sizeof(header.reserved2), 1, dest);
	fwrite(&header.offset, sizeof(header.offset), 1, dest);
}

BMP readBMP(FILE* source, int* error) {
	BMP bmp;
	bmp.fileHeader = readFileHeader(source);

	if (bmp.fileHeader.type != 0x4d42) {
		*error = CABEZERA_INCORRECTA;
		return bmp;
	}

	fread(&bmp.size, sizeof(bmp.size), 1, source);
	fread(&bmp.width, sizeof(bmp.width), 1, source);
	fread(&bmp.height, sizeof(bmp.height), 1, source);
	fread(&bmp.planes, sizeof(bmp.planes), 1, source);
	fread(&bmp.bits, sizeof(bmp.bits), 1, source);
	fread(&bmp.compression, sizeof(bmp.compression), 1, source);
	fread(&bmp.imagesize, sizeof(bmp.imagesize), 1, source);
	fread(&bmp.xresolution, sizeof(bmp.xresolution), 1, source);
	fread(&bmp.yresolution, sizeof(bmp.yresolution), 1, source);
	fread(&bmp.ncolours, sizeof(bmp.ncolours), 1, source);
	fread(&bmp.importantcolours, sizeof(bmp.importantcolours), 1, source);

	bmp.memory = malloc(bmp.imagesize);
	fread(bmp.memory, 1, bmp.imagesize, source);

	return bmp;
}

void writeBMP(BMP bmp, FILE* dest) {
	writeFileHeader(bmp.fileHeader, dest);

	fwrite(&bmp.size, sizeof(bmp.size), 1, dest);
	fwrite(&bmp.width, sizeof(bmp.width), 1, dest);
	fwrite(&bmp.height, sizeof(bmp.height), 1, dest);
	fwrite(&bmp.planes, sizeof(bmp.planes), 1, dest);
	fwrite(&bmp.bits, sizeof(bmp.bits), 1, dest);
	fwrite(&bmp.compression, sizeof(bmp.compression), 1, dest);
	fwrite(&bmp.imagesize, sizeof(bmp.imagesize), 1, dest);
	fwrite(&bmp.xresolution, sizeof(bmp.xresolution), 1, dest);
	fwrite(&bmp.yresolution, sizeof(bmp.yresolution), 1, dest);
	fwrite(&bmp.ncolours, sizeof(bmp.ncolours), 1, dest);
	fwrite(&bmp.importantcolours, sizeof(bmp.importantcolours), 1, dest);

	fwrite(bmp.memory, 1, bmp.imagesize, dest);
}

void freeBMP(BMP* bmp) {
	free(bmp->memory);
}

void flipBMP(BMP* bmp) {
	Color *start, *end, temp;
	char *row;
	int height, width;
	int y, rowsize;

	width = bmp->width;
	height = bmp->height;
	rowsize = ((bmp->bits * bmp->width + 31) / 32) * 4;

	row = (char *)(bmp->memory);
	for (y = 0; y < height; ++y) {
		start = (Color *)row;
		end = start + width - 1;
		while (start < end) {
			temp = *start;
			*(start++) = *end;
			*(end--) = temp;
		}
		row += rowsize;
	}

}

void greyscaleBMP(BMP* bmp) {
	Color *p;
	char *r;
	int width, height;
	int y, x;
	int grey, rowsize;

	height = bmp->height;
	width = bmp->width;

	r = (char *)bmp->memory;
	rowsize = ((bmp->bits * bmp->width + 31) / 32) * 4;

	for (y = 0; y < height; ++y) {
		p = (Color *)r;
		for (x = 0; x < width; ++x, ++p) {
            grey = (p->red + p->green + p->blue) / 3;
            p->red = grey;
            p->green = grey;
            p->blue = grey;
		}
		r += rowsize;
	}
}

void tintBMP(BMP* bmp, Color tint) {
	Color *p;
	int padding, width, height, x, y;

	height = bmp->height;
	width = bmp->width;

	padding = width  % 4;

	p = bmp->memory;
	for(y = 0; y < height; ++y) {
		for(x = 0; x < width; ++x, ++p) {
			p->red = (p->red + tint.red) / 2;
			p->blue = (p->blue + tint.blue) / 2;
			p->green = (p->green + tint.green) / 2;
		}
		p = (Color *)((char *)p + padding);
	}


}

int main() {
	FILE *input, *output;
	BMP bmp;
	int error;
	Color blue = {255, 0, 0};
	char nombre[50];
	scanf("%s",nombre);
	strcat(nombre,".bmp");
	printf("%s",nombre);
	input = fopen(nombre, "rb");
	error = 0;
	bmp = readBMP(input, &error);

	if (!error) {
		output = fopen("salida.bmp", "wb");

		flipBMP(&bmp);
		//greyscaleBMP(&bmp);
		tintBMP(&bmp, blue);

		writeBMP(bmp, output);
		freeBMP(&bmp);
		fclose(output);
	}
	else {
		puts("error al leer archivo");
	}

	fclose(input);
}
