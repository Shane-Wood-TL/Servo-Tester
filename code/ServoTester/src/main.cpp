#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>


//Setup
//servo motor pwm limits
#define USMIN 771  // min pwm value (for motor + display)
#define USMAX 2193 // max pwm value (for motor + display)

#define ServoPin 10 //what PWM pin for servo
#define maxAngle 180 //max set angle (only for display)
#define minAngle 0 //min set angle (only for display)
#define analogPot A0 //pot read value



//display setup
Adafruit_SSD1306 display(128, 64, &Wire, -1);
#define SCREEN_ADDRESS 0x3C

// raw pot value, mapped pot value
int potValue; 
int fixedPotValue;

//servo object
Servo testServo;

void setup() {
  Serial.begin(9600); //Start Serial
  Wire.begin(); //Start I2C


  //Setup display 
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();

  //Setup PWM
  testServo.attach(ServoPin,USMIN, USMAX);

}

void loop() {
  //Read the pot value
  potValue = analogRead(analogPot);
  //map the pot value
  fixedPotValue = (map(potValue,1023,0,minAngle,maxAngle));

  //update the display
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
         // Draw white text
  display.setCursor(0,0);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); 
  display.println("Servo Test");         // Start at top-left corner

  //write the angle to display
  display.setTextColor(SSD1306_WHITE); 
  display.print(fixedPotValue);
  display.println(" deg");

//write the PWM value to display
  display.println(map(potValue,1023,0,USMIN,USMAX));

//update display
  display.display();

  //update servo position
  testServo.write(fixedPotValue); 
}
