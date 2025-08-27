#include <linux/input-event-codes.h>

#include "mdra.hpp"

#define GENERAL_KBD_KEYS 133

using namespace mdra;

namespace kbd {

// Non-Charactor Keys
inline Input ESC(EV_KEY, KEY_ESC);

inline Input DELETE(EV_KEY, KEY_DELETE);
inline Input BACKSPACE(EV_KEY, KEY_BACKSPACE);
inline Input ENTER(EV_KEY, KEY_ENTER);

inline Input TAB(EV_KEY, KEY_TAB);

inline Input CAPS(EV_KEY, KEY_CAPSLOCK);
inline Input NUMLOCK(EV_KEY, KEY_NUMLOCK);
inline Input SCROLLLOCK(EV_KEY, KEY_SCROLLLOCK);

inline Input HOME(EV_KEY, KEY_HOME);
inline Input END(EV_KEY, KEY_END);

inline Input PAGEUP(EV_KEY, KEY_PAGEUP);
inline Input PAGEDOWN(EV_KEY, KEY_PAGEDOWN);

inline Input SCALE(EV_KEY, KEY_SCALE);

inline Input SYSRQ(EV_KEY, KEY_SYSRQ);
inline Input INSERT(EV_KEY, KEY_INSERT);

// Arrow Keys
inline Input LEFT(EV_KEY, KEY_LEFT);
inline Input DOWN(EV_KEY, KEY_DOWN);
inline Input UP(EV_KEY, KEY_UP);
inline Input RIGHT(EV_KEY, KEY_RIGHT);

// Modifier Keys
inline Input LSHIFT(EV_KEY, KEY_LEFTSHIFT);
inline Input LCTRL(EV_KEY, KEY_LEFTCTRL);
inline Input LMETA(EV_KEY, KEY_LEFTMETA);
inline Input LALT(EV_KEY, KEY_LEFTALT);
inline Input RSHIFT(EV_KEY, KEY_RIGHTSHIFT);
inline Input RCTRL(EV_KEY, KEY_RIGHTCTRL);
inline Input RMETA(EV_KEY, KEY_RIGHTMETA);
inline Input RALT(EV_KEY, KEY_RIGHTALT);

// Num Keys
inline Input N_1(EV_KEY, KEY_1);
inline Input N_2(EV_KEY, KEY_2);
inline Input N_3(EV_KEY, KEY_3);
inline Input N_4(EV_KEY, KEY_4);
inline Input N_5(EV_KEY, KEY_5);
inline Input N_6(EV_KEY, KEY_6);
inline Input N_7(EV_KEY, KEY_7);
inline Input N_8(EV_KEY, KEY_8);
inline Input N_9(EV_KEY, KEY_9);
inline Input N_0(EV_KEY, KEY_0);

// Numeric Keys
inline Input KP_1(EV_KEY, KEY_KP1);
inline Input KP_2(EV_KEY, KEY_KP2);
inline Input KP_3(EV_KEY, KEY_KP3);
inline Input KP_4(EV_KEY, KEY_KP4);
inline Input KP_5(EV_KEY, KEY_KP5);
inline Input KP_6(EV_KEY, KEY_KP6);
inline Input KP_7(EV_KEY, KEY_KP7);
inline Input KP_8(EV_KEY, KEY_KP8);
inline Input KP_9(EV_KEY, KEY_KP9);
inline Input KP_0(EV_KEY, KEY_KP0);

// other Numeric Keypad Keys
inline Input KP_MINUS(EV_KEY, KEY_KPMINUS);
inline Input KP_PLUS(EV_KEY, KEY_KPPLUS);
inline Input KP_DOT(EV_KEY, KEY_KPDOT);

inline Input KP_ASTERISK(EV_KEY, KEY_KPASTERISK);
inline Input KP_JPCOMMA(EV_KEY, KEY_KPJPCOMMA);
inline Input KP_ENTER(EV_KEY, KEY_KPENTER);
inline Input KP_SLASH(EV_KEY, KEY_KPSLASH);
inline Input KP_EQUAL(EV_KEY, KEY_KPEQUAL);
inline Input KP_COMMA(EV_KEY, KEY_KPCOMMA);

// Function Keys
inline Input F1(EV_KEY, KEY_F1);
inline Input F2(EV_KEY, KEY_F2);
inline Input F3(EV_KEY, KEY_F3);
inline Input F4(EV_KEY, KEY_F4);
inline Input F5(EV_KEY, KEY_F5);
inline Input F6(EV_KEY, KEY_F6);
inline Input F7(EV_KEY, KEY_F7);
inline Input F8(EV_KEY, KEY_F8);
inline Input F9(EV_KEY, KEY_F9);
inline Input F10(EV_KEY, KEY_F10);
inline Input F11(EV_KEY, KEY_F11);
inline Input F12(EV_KEY, KEY_F12);
inline Input F13(EV_KEY, KEY_F13);
inline Input F14(EV_KEY, KEY_F14);
inline Input F15(EV_KEY, KEY_F15);
inline Input F16(EV_KEY, KEY_F16);
inline Input F17(EV_KEY, KEY_F17);
inline Input F18(EV_KEY, KEY_F18);
inline Input F19(EV_KEY, KEY_F19);
inline Input F20(EV_KEY, KEY_F20);
inline Input F21(EV_KEY, KEY_F21);
inline Input F22(EV_KEY, KEY_F22);
inline Input F23(EV_KEY, KEY_F23);
inline Input F24(EV_KEY, KEY_F24);

// Charactor Keys
inline Input A(EV_KEY, KEY_A);
inline Input B(EV_KEY, KEY_B);
inline Input C(EV_KEY, KEY_C);
inline Input D(EV_KEY, KEY_D);
inline Input E(EV_KEY, KEY_E);
inline Input F(EV_KEY, KEY_F);
inline Input G(EV_KEY, KEY_G);
inline Input H(EV_KEY, KEY_H);
inline Input I(EV_KEY, KEY_I);
inline Input J(EV_KEY, KEY_J);
inline Input K(EV_KEY, KEY_K);
inline Input L(EV_KEY, KEY_L);
inline Input M(EV_KEY, KEY_M);
inline Input N(EV_KEY, KEY_N);
inline Input O(EV_KEY, KEY_O);
inline Input P(EV_KEY, KEY_P);
inline Input Q(EV_KEY, KEY_Q);
inline Input R(EV_KEY, KEY_R);
inline Input S(EV_KEY, KEY_S);
inline Input T(EV_KEY, KEY_T);
inline Input U(EV_KEY, KEY_U);
inline Input V(EV_KEY, KEY_V);
inline Input W(EV_KEY, KEY_W);
inline Input X(EV_KEY, KEY_X);
inline Input Y(EV_KEY, KEY_Y);
inline Input Z(EV_KEY, KEY_Z);

// Symbol Keys
inline Input MINUS(EV_KEY, KEY_MINUS);
inline Input EQUAL(EV_KEY, KEY_EQUAL);

inline Input LEFTBRACE(EV_KEY, KEY_LEFTBRACE);
inline Input RIGHTBRACE(EV_KEY, KEY_RIGHTBRACE);

inline Input SEMICOLON(EV_KEY, KEY_SEMICOLON);
inline Input APOSTROPHE(EV_KEY, KEY_APOSTROPHE);
inline Input GRAVE(EV_KEY, KEY_GRAVE);

inline Input SLASH(EV_KEY, KEY_SLASH);
inline Input BACKSLASH(EV_KEY, KEY_BACKSLASH);

inline Input COMMA(EV_KEY, KEY_COMMA);
inline Input DOT(EV_KEY, KEY_DOT);

inline Input SPACE(EV_KEY, KEY_SPACE);

inline Input DOLLAR(EV_KEY, KEY_DOLLAR);

// JIS
inline Input ZENKAKUHANKAKU(EV_KEY, KEY_ZENKAKUHANKAKU);
inline Input RO(EV_KEY, KEY_RO);
inline Input KATAKANA(EV_KEY, KEY_KATAKANA);
inline Input HIRAGANA(EV_KEY, KEY_HIRAGANA);
inline Input HENKAN(EV_KEY, KEY_HENKAN);
inline Input KATAKANAHIRAGANA(EV_KEY, KEY_KATAKANAHIRAGANA);
inline Input MUHENKAN(EV_KEY, KEY_MUHENKAN);
inline Input YEN(EV_KEY, KEY_YEN);

