#include<IRremote.hpp>

#define IR_RECEIVE_PIN 11
#define IR_SEND_PIN 3

#define NRG_AUTO 0
#define NRG_OFF 1
#define NRG_MIN 2
#define NRG_MED 3
#define NRG_MAX 4
#define NRG_SCREEN_OFF 5
#define NRG_N_OPTIONS 6

int energy_saving_options[6] = {NRG_AUTO, NRG_OFF, NRG_MIN, NRG_MED, NRG_MAX, NRG_SCREEN_OFF};
int current_energy_saving_option = -1;

void setup() {
    Serial.begin(9600);
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    //  IrSender.begin(IR_SEND_PIN);
    IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN); // Specify send pin and enable feedback LED at default feedback LED pin

    Serial.println("Ready to receive unknown IR signals at pin " + String(IR_RECEIVE_PIN) + " and decode it with hash decoder.");

    Serial.print(F("Send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
    delay(5000);
}

#define IR_UP 0x40
#define IR_DOWN 0x41
#define IR_BACK 0x1A
#define IR_OPEN_ENERGY_SAVING 0x95

void selectEnergySavingOption(int option) {
  if (option < 0 || option >= NRG_N_OPTIONS) {
    Serial.println("Invalid energy saving option: " + String(option));
    return;
  } else if (current_energy_saving_option == option) {
    Serial.println("Already selected energy saving option: " + String(option));
    return;
  } else if (current_energy_saving_option < option) {
    for (int i = current_energy_saving_option; i < option; i++) {
      Serial.println("pressing down, i: " + String(i));
      IrSender.sendNEC(0x4, IR_DOWN, 1);
      delay(500);
    }
  } else {
    for (int i = current_energy_saving_option; i > option; i--) {
      Serial.println("pressing up, i: " + String(i));
      IrSender.sendNEC(0x4, IR_UP, 1);
      delay(500);
    }
  }
}

void initEnergySaving() {
  Serial.println("opening energy saving options");
  IrSender.sendNEC(0x4, IR_OPEN_ENERGY_SAVING, 2);
  delay(500);
  // cycle up to the first option and beyond, to the "close window" button.
  // ensure that the "close window" button is definitely selected.
  // 1. get the length of the energy_saving_options array
  for (int i = 0; i < NRG_N_OPTIONS+1; i++) {
    Serial.println("pressing up, i: " + String(i));
    IrSender.sendNEC(0x4, IR_UP, 1);
    delay(500);
  }
  // at this point, the menu index is _actually_ at -1!
  // let's select "off", i.e. turn the energy saving off (max brightness)
  selectEnergySavingOption(NRG_OFF);
  // woohoo! let's wait 5 seconds, then select max energy saving
  delay(5000);
  selectEnergySavingOption(NRG_MAX);
}

void printIRSignal() {
  // IrReceiver.initDecodedIRData(); // is required, if we do not call decode();
  IrReceiver.decode();
  // Serial.println(IrReceiver.decodedIRData.address, HEX);
  // Serial.println(IrReceiver.decodedIRData.command, HEX);
  // Serial.println(getProtocolString(IrReceiver.decodedIRData.protocol));
  // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

  // We have an unknown protocol here, print extended info
  // IrReceiver.printIRResultRawFormatted(&Serial, true);

  IrReceiver.printIRResultShort(&Serial);
}

void loop() {
  if (IrReceiver.available()) {
    printIRSignal();
    delay(250);

    Serial.print("resending same signal... ");
    for (int i = 0; i < 5; i++) {
      IrSender.sendNEC(IrReceiver.decodedIRData.address, IrReceiver.decodedIRData.command, 0);
      delay(500);
    }
    Serial.println("finished same signal");
    initEnergySaving();

    delay(1000);
    IrReceiver.resume(); // Early enable receiving of the next IR frame
  }
}

