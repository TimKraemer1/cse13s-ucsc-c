#include <stdio.h> 
#include <stdlib.h>

#include "huffman.h"
#include "pq.h"
#include "node.h"
#include "code.h"
#include "io.h"
#include "stack.h"

void build(Code c, Node *root, Code table[static ALPHABET])
{
        if(root)
        {
                if(root->left == NULL && root->right == NULL)
                {
                        table[root->symbol] = c;
                }
                else
                {
                        code_push_bit(&c, 0);
                        build(c, root->left, table);
                        uint8_t popped_bit = 0;
                        code_pop_bit(&c, &popped_bit);

                        code_push_bit(&c, 1);
                        build(c, root->right, table);
                        code_pop_bit(&c, &popped_bit);
                }
        }
}

Node *build_tree(uint64_t hist[static ALPHABET])
{
	PriorityQueue *tree_queue = pq_create(256);
	for(uint32_t i = 0; i < 256; i ++)
	{
		if(hist[i] != 0)
		{
			Node *tree_node = node_create(i, hist[i]);
			enqueue(tree_queue, tree_node);
		}
	}
	while(pq_size(tree_queue) > 1)
	{
		Node *left = NULL;
		Node *right = NULL;
		dequeue(tree_queue, &left);
		dequeue(tree_queue, &right);
		Node *parent = node_join(left, right);
		enqueue(tree_queue, parent);
	}
	Node *root = NULL;
	dequeue(tree_queue, &root);
	pq_delete(&tree_queue);
	return root;
}


void build_codes(Node *root, Code table[static ALPHABET])
{
	Code c;
	c = code_init();
	build(c, root, table);
}
void dump_tree(int outfile, Node *root)
{
	uint8_t byteL = 76;
	uint8_t byteI = 73;
	if(root)
	{
		dump_tree(outfile, root->left);
		dump_tree(outfile, root->right);

		if(!(root->left) && !(root->right))
		//leaf node
		{
			write_bytes(outfile, &byteL, 1);
			write_bytes(outfile, &(root->symbol), 1);
		}
		else
		//interior node
		{
			write_bytes(outfile, &byteI, 1);
		}
	}
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes])
{
	Stack *tree_stack;
	tree_stack = stack_create(nbytes);
	uint32_t i = 0;
	while(i < nbytes)
	{
		if(tree_dump[i] == 76)
		{
			Node *leaf;
			leaf = node_create(tree_dump[i + 1], 0);
			stack_push(tree_stack, leaf);
			i += 2;
		}
		else if(tree_dump[i] == 73)
		{
			Node *right = NULL;
			Node *left = NULL;
			stack_pop(tree_stack, &right);
			stack_pop(tree_stack, &left);
			Node *parent = node_join(left, right);
			stack_push(tree_stack, parent);
			i += 1;
		}
	}
	Node *root = NULL;
	stack_pop(tree_stack, &root);
	return root;

}

void delete_tree(Node **root)
{
	if(*root)
	{
		delete_tree(&((*root)->left));
		delete_tree(&((*root)->right));
		
		node_delete(root);
	}
}
