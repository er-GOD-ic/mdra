#include <iostream>
#include <cstring>
#include <filesystem>
#include <algorithm>

#include "mdra.hpp"
#include "event/kbd.hpp"
#include "event/mouse.hpp"

namespace mdra {

Device Device::getDeviceByPath(const std::string& path) {
  Device device;
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error("Device path does not exist: " + path);
  }

  device.device_path = path;
  device.fd = open(path.c_str(), O_RDWR | O_NONBLOCK);
  if (device.fd < 0) {
    throw std::runtime_error("Failed to open device: " + path);
  }

  return device;
}

Device Device::getDeviceById(const std::string& id) {
  namespace fs = std::filesystem;
  Device device;

  for (auto& entry : fs::directory_iterator("/dev/input/by-id/")) {
    std::string path = entry.path();
    if (path.find(id) != std::string::npos) {
      device = getDeviceByPath(path);
      return device;
    }
  }

  throw std::runtime_error("Device with ID " + id + " not found");
}

Device Device::getDeviceByEventId(int id) {
  std::string path = "/dev/input/event" + std::to_string(id);
  return getDeviceByPath(path);
}

unsigned long evtypeToUinputIoctl(EvType evtype) {
  switch (evtype) {
    case EV_KEY:  return UI_SET_KEYBIT;
    case EV_REL:  return UI_SET_RELBIT;
    case EV_ABS:  return UI_SET_ABSBIT;
    case EV_MSC:  return UI_SET_MSCBIT;
    case EV_SW:   return UI_SET_SWBIT;
    case EV_LED:  return UI_SET_LEDBIT;
    case EV_SND:  return UI_SET_SNDBIT;
    case EV_FF:   return UI_SET_FFBIT;
    // EV_SYN, EV_REP, EV_PWR, EV_FF_STATUSなどは対応するioctlなし
    default:      return 0; // 不明（対応なし）
  }
}

DeviceInputList DeviceInputList::getConfigForPreset(DevicePreset type) {
  DeviceInputList config;
  switch (type) {
    case DevicePreset::Keyboard:
      for (auto& ref : kbd::general_kbd_keys) { config.inputs += ref.get(); }
      break;
    case DevicePreset::Mouse:
      for (auto& ref : mouse::general_mouse_events) { config.inputs += ref.get(); }
      break;
    case DevicePreset::Other:
      break;
  }
  return config;
}

VirtualDevice::VirtualDevice(const std::string& name, const DevicePreset& preset) {
  std::string device_path = "/dev/uinput";
  fd = open(device_path.c_str(), O_WRONLY | O_NONBLOCK);
  if (fd < 0) {
    std::cerr << "Faital: faild to open /dev/uinput" << std::strerror(errno) << std::endl;
    std::abort();
  }
  // deviceを設計
  std::memset(&virtual_device, 0, sizeof(virtual_device));
  std::strncpy(virtual_device.name, name.c_str(), UINPUT_MAX_NAME_SIZE - 1);
  virtual_device.name[UINPUT_MAX_NAME_SIZE - 1] = '\0';
  virtual_device.id.bustype = BUS_USB;
  virtual_device.id.vendor  = 0x1234;
  virtual_device.id.product = 0x5678;
  virtual_device.id.version = 1;
  // deviceのプリセット設定を適応
  config = DeviceInputList::getConfigForPreset(preset);
}
VirtualDevice::~VirtualDevice() {
  ioctl(fd, UI_DEV_DESTROY);
  close(fd);
  std::cout << "VirtualDevice has been deleted successfully." << std::endl;
};

