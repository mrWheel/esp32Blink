# Build log for esp32dev

Generated: 2026-02-23T13:38:16

$ pio run -e esp32dev
Processing esp32dev (platform: espressif32; board: esp32dev; framework: arduino)
--------------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/esp32dev.html
PLATFORM: Espressif 32 (6.10.0) > Espressif ESP32 Dev Module
HARDWARE: ESP32 240MHz, 320KB RAM, 4MB Flash
DEBUG: Current (cmsis-dap) External (cmsis-dap, esp-bridge, esp-prog, iot-bus-jtag, jlink, minimodule, olimex-arm-usb-ocd, olimex-arm-usb-ocd-h, olimex-arm-usb-tiny-h, olimex-jtag-tiny, tumpa)
PACKAGES: 
 - framework-arduinoespressif32 @ 3.20017.241212+sha.dcc1105b 
 - tool-esptoolpy @ 1.40501.0 (4.5.1) 
 - toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 33 compatible libraries
Scanning dependencies...
Dependency Graph
|-- FS @ 2.0.0
|-- LittleFS @ 2.0.0
Building in release mode
Retrieving maximum program size .pio.nosync/build/esp32dev/firmware.elf
Checking size .pio.nosync/build/esp32dev/firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [=         ]   6.6% (used 21496 bytes from 327680 bytes)
Flash: [==        ]  19.9% (used 313501 bytes from 1572864 bytes)
========================= [SUCCESS] Took 0.94 seconds =========================

Environment    Status    Duration
-------------  --------  ------------
esp32dev       SUCCESS   00:00:00.942
========================= 1 succeeded in 00:00:00.942 =========================
$ pio run -e esp32dev -t buildfs
Processing esp32dev (platform: espressif32; board: esp32dev; framework: arduino)
--------------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/esp32dev.html
PLATFORM: Espressif 32 (6.10.0) > Espressif ESP32 Dev Module
HARDWARE: ESP32 240MHz, 320KB RAM, 4MB Flash
DEBUG: Current (cmsis-dap) External (cmsis-dap, esp-bridge, esp-prog, iot-bus-jtag, jlink, minimodule, olimex-arm-usb-ocd, olimex-arm-usb-ocd-h, olimex-arm-usb-tiny-h, olimex-jtag-tiny, tumpa)
PACKAGES: 
 - framework-arduinoespressif32 @ 3.20017.241212+sha.dcc1105b 
 - tool-esptoolpy @ 1.40501.0 (4.5.1) 
 - tool-mklittlefs @ 1.203.210628 (2.3) 
 - toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 33 compatible libraries
Scanning dependencies...
Dependency Graph
|-- FS @ 2.0.0
|-- LittleFS @ 2.0.0
Building in release mode
Building FS image from 'data' directory to .pio.nosync/build/esp32dev/littlefs.bin
/platformio.ini
/partitions.csv
/main.cpp
========================= [SUCCESS] Took 0.36 seconds =========================

Environment    Status    Duration
-------------  --------  ------------
esp32dev       SUCCESS   00:00:00.359
========================= 1 succeeded in 00:00:00.359 =========================
Using partitions source: /Users/WillemA/Documents/platformioProjects/esp32Blink/partitions.csv

Resolved buildDir: /Users/WillemA/Documents/platformioProjects/esp32Blink/.pio.nosync/build/esp32dev
