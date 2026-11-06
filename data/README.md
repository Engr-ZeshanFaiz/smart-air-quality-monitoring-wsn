# Field data (Rahim Yar Khan District, Pakistan)

One CSV per site plus `all_sites_combined.csv` (108 site samples + 17-row initial ThingSpeak test log).

Columns: `group, site, temp_C, humidity_pct, mq135_raw_ppm_eq, mq7_raw_ppm_eq, pm1_0_ugm3, pm2_5_ugm3, pm10_ugm3`

- MQ values are uncalibrated outputs as logged; not regulatory concentrations; MQ-135 is not a CO2 sensor.
- In 80 of 108 samples the PMS5003 values break PM1.0 <= PM2.5 <= PM10. Treat PM columns as unvalidated.
- DELETE the old `RYK_Field_Tests.csv` (4 illustrative rows, not the measured dataset).
