#include <stdbool.h>
#include "status.h"

int main(void) {
  return 0;
}

status_t status_unpack(uint16_t word) {
  status_t status;

  status.heat  = get_field(word, HEAT_POS, HEAT_SIZE);
  status.cool  = get_field(word, COOL_POS, COOL_SIZE);
  status.fan   = get_field(word, FAN_POS, FAN_SIZE);
  status.fault = get_field(word, FAULT_POS, FAULT_SIZE);

  uint32_t mode = get_field(word, MODE_POS, MODE_SIZE);
  status.mode = (mode <= MAX_MODE) ? mode : INVALID_MODE;

  uint32_t reserved = get_field(word, RESERVED_POS, RESERVED_SIZE);
  if (reserved) {
    fprintf(stderr, "Warning: unpacked '%d' in reserved block. Should be '0'\n", reserved);
  }
  status.reserved = RESERVED_VALUE;

  status.setpoint = sign_extend(get_field(word, SETPOINT_POS, SETPOINT_SIZE), SETPOINT_SIZE);

  return status;
}
