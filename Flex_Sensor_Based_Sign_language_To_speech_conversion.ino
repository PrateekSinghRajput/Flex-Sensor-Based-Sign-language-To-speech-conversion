
//Prateek
//wwww.prateeks.in
//https://www.youtube.com/c/JustDoElectronics/videos

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

#define blue 2
#define green 3
#define red 4
unsigned int f;

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sign Language to");
  lcd.setCursor(0, 1);
  lcd.print("Speech Convert");
  delay(6000);
  lcd.clear();
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("Initializing DFPlayer..."));

  //Use softwareSerial to communicate with MP3
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30);

}

void loop()
{
  f = analogRead(1);
  Serial.println(f);
  if (f > 320)                       //No Bend; Blue LED Glows
  {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
    Serial.println("Please Give Me Water");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cmd 1");
    lcd.setCursor(0, 1);
    lcd.print("I Feel Sleepy");
    myDFPlayer.play(1);
    delay(1000);
  }
  else if ((f < 320) && (f > 280))   //Small Bend; Green LED Glows
  {
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
    Serial.println("Please Give Me Food");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cmd 2");
    lcd.setCursor(0, 1);
    lcd.print("Give Me Food");
    myDFPlayer.play(2);
    delay(1000);
  }
  else if ((f < 200) && (f > 100))   //Small Bend; Green LED Glows
  {
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
    Serial.println("Give Me Water");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cmd 3");
    lcd.setCursor(0, 1);
    lcd.print("Give Me Water");
    myDFPlayer.play(3);
    delay(1000);
  }
  else                              // Larger Bend; RED LED Glows
  {
    if (f > 100)
      digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Sign Language");
  }
  delay(50);
}
