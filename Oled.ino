/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "StopWatch.h" //URL: https://github.com/RobTillaart/StopWatch_RT

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     12 // Reset pin # (or -1 if sharing Arduino reset pin or no pin at all)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Stop watch
StopWatch sw_secs(StopWatch::SECONDS);

//Reset and Stop Pin
#define Reset_pin 2
#define Stop_pin 3

//variables for time
int seconds_elasped;
int reset_pin_count=1;
int col=10;




void setup() {
  Serial.begin(115200);
  pinMode(Reset_pin,INPUT); //for starting and reseting the whole stop watch
  pinMode(Stop_pin,INPUT);  //clears the entire screen.
  //pinMode(OLED_RESET,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Reset_pin), Reset_pinISR, RISING);
  attachInterrupt(digitalPinToInterrupt(Stop_pin), Stop_pinISR, RISING);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
    Serial.println("SSD1306 allocation failed");
    for(;;); //Dont proceed, loop forever
  }
  
  delay(2000);
  display.clearDisplay(); //clears display buffer

  display.setTextSize(1); //Size of text
  display.setTextColor(WHITE); //sets white texts and black background
  display.setCursor(0, col); //(x,y)
  // Display static text
  display.println("Stop Watch"); //fills the display buffer
  display.display(); //pushes the text to the screen
  delay(2000); // displays text for two seconds 
  display.clearDisplay();
  display.display();
  
}

void loop() {

  if(reset_pin_count == 1 ){
      seconds_elasped = sw_secs.elapsed();
  }

 if (reset_pin_count < 2){
  display.setCursor(0, col); //(x,y)
   }
 else if(reset_pin_count > 1 ) {
  display.setCursor(0, col+10); //(x,y)
 }
 
  display.print((int)seconds_elasped/3600); //loads elasped time to buffer(hrs)
  display.print(":");
  display.print((int)seconds_elasped/60); //loads elasped time to buffer(mins)
  display.print(":");
  display.println(seconds_elasped%60); //loads elasped time to buffer(secs)
  display.display();

}


//ISR for button presses

void Reset_pinISR(){
 sw_secs.reset();
 sw_secs.start();
 reset_pin_count++;
};


void Stop_pinISR(){
  col=10;
  sw_secs.stop();
  display.clearDisplay();
  display.display();
};
