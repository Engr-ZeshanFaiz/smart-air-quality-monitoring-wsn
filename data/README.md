# Field data (Rahim Yar Khan District, Pakistan)

One CSV per site plus `all_sites_combined.csv` (107 site samples + 17-row initial ThingSpeak test log; the original workbook `Field Testing Data Rahim Yar Khan.xlsx` (107 rows) is the source).

Columns: `group, site, temp_C, humidity_pct, mq135_raw_ppm_eq, mq7_raw_ppm_eq, pm1_0_ugm3, pm2_5_ugm3, pm10_ugm3`

- MQ values are uncalibrated outputs as logged; not regulatory concentrations; MQ-135 is not a CO2 sensor.
- In 79 of 107 samples the PMS5003 values break PM1.0 <= PM2.5 <= PM10. Treat PM columns as unvalidated.
- DELETE the old `RYK_Field_Tests.csv` (4 illustrative rows, not the measured dataset).

- The workbook labels the industrial-plant rows and a second group of 18 rows together as 'Industrial Areas' (46 rows); the CSV split into Industrial (28) / Residential (18) follows the authors' site descriptions.
- Gas columns are labelled ppm in the workbook; some values exceed 1023 (Arduino Uno 10-bit ADC maximum), so they are not raw Uno ADC counts. How they were derived is not documented; treat them as relative indices.
