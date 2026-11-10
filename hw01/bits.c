#include <stdbool.h>
#include "bits.h"

static const int MIN_WIDTH = 1;
static const int MAX_WIDTH = 32;
static const int MIN_POS   = 0;
static const int MAX_POS   = 31;
static const int SPACING   = 4;

int main(void) {
  uint32_t x;
  int32_t x_ext;
  int display_width, set_width;

  for (;;) {
    printf("Enter x: ");
    scanf("%d", &x);

    if (x == 0) { return 0; }

    printf("Enter display width: ");
    scanf("%d", &display_width);

    print_binary(x, display_width);

    printf("Enter set width: ");
    scanf("%d", &set_width);

    x_ext = sign_extend(x, set_width);

    print_binary(x_ext, display_width);
    printf("Sign extended: %d\n", x_ext);
  }
}

static bool check_bounds(int value, int min, int max) {
  if (value < min || value > max) { return false; }
  return true;
}

static void log_failed_bounds(int value, int min, int max, char *name) {
  printf("Must specify '%s' with range: [%d, %d]. Provided: %d\n", name, min, max, value);
}

static bool check_all_bounds(int pos, int width) {
  if (!check_bounds(pos, MIN_POS, MAX_POS)) {
    log_failed_bounds(pos, MIN_POS, MAX_POS, "pos");
    return false;
  }
  else if (!check_bounds(width, MIN_WIDTH, MAX_WIDTH)) {
    log_failed_bounds(width, MIN_WIDTH, MAX_WIDTH, "width");
    return false;
  }
  else if (!check_bounds(pos + width, MIN_POS, MAX_WIDTH)) {
    log_failed_bounds(pos + width, MIN_POS, MAX_WIDTH, "pos + width");
    return false;
  }

  return true;
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
  if (!check_all_bounds(pos, width)) {
    return word;
  }

  return word << (MAX_POS + 1 - width - pos) >> (MAX_POS - width + 1);
}

uint32_t set_field(uint32_t word, int pos, int width, uint32_t value) {
  if (!check_all_bounds(pos, width)) {
    return word;
  }

  uint32_t clear = ~0;
  clear = ~(clear >> (MAX_POS + 1 - width) << pos);
  uint32_t cleared_word = word & clear;

  uint32_t value_mask = get_field(value, 0, width) << pos;

  return cleared_word | value_mask;
}

int32_t sign_extend(uint32_t value, int width) {
  if (!check_bounds(width, MIN_WIDTH, MAX_WIDTH)) {
    log_failed_bounds(width, MIN_WIDTH, MAX_WIDTH, "width");
    return 0;
  }

  uint32_t base = get_field(value, 0, width);
  uint32_t mask = (base & 1 << (width - 1)) ? ~0 << width : 0;

  int32_t result = base | mask;
  return result;
}
