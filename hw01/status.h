#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>
#include "bits.h"

#define HEAT_SIZE     1
#define COOL_SIZE     1
#define FAN_SIZE      1
#define FAULT_SIZE    1
#define MODE_SIZE     3
#define RESERVED_SIZE 1
#define SETPOINT_SIZE 8

#define INVALID_MODE  7;

#define RESERVED_VALUE 0;

enum {
  HEAT_POS     = 0,
  COOL_POS     = 1,
  FAN_POS      = 2,
  FAULT_POS    = 3,
  MODE_POS     = 4,
  RESERVED_POS = 7,
  SETPOINT_POS = 8
};

typedef struct status_s {
  unsigned int heat:      HEAT_SIZE;
  unsigned int cool:      COOL_SIZE;
  unsigned int fan:       FAN_SIZE;
  unsigned int fault:     FAULT_SIZE;
  unsigned int mode:      MODE_SIZE;
  unsigned int reserved : RESERVED_SIZE;
  signed int setpoint:    SETPOINT_SIZE;
} status_t;

status_t status_unpack(uint16_t word);

#endif
