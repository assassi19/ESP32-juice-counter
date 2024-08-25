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
const int Lime_PIN = 13;
const int Anar_PIN = 36;

const int Mixed_Fruit_Milkshake_PIN = 22;
const int Banana_Lassi_PIN = 18;
const int Chocolate_Milkshake_PIN = 5;
const int Strawberry_Milkshake_PIN = 17;
const int Butterscotch_Milkshake_PIN = 16;
const int Anjeer_Milkshake_PIN = 15;
const int Khajoor_Milkshake_PIN = 34;
const int Dry_Fruits_Milkshake_PIN = 35;

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
int Lime_count = 0;
int Anar_count = 0;
//special guy
int limePrice;

// Milkshake Counters
int Mixed_Fruit_Milkshake_count = 0;
int Banana_Lassi_count = 0;
int Chocolate_Milkshake_count = 0;
int Strawberry_Milkshake_count = 0;
int Butterscotch_Milkshake_count = 0;
int Anjeer_Milkshake_count = 0;
int Khajoor_Milkshake_count = 0;
int Dry_Fruits_Milkshake_count = 0;

// Profit/Loss tracking
float Pinapple_investment = 0;
float Mosambi_investment = 0;
float Mango_investment = 0;
float Chikoo_investment = 0;
float Papaya_investment = 0;
float WaterMelon_investment = 0;
float Grapes_investment = 0;
float Banana_investment = 0;
float Kharbooza_investment = 0;
float Anar_investment = 0;
float Others = 0;   //no milkshake investment as it isn't required...

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
bool Lime_lastState = LOW;
bool Anar_lastState = LOW;

