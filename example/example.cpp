#include <iostream>
#include <mdra.hpp>

using namespace mdra;
using namespace kbd;

int main() {
  Device phisKbd = Device::getDeviceById("usb-Keychron_Keychron_K3-event-kbd");

  VirtualDevice kbd("TestKBD", DevicePreset::Keyboard);
  kbd.create();

  kbd.grab(phisKbd).remap = [](){
    // arrow keys
    caps + l >> right_arrow;
    caps + h >> left_arrow;
    caps + j >> down_arrow;
    caps + k >> up_arrow;

    // utils
    bool caps_used_as_modi = false;
    caps + !(all_kbd_keys - caps) >> (caps_used_as_modi)[]{ caps_used_as_modi = true };
    caps + x >> del;
    caps.up & !caps_used_as_modi >> backspace;
  }

  std::string dummy;
  std::cin >> dummy;

  return 0;
}
