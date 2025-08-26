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
public:
  struct input_event ev = {0};
  
  // constructor
  Input() = delete;
  Input(const Input&) = default;
  Input(const EvType& type, const EvCode& code);

  // check codes
  bool isValid(const Input* input);
  explicit operator bool() const;
};

// custom operator
bool operator==(const Input& lhs, const Input& rhs);                                          // Input == Input

std::vector<Input> operator+(const Input& lhs, const Input& rhs);                             // Input + Input
std::vector<Input> operator+(const Input& lhs, const std::vector<Input>& rhs);                // Input + vector<Input>
std::vector<Input> operator+(const std::vector<Input>& lhs, const Input& rhs);                // vector<Input> + Input
std::vector<Input> operator+(const std::vector<Input>& lhs, const std::vector<Input>& rhs);   // vector<Input> + vector<Input>

std::vector<Input>& operator+=(std::vector<Input>& lhs, const Input& rhs);                    // vector<Input> += Input
std::vector<Input>& operator+=(std::vector<Input>& lhs, const std::vector<Input>& rhs);       // vector<Input> += vector<Input>

std::vector<Input> operator-(const std::vector<Input>& lhs, const Input& rhs);                // vector<Input> - Input
std::vector<Input> operator-(const std::vector<Input>& lhs, const std::vector<Input>& rhs);   // vector<Input> - vector<Input>

std::vector<Input>& operator+=(std::vector<Input>& lhs, const Input& rhs);                    // vector<Input> -= Input
std::vector<Input>& operator+=(std::vector<Input>& lhs, const std::vector<Input>& rhs);       // vector<Input> -= vector<Input>

enum class DevicePreset {
  Keyboard,
  Mouse,
  Other
};

class DeviceInputList {
public:
  std::vector<Input> inputs;

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
  Device target;
public:
  struct uinput_setup virtual_device;
  DeviceInputList config;

  // constructor
  VirtualDevice(const std::string& name, const DevicePreset& config = DevicePreset::Keyboard);
  ~VirtualDevice();

  void create();

  virtual void remap();
  virtual void map();
};

}
