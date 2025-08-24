#include <iostream>
#include <mdra.hpp>

using namespace mdra;

int main() {
  VirtualDevice kbd("TestKBD", DevicePreset::Keyboard);
  kbd.create();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return 0;
}
