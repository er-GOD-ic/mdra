#include <mdra.hpp>

int main() {
  mdra::VirutalDevice kbd = new VirutalDevice("TestKBD", DevicePreset::Keyboard);
  kbd.create();
}
