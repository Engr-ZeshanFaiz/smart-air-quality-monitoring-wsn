# Open-source IoT node for air quality monitoring and image-based smog detection

Arduino Uno + ESP8266 (ThingSpeak), MQ-7, MQ-135, PMS5003, DHT11, ESP32-CAM and a MATLAB smog classifier.
Companion repository to a *Journal of Open Hardware* hardware metapaper.

Authors: Zeshan Faiz (corresponding), Muhammad Salaar Haider, Gul e Zahrah, Farhan Faiz, Arslan Hassan - KFUEIT, Rahim Yar Khan, Pakistan.

| Folder | Content |
|---|---|
| `Hardware/` | Block diagram, circuit schematic, photos, enclosure notes |
| `Firmware/` | Arduino sketch(es) |
| `Matlab/` | Smog classifier |
| `Data/` | Field data (CSV) |
| `Documentation/` | `BOM.csv`, `BUILD_GUIDE.md` |

## Limitations (read first)
Gas-sensor values are uncalibrated relative indicators. PMS5003 data fail a basic consistency check in 74% of samples. Not a life-safety CO alarm.

## Licences
Software: MIT (`LICENSE`). Hardware: CERN-OHL-W (add `Hardware/LICENSE-CERN-OHL-W.txt` from https://cern-ohl.web.cern.ch). Documentation and data: CC-BY 4.0.
