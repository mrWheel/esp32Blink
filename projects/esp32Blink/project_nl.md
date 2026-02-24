# esp32Blink

Het doel van dit project is het testen van verschillende aspecten van de flasher-website.
Het project flasht firmware naar een ESP32-bord met een niet-standaard partitielayout.

Om de applicatie correct te laten werken, moeten zowel de firmware als de SPIFFS-image worden geflasht.

Bij het opstarten mount de applicatie eerst het SPIFFS-bestandssysteem en toont vervolgens de bestanden die daarin aanwezig zijn.
Daarna begint de LED te knipperen: 2,5 seconden aan en 2,5 seconden uit.
