#include "outlet.h"

// Constructor implementation
Outlet::Outlet(unsigned int pin, const char* name)
  : pin(pin), mode(AUTO), current_state(0), target_state(0), last_target_state(0), name(name)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 1); // Off
}

void Outlet::update() {
  if (mode == AUTO) {
    if(target_state != last_target_state) {
      last_target_state = target_state;
      current_state = target_state;
    }
  }
  digitalWrite(pin, !current_state);
}

void Outlet::rename(const char* new_name) {
  name = new_name;
}