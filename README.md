# Open-source IoT node for air quality monitoring and image-based smog detection

Arduino Uno + ESP8266 (ThingSpeak), MQ-7, MQ-135, PMS5003, DHT11, ESP32-CAM and a MATLAB smog classifier.
Companion repository to a *Journal of Open Hardware* hardware metapaper.

Authors: Zeshan Faiz (corresponding), Muhammad Salaar Haider, Gul e Zahrah, Farhan Faiz, Arslan Hassan - KFUEIT, Rahim Yar Khan, Pakistan.

Archive (all versions): https://doi.org/10.5281/zenodo.18525620

## Repository layout
| Folder | Content |
|---|---|
| `hardware/` | Block diagram, circuit schematic, photos, CERN-OHL-W licence |
| `firmware/` | Reference Arduino sketch (`firmware/reference_firmware`) and credentials template |
| `matlab/` | Smog classifier (`smog_classifier.m`) |
| `data/` | Field data: original workbook (xlsx) and CSV files, 107 site samples |
| `documentation/` | `BOM.csv` and `BUILD_GUIDE.md` |

## Quick start
1. Buy the parts listed in `documentation/BOM.csv` and wire them as in `documentation/BUILD_GUIDE.md`.
2. Burn in the MQ-7 and MQ-135 sensors for 24-48 h.
3. Copy `firmware/credentials_example.h` to `credentials.h`, enter your Wi-Fi and ThingSpeak write key (never upload real credentials), and upload the sketch with the Arduino IDE.
4. Check the Serial Monitor (9600 baud) and your ThingSpeak channel.

## Limitations (read first)
- Gas-sensor values are uncalibrated relative indicators, not concentrations. Some logged values exceed the 10-bit ADC range of the Arduino Uno, and their derivation is not documented.
- PMS5003 data fail a basic consistency check (PM1.0 <= PM2.5 <= PM10) in 74% of samples.
- The firmware in `firmware/reference_firmware` is a reference implementation tested by the authors on the assembled node. The sketch used during the field campaign was not archived. Validate it on your own build.
- The smog classifier is qualitative and not validated against visibility measurements.
- Not a life-safety CO alarm.

## Licences
- Software: MIT (`LICENSE`)
- Hardware: CERN-OHL-W v2 (`hardware/LICENSE-CERN-OHL-W.txt`)
- Documentation and data: CC-BY 4.0
