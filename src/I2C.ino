
#include "oled-wing-adafruit.h"
#include "Wire.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"


SYSTEM_THREAD(ENABLED);
OledWingAdafruit display;
VCNL4040 sensor;


int red = D5;
int green = D6;
int blue = D7;


void setup() {
  //identifies the led output pins
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Serial.begin(9600);
    display.setup();
    display.clearDisplay();
    display.display();
  sensor.begin(); //turns on the proximity sensor
  Wire.begin(); //Join i2c bus
}

void loop() {
  display.loop();  
//prints the value the sensor is getting to the serial monitor. 
  unsigned int proxValue = sensor.getProximity(); 
  Serial.print("Proximity Value: ");
  Serial.print(proxValue);
  Serial.println();
  unsigned int ambientValue = sensor.getAmbient();
  
  //when button A is pressed, it will aquire the current value from the proiximity sensor and print that on the OLED display
  if (display.pressedA()) {
    display.clearDisplay();

    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    String output;
    uint16_t reading = sensor.getProximity();
    Serial.print(reading);

    display.println(reading);
    display.display();
    delay(200);
    
  }
  display.clearDisplay();

  //when button b is pressed, it will aquire the current value from the ambient light sensor and print that on the OLED display

 if (display.pressedB())
  {
    sensor.powerOnAmbient();
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    String output = "Light Level: ";
    uint16_t reading = sensor.getProximity();
    output += (String) reading;
    //print to display
    display.println(ambientValue);
    display.display();
  }
 
   //when button C is pressed, it will print the i2C address to the display

  if (display.pressedC()) {
		display.clearDisplay();

		display.setTextSize(3);
		display.setTextColor(WHITE);
		display.setCursor(0,0);
		display.println("0x60");
		display.display();
	}

  //when the proximity value is less than 8, it will turn on pin D5 
  if (proxValue < 8)
    {
      digitalWrite(D5, HIGH);
    } 
      else {
      digitalWrite(D5, LOW);
    }
  
    //when the proximity value is greater than 8 and less than 100, it will turn on pin D6 

  if (proxValue > 8 && proxValue < 100) 
    {
      digitalWrite(D6, HIGH);
    } 
      else {
      digitalWrite(D6, LOW);
    }
 
   //when the proximity value is greater than 100, it will turn on pin D7

  if (proxValue > 100) 
    {
      digitalWrite(D7 ,HIGH);
    } 
      else {
      digitalWrite(D7, LOW);
    }
}