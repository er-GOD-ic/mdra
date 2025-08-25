#include <iostream>
#include <mdra.hpp>
#include <event/kbd.hpp>

using namespace mdra;
using namespace kbd;

class MyKBD : VirtualDevice {
  void remap() override {

  }
}

int main() {
  Device phisKbd = Device::getDeviceById("usb-Keychron_Keychron_K3-event-kbd");

  VirtualDevice kbd("TestKBD", DevicePreset::Keyboard);
  kbd.create();

  kbd.grab(phisKbd).remap = [](){
    // arrow keys
    CAPS + H >> LEFT;
    CAPS + J >> DOWN;
    CAPS + K >> UP;
    CAPS + L >> RIGHT;

    // utils
    bool caps_used_as_modi = false;
    CAPS + !(all_kbd_keys - CAPS) >> (caps_used_as_modi)[]{ caps_used_as_modi = true };
    CAPS + X >> DEL;
    CAPS.up & !caps_used_as_modi >> backspace;
  }

  std::string dummy;
  std::cin >> dummy;

  return 0;
}
