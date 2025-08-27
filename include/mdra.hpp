#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <linux/input.h>
#include <linux/uinput.h>
#include <linux/input-event-codes.h>

using FileDiscriptor = int;
using EvType = uint16_t;
using EvCode = uint16_t;
using EvValue = uint16_t;

namespace mdra {

class Device;
class VirtualDevice;

unsigned long evtypeToUinputIoctl(EvType evtype);

enum class Trigger {
  Occuring,
  Start,
  Update,
  End
};

class Input {
private:
  Trigger trigger = Trigger::Occuring;
  int valid_time = 0;

  // check code
  bool isValid() const;
public:
  struct input_event ev = {0};

  // constructor
  Input() = delete;
  Input(const Input&) = default;
  Input(const EvType& type, const EvCode& code, const int& value = 1);

  // check code
  explicit operator bool() const;
  // send code
  void send(VirtualDevice& device) const;
};

inline Input updater(EV_SYN, SYN_REPORT, 0);

class Inputs : public std::vector<Input> {
public:
  // constructor
  using std::vector<Input>::vector;

  // check code
  explicit operator bool() const;
  // send code
  void send() const;
};

// custom operator
bool operator==(const Input& lhs, const Input& rhs);      // Input == Input

Inputs operator+(const Input& lhs, const Input& rhs);     // Input + Input
Inputs operator+(const Input& lhs, const Inputs& rhs);    // Input + Inputs
Inputs operator+(const Inputs& lhs, const Input& rhs);    // Inputs + Input
Inputs operator+(const Inputs& lhs, const Inputs& rhs);   // Inputs + Inputs

Inputs& operator+=(Inputs& lhs, const Input& rhs);        // Inputs += Input
Inputs& operator+=(Inputs& lhs, const Inputs& rhs);       // Inputs += Inputs

Inputs operator-(const Inputs& lhs, const Input& rhs);    // Inputs - Input
Inputs operator-(const Inputs& lhs, const Inputs& rhs);   // Inputs - Inputs

Inputs& operator+=(Inputs& lhs, const Input& rhs);        // Inputs -= Input
Inputs& operator+=(Inputs& lhs, const Inputs& rhs);       // Inputs -= Inputs

void operator>>(const Input& lhs, const Input& rhs);
void operator>>(Inputs& lhs, const Input& rhs);
void operator>>(Inputs& lhs, Inputs& rhs);

enum class DevicePreset {
  Keyboard,
  Mouse,
  Other
};

class DeviceInputList {
public:
  Inputs inputs;

  static DeviceInputList getConfigForPreset(DevicePreset preset);
};

class Device {
public:
  std::string device_path;
  FileDiscriptor fd = -1;

  static Device getDeviceByPath(const std::string& path);
  static Device getDeviceById(const std::string& id);
  static Device getDeviceByEventId(int id);
};

class VirtualDevice : public Device {
private:
public:
  struct uinput_setup virtual_device;
  DeviceInputList config;

  Device target;

  // constructor
  VirtualDevice(const std::string& name, const DevicePreset& config = DevicePreset::Keyboard);
  ~VirtualDevice();

  void create();

  virtual void remap();
  virtual void map();
};

}
