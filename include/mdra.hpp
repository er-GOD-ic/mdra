#include <memory>
#include <cstdint>

#include <unistd.h>
#include <fctntl.h>
#include <sys/ioctl.h>

#include <linux/input.h>
#include <linux/uinput.h>

using FileDiscriptor = int;
using EvType = uint16_t;
using EvCode = uint16_t;
using EvValue = uint32_t;

namespace mdra {

unsigned long evtypeToUinputIoctl(EvType evtype);

enum class DevicePreset {
  Keyboard,
  Mouse,
  Other
};

class DeviceConfig {
private:
  static std::vector<EvCode> allKeyboardKeys();
public:
  std::vector<Input> inputs;

  static DeviceConfig getConfigForType(DevicePreset type);
};

class VirtualDevice {
public:
  FileDiscriptor fd;
  struct uinput_setup device;
  DeviceConfig config;

  // constructor
  VirtualDevice(const std::string& name, const DevicePreset& config = DevicePreset::Keyboard);
  ~VirtualDevice();

  create();
};

class Input {
public:
  struct input_event ev = {0};
  // constructor
  Input() = delete;
  Input(const input&) = default;
  Input(const EvType& type, const EvCode& code, const EvValue& value = 1);
};

}
