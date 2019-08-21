#ifndef STR_MAX_LEN
#define STR_MAX_LEN 255
#endif

struct Yogurt {
  char name[STR_MAX_LEN];
  char topping[STR_MAX_LEN];
  unsigned int size;
  unsigned int price;
};