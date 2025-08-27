#include <iostream>
#include <mdra.hpp>
#include <event/kbd.hpp>

using namespace mdra;
using namespace kbd;

class MyKBD : public VirtualDevice {
  using VirtualDevice::VirtualDevice;

  void map() override {
    // arrow keys
    if (CAPS + H) LEFT.send(*this);
    if (CAPS + J) DOWN.send(*this);
    if (CAPS + K) UP.send(*this);
    if (CAPS + L) RIGHT.send(*this);

    // utils
    bool caps_used_as_modi = false;
    if (CAPS && !(general_kbd_keys - CAPS)) caps_used_as_modi = true;
    if (CAPS + X) DELETE.send(*this);
    if (CAPS && !caps_used_as_modi) BACKSPACE.send(*this);
  }
};

int main() {
  Device phisKbd = Device::getDeviceById("usb-Keychron_Keychron_K3-event-kbd");

  MyKBD kbd("TestKBD", DevicePreset::Keyboard);
  kbd.create();

  std::string dummy;
  std::cin >> dummy;

  return 0;
}
