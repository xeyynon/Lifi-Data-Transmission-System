#define SOLAR_PIN A0     // Analog pin for the solar panel
#define THRESHOLD 700    // Adjust based on your readings
const int PERIOD = 4;  // Time between each bit

bool previous_state = false;
bool current_state = false;
String decoded_message = "";

void setup() {
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  current_state = (analogRead(SOLAR_PIN) > THRESHOLD);  // Check if above threshold

  if (!current_state && previous_state) {  // Detect transition from high to low (start bit)
    char decoded_byte = get_byte();  // Read the byte
    if (isPrintable(decoded_byte)) {
      decoded_message += decoded_byte;  // Add to the complete message
      Serial.print("Decoded Message So Far: ");
      Serial.println(decoded_message);  // Print the full message
    } else {
      Serial.println("Non-printable character received, retrying...");
    }
  }

  previous_state = current_state;  // Store current state for comparison
}

// Function to read a byte (8 bits) from the signal
char get_byte() {
  char byte_value = 0;  // Initialize the byte
  delay(PERIOD * 1.5);  // Wait for 1.5 periods to sync with the middle of the first bit

  for (int i = 0; i < 8; i++) {  // Read 8 bits (1 byte)
    int bit_value = (analogRead(SOLAR_PIN) > THRESHOLD) ? 1 : 0;  // Read each bit
    byte_value |= (bit_value << i);  // Shift the bit into the correct position
    delay(PERIOD);  // Wait for the next bit
  }

  delay(PERIOD);  // Extra delay for stop bit
  return byte_value;  // Return the decoded byte
}

// Helper function to check if the received byte is printable
bool isPrintable(char c) {
  return c >= 32 && c <= 126;  // Printable ASCII range from space to tilde
}