#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

#include "pq.h"
#include "node.h"
#include "code.h"
#include "stack.h"
#include "huffman.h"
#include "io.h"
#include "defines.h"

typedef struct {
	uint32_t magic;
	uint16_t permissions;
	uint16_t tree_size;
	uint64_t file_size;
} Header;

int main()
{
	//open input and output file, create histogram
	int infile = open("input.txt", O_RDONLY);
	int outfile = open("output.txt", O_WRONLY);
	uint64_t hist[256];
	for(int i = 0; i < 256; i++)
	{
		hist[i] = 0;
	}

	hist[0] += 1;
	hist[255] += 1;

	uint8_t buffer[4096];

	//loop through bytes read, and increment associated histogram position for character
	int leave_condition = 1;
	while(leave_condition)
	{
		int bytes = read_bytes(infile, buffer, 4096);
		if(bytes > 0)
		{
			for(int i = 0; i < bytes; i++)
			{
				hist[buffer[i]] += 1;
			}
		}
		else
		{
			leave_condition = 0;
		}
	}

	//build huffman tree and codes from tree
	Node *root = build_tree(hist);
	Code code_table[ALPHABET];
	build_codes(root, code_table);

	//dump tree to outfile, move infile to beginning, and write code to outfile
	dump_tree(outfile, root);

	lseek(infile, 0, SEEK_SET);

	int exit_condition = 1;
	while(exit_condition)
	{
		int bytes = read_bytes(infile, buffer, 4096);
		if(bytes > 0)
		{
			for(int i = 0; i < bytes; i++)
			{
				write_code(outfile, &(code_table[buffer[i]]));
			}
		}
		else
		{
			exit_condition = 0;
		}
	}
	flush_codes(outfile);
}
