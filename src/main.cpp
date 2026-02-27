//--- Simple test program (LED or NeoPixel selected via build_flags)

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

const char* PROG_VERSION = "1.1.0";

#ifdef USE_NEOPIXEL
  #include <Adafruit_NeoPixel.h>
#endif

#ifdef USE_NEOPIXEL
Adafruit_NeoPixel neoPixel(
  NEOPIXEL_COUNT,
  NEOPIXEL_PIN,
  NEO_GRB + NEO_KHZ800
);
#endif

uint32_t delayTime = 2000;

void listFiles(fs::FS &fileSystem, const char *directoryPath)
{
  Serial.println();
#if defined(ARDUINO_ARCH_ESP32)
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
#elif defined(ARDUINO_ARCH_ESP8266)
  Dir directory = fileSystem.openDir(directoryPath);
  bool hasFiles = false;

  while (directory.next())
  {
    hasFiles = true;
    File currentEntry = directory.openFile("r");

    Serial.printf(
      "%s%s",
      currentEntry.isDirectory() ? "DIR : " : "FILE: ",
      directory.fileName().c_str()
    );

    if (!currentEntry.isDirectory())
    {
      Serial.printf("\tSIZE: %u\n", (unsigned)directory.fileSize());
    }
    else
    {
      Serial.println();
    }
  }

  if (!hasFiles)
  {
    Serial.println("Info: No files found.");
  }
#else
  Serial.println("Error: Unsupported architecture for file listing.");
#endif

}   //   listFiles()

void printLittleFsUsage()
{
  Serial.println();
#if defined(ARDUINO_ARCH_ESP32)
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
#elif defined(ARDUINO_ARCH_ESP8266)
  FSInfo fsInfo;
  if (!LittleFS.info(fsInfo))
  {
    Serial.println("Error: Unable to read LittleFS usage.");
    return;
  }

  float usedPercent = 0.0F;
  if (fsInfo.totalBytes > 0)
  {
    usedPercent = (float)fsInfo.usedBytes * 100.0F / (float)fsInfo.totalBytes;
  }

  Serial.printf("LittleFS total bytes: %u\n", (unsigned)fsInfo.totalBytes);
  Serial.printf("LittleFS used bytes : %u\n", (unsigned)fsInfo.usedBytes);
  Serial.printf("LittleFS usage      : %.2f%%\n", usedPercent);
#else
  Serial.println("Error: Unsupported architecture for LittleFS usage.");
#endif

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
#if defined(ARDUINO_ARCH_ESP32)
  if (!LittleFS.begin(true))
#elif defined(ARDUINO_ARCH_ESP8266)
  if (!LittleFS.begin())
#else
  if (!LittleFS.begin())
#endif
  {
    Serial.println("Error: LittleFS initialization failed.");
    delayTime = 1000;
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

  Serial.printf("Program version: %s\n", PROG_VERSION);

  initOutput();
  initLittleFs();

}   //   setup()

void loop()
{
  static int count = 5;
  toggleOutput();
  delay(delayTime);
  if (count > 10)
  {
    initLittleFs();
    count = 0;
    delay(delayTime/2);
    return;
  }
  count++;

}   //   loop()
