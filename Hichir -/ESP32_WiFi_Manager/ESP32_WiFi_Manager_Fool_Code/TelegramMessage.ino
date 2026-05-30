#include <WiFiClientSecure.h>

void sendMessage(String message) { 

  if (chatID.length() == 0) {
    Serial.println("Telegram: chatID not set");
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure client;
    client.setInsecure(); // SSL certificate check off

    HTTPClient http;

    message.replace(" ", "%20");
    
    String url = "https://api.telegram.org/bot" + botToken +
                 "/sendMessage?chat_id=" + chatID +
                 "&text=" + message;

    Serial.println(url);

    if (http.begin(client, url)) {

      int httpCode = http.GET();

      Serial.print("HTTP Code: ");
      Serial.println(httpCode);

      if (httpCode > 0) {
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.println("Request failed");
      }

      http.end();
    }
    else {
      Serial.println("HTTP begin failed");
    }

  } 
  else {
    Serial.println("WiFi not connected");
  }
}
