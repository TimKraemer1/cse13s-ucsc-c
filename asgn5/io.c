#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#include "io.h"
#include "code.h"
#include "defines.h"

//read bytes from input file until no more bytes can be read, circumnavigates issues with read() function
int read_bytes(int infile, uint8_t *buf, int nbytes) {
	int bytes = 0, bytes_read = 0;

	do {
		bytes = read(infile, buf + bytes_read, nbytes - bytes_read);
		bytes_read += bytes;
	} while (bytes > 0);

	return bytes_read;
}

//same as read_bytes, but instead writes to output file
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
	int bytes = 0;
	int bytes_write = 0;

	do {
		bytes = write(outfile, buf + bytes_write, nbytes - bytes_write);
		bytes_write += bytes;
	} while (bytes > 0);

	return bytes_write;
}

static uint32_t top = BLOCK;
uint8_t buffer[BLOCK];
uint32_t read_num_bytes = 0;
int bit_tracker = 0;

//read in a block of bytes, and then read a bit one at a time
bool read_bit(int infile, uint8_t *bit)
{
	if(top == BLOCK)
	{
		read_num_bytes = read_bytes(infile, buffer, BLOCK);
		top = 0;
	}
	if(top < read_num_bytes)
	{
		uint8_t *byte = &buffer[top];
		*bit = (*byte & (128 >> (bit_tracker % 8))) >> (7 - (bit_tracker % 8));
		bit_tracker += 1;
		if(bit_tracker == 8)
		{
			top++;
			bit_tracker = 0;
		}
		return true;
	}
	else
	{
		return false;
	}
}

static uint8_t write_buffer[BLOCK];
static uint32_t index = 0;

//write codes to outfile bit by bit
void write_code(int outfile, Code *c)
{
	bool exit_condition = 0;
	while(!exit_condition)
	{
		uint32_t code_to_be_written = code_size(c);
		while(index < (BLOCK * 8) && index < code_to_be_written)
		{
			if(code_get_bit(c, index))
			{
				write_buffer[index/8] |= (1 << (7 - (index % 8)));
			}
			index ++;
		}
		code_to_be_written -= index;
		if(index < BLOCK * 8)
		{
			exit_condition = 1;
		}
		else
		{
			write_bytes(outfile, write_buffer, BLOCK);
			index = 0;
		}
	}
}

//flush the codes to the outfile
void flush_codes(int outfile)
{
	if(index < BLOCK * 8)
	{
		write_bytes(outfile, write_buffer, (index / 8) + 1);
	}
}
