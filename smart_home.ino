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

int pos = 0;
bool servoActive = false;

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

  //  Set the RTC time (Uncomment this section and enter the correct time)
  // tmElements_t tm;
  // tm.Year = CalendarYrToTm(2023);  // Year
  // tm.Month = 11;                    // Month
  // tm.Day = 16;                      // Day
  // tm.Hour = 12;                     // Hour
  // tm.Minute = 10;                    // Minute
  // tm.Second = 0;                    // Second
  // myRTC.write(tm);

  // // Get the current time from the RTC
  // time_t myTime = myRTC.get();
  
  // // Check if the time is valid
  // if (myTime != 0) {
  //   Serial.println("RTC time is valid.");
  //   // Print the time retrieved from the RTC
  //   Serial.println(F("RTC Time: "));
  // } else {
  //   Serial.println("RTC time is invalid or uninitialized.");
  // }
}

void loop() {
    time_t myTime = myRTC.get();
    tmElements_t tm;
    breakTime(myTime, tm);
  
   if (tm.Hour == 7 && tm.Minute == 0) {
    if (!servoActive) {
      myservo.write(180);
      delay(1000);
      myservo.write(0);
      servoActive = true;
    }
   }

   if (tm.Hour == 9 && tm.Minute == 0) {
    if (!servoActive) {
      myservo.write(180);
      delay(1000);
      myservo.write(0);
      servoActive = true;
    }
   }

   if (tm.Hour == 12 && tm.Minute == 40) {
    if (!servoActive) {
      myservo.write(180);
      delay(1000);
      myservo.write(0);
      servoActive = true;
    }
   }

   if (tm.Hour == 22 && tm.Minute == 0) {
    if (!servoActive) {
      myservo.write(180);
      delay(1000);
      myservo.write(0);
      servoActive = true;
    }
   }

   if (tm.Hour == 23 && tm.Minute == 50) {
    if (!servoActive) {
      myservo.write(180);
      delay(1000);
      myservo.write(0);
      servoActive = true;
    }
   }

    lcd.setCursor(0,0);
    lcd.print("Time: ");
    printTimeToLCD(myTime);

    lcd.setCursor(0,1);
    lcd.print("Date: ");
    printDateToLCD(myTime);
    
    delay(3000);
    lcd.clear();

    // Attempt to read the temperature value from the DHT11 sensor.
    int temperature = dht11.readTemperature();
    lcd.setCursor(0,0);
    lcd.print("Temperature: ");
    lcd.setCursor(4,1);
    printTemperatureToLCD(temperature);
    
    delay(3000);
    lcd.clear();
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
}