#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS3232RTC.h>
#include <Wire.h>
#include <DHT11.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
DS3232RTC myRTC;
DHT11 dht11(2);
Servo myservo;

bool displayTimeDate = true;
int pos = 0;

void setup() {
  Serial.begin(9600);

  // initialize for LCD 
  lcd.init(); // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();

  // Intialize for RTC
  myRTC.begin();

  // initialize for servo 
  myservo.attach(9);

   // Set the RTC time (Uncomment this section and enter the correct time)
  // tmElements_t tm;
  // tm.Year = CalendarYrToTm(2023);  // Year
  // tm.Month = 11;                    // Month
  // tm.Day = 14;                      // Day
  // tm.Hour = 22;                     // Hour
  // tm.Minute = 46;                    // Minute
  // tm.Second = 00;                    // Second
  // myRTC.write(tm);

  // // Get the current time from the RTC
  // time_t myTime = myRTC.get();
  
  // // Check if the time is valid
  // if (myTime != 0) {
  //   Serial.println("RTC time is valid.");
  //   // Print the time retrieved from the RTC
  //   Serial.println(F("RTC Time: "));
  //   printTimeToLCD(myTime);
  //   printDateToLCD(myTime);
  // } else {
  //   Serial.println("RTC time is invalid or uninitialized.");
  // }
}

void loop() {
  time_t myTime = myRTC.get();

  if (displayTimeDate) {
    lcd.setCursor(0,0);
    lcd.print("Time: ");
    printTimeToLCD(myTime);

    lcd.setCursor(0,1);
    lcd.print("Date: ");
    printDateToLCD(myTime);
    
  } else {
    lcd.clear();
    // Attempt to read the temperature value from the DHT11 sensor.
    int temperature = dht11.readTemperature();
    lcd.setCursor(0,0);
    lcd.print("Temperature: ");
    lcd.setCursor(4,1);
    printTemperatureToLCD(temperature);
  }

  delay(1000);
  displayTimeDate = !displayTimeDate;
}

void printTimeToLCD(time_t t) {
  lcd.print(" ");
  printDigits(hour(t));
  lcd.print(":");
  printDigits(minute(t));
  lcd.print(":");
  printDigits(second(t));
  lcd.print(" ");
}

// Function to print time in a readable format
void printDateToLCD(time_t t) {
  lcd.print(year(t));
  lcd.print("/");
  printDigits(month(t));
  lcd.print("/");
  printDigits(day(t));
}

// Function to ensure leading zero if value is less than 10
void printDigits(int digits) {
  if (digits < 10) {
    lcd.print('0');
  }
  lcd.print(digits);
}

void printTemperatureToLCD(int temperature){
    // Check the result of the reading.
    // If there's no error, print the temperature value.
    // If there's an error, print the appropriate error message.
    if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT)
    {
        lcd.print(temperature);
        lcd.print(" Celcius");
    }
    else
    {
        lcd.println(DHT11::getErrorString(temperature));
    }

    // Wait for 1 seconds before the next reading.
    delay(1000);
}

void turnOnTheLamp() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void turnOffTheLamp() {
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}