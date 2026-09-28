/* AMB82-MINI LED serial controller: LEFT=blue, RIGHT=green, BLUE=blink. */

constexpr uint8_t BLUE_LED_PIN = LED_B;
constexpr uint8_t GREEN_LED_PIN = LED_G;
char commandBuffer[32];
uint8_t commandLength = 0;
bool blueIsOn = false;
bool greenIsOn = false;

void setLeds(bool blue, bool green) {
    blueIsOn = blue;
    greenIsOn = green;
    digitalWrite(BLUE_LED_PIN, blue ? HIGH : LOW);
    digitalWrite(GREEN_LED_PIN, green ? HIGH : LOW);
}

void printState() {
    Serial.print(" BLUE="); Serial.print(blueIsOn ? "ON" : "OFF");
    Serial.print(" GREEN="); Serial.println(greenIsOn ? "ON" : "OFF");
}

void blinkBlueThreeTimes() {
    // Preserve the green LED state while the blue LED blinks.
    for (uint8_t count = 0; count < 3; count++) {
        setLeds(true, greenIsOn);
        delay(300);
        setLeds(false, greenIsOn);
        delay(300);
    }
}

void handleCommand(const char *command) {
    if (strcmp(command, "LEFT") == 0) {
        setLeds(true, false); Serial.print("ACK LEFT"); printState();
    } else if (strcmp(command, "RIGHT") == 0) {
        setLeds(false, true); Serial.print("ACK RIGHT"); printState();
    } else if (strcmp(command, "BLUE") == 0) {
        blinkBlueThreeTimes(); Serial.print("ACK BLUE_BLINKED"); printState();
    } else if (strcmp(command, "STATUS") == 0) {
        Serial.print("ACK STATUS"); printState();
    } else {
        // Invalid commands must never change the LED state.
        Serial.print("ERR UNKNOWN_COMMAND"); printState();
    }
}

void readSerialCommands() {
    while (Serial.available() > 0) {
        const char character = (char)Serial.read();
        if (character == '\r') continue;
        if (character == '\n') {
            commandBuffer[commandLength] = '\0';
            if (commandLength > 0) handleCommand(commandBuffer);
            commandLength = 0;
        } else if (commandLength < sizeof(commandBuffer) - 1) {
            commandBuffer[commandLength++] = character;
        } else {
            commandLength = 0;
            Serial.println("ERR COMMAND_TOO_LONG");
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    setLeds(false, false);
    Serial.println("READY AMB82 LED controller");
    Serial.print("ACK STATUS"); printState();
}

void loop() { readSerialCommands(); }
