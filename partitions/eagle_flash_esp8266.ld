/*— ESP8266 (Wemos D1 mini / 4MB flash) custom layout (clean base)
  — Sketch/IROM (max) : ~1.5MB
  — FS (LittleFS/SPIFFS): ~2.45MB (between ~2MB and ~3MB)

  Flash offsets:
  - Firmware (IROM) ends before FS starts at 0x180000
  - FS starts at 0x180000 and ends at 0x3FB000 (leaves end-of-flash area for SDK/system params)

  Mapped address rule:
  - mapped = 0x40200000 + flash_offset
*/

MEMORY
{
  /*— DPORT: special region used for cache/MMU registers */
  dport0_0_seg : org = 0x3FF00000, len = 0x10

  /*— IRAM: instruction RAM */
  iram1_0_seg  : org = 0x40100000, len = 0x8000

  /*— IROM: flash-mapped code (max sketch size) */
  irom0_0_seg  : org = 0x40201010, len = 0x17EFF0

  /*— DRAM: data RAM */
  dram0_0_seg  : org = 0x3FFE8000, len = 0x14000
}

/*— Filesystem region (LittleFS/SPIFFS) */
PROVIDE ( _FS_start = 0x40380000 );  /* flash offset 0x180000 */
PROVIDE ( _FS_end   = 0x405FB000 );  /* flash offset 0x3FB000 */
PROVIDE ( _FS_page  = 0x100 );
PROVIDE ( _FS_block = 0x1000 );

/*— Standard ESP8266 Arduino sections (use the OFFICIAL files from the ESP8266 Arduino framework) */
INCLUDE "partitions/eagle.app.v6.common.ld"