// Milkshake last states
bool Mixed_Fruit_Milkshake_lastState = LOW;
bool Banana_Lassi_lastState = LOW;
bool Chocolate_Milkshake_lastState = LOW;
bool Strawberry_Milkshake_lastState = LOW;
bool Butterscotch_Milkshake_lastState = LOW;
bool Anjeer_Milkshake_lastState = LOW;
bool Khajoor_Milkshake_lastState = LOW;
bool Dry_Fruits_Milkshake_lastState = LOW;

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
  pinMode(Lime_PIN, INPUT_PULLUP);
  pinMode(Anar_PIN, INPUT_PULLUP);

  // Milkshake pin setups
  pinMode(Mixed_Fruit_Milkshake_PIN, INPUT_PULLUP);
  pinMode(Banana_Lassi_PIN, INPUT_PULLUP);
  pinMode(Chocolate_Milkshake_PIN, INPUT_PULLUP);
  pinMode(Strawberry_Milkshake_PIN, INPUT_PULLUP);
  pinMode(Butterscotch_Milkshake_PIN, INPUT_PULLUP);
  pinMode(Anjeer_Milkshake_PIN, INPUT_PULLUP);
  pinMode(Khajoor_Milkshake_PIN, INPUT_PULLUP);
  pinMode(Dry_Fruits_Milkshake_PIN, INPUT_PULLUP);

  // Connect to Wi-Fi
  WiFi.softAP(ssid, password);
  Serial.println("Setting up WiFi...");
  
  // Setup web server routes
  server.on("/", handleRoot);
  server.on("/reset", handleReset);
  server.on("/investment", handleInvestment);
  server.on("/setLimePrice", handleSetLimePrice);
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
  checkButton(Anar_PIN, Anar_lastState, Anar_count);
  checkButton(Lime_PIN, Lime_lastState, Lime_count);

  // Milkshake button checks
  checkButton(Mixed_Fruit_Milkshake_PIN, Mixed_Fruit_Milkshake_lastState, Mixed_Fruit_Milkshake_count);
  checkButton(Banana_Lassi_PIN, Banana_Lassi_lastState, Banana_Lassi_count);
  checkButton(Chocolate_Milkshake_PIN, Chocolate_Milkshake_lastState, Chocolate_Milkshake_count);
  checkButton(Strawberry_Milkshake_PIN, Strawberry_Milkshake_lastState, Strawberry_Milkshake_count);
  checkButton(Butterscotch_Milkshake_PIN, Butterscotch_Milkshake_lastState, Butterscotch_Milkshake_count);
  checkButton(Anjeer_Milkshake_PIN, Anjeer_Milkshake_lastState, Anjeer_Milkshake_count);
  checkButton(Khajoor_Milkshake_PIN, Khajoor_Milkshake_lastState, Khajoor_Milkshake_count);
  checkButton(Dry_Fruits_Milkshake_PIN, Dry_Fruits_Milkshake_lastState, Dry_Fruits_Milkshake_count);
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

    int juiceSales[12] = {
        Mixed_Fruit_count * 10,
        Pinapple_count * 10,
        Mosambi_count * 10,
        Mango_count * 10,
        Chikoo_count * 10,
        Papaya_count * 10,
        WaterMelon_count * 10,
        Grapes_count * 10,
        Banana_count * 10,
        Kharbooza_count * 10,
        Anar_count * 10,
        Lime_count * limePrice,
    };

    int milkshakeSales[8] = {
        Mixed_Fruit_Milkshake_count * 40,
        Banana_Lassi_count * 40,
        Chocolate_Milkshake_count * 40,
        Strawberry_Milkshake_count * 40,
        Butterscotch_Milkshake_count * 40,
        Anjeer_Milkshake_count * 80,
        Khajoor_Milkshake_count * 40,
        Dry_Fruits_Milkshake_count * 100
    };

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
    html += "<tr><td>Anaar</td><td>" + String(Anar_count) + "</td><td>" + String(Anar_count * 10) + "</td></tr>";
    html += "<tr><td>LIME</td><td>" + String(Lime_count) + "</td><td>" + String(Lime_count*limePrice) + "</td></tr>";
    html += "<tr><td>DryFruits Milkshake</td><td>" + String(Dry_Fruits_Milkshake_count) + "</td><td>" + String(Dry_Fruits_Milkshake_count * 100) + "<td></tr>";
    html += "<tr><td>Mix-Milkshake</td><td>" + String(Mixed_Fruit_Milkshake_count) + "</td><td>" + String(Mixed_Fruit_Milkshake_count* 40) + "</td></tr>";
    html += "<tr><td>Banana Lassi</td><td>" + String(Banana_Lassi_count) + "</td><td>" + String(Banana_Lassi_count * 40) + "</td></tr>";
    html += "<tr><td>Chocolate </td><td>" + String(Chocolate_Milkshake_count) + "</td><td>" + String(Chocolate_Milkshake_count * 40) + "</td></tr>";
    html += "<tr><td>Strawberry</td><td>" + String(Strawberry_Milkshake_count) + "</td><td>" + String(Strawberry_Milkshake_count * 40) + "</td></tr>";
    html += "<tr><td>Butterscotch</td><td>" + String(Butterscotch_Milkshake_count) + "</td><td>" + String(Butterscotch_Milkshake_count * 40) + "</td></tr>";
    html += "<tr><td>Anjeer</td><td>" + String(Anjeer_Milkshake_count) + "</td><td>" + String(Anjeer_Milkshake_count * 80) + "</td></tr>";
    html += "<tr><td>Khajoor</td><td>" + String(Khajoor_Milkshake_count) + "</td><td>" + String(Khajoor_Milkshake_count * 40) + "</td></tr>";

    int totalDrinks = Strawberry_Milkshake_count+Butterscotch_Milkshake_count+Anjeer_Milkshake_count+Khajoor_Milkshake_count+ Lime_count + Dry_Fruits_Milkshake_count+ Mixed_Fruit_Milkshake_count+Banana_Lassi_count+Chocolate_Milkshake_count +Mixed_Fruit_count + Lime_count +Kharbooza_count + Pinapple_count + Mosambi_count + Mango_count + Chikoo_count + Papaya_count + WaterMelon_count + Grapes_count + Banana_count;
    int totalCost = (Mixed_Fruit_count + Pinapple_count + Mosambi_count + Mango_count + Chikoo_count + Papaya_count + WaterMelon_count + Grapes_count + Banana_count + Kharbooza_count)*10 + Lime_count*limePrice + (Mixed_Fruit_Milkshake_count + Banana_Lassi_count + Chocolate_Milkshake_count + Strawberry_Milkshake_count + Butterscotch_Milkshake_count + Khajoor_Milkshake_count) * 40 + Anjeer_Milkshake_count * 80 + Dry_Fruits_Milkshake_count * 100;
    html += "<tr><td>Total Drinks</td><td>" + String(totalDrinks) + "</td><td>" + String(totalCost) + "</td></tr>";

    // Profit/Loss for each item and total
    html += "</table><h2>Profit/Loss</h2><table><tr><th>Juice</th><th>Investment (Rs)</th><th>Profit/Loss (Rs)</th></tr>";
    html += "<tr><td>Pinapple</td><td>" + String(Pinapple_investment) + "</td><td>" + String((Pinapple_count * 10) - Pinapple_investment) + "</td></tr>";
    html += "<tr><td>Mosambi</td><td>" + String(Mosambi_investment) + "</td><td>" + String((Mosambi_count * 10) - Mosambi_investment) + "</td></tr>";
    html += "<tr><td>Mango</td><td>" + String(Mango_investment) + "</td><td>" + String((Mango_count * 10) - Mango_investment) + "</td></tr>";
    html += "<tr><td>Chikoo</td><td>" + String(Chikoo_investment) + "</td><td>" + String((Chikoo_count * 10) - Chikoo_investment) + "</td></tr>";
    html += "<tr><td>Papaya</td><td>" + String(Papaya_investment) + "</td><td>" + String((Papaya_count * 10) - Papaya_investment) + "</td></tr>";
    html += "<tr><td>WaterMelon</td><td>" + String(WaterMelon_investment) + "</td><td>" + String((WaterMelon_count * 10) - WaterMelon_investment) + "</td></tr>";
    html += "<tr><td>Grapes</td><td>" + String(Grapes_investment) + "</td><td>" + String((Grapes_count * 10) - Grapes_investment) + "</td></tr>";
    html += "<tr><td>Banana</td><td>" + String(Banana_investment) + "</td><td>" + String((Banana_count * 10) - Banana_investment) + "</td></tr>";
    html += "<tr><td>Kharbooza</td><td>" + String(Kharbooza_investment) + "</td><td>" + String((Kharbooza_count * 10) - Kharbooza_investment) + "</td></tr>";

    float totalInvestment = Others + Kharbooza_investment + Pinapple_investment + Mosambi_investment + Mango_investment + Chikoo_investment + Papaya_investment + WaterMelon_investment + Grapes_investment + Banana_investment;
    float totalProfitLoss = (totalCost) - totalInvestment;
    html += "<tr><td>Total</td><td>" + String(totalInvestment) + "</td><td>" + String(totalProfitLoss) + "</td></tr>";
    
    html += "</table><form action=\"/reset\" method=\"GET\"><button type=\"submit\">Reset</button></form>";
    html += "<form action=\"/investment\" method=\"GET\"><h2>Investment Input</h2><label for=\"item\">Item:</label><select id=\"item\" name=\"item\"><option value=\"Others\">Others</option><option value=\"Pinapple\">Pinapple</option><option value=\"Kharbooza\">Kharbooza</option><option value=\"Mosambi\">Mosambi</option><option value=\"Mango\">Mango</option><option value=\"Chikoo\">Chikoo</option><option value=\"Papaya\">Papaya</option><option value=\"WaterMelon\">WaterMelon</option><option value=\"Grapes\">Grapes</option><option value=\"Banana\">Banana</option></select><label for=\"price\">Price/kg:</label><input type=\"number\" id=\"price\" name=\"price\" required><label for=\"quantity\">Quantity (kgs):</label><input type=\"number\" id=\"quantity\" name=\"quantity\" required><button type=\"submit\">Submit</button></form>";
    html += "<form action=\"/setLimePrice\" method=\"GET\"><h2>Lime Price</h2><label for=\"limePrice\">Price:</label><input type=\"number\" id=\"limePrice\" name=\"limePrice\" required><button type=\"submit\">Submit</button></form>";
  //add the others option here
