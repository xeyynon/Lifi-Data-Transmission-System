#define LED_PIN 9   // Control pin for the Laser Module
#define PERIOD 4 // Transmission period in milliseconds

const char *message = "Chal Raha";  // The text message to transmit
int message_length;

void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set the control pin as an output
  Serial.begin(9600);        // Start serial communication for debugging
  message_length = strlen(message);  // Get the length of the message
}

void loop() {
  for (int i = 0; i < message_length; i++) {
    send_byte(message[i]);  // Send each character as a byte
  }
  delay(100);  // Wait 500ms before sending the message again
}

void send_byte(char my_byte) {
  digitalWrite(LED_PIN, LOW);  
  delay(PERIOD);  // Start bit (LOW)

  for (int i = 0; i < 32; i++) {  
    int bit = bitRead(my_byte, i);  // Read each bit of the character
    digitalWrite(LED_PIN, bit);     // Set Laser module based on the bit (HIGH/LOW)
    delay(PERIOD);  // Wait for the next bit
  }

  digitalWrite(LED_PIN, HIGH);  
  delay(PERIOD);  // Stop bit (HIGH)
}
