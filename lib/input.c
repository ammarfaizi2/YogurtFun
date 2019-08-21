#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "input.h"

#ifndef BUFFER
#define BUFFER 1024 
#endif

#ifndef STR_MAX_LEN
#define STR_MAX_LEN 255
#endif

int ys_input_get_number(char *message, int min, int max) {
	char buffer[BUFFER];
	bool is_input_valid;
	int input;
	
	do {
		printf("%s", message);
		
		if (!fgets(buffer, BUFFER, stdin)) {
			return -1;
		}
		
		char *endptr;
		
		errno = 0;
		input = strtol(buffer, &endptr, 10);
		if (errno == ERANGE) {
			is_input_valid = false;
		} else if (endptr == buffer) {
			is_input_valid = false;
		} else if (*endptr && *endptr != '\n') {
			is_input_valid = false;
		} else {
			if (input >= min && input <= max) {
				is_input_valid = true;
			} else {
				is_input_valid = false;
			}
		}
	} while (!is_input_valid);
	
	return input;
}

char *ys_input_get_string(char *message) {
	char input[STR_MAX_LEN];
	bool is_input_valid;
	
	do {
		printf("%s", message);
		
		if (fgets(input, STR_MAX_LEN, stdin)) {
			input[strcspn(input, "\n")] = 0;
			is_input_valid = true;
		} else {
			is_input_valid = false;
		}
		
	} while (!is_input_valid);
	
	char *result = malloc(sizeof(*result) * STR_MAX_LEN + 1);
	strcpy(result, input);
	
	return result;
}
