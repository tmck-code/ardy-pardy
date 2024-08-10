#include<IRremote.hpp>

#define IR_RECEIVE_PIN 11

void setup() {
    Serial.begin(9600);
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    Serial.println("Ready to receive unknown IR signals at pin " + String(IR_RECEIVE_PIN) + " and decode it with hash decoder.");
}

void loop() {
  if (IrReceiver.available()) {
    IrReceiver.initDecodedIRData(); // is required, if we do not call decode();
    IrReceiver.decodeHash();

    // We have an unknown protocol here, print extended info
    IrReceiver.printIRResultRawFormatted(&Serial, true);
    IrReceiver.resume(); // Early enable receiving of the next IR frame

    IrReceiver.printIRResultShort(&Serial);
    Serial.println();
  }
}
