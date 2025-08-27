#include <iostream>
#include <mdra.hpp>
#include <event/kbd.hpp>

using namespace mdra;
using namespace kbd;

class MyKBD : public VirtualDevice {
  using VirtualDevice::VirtualDevice;

  void remap() override {
    // arrow keys
    CAPS + H >> LEFT;
    CAPS + J >> DOWN;
    CAPS + K >> UP;
    CAPS + L >> RIGHT;

    // utils
    bool caps_used_as_modi = false;
    if (CAPS && !(general_kbd_keys - CAPS)) caps_used_as_modi = true;
    CAPS + X >> DELETE;
    if (CAPS && !caps_used_as_modi) BACKSPACE;
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
