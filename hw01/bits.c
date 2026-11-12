#include <stdlib.h>
#include "bits.h"

#define POS_TAG "pos"
#define WIDTH_TAG "width"
#define POS_WIDTH_TAG "pos + width"

static const int MIN_WIDTH = 1;
static const int MAX_WIDTH = 32;
static const int MIN_POS   = 0;
static const int MAX_POS   = 31;
static const int SPACING   = 4;

static void check_bounds(int value, int min, int max, const char *name) {
  if (value < min || value > max) {
    fprintf(stderr, "Value '%s' = %d is out of range: [%d, %d]\n", name, value, min, max);
    exit(EXIT_FAILURE);
  }
}

static void check_all_bounds(int pos, int width) {
  check_bounds(pos, MIN_POS, MAX_POS, POS_TAG);
  check_bounds(width, MIN_WIDTH, MAX_WIDTH, WIDTH_TAG);
  check_bounds(pos + width, MIN_POS, MAX_WIDTH, POS_WIDTH_TAG);
}

void print_binary(uint32_t x, int width) {
  check_bounds(width, MIN_WIDTH, MAX_WIDTH, WIDTH_TAG);

  int bit;
  for (int i = width - 1; i >= 0; i--){
    bit = (x >> i) & 1;
    printf("%c", '0' + bit);

    if (i > 0 && i % SPACING == 0) { printf(" "); }
  }

  printf("\n");
}

uint32_t get_field(uint32_t word, int pos, int width) {
  check_all_bounds(pos, width);

  return word << (MAX_POS + 1 - width - pos) >> (MAX_POS - width + 1);
}

uint32_t set_field(uint32_t word, int pos, int width, uint32_t value) {
  check_all_bounds(pos, width);

  uint32_t clear = ~(UINT32_MAX >> (MAX_POS + 1 - width) << pos);
  uint32_t cleared_word = word & clear;

  uint32_t value_mask = get_field(value, 0, width) << pos;

  return cleared_word | value_mask;
}

int32_t sign_extend(uint32_t value, int width) {
  check_bounds(width, MIN_WIDTH, MAX_WIDTH, WIDTH_TAG);

  uint32_t base = get_field(value, 0, width);
  uint32_t bit_mask = UINT32_C(1) << (width - 1);
  uint32_t mask = (base & bit_mask && width < MAX_WIDTH) ? UINT32_MAX << width : 0;

  int32_t result = base | mask;
  return result;
}
