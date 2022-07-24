#pragma once
#include <stdint.h>
#include <stdlib.h>

void Log_Info(char *fmt, ...);

void Log_Error(char *fmt, ...);

void Log_Hex(uint8_t *data, size_t size);
