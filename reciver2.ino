define SOLAR_PIN A0       // Pin connected to the phototransistor
#define THRESHOLD 700      // Threshold to detect light
const int PERIOD = 4;      // Bit transmission period in milliseconds

bool previous_state = false;
bool current_state = false;
String decoded_message = "";

void setup() {
  Serial.begin(9600);  
  Serial.println("Waiting for transmission...");
}

void loop() {
  current_state = (analogRead(SOLAR_PIN) > THRESHOLD);  

  if (!current_state && previous_state) {  
    char decoded_byte = get_byte();  

    if (decoded_byte == '\0') {
      // Null character detected, end of message
      Serial.println("Message received: ");
      Serial.println(decoded_message);
      decoded_message = "";  // Clear the message for the next transmission
      Serial.println("Ready for next transmission...");
      delay(1000);  // Pause before the next reception
    } else if (isPrintable(decoded_byte)) {
      decoded_message += decoded_byte;  
    } else {
      Serial.println("Non-printable character received, ignoring...");
    }
  }

  previous_state = current_state;  
}

char get_byte() {
  char byte_value = 0;  
  delay(PERIOD * 1.5);  

  for (int i = 0; i < 8; i++) {  
    int bit_value = (analogRead(SOLAR_PIN) > THRESHOLD) ? 1 : 0;  
    byte_value |= (bit_value << i);  
    delay(PERIOD);  
  }

  delay(PERIOD);  
  return byte_value;  
}

bool isPrintable(char c) {
  return c >= 32 && c <= 126;  
}