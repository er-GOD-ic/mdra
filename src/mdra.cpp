#include <iostream>
#include "mdra.hpp"

namespace mdra {

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

std::vector<Input> DeviceConfig::allKeyboardKeys() {
  std::vector<Input> keys;
  for (EvCode i = 0; i < KEY_MAX; i++) {
    Input key(EV_KEY, i);
    keys += key;
  }
  return keys;
}

DeviceConfig DeviceConfig::getConfigForPreset(DevicePreset type) {
  DeviceConfig config;
  switch (type) {
    case DevicePreset::Keyboard:
      config.inputs = allKeyboardKeys();
      break;
    case DevicePreset::Mouse:
      config.inputs = {
        Input(EV_KEY, BTN_LEFT),
        Input(EV_KEY, BTN_RIGHT),
        Input(EV_KEY, BTN_MIDDLE),
        Input(EV_KEY, BTN_SIDE),
        Input(EV_KEY, BTN_EXTRA),
        Input(EV_REL, REL_X),
        Input(EV_REL, REL_Y),
        Input(EV_REL, REL_HWHEEL),
        Input(EV_REL, REL_WHEEL),
        Input(EV_REL, REL_WHEEL_HI_RES),
        Input(EV_REL, REL_HWHEEL_HI_RES)
      };
      break;
    case DevicePreset::Other:
      break;
  }
  return config;
}

VirtualDevice::VirtualDevice(const std::string& name, const DevicePreset& preset) {
  fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
  if (fd < 0) {
    std::cerr << "Faital: faild to open /dev/uinput" << std::strerror(errno) << std::endl;
    std::abort();
  }
  // deviceを設計
  std::memset(&device, 0, sizeof(device));
  std::strncpy(device.name, name.c_str(), UINPUT_MAX_NAME_SIZE - 1);
  device.name[UINPUT_MAX_NAME_SIZE - 1] = '\0';
  device.id.bustype = BUS_USB;
  device.id.vendor  = 0x1234;
  device.id.product = 0x5678;
  device.id.version = 1;

  config = DeviceConfig::getConfigForPreset(preset);
}
VirtualDevice::~VirtualDevice() {};

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
  if (ioctl(fd, UI_DEV_SETUP, &device) < 0) {
    perror("UI_DEV_SETUP");
    exit(1);
  }
  if (ioctl(fd, UI_DEV_CREATE) < 0) {
    perror("UI_DEV_CREATE");
    exit(1);
  }
  std::cout << "VirtualDevice " << device.name << " has been created!" << std::endl;
}

Input::Input(const EvType& type, const EvCode& code, const EvValue& value) {
  ev.type = type;
  ev.code = code;
  ev.value = value;
}

// Input + Input
std::vector<Input> operator+(const Input& lhs, const Input& rhs) {
    return {lhs, rhs};
}

// Input + vector<Input>
std::vector<Input> operator+(const Input& lhs, const std::vector<Input>& rhs) {
    std::vector<Input> result;
    result.reserve(rhs.size() + 1);
    result.push_back(lhs);
    result.insert(result.end(), rhs.begin(), rhs.end());
    return result;
}

// vector<Input> + Input
std::vector<Input> operator+(const std::vector<Input>& lhs, const Input& rhs) {
    std::vector<Input> result = lhs;
    result.push_back(rhs);
    return result;
}

// vector<Input> + vector<Input>
std::vector<Input> operator+(const std::vector<Input>& lhs, const std::vector<Input>& rhs) {
    std::vector<Input> result = lhs;
    result.insert(result.end(), rhs.begin(), rhs.end());
    return result;
}

// vector<Input> += Input
std::vector<Input>& operator+=(std::vector<Input>& lhs, const Input& rhs) {
    lhs.push_back(rhs);
    return lhs;
}

// vector<Input> += vector<Input>
std::vector<Input>& operator+=(std::vector<Input>& lhs, const std::vector<Input>& rhs) {
    lhs.insert(lhs.end(), rhs.begin(), rhs.end());
    return lhs;
}

}
