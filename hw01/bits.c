#include <stdbool.h>
#include "bits.h"

static const int MIN_WIDTH = 1;
static const int MAX_WIDTH = 32;
static const int MIN_POS   = 0;
static const int MAX_POS   = 31;
static const int SPACING   = 4;

int main(void) {
  uint32_t x, field;
  int width, pos, field_width;

  for (;;) {
    printf("Enter x: ");
    scanf("%d", &x);

    if (x == 0) { return 0; }

    printf("Enter width: ");
    scanf("%d", &width);

    print_binary(x, width);

    printf("Enter pos: ");
    scanf("%d", &pos);
    printf("Enter width: ");
    scanf("%d", &field_width);

    field = get_field(x, pos, field_width);
    print_binary(field, width);
  }
}

static bool check_bounds(int value, int min, int max) {
  if (value < min || value > max) { return false; }
  return true;
}

static void log_failed_bounds(int value, int min, int max, char *name) {
  printf("Must specify %s with range: [%d, %d]. Provided: %d\n", name, min, max, value);
}

void print_binary(uint32_t x, int width) {
  if (!check_bounds(width, MIN_WIDTH, MAX_WIDTH)) {
    log_failed_bounds(width, MIN_WIDTH, MAX_WIDTH, "width");
    return;
  }  

  int bit;
  for (int i = width - 1; i >= 0; i--){
    bit = (x >> i) & 1;
    printf("%c", '0' + bit);

    if (i > 0 && i % SPACING == 0) { printf(" "); }
  }

  printf("\n");
}

uint32_t get_field(uint32_t word, int pos, int width) {
  if (!check_bounds(pos, MIN_POS, MAX_POS)) {
    log_failed_bounds(pos, MIN_POS, MAX_POS, "pos");
    return word;
  }
  else if (!check_bounds(width, MIN_WIDTH, MAX_WIDTH)) {
    log_failed_bounds(width, MIN_WIDTH, MAX_WIDTH, "width");
    return word;
  }
  else if (!check_bounds(pos + width, MIN_POS, MAX_WIDTH)) {
    log_failed_bounds(pos + width, MIN_POS, MAX_WIDTH, "pos + width");
    return word;
  }

  return word << (MAX_POS + 1 - width - pos) >> (MAX_POS - width + 1);
}
