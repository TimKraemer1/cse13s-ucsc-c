#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code.h"
#include "defines.h"

Code code_init(void)
{
	Code c;
	c.top = 0;
	for(uint32_t i = 0; i < MAX_CODE_SIZE; i++)
	{
		c.bits[i] = 0;
	}
	return c;
}

uint32_t code_size(Code *c)
{
	return c->top;
}

bool code_empty(Code *c)
{
	if(c->top == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool code_full(Code *c)
{
	if(c->top > ALPHABET)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool code_set_bit(Code *c, uint32_t i)
{
	if(i < 0 || i > MAX_CODE_SIZE * 8)
	{
		return false;
	}
	uint8_t curr_byte = c->bits[i/8];
	curr_byte |= (1 << (i % 8));
	c->bits[i/8] = curr_byte;
	return true;
}

bool code_clr_bit(Code *c, uint32_t i)
{
	if(i < 0 || i > MAX_CODE_SIZE * 8)
	{
		return false;
	}
	uint8_t curr_byte = c->bits[i/8];
	curr_byte &= ~(1 << (i % 8));
	c->bits[i/8] = curr_byte;
	return true;
}

bool code_get_bit(Code *c, uint32_t i)
{
	if(i < 0 || i > MAX_CODE_SIZE * 8)
	{
		return false;
	}
	uint8_t curr_byte = c->bits[i/8];
	if(curr_byte & (1 << (i % 8)))
	{
		return true;
	}
	else
	{
		return false; 
	}
}

bool code_push_bit(Code *c, uint8_t bit)
{
	if(code_full(c))
	{
		return false;
	}

	if(bit == 0)
	{
		c->top += 1;
		return true;
	}
	else if(bit == 1)
	{
		code_set_bit(c, c->top);
		c->top += 1;
		return true;
	}
	else
	{
		return false;
	}
}

bool code_pop_bit(Code *c, uint8_t *bit)
{
	if(code_empty(c))
	{
		return false;
	}

	if(code_get_bit(c, c->top - 1))
	{
		*bit = 1; 
		c->top -= 1;
		code_clr_bit(c, c->top);
		return true;
	}
	//negate the code_get_bit since if the bit you pop is a zero, then code_get_bit of top - one should return false, but we want it to be true for the else if to work
	else if(!(code_get_bit(c, c->top - 1)))
	{
		*bit = 0;
		c->top -= 1;
		return true;
	}
	else
	{
		return false;
	}
}

void code_print(Code *c)
{
	for (uint32_t i = 0; i < code_size(c); i++)
	{
		if (code_get_bit(c, i))
		{
			printf("%d", 1);
		}
		else
		{
			printf("%d", 0);
		}
	}
}