html += "<h2>Sales Graph</h2><canvas id=\"salesChart\"></canvas>";
html += "<script>let ctx=document.getElementById('salesChart').getContext('2d');";
html += "let chart=new Chart(ctx,{type:'line',data:{labels:['5am','6am','7am','8am','9am','10am','11am','12pm','1pm','2pm','3pm','4pm','5pm','6pm','7pm','8pm','9pm','10pm','11pm','12am','1am'],datasets:[";
html += "{label:'Mixed Fruit',data:[" + String(juiceSales[0]) + "],borderColor:'rgba(255, 99, 132, 1)',fill:false},";
html += "{label:'Pinapple',data:[" + String(juiceSales[1]) + "],borderColor:'rgba(54, 162, 235, 1)',fill:false},";
html += "{label:'Mosambi',data:[" + String(juiceSales[2]) + "],borderColor:'rgba(255, 206, 86, 1)',fill:false},";
html += "{label:'Mango',data:[" + String(juiceSales[3]) + "],borderColor:'rgba(75, 192, 192, 1)',fill:false},";
html += "{label:'Chikoo',data:[" + String(juiceSales[4]) + "],borderColor:'rgba(153, 102, 255, 1)',fill:false},";
html += "{label:'Papaya',data:[" + String(juiceSales[5]) + "],borderColor:'rgba(255, 159, 64, 1)',fill:false},";
html += "{label:'WaterMelon',data:[" + String(juiceSales[6]) + "],borderColor:'rgba(201, 203, 207, 1)',fill:false},";
html += "{label:'Grapes',data:[" + String(juiceSales[7]) + "],borderColor:'rgba(102, 255, 51, 1)',fill:false},";
html += "{label:'Banana',data:[" + String(juiceSales[8]) + "],borderColor:'rgba(255, 128, 0, 1)',fill:false},";
html += "{label:'Kharbooza',data:[" + String(juiceSales[9]) + "],borderColor:'rgba(0, 204, 102, 1)',fill:false},";
html += "{label:'Anar',data:[" + String(juiceSales[10]) + "],borderColor:'rgba(204, 0, 204, 1)',fill:false},";
html += "{label:'Lime',data:[" + String(juiceSales[11]) + "],borderColor:'rgba(255, 102, 102, 1)',fill:false},";
html += "{label:'MixFruit Milkshake',data:[" + String(milkshakeSales[0]) + "],borderColor:'rgba(153, 153, 255, 1)',fill:false},";
html += "{label:'Banana Lassi',data:[" + String(milkshakeSales[1]) + "],borderColor:'rgba(255, 255, 102, 1)',fill:false},";
html += "{label:'Chocolate Milkshake',data:[" + String(milkshakeSales[2]) + "],borderColor:'rgba(102, 51, 0, 1)',fill:false},";
html += "{label:'Strawberry Milkshake',data:[" + String(milkshakeSales[3]) + "],borderColor:'rgba(255, 99, 132, 1)',fill:false},";
html += "{label:'ButterScotch Milkshake',data:[" + String(milkshakeSales[4]) + "],borderColor:'rgba(255, 159, 64, 1)',fill:false},";
html += "{label:'Anjeer Milkshake',data:[" + String(milkshakeSales[5]) + "],borderColor:'rgba(153, 102, 51, 1)',fill:false},";
html += "{label:'Khajoor Milkshake',data:[" + String(milkshakeSales[6]) + "],borderColor:'rgba(102, 204, 255, 1)',fill:false},";
html += "{label:'Dry-Fruit Milkshake',data:[" + String(milkshakeSales[7]) + "],borderColor:'rgba(255, 204, 102, 1)',fill:false}]},";
html += "options:{layout:{padding:{top:10,bottom:10,left:10,right:10}},scales:{x:{title:{display:true,text:'Time (Hours)'}},y:{title:{display:true,text:'Money (Rs 100)'}}}}});</script>";

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
  Banana_Lassi_count = 0;
  Mixed_Fruit_Milkshake_count = 0;
  Dry_Fruits_Milkshake_count = 0;
  Anjeer_Milkshake_count = 0;
  Anar_count = 0;
  Lime_count = 0;
  Butterscotch_Milkshake_count = 0;
  Strawberry_Milkshake_count = 0;
  Khajoor_Milkshake_count = 0;

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

  if (item == "Pinapple") Pinapple_investment += investment;
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

void handleSetLimePrice() {
  limePrice = server.arg("limePrice").toInt();
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}
