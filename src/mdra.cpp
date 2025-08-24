#include <iostream>
#include "mdra.hpp"

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

DeviceConfig::allKeyboardKeys() {
  std::vector<Input> keys;
  for (EvCode i = 0; i < KEY_MAX; i++) {
    Input key(EV_KEY, i);
    keys += key;
  }
  return keys;
}

DeviceConfig::getConfigForType(DevicePreset type) {
  DeviceConfig config;
  switch (type) {
    case DevicePreset::Keyboard:
      config.inputs = this.allKeyboardKeys();
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
        Input(EV_REL,  REL_HWHEEL),
        Input(EV_REL,  REL_WHEEL),
        Input(EV_REL,  REL_WHEEL_HI_RES),
        Input(EV_REL,  REL_HWHEEL_HI_RES)
      };
      break;
    case DevicePresET::Other:
      break;
  }
  return config;
}

VirtualDevice::VirtualDevice(const std::string& name, const DevicePreset& config = DevicePreset::Keyboard) {
  fd = open("/dev/uinput", O_WONLY | O_NONBLOCK);
  if (fd < 0) {
    std::cerror << "Faital: faild to open /dev/uinput" << std::strerror(errno) << std::endl;
    std::abort();
  }
  // deviceを設計
  memset(&device, 0, sizeof(device));
  std::strncpy(device.name, name.c_str(), UINPUT_MAX_NAME_SIZE - 1);
  device.name[UINPUT_MAX_NAME_SIZE - 1] = '\0';
  device.id.bustype = BUS_USB;
  device.id.vendor  = 0x1234;
  device.id.product = 0x5678;
  device.id.version = 1;
}

VirtualDevice::create() {
  // set ioctl EvType
  for (EvType i = 0; i < EV_MAX; i++) {
    for (int j = 0; j < config.inputs.size(); j++) {
      if (config.inputs.at(j).ev.type == i) {
        if (ioctl(fd, UI_SET_EVBIT, i) < 0) {
          std::cerror << "Faital: faild to set ioctl(UI_SET_EVBIT) EV_TYPE: " << i << std::strerror(errno) << std::endl;
          std::abort();
        }
        break;
      }
    }
  }
  // set ioctl EvCode
  for (int i = 0; i < config.inputs.size(); i++) {
    if (ioctl(fd, evtypeToUinputIoctl(config.inputs.at(i).ev.type), config.inputs.at(i).ev.code) < 0) {
      std::cerror << "Faital: faild to set ioctl(UI_SET_EVBIT) EV_TYPE: " << i << std::strerror(errno) << std::endl;
      std::abort();
    }
  }
}

Input::Input(const EvType& type, const EvCode& code, const EvValue& value = 1) : ev.type(type), ev.code(code), ev.value(value) {}

