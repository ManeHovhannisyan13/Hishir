//Analytics file
//void sendAnalyticsEvent(
//  String eventName,
//  String medicineId,
//  String scheduleId,
//  String dataJson
//) {
//  if (WiFi.status() != WL_CONNECTED || analyticsURL == "") {
//    Serial.println("Analytics skipped: no WiFi or URL");
//    return;
//  }
//
//  HTTPClient http;
//  http.begin(analyticsURL);
//  http.addHeader("Content-Type", "application/json");
//
//  String payload = "{";
//  payload += "\"event_name\":\"" + eventName + "\",";
//  payload += "\"device_id\":\"" + deviceID + "\",";
//  payload += "\"user_id\":\"" + userID + "\",";
//  payload += "\"medicine_id\":\"" + medicineId + "\",";
//  payload += "\"schedule_id\":\"" + scheduleId + "\",";
//  payload += "\"data\":" + dataJson;
//  payload += "}";
//
//  int httpCode = http.POST(payload);
//
//  Serial.print("Analytics event: ");
//  Serial.print(eventName);
//  Serial.print(" | HTTP: ");
//  Serial.println(httpCode);
//
//  http.end();
//}