void VirtualDevice::create() {
  // set ioctl EvType
  for (EvType i = 0; i < EV_MAX; i++) {
    for (int j = 0; j < config.inputs.size(); j++) {
      if (config.inputs.at(j).ev.type == i) {
        if (ioctl(fd, UI_SET_EVBIT, i) < 0) {
          std::cerr << "Faital: faild to set ioctl(UI_SET_EVBIT) EV_TYPE: " << i << std::strerror(errno) << std::endl;
          std::abort();
        }
        break;
      }
    }
  }
  // set ioctl EvCode
  for (int i = 0; i < config.inputs.size(); i++) {
    if (ioctl(fd, evtypeToUinputIoctl(config.inputs.at(i).ev.type), config.inputs.at(i).ev.code) < 0) {
      std::cerr << "Faital: faild to set ioctl(UI_SET_EVBIT) EV_TYPE: " << i << std::strerror(errno) << std::endl;
      std::abort();
    }
  }

  // deviceを作成
  if (ioctl(fd, UI_DEV_SETUP, &virtual_device) < 0) {
    perror("UI_DEV_SETUP");
    exit(1);
  }
  if (ioctl(fd, UI_DEV_CREATE) < 0) {
    perror("UI_DEV_CREATE");
    exit(1);
  }
  std::cout << "VirtualDevice " << virtual_device.name << " has been created!" << std::endl;
}

bool Input::isValid() const {
  switch (trigger) {
    case Trigger::Occuring:
      return this -> ev.value != 0;
    case Trigger::Start:
      return this -> ev.value == 1 && this -> valid_time == 1;
    case Trigger::Update:
      return this -> ev.value != 0 && this -> valid_time > 1;
    case Trigger::End:
      if (this -> ev.type != EV_KEY) return false;
      return this -> ev.value == 0;
    default:
      return false;
  }
}

Input::operator bool() const {
  return isValid();
}

Input::Input(const EvType& type, const EvCode& code) {
  ev.type = type;
  ev.code = code;
}

// Input == Input
bool operator==(const Input& lhs, const Input& rhs) {
  return lhs.ev.type == rhs.ev.type && lhs.ev.code == rhs.ev.code;
}

// Input + Input
Inputs operator+(const Input& lhs, const Input& rhs) {
  return Inputs({lhs, rhs});
}

// Input + vector<Input>
Inputs operator+(const Input& lhs, const Inputs& rhs) {
  Inputs result;
  result.reserve(rhs.size() + 1);
  result.push_back(lhs);
  result.insert(result.end(), rhs.begin(), rhs.end());
  return result;
}

// vector<Input> + Input
Inputs operator+(const Inputs& lhs, const Input& rhs) {
  Inputs result = lhs;
  result.push_back(rhs);
  return result;
}

// vector<Input> + vector<Input>
Inputs operator+(const Inputs& lhs, const Inputs& rhs) {
  Inputs result = lhs;
  result.insert(result.end(), rhs.begin(), rhs.end());
  return result;
}

// vector<Input> += Input
Inputs& operator+=(Inputs& lhs, const Input& rhs) {
  lhs.push_back(rhs);
  return lhs;
}

// vector<Input> += vector<Input>
Inputs& operator+=(Inputs& lhs, const Inputs& rhs) {
  lhs.insert(lhs.end(), rhs.begin(), rhs.end());
  return lhs;
}

// vector<Input> - Input
Inputs operator-(const Inputs& lhs, const Input& rhs) {
  Inputs result;
  std::copy_if(lhs.begin(), lhs.end(), std::back_inserter(result),
               [&rhs](const Input& x) { return !(x == rhs); });
  return result;
}

// vector<Input> - vector<Input>
Inputs operator-(const Inputs& lhs, const Inputs& rhs) {
  Inputs result = lhs;
  for (const auto& r : rhs) {
    result = result - r; // 上のoperator-を再利用
  }
  return result;
}

// vector<Input> -= Input
Inputs& operator-=(Inputs& lhs, const Input& rhs) {
  lhs.erase(
    std::remove(lhs.begin(), lhs.end(), rhs),
    lhs.end()
  );
  return lhs;
}

// vector<Input> -= vector<Input>
Inputs& operator-=(Inputs& lhs, const Inputs& rhs) {
  for (const auto& r : rhs) {
    lhs -= r;
  }
  return lhs;
}

}
