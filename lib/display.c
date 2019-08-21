#include <stdio.h>
#include <stdlib.h>

#ifndef STR_MAX_LEN
#define STR_MAX_LEN 255
#endif

#ifndef NUMBER_OF_MENU
#define NUMBER_OF_MENU 4
#endif

void ys_display_banner() {
  printf("Yogurt Shop\n");
	printf("================\n");
}

void ys_display_menu() {
  ys_display_banner();
	
	char menu[NUMBER_OF_MENU][STR_MAX_LEN] = {
		"Buy Yogurt", 
		"View History", 
		"Delete History", 
		"Exit"
	};
	
	int i;
	for (i = 0; i < NUMBER_OF_MENU; i++) {
		printf("%d. %s\n", i + 1, menu[i]);
	}
}

void ys_display_clear_screen() {
  system("cls||clear");
}