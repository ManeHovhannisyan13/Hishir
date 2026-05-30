void checkForUpdate() {

  WiFiClientSecure client;
  client.setInsecure();
  client.setTimeout(15000);
  
  HTTPClient http;
  
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  
  Serial.println("Checking for firmware update...");

  http.begin(client, versionURL);

  int httpCode = http.GET();

  if (httpCode == 200) {

    String newVersion = http.getString();
    newVersion.trim();

    Serial.print("Current version: ");
    Serial.println(firmwareVersion); // Print version ----------------

    Serial.print("Available version: ");
    Serial.println(newVersion);

    //նայել
    newVersion.trim();
    //firmwareVersion.trim();
    
    if (newVersion != firmwareVersion) {

      Serial.println("New firmware found");

      displayManager.clearSafe();
      Serial.println("Updating...");
      Serial.println("Please wait");

      t_httpUpdate_return ret =
        httpUpdate.update(client, firmwareURL);

      switch (ret) {

        case HTTP_UPDATE_FAILED:

          Serial.printf("Update failed Error (%d): %s\n",
                        httpUpdate.getLastError(),
                        httpUpdate.getLastErrorString().c_str());

          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("No updates");
          break;

        case HTTP_UPDATE_OK:
          Serial.println("Update OK");
          break;
      }
    }
    else {
      Serial.println("Already latest version");
    }
  }
  else {
    Serial.println("Version check failed");
  }

  http.end();
}