  // ISO
inline Input ISO_102ND(EV_KEY, KEY_102ND);
inline Input HANGEUL(EV_KEY, KEY_HANGEUL);
inline Input HANGUEL(EV_KEY, KEY_HANGUEL);
inline Input HANJA(EV_KEY, KEY_HANJA);
inline Input COMPOSE(EV_KEY, KEY_COMPOSE);
inline Input EURO(EV_KEY, KEY_EURO);


inline Inputs general_kbd_keys = {
  ESC, DELETE, BACKSPACE, ENTER, TAB, CAPS, NUMLOCK, SCROLLLOCK,
  HOME, END, PAGEUP, PAGEDOWN, SCALE, SYSRQ, INSERT, LEFT, DOWN, UP, RIGHT,
  LSHIFT, LCTRL, LMETA, LALT, RSHIFT, RCTRL, RMETA, RALT,
  N_1, N_2, N_3, N_4, N_5, N_6, N_7, N_8, N_9, N_0,
  KP_1, KP_2, KP_3, KP_4, KP_5, KP_6, KP_7, KP_8, KP_9, KP_0,
  KP_MINUS, KP_PLUS, KP_DOT, KP_ASTERISK, KP_JPCOMMA, KP_ENTER, KP_SLASH, KP_EQUAL, KP_COMMA,
  F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  MINUS, EQUAL, LEFTBRACE, RIGHTBRACE, SEMICOLON, APOSTROPHE,
  GRAVE, SLASH, BACKSLASH, COMMA, DOT, SPACE, DOLLAR,
  ZENKAKUHANKAKU, RO, KATAKANA, HIRAGANA, HENKAN, KATAKANAHIRAGANA, MUHENKAN, YEN,
  ISO_102ND, HANGEUL, HANGUEL, HANJA, COMPOSE, EURO,
};

}
