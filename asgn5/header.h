#pragma once

#include <stdint.h>

typedef struct {
	uint32_t magic;
	uint16_t permissions;
	uint16_t tree_size;
	uint16_t file_size;
} Header;
