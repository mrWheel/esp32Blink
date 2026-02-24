# esp32Blink

The purpose of this project is to test various aspects of the flasher website.
It flashes firmware to an ESP32 board that uses a non-standard partition layout.

For the application to function correctly, both the firmware and the SPIFFS image must be flashed.

On startup, the application first mounts the SPIFFS filesystem and lists the files it contains.
It then starts blinking the LED, staying on for 2.5 seconds and off for 2.5 seconds.
