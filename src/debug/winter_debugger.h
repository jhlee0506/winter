#ifndef WINTER_DEBUGGER_H
#define WINTER_DEBUGGER_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>


void
winter_debugger_turn_on(int level);

bool
winter_debugger_is_enabled();
#endif /* WINTER_DEBUGGER_H */