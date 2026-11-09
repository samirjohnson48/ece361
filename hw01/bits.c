#include <stdbool.h>
#include "bits.h"

static const int MIN_WIDTH = 1;
static const int MAX_WIDTH = 32;
static const int MIN_POS = 0;
static const int MAX_POS = 31;

int main(void) {
  uint32_t x;
  int width;

  for (;;) {
    printf("Enter x: ");
    scanf("%d", &x);

    if (x == 0) { return 0; }

    printf("Enter width: ");
    scanf("%d", &width);

    print_binary(x, width);
  }
}

static bool check_bounds(int value, int min, int max) {
  if (value < min || value > max) { return false; }
  return true;
}

void print_binary(uint32_t x, int width) {
  const int spacing = 4;

  if (!check_bounds(width, MIN_WIDTH, MAX_WIDTH)) {
    printf("Must specify width within range: [%d, %d]. Provided: %d\n", MIN_WIDTH, MAX_WIDTH, width);
    return;
  }  

  int bit;
  for (int i = width - 1; i >= 0; i--){
    bit = (x >> i) & 1;
    printf("%c", '0' + bit);

    if (i > 0 && i % spacing == 0) { printf(" "); }
  }

  printf("\n");
}
