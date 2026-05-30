//#include <Arduino.h>
//#include <WiFi.h>
//#include <ESPAsyncWebServer.h>
//#include <AsyncTCP.h>
//#include "SPIFFS.h"
//#include "time.h"
//#include "LiquidCrystal_I2C.h"
//#include <ESP32Servo.h>
//#include <HTTPClient.h>
//#include <Keypad.h>
//#include "ServoController.h"
//#include <HTTPUpdate.h>
//#include <WiFiClientSecure.h>
//#include "Buzzer.h"
//#include "KeypadController.h"
//#include "TimeManager.h"
//#include "DisplayManager.h"
//#include "mbedtls/sha256.h"
//
//using ServoImpl = Servo;
//
//AsyncWebServer server(80);
//const char login_html[] PROGMEM = R"rawliteral(
//<!DOCTYPE html>
//<html lang="hy">
//<head>
//<meta charset="UTF-8">
//<meta name="viewport" content="width=device-width, initial-scale=1.0">
//<title>Մուտք / Գրանցում</title>
//<style>
//body {
//    font-family: Arial, sans-serif;
//    display: flex;
//    justify-content: center;
//    align-items: center;
//    height: 100vh;
//    background: #f0f2f5;
//    margin: 0;
//}
//.box {
//    background: white;
//    padding: 30px;
//    border-radius: 15px;
//    box-shadow: 0 0 15px rgba(0,0,0,0.15);
//    width: 320px;
//    text-align: center;
//}
//.tabs {
//    display: flex;
//    justify-content: space-around;
//    margin-bottom: 20px;
//    border-bottom: 2px solid #ccc;
//}
//.tab {
//    padding: 10px;
//    cursor: pointer;
//    font-weight: bold;
//    color: #666;
//    width: 50%;
//    display: block;
//}
//.tab.active {
//    color: #28a745;
//    border-bottom: 3px solid #28a745;
//}
//input {
//    width: 90%;
//    padding: 12px;
//    margin: 10px 0;
//    border-radius: 8px;
//    border: 1px solid #ccc;
//    font-size: 14px;
//}
//button {
//    width: 98%;
//    padding: 12px;
//    background: #28a745;
//    color: white;
//    border: none;
//    border-radius: 8px;
//    font-size: 16px;
//    cursor: pointer;
//    margin-top: 10px;
//}
//button:hover {
//    background: #218838;
//}
//.form-panel {
//    display: none;
//}
//.form-panel.active {
//    display: block;
//}
//</style>
//</head>
//<body onload="checkRegistration()">
//
//<div class="box">
//    <div class="tabs">
//        <div class="tab" id="tab-login" onclick="switchTab('login')">Մուտք</div>
//        <div class="tab" id="tab-reg" onclick="switchTab('reg')">Գրանցում</div>
//    </div>
//
//    <div id="panel-login" class="form-panel">
//        <h2>Մուտք Գործել</h2>
//        <input type="text" id="login-user" placeholder="Մուտքանուն">
//        <input type="password" id="login-pass" placeholder="Գաղտնաբառ">
//        <button onclick="login()">Մուտք</button>
//    </div>
//
//    <div id="panel-reg" class="form-panel">
//        <h2>Ստեղծել Հաշիվ</h2>
//        <input type="text" id="reg-user" placeholder="Նոր Մուտքանուն">
//        <input type="password" id="reg-pass" placeholder="Նոր Գաղտնաբառ">
//        <button onclick="register()" style="background: #007bff;">Գրանցվել</button>
//    </div>
//</div>
//
//<script>
//function checkRegistration() {
//    fetch('/is_registered')
//    .then(response => response.text())
//    .then(data => {
//        if(data === "YES") {
//            document.getElementById('tab-reg').style.display = 'none';
//            document.getElementById('tab-login').style.width = '100%';
//            switchTab('login');
//        } else {
//            document.getElementById('tab-login').style.display = 'none';
//            document.getElementById('tab-reg').style.width = '100%';
//            switchTab('reg');
//        }
//    });
//}
//
//function switchTab(type) {
//    if(document.getElementById('tab-reg').style.display === 'none' && type === 'reg') return;
//    if(document.getElementById('tab-login').style.display === 'none' && type === 'login') return;
//
//    document.getElementById('tab-login').classList.remove('active');
//    document.getElementById('tab-reg').classList.remove('active');
//    document.getElementById('panel-login').classList.remove('active');
//    document.getElementById('panel-reg').classList.remove('active');
//
//    if(type === 'login') {
//        document.getElementById('tab-login').classList.add('active');
//        document.getElementById('panel-login').classList.add('active');
//    } else {
//        document.getElementById('tab-reg').classList.add('active');
//        document.getElementById('panel-reg').classList.add('active');
//    }
//}
//
//function login() {
//    let user = document.getElementById("login-user").value;
//    let pass = document.getElementById("login-pass").value;
//    
//    if(!user || !pass) { alert("Լրացրեք բոլոր դաշտերը"); return; }
//
//    fetch(`/login?user=${encodeURIComponent(user)}&pass=${encodeURIComponent(pass)}`)
//    .then(response => response.text())
//    .then(data => {
//        if(data === "OK") {
//            window.location.href = "/index";
//        } else {
//            alert("Սխալ մուտքանուն կամ գաղտնաբառ");
//        }
//    });
//}
//
//function register() {
//    let user = document.getElementById("reg-user").value;
//    let pass = document.getElementById("reg-pass").value;
//
//    if(!user || !pass) { alert("Լրացրեք բոլոր դաշտերը"); return; }
//
//    fetch(`/register?user=${encodeURIComponent(user)}&pass=${encodeURIComponent(pass)}`, { method: 'POST' })
//    .then(response => response.text())
//    .then(data => {
//        if(data === "REG_OK") {
//            alert("Գրանցումը հաջողվեց: Հիմա կարող եք մուտք գործել:");
//            document.getElementById('tab-login').style.display = 'block';
//            document.getElementById('tab-login').style.width = '50%';
//            document.getElementById('tab-reg').style.display = 'none';
//            document.getElementById('tab-login').style.width = '100%';
//            switchTab('login');
//            document.getElementById("login-user").value = user;
//        } else {
//            alert("Գրանցման սխալ:");
//        }
//    });
//}
//</script>
//
//</body>
//</html>
//)rawliteral";
//
//// PINS
//static const int buzzerPin = 18;
//static const int servoPin = 15;
//static const int buttonPin = 4; 
//
//const char* PARAM_INPUT_1 = "ssid";
//const char* PARAM_INPUT_2 = "pass";
//const char* PARAM_INPUT_3 = "ip";
//const char* PARAM_INPUT_4 = "gateway";
//const char* PARAM_INPUT_5 = "chatID";
//const char* PARAM_MED_INDEX = "medIndex";
//
//String ssid;
//String pass;
//String ip;
//String gateway;
//
//const char* ssidPath = "/ssid.txt";
//const char* passPath = "/pass.txt";
//const char* ipPath = "/ip.txt";
//const char* gatewayPath = "/gateway.txt";
//const char* chatIDPath = "/chatid.txt";
//
//IPAddress localIP;
//IPAddress localGateway;
//IPAddress subnet(255, 255, 0, 0);
//
//unsigned long previousMillis = 0;
//const long interval = 10000;
//
//String ledState;
//
//static const long gmtOffset_sec = 4 * 3600;
//static const int daylightOffset_sec = 0;
//static const char* ntpServer = "pool.ntp.org";
//
//bool timeSynced = false;
//unsigned long lastTimeSyncAttemptMs = 0;
//
//static const int MAX_MEDS = 7;
//static const int MAX_TIMES_PER_MED = 12;
//int medCount = 0;
//String medNames[MAX_MEDS];
//String medTimes[MAX_MEDS];
//int medTimeCount[MAX_MEDS];
//
//int medYears[MAX_MEDS][MAX_TIMES_PER_MED];
//int medMonths[MAX_MEDS][MAX_TIMES_PER_MED];
//int medDays[MAX_MEDS][MAX_TIMES_PER_MED];
//int medHours[MAX_MEDS][MAX_TIMES_PER_MED];
//int medMinutes[MAX_MEDS][MAX_TIMES_PER_MED];
//
//int medCounts[MAX_MEDS] = {0, 0, 0, 0, 0, 0, 0}; 
//
//TimeManager timeManager(
//  medTimeCount,
//  medYears, medMonths, medDays,
//  medHours, medMinutes,
//  medNames,
//  medTimes,
//  &medCount
//);
//
//bool alarmActive = false;
//bool alarmSilencedByButton = false;
//unsigned long alarmStopAtMs = 0;
//
//int lastAlarmYear = -1;
//int lastAlarmMonth = -1;
//int lastAlarmDay = -1;
//int lastAlarmHour = -1;
//int lastAlarmMinute = -1;
//
//int activeAlarmMedIndex = -1;
//unsigned long alarmStartTimeMs = 0;
//
//String botToken = "8977429034:AAEJb8E5l69OoPCsBOmR6zzIH3XacCoWIrQ";
//String chatID;
//
//String savedUsername = "";
//String savedPassword = "";
//bool isLoggedIn = false;
//int dPressCount = 0;
//unsigned long lastDPressTime = 0;
//
//// OTA
//const char* firmwareVersion = "1.3";
//String versionURL = "https://raw.githubusercontent.com/ManeHovhannisyan13/ESP32_OTA/main/version.txt";
//String firmwareURL = "https://raw.githubusercontent.com/ManeHovhannisyan13/ESP32_OTA/main/firmware.bin";
//
//// LOGIN
//const char* userPath = "/username.txt";
//const char* passwordPath = "/password.txt";
//const char* medsPath = "/meds.txt";
//
//// OBJ
//LiquidCrystal_I2C lcd(0x27, 16, 2);
//Buzzer buzzerControll;
//ServoController servoCtrl;
//KeypadController keypadCtrl;
//DisplayManager displayManager(&lcd, &timeManager, medNames);
//
//int ledPin1 = 2;
//int ledPin2 = 4;
//
//unsigned long dButtonPressStartMs = 0;
//bool dButtonIsPressed = false;
//
//// ✅ ANALYTICS FUNCTION
//String analyticsURL = "https://script.google.com/macros/s/AKfycbxTKi5dCg9P0m4u9q3rGK6fXFEgB4b-CxMKDOw57mfNvUELvahtkS83EqXsgJZ-6XVBHA/exec";
//String deviceID = "HISHIR_01";
//
//void trackEvent(
//    String eventName,
//    String medicineName = "",
//    int boxNumber = -1,
//    String status = "success",
//    String value = "",
//    String errorMessage = ""
//) {
//    if (WiFi.status() != WL_CONNECTED) return;
//
//    HTTPClient http;
//    http.begin(analyticsURL);
//    http.addHeader("Content-Type", "application/json");
//
//    String json = "{";
//    json += "\"device_id\":\"" + deviceID + "\",";
//    json += "\"username\":\"" + savedUsername + "\",";
//    json += "\"event_name\":\"" + eventName + "\",";
//    json += "\"medicine_name\":\"" + medicineName + "\",";
//    json += "\"box_number\":\"" + String(boxNumber) + "\",";
//    json += "\"status\":\"" + status + "\",";
//    json += "\"value\":\"" + value + "\",";
//    json += "\"error_message\":\"" + errorMessage + "\",";
//    json += "\"firmware_version\":\"" + String(firmwareVersion) + "\"";
//    json += "}";
//
//    int code = http.POST(json);
//
//    Serial.println("=== ANALYTICS EVENT ===");
//    Serial.println(json);
//    Serial.println("Response: " + String(code));
//
//    http.end();
//}
//
//String urlEncode(String str) {
//    String encodedString = "";
//    char c;
//    for (int i = 0; i < str.length(); i++) {
//        c = str.charAt(i);
//        if (isalnum(c)) {
//            encodedString += c;
//        } else {
//            char code0 = (c >> 4) & 0xf;
//            char code1 = c & 0xf;
//            encodedString += '%';
//            encodedString += (char)(code0 > 9 ? code0 - 10 + 'A' : code0 + '0');
//            encodedString += (char)(code1 > 9 ? code1 - 10 + 'A' : code1 + '0');
//        }
//    }
//    return encodedString;
//}
//
//void sendTelegramMessage(String message) {
//  if (WiFi.status() != WL_CONNECTED || chatID == "") return;
//  
//  WiFiClientSecure client;
//  client.setInsecure();
//  
//  HTTPClient http;
//  String url = "https://api.telegram.org/bot" + botToken + "/sendMessage?chat_id=" + chatID + "&text=" + urlEncode(message);
//  
//  http.begin(client, url);
//  int httpCode = http.GET();
//  if (httpCode > 0) {
//    Serial.println("Telegram message sent successfully");
//    trackEvent("telegram_notification_sent", "", -1, "success");
//  } else {
//    Serial.println("Error sending Telegram message");
//    trackEvent("telegram_notification_failed", "", -1, "fail", "", String(httpCode));
//  }
//  http.end();
//}
//
//static bool shouldBuzzNow(int yNow, int monNow, int dNow, int hNow, int mNow) {
//  if (medCount <= 0) return false;
//  for (int i = 0; i < medCount; i++) {
//    for (int t = 0; t < medTimeCount[i]; t++) {
//      if (medYears[i][t] == yNow && medMonths[i][t] == monNow && 
//          medDays[i][t] == dNow && medHours[i][t] == hNow && 
//          medMinutes[i][t] == mNow) {
//        return true;
//      }
//    }
//  }
//  return false;
//}
//
//static int findMatchingMedIndex(int yNow, int monNow, int dNow, int hNow, int mNow) {
//  for (int i = 0; i < medCount; i++) {
//    for (int t = 0; t < medTimeCount[i]; t++) {
//      if (medYears[i][t] == yNow && medMonths[i][t] == monNow && 
//          medDays[i][t] == dNow && medHours[i][t] == hNow && 
//          medMinutes[i][t] == mNow) return i;
//    }
//  }
//  return -1;
//}
//
//void setup() {
//  Serial.begin(115200);
//
//  initSPIFFS();
//  loadMedicines();
//  
//  buzzerControll.setPin(buzzerPin);
//  buzzerControll.init();
//  pinMode(buttonPin, INPUT_PULLUP);
//  pinMode(ledPin1, OUTPUT);
//  pinMode(ledPin2, OUTPUT);
//
//  lcd.init();
//  lcd.backlight();
//  displayManager.clearSafe(); 
//
//  servoCtrl.begin();
//  
//  ssid = readFile(SPIFFS, ssidPath);
//  pass = readFile(SPIFFS, passPath);
//  ip = readFile(SPIFFS, ipPath);
//  gateway = readFile(SPIFFS, gatewayPath);
//  chatID = readFile(SPIFFS, chatIDPath);
//  chatID.trim();
//
//  savedUsername = readFile(SPIFFS, userPath);
//  savedPassword = readFile(SPIFFS, passwordPath);
//  savedUsername.trim();
//  savedPassword.trim();
//
//  WiFi.mode(WIFI_AP_STA);
//  WiFi.softAP("ՀԻՇԻՐ", NULL); 
//  Serial.print("AP IP address: ");
//  Serial.println(WiFi.softAPIP());
//
//  trackEvent("device_started", "", -1, "success", "boot");
//
//  if(ssid != "") {
//    Serial.println("Saved SSID: " + ssid);
//    Serial.println("Saved PASS: " + pass);
//
//    WiFi.begin(ssid.c_str(), pass.c_str());
//    Serial.print("Connecting to WiFi");
//
//    int attempts = 0;
//    while(WiFi.status() != WL_CONNECTED && attempts < 30){
//        delay(500);
//        Serial.print(".");
//        attempts++;
//    }
//
//    if(WiFi.status() == WL_CONNECTED){
//        Serial.println("\nConnected!");
//        Serial.print("IP: ");
//        Serial.println(WiFi.localIP());
//
//        trackEvent("wifi_connected", "", -1, "success", WiFi.localIP().toString());
//
//        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//        checkForUpdate();
//    } else {
//        Serial.println("\nFAILED TO CONNECT");
//        Serial.println("Status: " + String(WiFi.status()));
//    }
//  }
//
//  // === ROUTES ===
//  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//    if (WiFi.status() == WL_CONNECTED) {
//      request->send_P(200, "text/html", login_html);
//    } else {
//      request->send(SPIFFS, "/wifimanager.html", "text/html; charset=utf-8");
//    }
//  });
//
//  server.on("/is_registered", HTTP_GET, [](AsyncWebServerRequest *request) {
//    if (savedUsername != "") {
//      request->send(200, "text/plain", "YES");
//    } else {
//      request->send(200, "text/plain", "NO");
//    }
//  });
//
//  server.on("/login", HTTP_GET, [](AsyncWebServerRequest *request) {
//    String user = request->hasParam("user") ? request->getParam("user")->value() : "";
//    String pass = request->hasParam("pass") ? request->getParam("pass")->value() : "";
//    user.trim(); pass.trim();
//
//    String hashedInput = sha256(pass);
//
//    if(user == savedUsername && hashedInput == savedPassword){
//      isLoggedIn = true;
//      request->send(200, "text/plain", "OK");
//      trackEvent("user_login", "", -1, "success");
//    } else {
//      request->send(200, "text/plain", "ERROR");
//      trackEvent("login_failed", "", -1, "fail", "", "wrong_credentials");
//    }
//  });
//
//  server.on("/register", HTTP_POST, [](AsyncWebServerRequest *request) {
//    String newUser = request->hasParam("user") ? request->getParam("user")->value() : "";
//    String newPass = request->hasParam("pass") ? request->getParam("pass")->value() : "";
//    newUser.trim(); newPass.trim();
//
//    if (newUser != "" && newPass != "") {
//      writeFile(SPIFFS, userPath, newUser.c_str());
//      String hashedPass = sha256(newPass);
//      writeFile(SPIFFS, passwordPath, hashedPass.c_str());
//      savedPassword = hashedPass;
//      savedUsername = newUser;
//      request->send(200, "text/plain", "REG_OK");
//      trackEvent("user_registered", "", -1, "success");
//    } else {
//      request->send(400, "text/plain", "REG_FAILED");
//    }
//  });
//
//  server.on("/index", HTTP_GET, [](AsyncWebServerRequest *request) {
//    if(!isLoggedIn){ request->redirect("/"); return; }
//    request->send(SPIFFS, "/index.html", "text/html; charset=utf-8");
//  });
//
//  server.serveStatic("/", SPIFFS, "/");
//
//  server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request) {
//    int params = request->params();
//    for(int i=0; i<params; i++){
//      const AsyncWebParameter* p = request->getParam(i);
//      if(p->isPost()){
//        if (p->name() == PARAM_INPUT_1) { ssid = p->value().c_str(); writeFile(SPIFFS, ssidPath, ssid.c_str()); }
//        if (p->name() == PARAM_INPUT_2) { pass = p->value().c_str(); writeFile(SPIFFS, passPath, pass.c_str()); }
//        if (p->name() == PARAM_INPUT_3) { ip = p->value().c_str(); writeFile(SPIFFS, ipPath, ip.c_str()); }
//        if (p->name() == PARAM_INPUT_4) { gateway = p->value().c_str(); writeFile(SPIFFS, gatewayPath, gateway.c_str()); }
//        if (p->name() == PARAM_INPUT_5) { chatID = p->value().c_str(); chatID.trim(); writeFile(SPIFFS, chatIDPath, chatID.c_str()); }
//      }
//    }
//    request->send(200, "text/plain", "Տվյալները պահպանվեցին։ Սարքը վերագործարկվում է...");
//    delay(2000);
//    ESP.restart();
//  });
//
//  server.on("/meds", HTTP_POST, [](AsyncWebServerRequest *request) {
//    int receivedMedCount = request->hasParam("medCount", true) ? request->getParam("medCount", true)->value().toInt() : 0;
//    if (receivedMedCount < 0) receivedMedCount = 0;
//    if (receivedMedCount > MAX_MEDS) receivedMedCount = MAX_MEDS;
//    medCount = receivedMedCount;
//    for (int i = 0; i < MAX_MEDS; i++) { medNames[i] = ""; medTimes[i] = ""; medTimeCount[i] = 0; }
//    for (int i = 1; i <= medCount; i++) {
//      if (request->hasParam("medName_" + String(i), true)) medNames[i - 1] = request->getParam("medName_" + String(i), true)->value();
//      if (request->hasParam("times_" + String(i), true)) medTimes[i - 1] = request->getParam("times_" + String(i), true)->value();
//    }
//    for (int i = 0; i < medCount; i++) { medTimeCount[i] = timeManager.splitAndStoreTimes(medTimes[i], i); }
//    saveMedicines();
//    request->send(200, "text/plain", "OK");
//    trackEvent("medicine_added", "", -1, "success", "medCount=" + String(medCount));
//  });
//
//  server.on("/medOne", HTTP_POST, [](AsyncWebServerRequest *request) {
//    if (!request->hasParam(PARAM_MED_INDEX, true)) { request->send(400, "text/plain", "Missing medIndex"); return; }
//    int idx1 = request->getParam(PARAM_MED_INDEX, true)->value().toInt();
//    if (idx1 < 1 || idx1 > MAX_MEDS) { request->send(400, "text/plain", "Invalid medIndex"); return; }
//    
//    String name = request->hasParam("medName_1", true) ? request->getParam("medName_1", true)->value() : "";
//    String times = request->hasParam("times_1", true) ? request->getParam("times_1", true)->value() : "";
//    
//    int count = request->hasParam("count_1", true) ? request->getParam("count_1", true)->value().toInt() : 0;
//    medCounts[idx1 - 1] = count; 
//
//    timeManager.updateSingleMedicine(idx1 - 1, name, times);
//    saveMedicines();
//    request->send(200, "text/plain", "OK");
//    trackEvent("medicine_updated", name, idx1, "success", "count=" + String(count));
//  });
//
//  server.on("/fill", HTTP_GET, [](AsyncWebServerRequest *request) {
//    if (alarmActive) { request->send(409, "text/plain", "Alarm active"); return; }
//    if (!request->hasParam("box")) { request->send(400, "text/plain", "Missing box"); return; }
//    int box = request->getParam("box")->value().toInt();
//    if (box < 1) box = 1; if (box > MAX_MEDS) box = MAX_MEDS;
//    servoCtrl.fillBox(box);
//    request->send(200, "text/plain", "Filling box " + String(box));
//    trackEvent("box_opened", "", box, "success", "manual_fill");
//  });
//
//  server.on("/filled", HTTP_POST, [](AsyncWebServerRequest *request) {
//    if (alarmActive) { request->send(409, "text/plain", "Alarm active"); return; }
//    servoCtrl.rest();
//    request->send(200, "text/plain", "OK");
//  });
//
//  server.begin();
//}
//
//void loop() {
//  servoCtrl.tick(); 
//
//  char key = keypadCtrl.getKey();
//
//  // 'D' կոճակի տրամաբանություն՝ 5 անգամ սեղմելիս հաշվի ջնջում և ռեսեթ
//  if (key == '7 ') {
//    unsigned long now = millis();
//    if (now - lastDPressTime > 1500) {
//      dPressCount = 0;
//    }
//    dPressCount++;
//    lastDPressTime = now;
//    Serial.printf("'D' կոճակը սեղմվեց %d անգամ\n", dPressCount);
//
//    if (dPressCount >= 5) {
//      Serial.println("Ռեսեթ 'D' կոճակով... Տվյալները ջնջվում են:");
//      
//      SPIFFS.remove(userPath);
//      SPIFFS.remove(passwordPath);
//      
//      savedUsername = "";
//      savedPassword = "";
//      isLoggedIn = false;
//
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("Reset Success!");
//      delay(2000);
//      
//      ESP.restart();
//    }
//  }
//
//  if (key != '\0' && key != 'D') {
//    dPressCount = 0;
//  }
//
//  struct tm timeinfo;
//  if (!getLocalTime(&timeinfo)) {
//    delay(10); 
//    return;
//  }
//
//  int currentYear = timeinfo.tm_year + 1900;
//  int currentMonth = timeinfo.tm_mon + 1;
//  int currentDay = timeinfo.tm_mday;
//  int currentHour = timeinfo.tm_hour;
//  int currentMinute = timeinfo.tm_min;
//
//  if (shouldBuzzNow(currentYear, currentMonth, currentDay, currentHour, currentMinute)) {
//    if (!alarmActive && (currentYear != lastAlarmYear || currentMonth != lastAlarmMonth || 
//                         currentDay != lastAlarmDay || currentHour != lastAlarmHour || 
//                         currentMinute != lastAlarmMinute)) {
//      alarmActive = true;
//      alarmSilencedByButton = false; 
//      alarmStartTimeMs = millis();
//      
//      lastAlarmYear = currentYear;
//      lastAlarmMonth = currentMonth;
//      lastAlarmDay = currentDay;
//      lastAlarmHour = currentHour;
//      lastAlarmMinute = currentMinute;
//      
//      activeAlarmMedIndex = findMatchingMedIndex(currentYear, currentMonth, currentDay, currentHour, currentMinute);
//      
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("Take Medicine!");
//      
//      String currentMedName = "Անհայտ դեղ";
//      if(activeAlarmMedIndex != -1) {
//        currentMedName = medNames[activeAlarmMedIndex];
//        lcd.setCursor(0, 1);
//        lcd.print(currentMedName);
//        
//        servoCtrl.fillBox(activeAlarmMedIndex + 1);
//      }
//
//      if (activeAlarmMedIndex >= 0) {
//        trackEvent("medicine_reminder_triggered", currentMedName, activeAlarmMedIndex + 1, "success", "alarm_start");
//      }
//
//      String startMsg = "🔔 Դեղի հիշեցում!\n";
//      startMsg += "💊 Ժամն է ընդունելու հետևյալ դեղը՝ " + currentMedName + "\n";
//      startMsg += "📦 Տուփ՝ #" + String(activeAlarmMedIndex + 1) + "\n";
//      if (activeAlarmMedIndex != -1) {
//        startMsg += "🔢 Այս պահին տուփում առկա է՝ " + String(medCounts[activeAlarmMedIndex]) + " հատ";
//      }
//      
//      sendTelegramMessage(startMsg);
//    }
//  }
//
//  if (alarmActive) {
//    unsigned long elapsedAlarmMs = millis() - alarmStartTimeMs;
//
//    if (elapsedAlarmMs > 90000) {
//      alarmActive = false;
//      alarmSilencedByButton = false;
//      buzzerControll.off();
//      digitalWrite(ledPin1, LOW);  
//      digitalWrite(ledPin2, LOW);
//      servoCtrl.rest();
//
//      if (activeAlarmMedIndex >= 0) {
//        trackEvent("medicine_missed", medNames[activeAlarmMedIndex], activeAlarmMedIndex + 1, "fail", "timeout");
//      }
//
//      String alertMsg = "⚠️ ՈՒՇԱԴՐՈՒԹՅՈՒՆ։ Դեղը ՉԻ ընդունվել։\nԴեղ՝ ";
//      if (activeAlarmMedIndex != -1) {
//        alertMsg += medNames[activeAlarmMedIndex] + "\nՏուփ՝ #" + String(activeAlarmMedIndex + 1);
//        alertMsg += "\nՄնացած քանակ՝ " + String(medCounts[activeAlarmMedIndex]) + " հատ";
//      }
//      sendTelegramMessage(alertMsg);
//      
//      lcd.clear();
//      displayManager.update();
//    }
//    else if (!alarmSilencedByButton) {
//      unsigned long cycleTimeMs = elapsedAlarmMs % 30000;
//
//      if (cycleTimeMs < 10000) {
//        if ((millis() / 500) % 2 == 0) {
//          buzzerControll.on();
//          digitalWrite(ledPin1, HIGH);
//          digitalWrite(ledPin2, LOW);
//        } else {
//          buzzerControll.off();
//          digitalWrite(ledPin1, LOW);
//          digitalWrite(ledPin2, HIGH);
//        }
//      } 
//      else {
//        buzzerControll.off(); 
//        
//        if ((millis() / 500) % 2 == 0) {
//          digitalWrite(ledPin1, HIGH);
//          digitalWrite(ledPin2, LOW);
//        } else {
//          digitalWrite(ledPin1, LOW);
//          digitalWrite(ledPin2, HIGH);
//        }
//      }
//    } 
//    else {
//      buzzerControll.off(); 
//      digitalWrite(ledPin1, LOW);
//      digitalWrite(ledPin2, LOW);
//    }
//    
//    // ✅ Բզզիչի անջատում '*' կոճակով (ըստ պահանջի)
//    if (key == '*') {
//      alarmActive = false;
//      alarmSilencedByButton = false;
//      servoCtrl.rest();
//    
//      if (activeAlarmMedIndex != -1) {
//          if (medCounts[activeAlarmMedIndex] > 0) {
//              medCounts[activeAlarmMedIndex]--;
//          }
//          
//          saveMedicines();
//
//          if (activeAlarmMedIndex >= 0) {
//            trackEvent("medicine_taken", medNames[activeAlarmMedIndex], activeAlarmMedIndex + 1, "success", "remaining=" + String(medCounts[activeAlarmMedIndex]));
//          }
//
//          if (medCounts[activeAlarmMedIndex] <= 3) {
//            trackEvent("medicine_low_quantity", medNames[activeAlarmMedIndex], activeAlarmMedIndex + 1, "warning", "remaining=" + String(medCounts[activeAlarmMedIndex]));
//          }
//
//          sendTelegramMessage("✅ Դեղը հաջողությամբ ընդունվեց: Մնաց " + String(medCounts[activeAlarmMedIndex]) + " հատ:");
//      }
//    
//      lcd.clear();
//      displayManager.update();
//    }
//  }
//}
