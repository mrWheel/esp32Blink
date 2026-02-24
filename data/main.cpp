/* simpel test program */

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

#ifndef LED_BUILTIN
  #define LED_BUILTIN 2
#endif

const char *progVersion = "1.1.0";

void listFiles(fs::FS &fileSystem, const char *directoryPath)
{
  File rootDirectory = fileSystem.open(directoryPath);

  if (!rootDirectory || !rootDirectory.isDirectory())
  {
    Serial.println("Kon root directory niet openen.");
    return;
  }

  File currentEntry = rootDirectory.openNextFile();
  if (!currentEntry)
  {
    Serial.println("Geen bestanden gevonden.");
  }

  while (currentEntry)
  {
    Serial.print(currentEntry.isDirectory() ? "DIR : " : "FILE: ");
    Serial.print(currentEntry.name());
    if (!currentEntry.isDirectory())
    {
      Serial.print("\tSIZE: ");
      Serial.println(currentEntry.size());
    }
    else
    {
      Serial.println();
    }
    currentEntry = rootDirectory.openNextFile();
  }
}

void printLittleFsUsage()
{
  size_t totalBytes = LittleFS.totalBytes();
  size_t usedBytes = LittleFS.usedBytes();
  float usedPercent = 0.0F;

  if (totalBytes > 0)
  {
    usedPercent = (static_cast<float>(usedBytes) * 100.0F) / static_cast<float>(totalBytes);
  }

  Serial.print("LittleFS total bytes: ");
  Serial.println(totalBytes);
  Serial.print("LittleFS used bytes: ");
  Serial.println(usedBytes);
  Serial.print("LittleFS usage: ");
  Serial.print(usedPercent, 2);
  Serial.println("%");
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1000);
  }

  Serial.print("Program version: ");
  Serial.println(progVersion);

  pinMode(LED_BUILTIN, OUTPUT);

  if (!LittleFS.begin(true))
  {
    Serial.println("LittleFS initialisatie mislukt.");
  }
  else
  {
    Serial.println("LittleFS initialisatie OK.");
    printLittleFsUsage();
    listFiles(LittleFS, "/");
  }

} // setup()

void loop()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  if (digitalRead(LED_BUILTIN) == HIGH)
  {
    Serial.println("LED pin is HIGH");
  }
  else
  {
    Serial.println("LED pin is LOW");
  }

  delay(2500);

} // loop()