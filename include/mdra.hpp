#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/input.h>
#include <linux/uinput.h>
#include <linux/input-event-codes.h>

using FileDiscriptor = int;
using EvType = uint16_t;
using EvCode = uint16_t;
using EvValue = uint16_t;

namespace mdra {

unsigned long evtypeToUinputIoctl(EvType evtype);

class Input {
public:
  struct input_event ev = {0};
  // constructor
  Input() = delete;
  Input(const Input&) = default;
  Input(const EvType& type, const EvCode& code, const EvValue& value = 1);

};

// custom operator
std::vector<Input> operator+(const Input& lhs, const Input& rhs);                             // Input + Input
std::vector<Input> operator+(const Input& lhs, const std::vector<Input>& rhs);                // Input + vector<Input>
std::vector<Input> operator+(const std::vector<Input>& lhs, const Input& rhs);                // vector<Input> + Input
std::vector<Input> operator+(const std::vector<Input>& lhs, const std::vector<Input>& rhs);   // vector<Input> + vector<Input>

std::vector<Input>& operator+=(std::vector<Input>& lhs, const Input& rhs);                    // vector<Input> += Input
std::vector<Input>& operator+=(std::vector<Input>& lhs, const std::vector<Input>& rhs);       // vector<Input> += vector<Input>

enum class DevicePreset {
  Keyboard,
  Mouse,
  Other
};

class DeviceConfig {
private:
  static std::vector<Input> allKeyboardKeys();
public:
  std::vector<Input> inputs;

  static DeviceConfig getConfigForPreset(DevicePreset preset);
};

class VirtualDevice {
public:
  FileDiscriptor fd;
  struct uinput_setup device;
  DeviceConfig config;

  // constructor
  VirtualDevice(const std::string& name, const DevicePreset& config = DevicePreset::Keyboard);
  ~VirtualDevice();

  void create();
};

}
