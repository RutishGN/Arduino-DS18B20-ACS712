#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Data wire is connected to Arduino digital pin 4
#define ONE_WIRE_BUS 4

// ACS712 Current Sensor
const int sensorPin = A0;  // ACS712 analog input connected to A0
const float sensitivity = 0.100; // Sensitivity of ACS712 (100mV/A for ACS712-20A)

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Initialize LCD Display
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the I2C address for your LCD

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  
  // Start up the DS18B20 temperature sensor library
  sensors.begin();

  // Initialize LCD Display
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp (C):");
  lcd.setCursor(0, 1);
  lcd.print("Curr (A):");
  analogReference(DEFAULT);  // Set the analog reference to default (5V on most Arduinos)
}

void loop(void)
{
  // Temperature Reading
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);

  // Current Reading
  int sensorValue = analogRead(sensorPin);
  float current = (sensorValue - 512) * (5.0 / 1024.0) / sensitivity;

  // Display Temperature on LCD
  lcd.setCursor(10, 0);
  lcd.print(temperatureC, 2);

  // Display Current on LCD
  lcd.setCursor(10, 1);
  lcd.print(current, 2);

  // Print Temperature and Current to Serial Monitor
  Serial.print("Temperature (C): ");
  Serial.print(temperatureC, 2);
  Serial.print(" - Temperature (F): ");
  Serial.print(temperatureF, 2);
  Serial.print(" - Current (A): ");
  Serial.println(current, 2);

  delay(1000); // Delay for one second before the next reading
}
