#include <linux/input-event-codes.h>

#include "mdra.hpp"

#define GENERAL_MOUSE_EVENTS 11

using namespace mdra;

namespace mouse {

inline Input LEFT(EV_KEY, BTN_LEFT);
inline Input RIGHT(EV_KEY, BTN_RIGHT);
inline Input MIDDLE(EV_KEY, BTN_MIDDLE);
inline Input SIDE(EV_KEY, BTN_SIDE);
inline Input EXTRA(EV_KEY, BTN_EXTRA);
inline Input X(EV_REL, REL_X);
inline Input Y(EV_REL, REL_Y);
inline Input HWHEEL(EV_REL, REL_HWHEEL);
inline Input WHEEL(EV_REL, REL_WHEEL);
inline Input WHEEL_HI_RES(EV_REL, REL_WHEEL_HI_RES);
inline Input HWHEEL_HI_RES(EV_REL, REL_HWHEEL_HI_RES);

inline Inputs general_mouse_events = {
  LEFT, RIGHT, MIDDLE, SIDE, EXTRA, X, Y,
  HWHEEL, WHEEL, WHEEL_HI_RES, HWHEEL_HI_RES
};

}
