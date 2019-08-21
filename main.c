#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lib/data.h"
#include "lib/display.h"
#include "lib/actions.h"
#include "lib/input.h"
#include "lib/lang_en.h"

#define YGSIZE (sizeof(struct Yogurt))
#ifndef STR_MAX_LEN
#define STR_MAX_LEN 255
#endif

/*
* Status: Work in progress, not finished yet
*/

bool do_action(struct Yogurt **yogurts, unsigned int *yogurt_size, unsigned int action);

int main() {
  unsigned int action, yogurt_size = 0;
  struct Yogurt *yogurts = malloc(YGSIZE);

  while (true) {
    ys_display_menu();

    action = ys_input_get_number(INPUT_ACTION_MESSAGE, 1, 4);

    if (do_action(&yogurts, &yogurt_size, action)) {
      getchar();
      ys_display_clear_screen();
      continue;
    } else {
      break;
    }
  }

  return 0;
}

bool do_action(struct Yogurt **yogurts, unsigned int *yogurt_size, unsigned int action) {
  char message[STR_MAX_LEN], *confirmation;
  char valid_yogurts[3][STR_MAX_LEN] = { "chocolate", "vanilla", "strawberry" };
  char valid_toppings[4][STR_MAX_LEN] = { "kitkat", "jelly", "kiwi", "mango" };
  struct Yogurt new_yogurt;
  bool is_valid = false;
  unsigned int i;
  void *temp;

  switch (action) {
    case ACTION_BUY_YOGURT:
      sprintf(message, "%s", INPUT_YOGURT_MESSAGE);
      while (!is_valid) {
        strcpy(new_yogurt.name, ys_input_get_string(message));
        for (i = 0; i < 3; i++) {
          if (strcmp(new_yogurt.name, valid_yogurts[i]) == 0) {
            is_valid = true;
          }
        }
      }
      is_valid = false; // reset

      sprintf(message, "%s", INPUT_YOGURT_TOPPING_MESSAGE);
      while (!is_valid) {
        strcpy(new_yogurt.topping, ys_input_get_string(message));
        for (i = 0; i < 4; i++) {
          if (strcmp(new_yogurt.topping, valid_toppings[i]) == 0) {
            is_valid = true;
          }
        }
      }
      is_valid = false; // reset

      sprintf(message, "%s", INPUT_YOGURT_TOPPING_SIZE_MESSAGE);
      new_yogurt.size = ys_input_get_number(message, 100, 500);
      new_yogurt.price = new_yogurt.size * strlen(new_yogurt.name) * strlen(new_yogurt.topping) * 10;

      printf("%s\n", DETAIL_PURCHASE_MESSAGE);
      printf("%-16s : %s\n", YOGURT_NAME_MESSAGE, new_yogurt.name);
      printf("%-16s : %s\n", YOGURT_TOPPING_NAME_MESSAGE, new_yogurt.topping);
      printf("%-16s : %d\n", YOGURT_TOPPING_SIZE_MESSAGE, new_yogurt.size);
      printf("%-16s : %d\n", YOGURT_PRICE_MESSAGE, new_yogurt.price);

      while (!is_valid) {
        confirmation = ys_input_get_string(INPUT_PURCHASE_CONFIRMATION);
        if (strcmp(confirmation, "y") == 0 || strcmp(confirmation, "Y") == 0) {
          is_valid = true;

          memcpy(&((*yogurts)[*yogurt_size]), &new_yogurt, YGSIZE);
          (*yogurt_size) += 1;
          temp = realloc(*yogurts, YGSIZE * ((*yogurt_size) + 1));

          if (temp == NULL) {
            printf("Cannot allocate more memory.");
            return false;
          } else {
            (*yogurts) = temp;
          }

        } else if (strcmp(confirmation, "n") == 0 || strcmp(confirmation, "N") == 0) {
          is_valid = true;
        }
      }
      is_valid = false;

      printf("%s . . .\n", DATA_ADDED_MESSAGE);

      return true;
      break;
    case ACTION_VIEW_HISTORY:
      ys_display_clear_screen();
      printf("%-4s | %-16s | %-16s | %-16s | %-16s |\n", "No.", "Name", "Topping", "Size", "Price ");
      for (i = 0; i < *yogurt_size; i++) {
        printf("%-4d | %-16s | %-16s | %-16d | %-16d |\n", i + 1, (*yogurts)[i].name, (*yogurts)[i].topping, (*yogurts)[i].size, (*yogurts)[i].price);
      }
      printf("Press any key to continue . . .\n");

      return true;
      break;
    case ACTION_DELETE_HISTORY:
      ys_display_clear_screen();
      printf("%-4s | %-16s | %-16s | %-16s | %-16s |\n", "No.", "Name", "Topping", "Size", "Price ");
      for (i = 0; i < *yogurt_size; i++) {
        printf("%-4d | %-16s | %-16s | %-16d | %-16d |\n", i + 1, (*yogurts)[i].name, (*yogurts)[i].topping, (*yogurts)[i].size, (*yogurts)[i].price);
      }
      printf("Press any key to continue . . .\n");

      return true;
      break;
    case ACTION_EXIT:
      return false;
      break;
    default:
      return false;
      break;
  }
}