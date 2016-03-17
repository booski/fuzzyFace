#pragma once
#include "string.h"
#include <stdbool.h>

bool build_time_string(int h, int m, int s, char* buffer, size_t length);
void build_date_string(int month, int day, int weekday, char* buffer, size_t length);