#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define FN1 1 // symbols
#define SPACE4 2 // 4 spaces
#define BRACKETS 3 // BRACKETS
#define TESTCARD 10001

#define CAPS_CTL CTL_T(KC_CAPS)  // Caps on tap, Ctrl on hold.
#define COPY     LCTL(KC_V)      // C-c Copy
#define PASTE    LCTL(KC_V)      // C-v Paste
#define ZM_NRM   LCTL(KC_0)      // C-0 Zoom Normal
#define ZM_OUT   LCTL(KC_MINS)   // C-- Zoom Out
#define ZM_IN    LCTL(KC_PLUS)   // C-+ Zoom In
#define EM_UNDO  LCTL(KC_UNDS)   // C-_ Emacs Undo

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC ~  |   1  |   2  |   3  |   4  |   5  | Spot |           |   6  |   7  |   8  |   9  |   0  |   -  | BSpace |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | [ {  |           |  ] } |   Y  |   U  |   I  |   O  |   P  |   \ |  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Ctl    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|copy  |           |space4|------+------+------+------+------+--------|
 * |( LShift|   Z  |   X  |   C  |   V  |   B  | Clip |           |      |   N  |   M  |   ,  |   .  |   /  |RShift )|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | `~   |Ctrl+`| PASTE| Alt  | LGui |                                       | RGUI | Left |  Dn  |  Up  | Right  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Copy |PASTE |       |  ESC |  {}  |
 *                                 ,------|------+------|       |------+------+------.
 *                                 |      |      |ScCopy|       |  PgUp|      |      |
 *                                 |Space |' = ' |------|       |------| Enter| Space|
 *                                 |      |      | Spot |       |  PgDn|      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
    [BASE] = KEYMAP(  // layer 0 : default
	// Left hand KC_GRV,  KC_GESC
	KC_ESC,   KC_1,    KC_2,    KC_3,     KC_4,     KC_5,    LGUI(KC_SPC),
	KC_TAB,   KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,    KC_LBRC,
	KC_LCTL,  KC_A,  KC_S, KC_D,     KC_F,     KC_G,
	KC_LSFT,  KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,    LSFT(LGUI(KC_V)),
	KC_GRV,LCTL(KC_GRV),LCTL(KC_GRV), KC_LALT,  KC_LGUI,
	SPACE4,  BRACKETS,
	SCMD(LCTL(KC_4)),
	KC_SPC, KC_EQL,  KC_FN1,

	// Right hand
	KC_6,    KC_7,    KC_8,     KC_9,     KC_0,    KC_MINS,   KC_BSPC,
	KC_RBRC,  KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,    KC_BSLS,
	          KC_H,    KC_J,    KC_K,     KC_L,     LT(1,KC_SCOLON), KC_QUOT,
	KC_B,  KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH, KC_RSFT,
	KC_RGUI,KC_LEFT,  KC_DOWN, KC_UP,   KC_RIGHT,
	KC_ESC,  TESTCARD,
	KC_PGUP,
	KC_PGDN, KC_ENT, KC_SPC),
/* Keymap 1: Fn Keys, media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Esc   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | BSpace |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      | Mute |VolDn |VolUp |   {  |   }    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|sl l  |sl dn |sl up |sl r  |   [  |   ]    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | LClk | MClk | RClk |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Teensy|      | ZmNrm| ZmOut| ZmIn |                                       | Undo |VolDn |VolUp | Mute |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------+------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// FN1 Layer
    [FN1] = KEYMAP(
	// Left hand
	KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN3, KC_BTN2, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, ZM_NRM,  ZM_OUT,  ZM_IN,
	KC_TRNS, RGB_TOG,
	KC_TRNS,
	RESET,   KC_TRNS, KC_TRNS,
	// Right hand
	KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC,
	KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, LSFT(KC_LBRC), LSFT(KC_RBRC),
	LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_UP), LSFT(KC_RIGHT), KC_LBRC, KC_RBRC,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	EM_UNDO, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS,
	KC_TRNS, KC_TRNS,
	KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS
	),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(FN1)                // FN1 - Momentary Layer 1 (Symbols)
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING ("");
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
		  }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING ("");
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
	  case BRACKETS:
	    if (record->event.pressed) {
        SEND_STRING ("{}");
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
      }
      return false;
      break;
	  case SPACE4:
	    if (record->event.pressed) {
        SEND_STRING ("    ");
      }
      return false;
      break;
    case TESTCARD:
      if (record->event.pressed) {
        SEND_STRING ("4242424242424242");
      }
      return false;
      break;
  }

  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
