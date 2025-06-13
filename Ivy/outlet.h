#ifndef IVY_OUTLET_H
#define IVY_OUTLET_H

#include "Arduino.h"

class Outlet {
public:
  // Constants for modes
  static constexpr unsigned int AUTO   = 0;
  static constexpr unsigned int MANUAL = 1;

  // Member variables
  unsigned int pin;
  unsigned int mode;
  unsigned int current_state;
  unsigned int target_state;
  unsigned int last_target_state;
  String name;
  
  Outlet(unsigned int pin, const char* name);
  void rename(const char* new_name);
  void update();
};

#endif
