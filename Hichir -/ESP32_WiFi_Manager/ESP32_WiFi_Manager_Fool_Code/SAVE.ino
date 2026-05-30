void saveMedicines() {

  File file = SPIFFS.open(medsPath, FILE_WRITE);

  if(!file){
    Serial.println("Failed to open meds file for writing");
    return;
  }

  file.println(medCount);

  for(int i = 0; i < medCount; i++){

    file.println(medNames[i]);

    file.println(medCounts[i]);

    file.println(medTimeCount[i]);

    for(int t = 0; t < medTimeCount[i]; t++){

      String line =
        String(medYears[i][t]) + "," +
        String(medMonths[i][t]) + "," +
        String(medDays[i][t]) + "," +
        String(medHours[i][t]) + "," +
        String(medMinutes[i][t]);

      file.println(line);
    }
  }

  file.close();

  Serial.println("Medicines saved");
}
//———————————————————load————————————————
void loadMedicines() {

  File file = SPIFFS.open(medsPath);

  if(!file){
    Serial.println("No medicines file");
    return;
  }

  medCount = file.readStringUntil('\n').toInt();

  if(medCount > MAX_MEDS){
    medCount = MAX_MEDS;
  }

  for(int i = 0; i < medCount; i++){

    medNames[i] = file.readStringUntil('\n');
    medNames[i].trim();

    medCounts[i] = file.readStringUntil('\n').toInt();

    medTimeCount[i] = file.readStringUntil('\n').toInt();
    medTimes[i] = "";

    for(int t = 0; t < medTimeCount[i]; t++){

      String line = file.readStringUntil('\n');

      int values[5];
      int index = 0;

      while(line.length() > 0 && index < 5){

        int comma = line.indexOf(',');

        if(comma == -1){
          values[index++] = line.toInt();
          break;
        }

        values[index++] = line.substring(0, comma).toInt();

        line = line.substring(comma + 1);
      }

      medYears[i][t] = values[0];
      medMonths[i][t] = values[1];
      medDays[i][t] = values[2];
      medHours[i][t] = values[3];
      medMinutes[i][t] = values[4];
    }
  }

  file.close();

  Serial.println("Medicines loaded");
}
