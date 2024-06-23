#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_Hotspot";
const char* password = "Chacha@98457";
WebServer server(80);

// Pin assignments
const int Mixed_Fruit_PIN = 4;
const int Pinapple_PIN = 23;
const int Mosambi_PIN = 19;
const int Mango_PIN = 21;
const int Chikoo_PIN = 32;
const int Papaya_PIN = 33;
const int WaterMelon_PIN = 25;
const int Grapes_PIN = 26;
const int Banana_PIN = 27;

// Counters
int Mixed_Fruit_count = 0;
int Pinapple_count = 0;
int Mosambi_count = 0;
int Mango_count = 0;
int Chikoo_count = 0;
int Papaya_count = 0;
int WaterMelon_count = 0;
int Grapes_count = 0;
int Banana_count = 0;

// Previous button states
bool Mixed_Fruit_lastState = LOW;
bool Pinapple_lastState = LOW;
bool Mosambi_lastState = LOW;
bool Mango_lastState = LOW;
bool Chikoo_lastState = LOW;
bool Papaya_lastState = LOW;
bool WaterMelon_lastState = LOW;
bool Grapes_lastState = LOW;
bool Banana_lastState = LOW;

void setup() {
  Serial.begin(115200);

  // Configure button pins as inputs with internal pull-up resistors
  pinMode(Mixed_Fruit_PIN, INPUT_PULLUP);
  pinMode(Pinapple_PIN, INPUT_PULLUP);
  pinMode(Mosambi_PIN, INPUT_PULLUP);
  pinMode(Mango_PIN, INPUT_PULLUP);
  pinMode(Chikoo_PIN, INPUT_PULLUP);
  pinMode(Papaya_PIN, INPUT_PULLUP);
  pinMode(WaterMelon_PIN, INPUT_PULLUP);
  pinMode(Grapes_PIN, INPUT_PULLUP);
  pinMode(Banana_PIN, INPUT_PULLUP);

  // Connect to Wi-Fi
  WiFi.softAP(ssid, password);
  Serial.println("Setting up WiFi...");
  
  // Setup web server routes
  server.on("/", handleRoot);
  server.on("/reset", handleReset);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Check each button and increment counters
  checkButton(Mixed_Fruit_PIN, Mixed_Fruit_lastState, Mixed_Fruit_count);
  checkButton(Pinapple_PIN, Pinapple_lastState, Pinapple_count);
  checkButton(Mosambi_PIN, Mosambi_lastState, Mosambi_count);
  checkButton(Mango_PIN, Mango_lastState, Mango_count);
  checkButton(Chikoo_PIN, Chikoo_lastState, Chikoo_count);
  checkButton(Papaya_PIN, Papaya_lastState, Papaya_count);
  checkButton(WaterMelon_PIN, WaterMelon_lastState, WaterMelon_count);
  checkButton(Grapes_PIN, Grapes_lastState, Grapes_count);
  checkButton(Banana_PIN, Banana_lastState, Banana_count);
  
  // Handle web server
  server.handleClient();
}

void checkButton(int pin, bool &lastState, int &count) {
  bool currentState = digitalRead(pin); // remember we are using internal pull-up resistor so when button pressed it'll read low
  if (currentState == LOW && lastState == HIGH) {
    count++;
    Serial.print("Button on pin ");
    Serial.print(pin);
    Serial.print(" pressed. New count: ");
    Serial.println(count);
  }
  lastState = currentState;
}

void handleRoot() {
  String html = "<html><head><title>Juice Counter</title></head><style>";
  html += "table {width: 60%; border-collapse: collapse; margin: 50px 0;}";
  html += "th, td, tf {padding: 12px; border: 1px solid #ddd; text-align: center;}";
  html += "th,tf {background-color: #f2f2f2;}";
  html += "button {padding: 10px 20px; margin: 50px 0; font-size: 16px; background-color: #4CAF50; color: white; border: none; border-radius: 5px;}";
  html += "button:hover {background-color: #45a049;}";
  html += "</style></head><body>";
  html += "<h1>Juice Counters</h1>";
  html += "<table><tr><th>Juice</th><th>Count</th><th>Rupees</th></tr><tf><td></td><td></td></tf>";
  html += "<tr><td>Mixed Fruit</td><td>" + String(Mixed_Fruit_count) + "</td><td>" + String(Mixed_Fruit_count*10) + "</td></tr>";
  html += "<tr><td>Pinapple</td><td>" + String(Pinapple_count) + "</td><td>" + String(Pinapple_count*10) + "</td></tr>";
  html += "<tr><td>Mosambi</td><td>" + String(Mosambi_count) + "</td><td>" + String(Mosambi_count*10) + "</td></tr>";
  html += "<tr><td>Mango</td><td>" + String(Mango_count) + "</td><td>" + String(Mango_count*10) + "</td></tr>";
  html += "<tr><td>Chikoo</td><td>" + String(Chikoo_count) + "</td><td>" + String(Chikoo_count*10) + "</td></tr>";
  html += "<tr><td>Papaya</td><td>" + String(Papaya_count) + "</td><td>" + String(Papaya_count*10) + "</td></tr>";
  html += "<tr><td>WaterMelon</td><td>" + String(WaterMelon_count) + "</td><td>" + String(WaterMelon_count*10) + "</td></tr>";
  html += "<tr><td>Grapes</td><td>" + String(Grapes_count) + "</td><td>" + String(Grapes_count*10) + "</td></tr>";
  html += "<tr><td>Banana</td><td>" + String(Banana_count) + "</td><td>" + String(Banana_count*10) + "</td></tr>";
  int totalDrinks = Mixed_Fruit_count + Pinapple_count + Mosambi_count + Mango_count + Chikoo_count + Papaya_count + WaterMelon_count + Grapes_count + Banana_count;
  int totalCost = totalDrinks * 10;
  html += "<tf><td>Total Drinks</td><td>" + String(totalDrinks) + "</td><td>" + String(totalCost) + "</td></tf>";
  html += "</table>";
  html += "<form action=\"/reset\" method=\"POST\"><button type=\"submit\">Reset</button></form>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void handleReset() {
  Mixed_Fruit_count = 0;
  Pinapple_count = 0;
  Mosambi_count = 0;
  Mango_count = 0;
  Chikoo_count = 0;
  Papaya_count = 0;
  WaterMelon_count = 0;
  Grapes_count = 0;
  Banana_count = 0;
  
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}
