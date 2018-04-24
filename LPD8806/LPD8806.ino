/*
 *     USB MIDI to LPD8806 by mat1jaczyyy
 *     ----------------------------------
 */

/*  
 * LED Strip definition
 * --------------------
 */

const byte _nLED = 60;  // Number of LEDs
const byte _dLED = 4;   // Data pin
const byte _cLED = 3;   // Clock pin

#include <LPD8806.h>
LPD8806 _LED = LPD8806(_nLED, _dLED, _cLED);

/*
 * Color Palette
 * Generate with retinaConverter.py (Retina 2.0+ Palette)
 * ------------------------------------------------------
 */

const uint8_t _r[128] = {0, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 22, 46, 71, 111, 95, 14, 30, 46, 95, 62, 6, 14, 22, 79, 30, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 6, 14, 22, 79, 30, 14, 30, 46, 95, 62, 22, 46, 71, 111, 95, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 18, 36, 54, 73, 91, 109, 127};
const uint8_t _g[128] = {0, 0, 0, 0, 62, 0, 6, 14, 22, 79, 30, 14, 30, 46, 95, 62, 22, 46, 71, 111, 95, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 22, 46, 71, 111, 95, 14, 30, 46, 95, 62, 6, 14, 22, 79, 30, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 18, 36, 54, 73, 91, 109, 127};
const uint8_t _b[128] = {0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 0, 0, 0, 62, 0, 6, 14, 22, 79, 30, 14, 30, 46, 95, 62, 22, 46, 71, 111, 95, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 30, 62, 95, 127, 127, 22, 46, 71, 111, 95, 14, 30, 46, 95, 62, 6, 14, 22, 79, 30, 18, 36, 54, 73, 91, 109, 127};

/*
 * MIDI handler
 * ------------
 */

const uint8_t _pStart = 36;  // First note in array
bool update = false;

void noteOn(byte ch, byte p, byte v) {
  _LED.setPixelColor(p - _pStart, _r[v], _b[v], _g[v]);  // LPD8806 uses RBG format
}

void noteOff(byte ch, byte p, byte v) {
  _LED.setPixelColor(p - _pStart, 0, 0, 0);
}

/*
 * Initialize LED Strip and USB MIDI
 * ---------------------------------
 */

void setup() {
  _LED.begin();
  _LED.show();
  
  usbMIDI.setHandleNoteOn(noteOn);
  usbMIDI.setHandleNoteOff(noteOff);
}

/*
 * Read MIDI and update Strip
 * --------------------------
 */
void loop() {
  while (usbMIDI.read()) {
    update = true;
  }
  if (update) {
    _LED.show();
    update = false;
  }
}
