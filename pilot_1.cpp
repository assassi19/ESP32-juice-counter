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
const int Kharbooza_PIN = 14;

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
int Kharbooza_count = 0;

// Profit/Loss tracking
float Mixed_Fruit_investment = 0;
float Pinapple_investment = 0;
float Mosambi_investment = 0;
float Mango_investment = 0;
float Chikoo_investment = 0;
float Papaya_investment = 0;
float WaterMelon_investment = 0;
float Grapes_investment = 0;
float Banana_investment = 0;
float Kharbooza_investment = 0;
float Others = 0;

bool Mixed_Fruit_lastState = LOW;
bool Pinapple_lastState = LOW;
bool Mosambi_lastState = LOW;
bool Mango_lastState = LOW;
bool Chikoo_lastState = LOW;
bool Papaya_lastState = LOW;
bool WaterMelon_lastState = LOW;
bool Grapes_lastState = LOW;
bool Banana_lastState = LOW;
bool Kharbooza_lastState = LOW;

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
  pinMode(Kharbooza_PIN, INPUT_PULLUP);

  // Connect to Wi-Fi
  WiFi.softAP(ssid, password);
  Serial.println("Setting up WiFi...");
  
  // Setup web server routes
  server.on("/", handleRoot);
  server.on("/reset", handleReset);
  server.on("/investment", handleInvestment);
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
  checkButton(Kharbooza_PIN, Kharbooza_lastState, Kharbooza_count);
  
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
    String html = "<html><head><title>Juice Counter</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    html += "<style>body{font-family:Arial,sans-serif;margin:20px;}h1{text-align:center;}table{width:100%;margin-bottom:30px;border-collapse:collapse;}th,td{padding:10px;text-align:center;border:1px solid #ddd;}th{background:#f2f2f2;}button{display:block;width:100%;padding:15px;margin:10px auto;font-size:16px;background:#4CAF50;color:white;border:none;border-radius:5px;}button:hover{background:#45a049;}canvas{width:100%;height:auto;}</style>";
    html += "<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>";
    html += "</head><body><h1>Juice Counters</h1><table><tr><th>Juice</th><th>Count</th><th>Rupees</th></tr>";
    html += "<tr><td>Mixed Fruit</td><td>" + String(Mixed_Fruit_count) + "</td><td>" + String(Mixed_Fruit_count * 10) + "</td></tr>";
    html += "<tr><td>Pinapple</td><td>" + String(Pinapple_count) + "</td><td>" + String(Pinapple_count * 10) + "</td></tr>";
    html += "<tr><td>Mosambi</td><td>" + String(Mosambi_count) + "</td><td>" + String(Mosambi_count * 10) + "</td></tr>";
    html += "<tr><td>Mango</td><td>" + String(Mango_count) + "</td><td>" + String(Mango_count * 10) + "</td></tr>";
    html += "<tr><td>Chikoo</td><td>" + String(Chikoo_count) + "</td><td>" + String(Chikoo_count * 10) + "</td></tr>";
    html += "<tr><td>Papaya</td><td>" + String(Papaya_count) + "</td><td>" + String(Papaya_count * 10) + "</td></tr>";
    html += "<tr><td>WaterMelon</td><td>" + String(WaterMelon_count) + "</td><td>" + String(WaterMelon_count * 10) + "</td></tr>";
    html += "<tr><td>Grapes</td><td>" + String(Grapes_count) + "</td><td>" + String(Grapes_count * 10) + "</td></tr>";
    html += "<tr><td>Banana</td><td>" + String(Banana_count) + "</td><td>" + String(Banana_count * 10) + "</td></tr>";
    html += "<tr><td>Kharbooza</td><td>" + String(Kharbooza_count) + "</td><td>" + String(Kharbooza_count * 10) + "</td></tr>";

    int totalDrinks = Mixed_Fruit_count + Kharbooza_count + Pinapple_count + Mosambi_count + Mango_count + Chikoo_count + Papaya_count + WaterMelon_count + Grapes_count + Banana_count;
    int totalCost = totalDrinks * 10;
    html += "<tr><td>Total Drinks</td><td>" + String(totalDrinks) + "</td><td>" + String(totalCost) + "</td></tr>";
  
    // Profit/Loss for each item and total
    html += "</table><h2>Profit/Loss</h2><table><tr><th>Juice</th><th>Investment (Rs)</th><th>Profit/Loss (Rs)</th></tr>";
    html += "<tr><td>Mixed Fruit</td><td>" + String(Mixed_Fruit_investment) + "</td><td>" + String((Mixed_Fruit_count * 10) - Mixed_Fruit_investment) + "</td></tr>";
    html += "<tr><td>Pinapple</td><td>" + String(Pinapple_investment) + "</td><td>" + String((Pinapple_count * 10) - Pinapple_investment) + "</td></tr>";
    html += "<tr><td>Mosambi</td><td>" + String(Mosambi_investment) + "</td><td>" + String((Mosambi_count * 10) - Mosambi_investment) + "</td></tr>";
    html += "<tr><td>Mango</td><td>" + String(Mango_investment) + "</td><td>" + String((Mango_count * 10) - Mango_investment) + "</td></tr>";
    html += "<tr><td>Chikoo</td><td>" + String(Chikoo_investment) + "</td><td>" + String((Chikoo_count * 10) - Chikoo_investment) + "</td></tr>";
    html += "<tr><td>Papaya</td><td>" + String(Papaya_investment) + "</td><td>" + String((Papaya_count * 10) - Papaya_investment) + "</td></tr>";
    html += "<tr><td>WaterMelon</td><td>" + String(WaterMelon_investment) + "</td><td>" + String((WaterMelon_count * 10) - WaterMelon_investment) + "</td></tr>";
    html += "<tr><td>Grapes</td><td>" + String(Grapes_investment) + "</td><td>" + String((Grapes_count * 10) - Grapes_investment) + "</td></tr>";
    html += "<tr><td>Banana</td><td>" + String(Banana_investment) + "</td><td>" + String((Banana_count * 10) - Banana_investment) + "</td></tr>";
    html += "<tr><td>Kharbooza</td><td>" + String(Kharbooza_investment) + "</td><td>" + String((Kharbooza_count * 10) - Kharbooza_investment) + "</td></tr>";

    float totalInvestment = Others + Mixed_Fruit_investment +Kharbooza_investment + Pinapple_investment + Mosambi_investment + Mango_investment + Chikoo_investment + Papaya_investment + WaterMelon_investment + Grapes_investment + Banana_investment;
    float totalProfitLoss = (totalDrinks * 10) - totalInvestment;
    html += "<tr><td>Total</td><td>" + String(totalInvestment) + "</td><td>" + String(totalProfitLoss) + "</td></tr>";
    
    html += "</table><form action=\"/reset\" method=\"GET\"><button type=\"submit\">Reset</button></form>";
    html += "<form action=\"/investment\" method=\"GET\"><h2>Investment Input</h2><label for=\"item\">Item:</label><select id=\"item\" name=\"item\"><option value=\"Others\">Others</option><option value=\"Mixed_Fruit\">Mixed Fruit</option><option value=\"Pinapple\">Pinapple</option><option value=\"Kharbooza\">Kharbooza</option><option value=\"Mosambi\">Mosambi</option><option value=\"Mango\">Mango</option><option value=\"Chikoo\">Chikoo</option><option value=\"Papaya\">Papaya</option><option value=\"WaterMelon\">WaterMelon</option><option value=\"Grapes\">Grapes</option><option value=\"Banana\">Banana</option></select><label for=\"price\">Price/kg:</label><input type=\"number\" id=\"price\" name=\"price\" required><label for=\"quantity\">Quantity (kgs):</label><input type=\"number\" id=\"quantity\" name=\"quantity\" required><button type=\"submit\">Submit</button></form>";
  //add the others option here
    html += "<h2>Sales Graph</h2><canvas id=\"salesChart\"></canvas>";
    html += "<script>let ctx=document.getElementById('salesChart').getContext('2d');";
    html += "let chart=new Chart(ctx,{type:'line',data:{labels:[0,1,2,3,4,5,6,7,8,9],datasets:[{label:'Total Sales (Rs 100)',";
    html += "data:[" + String(totalCost/100) + "],borderColor:'rgba(75, 192, 192, 1)',fill:false}]},";
    html += "options:{scales:{x:{title:{display:true,text:'Time (Hours)'}},y:{title:{display:true,text:'Money (Rs 100)'}}}}});</script>";
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
  Kharbooza_count = 0;

  Mixed_Fruit_investment = 0;
  Kharbooza_investment = 0;
  Pinapple_investment = 0;
  Mosambi_investment = 0;
  Mango_investment = 0;
  Chikoo_investment = 0;
  Papaya_investment = 0;
  WaterMelon_investment = 0;
  Grapes_investment = 0;
  Banana_investment = 0;
  Others = 0;
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleInvestment() {
  String item = server.arg("item");
  float price = server.arg("price").toFloat();
  float quantity = server.arg("quantity").toFloat();
  float investment = price * quantity;

  if (item == "Mixed_Fruit") Mixed_Fruit_investment += investment;
  else if (item == "Pinapple") Pinapple_investment += investment;
  else if (item == "Mosambi") Mosambi_investment += investment;
  else if (item == "Mango") Mango_investment += investment;
  else if (item == "Chikoo") Chikoo_investment += investment;
  else if (item == "Papaya") Papaya_investment += investment;
  else if (item == "WaterMelon") WaterMelon_investment += investment;
  else if (item == "Grapes") Grapes_investment += investment;
  else if (item == "Banana") Banana_investment += investment;
  else if (item == "Kharbooza") Kharbooza_investment += investment;
  else if (item == "Others") Others += investment;

  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}
