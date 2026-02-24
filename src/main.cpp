//--- Simple test program (LED or NeoPixel selected via build_flags)

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

const char* PROG_VERSION = "1.0.0";
#ifdef USE_NEOPIXEL
  #include <Adafruit_NeoPixel.h>
#endif

const char* progVersion = "1.1.0";

#ifdef USE_NEOPIXEL
Adafruit_NeoPixel neoPixel(
  NEOPIXEL_COUNT,
  NEOPIXEL_PIN,
  NEO_GRB + NEO_KHZ800
);
#endif

void listFiles(fs::FS &fileSystem, const char *directoryPath)
{
  Serial.println();
  File rootDirectory = fileSystem.open(directoryPath);

  if (!rootDirectory || !rootDirectory.isDirectory())
  {
    Serial.println("Error: Could not open root directory.");
    return;
  }

  File currentEntry = rootDirectory.openNextFile();
  if (!currentEntry)
  {
    Serial.println("Info: No files found.");
  }

  while (currentEntry)
  {
    Serial.printf(
      "%s%s",
      currentEntry.isDirectory() ? "DIR : " : "FILE: ",
      currentEntry.name()
    );

    if (!currentEntry.isDirectory())
    {
      Serial.printf("\tSIZE: %u\n", (unsigned)currentEntry.size());
    }
    else
    {
      Serial.println();
    }

    currentEntry = rootDirectory.openNextFile();
  }

}   //   listFiles()

void printLittleFsUsage()
{
  Serial.println();
  size_t totalBytes = LittleFS.totalBytes();
  size_t usedBytes  = LittleFS.usedBytes();

  float usedPercent = 0.0F;
  if (totalBytes > 0)
  {
    usedPercent = (float)usedBytes * 100.0F / (float)totalBytes;
  }

  Serial.printf("LittleFS total bytes: %u\n", (unsigned)totalBytes);
  Serial.printf("LittleFS used bytes : %u\n", (unsigned)usedBytes);
  Serial.printf("LittleFS usage      : %.2f%%\n", usedPercent);

}   //   printLittleFsUsage()

void initOutput()
{
#ifdef USE_LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.printf("Using LED on pin %d\n", LED_PIN);
#endif

#ifdef USE_NEOPIXEL
  neoPixel.begin();
  neoPixel.setBrightness(20);
  neoPixel.clear();
  neoPixel.show();
  Serial.printf("Using NeoPixel on pin %d\n", NEOPIXEL_PIN);
#endif

}   //   initOutput()

void toggleOutput()
{
#ifdef USE_LED
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  Serial.printf(
    "LED is %s\n",
    digitalRead(LED_PIN) ? "ON" : "OFF"
  );
#endif

#ifdef USE_NEOPIXEL
  static bool isOn = false;

  if (isOn)
  {
    neoPixel.clear();
    Serial.println("NeoPixel is OFF");
  }
  else
  {
    neoPixel.setPixelColor(0, neoPixel.Color(0, 0, 255));
    Serial.println("NeoPixel is ON");
  }

  neoPixel.show();
  isOn = !isOn;
#endif

}   //   toggleOutput()

void initLittleFs()
{
  Serial.println("\n\nInitializing LittleFS...");
  if (!LittleFS.begin(true))
  {
    Serial.println("Error: LittleFS initialization failed.");
    return;
  }

  Serial.println("Info: LittleFS initialization OK.");
  printLittleFsUsage();
  listFiles(LittleFS, "/");

  Serial.println("\n");

}   //   initLittleFs()

void setup()
{
  Serial.begin(115200);
  delay(200);

  Serial.printf("Program version: %s\n", progVersion);

  initOutput();
  initLittleFs();

}   //   setup()

void loop()
{
  static int count = 5;
  toggleOutput();
  delay(2500);
  if (count > 10)
  {
    initLittleFs();
    count = 0;
    delay(2000);
    return;
  }
  count++;

}   //   loop()
