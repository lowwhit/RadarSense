// Includes the Servo library
#include <Servo.h>
#include <LiquidCrystal.h>

int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;
//int Con=0;//contrast of the lcd

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 6; //def = 11
const int echoPin = 5; //def= 10
// Variables for the duration and the distance
long duration;
int distance;
float distanceCm, DistanceSec;
Servo myServo; // Creates a servo object for controlling the servo motor
void setup() 
  {
    //analogWrite(6,0); to use without 10kpot
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600);
    myServo.attach(4); // Defines on which pin is the servo motor attached , def = 12
    lcd.begin(16,2);
    DistanceSec=20;
    distanceCm=distance;
  }
void loop() 
  {
    //lcd.setCursor(0,0);
    //lcd.print(distance);
    //lcd.setCursor(0,1);
    //lcd.print("Angle is :");
    //delay(1000);
    //lcd.clear();
    // rotates the servo motor from 15 to 165 degrees
    
    for(int i=15;i<=165;i++)
    {  
      myServo.write(i);
      delay(30);
      distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
      Serial.print(i); // Sends the current degree into the Serial Port
      Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      Serial.print(distance); // Sends the distance value into the Serial Port
      Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      
      distanceCm= duration*0.034/2;
      if (distanceCm <= DistanceSec)
      {
 
          if(distanceCm <= DistanceSec/2)
          {
              lcd.setCursor(0,0); // positions the  cursor at 0,0
              lcd.print("Distance: "); // Prints "Distance" on the LCD
              lcd.print(distanceCm); // Prints the value on the  LCD
              lcd.print("cm "); // Prints the unit on the LCD
              delay(10);
              lcd.setCursor(0,1);
              lcd.print("Angle : ");
              lcd.print(i);
              lcd.print(" deg ");
              delay(2000);
          }
          else
          {
              lcd.setCursor(0,0); // positions the cursor at 0,0
              lcd.print("Distance: "); // Prints "Distance" on the LCD
              lcd.print(distanceCm); // Printe the value on the LCD
              lcd.print("cm "); // Prints the unit on the LCD
              delay(10);
              lcd.setCursor(0,1);
              lcd.print("Angle : ");
              lcd.print(i);
              lcd.print(" deg ");
              delay(2000);
          }
       }

       else
       {
            lcd.setCursor(0,0); // positions the  cursor at 0,0
            lcd.print("Distance: "); // Prints "Distance" on the LCD
            lcd.print(distanceCm); // Printe the value on the LCD
            lcd.print(" cm "); // Prints the unit on the LCD
            delay(10);
            lcd.setCursor(0,1);
            lcd.print("Angle : ");
            lcd.print(i);
            lcd.print(" deg ");
            delay(80); //delays 80ms to read the position of the lcd
       }
     
    }
    
    // Repeats the previous lines from 165 to 15 degrees
    for(int i=165;i>15;i--)
    {  
      myServo.write(i);
      delay(30);
      distance = calculateDistance();
      Serial.print(i);
      Serial.print(",");
      Serial.print(distance);
      Serial.print(".");
      distanceCm= duration*0.034/2;
      if (distanceCm <= DistanceSec)
      {
          if(distanceCm <= DistanceSec/2)
          {
              lcd.setCursor(0,0); // positionner le cursor a 0,0
              lcd.print("Distance: "); // Printe "Distance" sur LCD
              lcd.print(distanceCm); // Printe la valeur Obtenue sur LCD
              lcd.print(" cm "); // Printe l'unité sur LCD
              delay(10);
              lcd.setCursor(0,1);
              lcd.print("Angle : ");
              lcd.print(i);
              lcd.print(" deg ");
              delay(2000);
          }
          else
          {
              lcd.setCursor(0,0); // positionner le cursor a 0,0
              lcd.print("Distance: "); // Printe "Distance" sur LCD
              lcd.print(distanceCm); // Printe la valeur Obtenue sur LCD
              lcd.print(" cm "); // Printe l'unité sur LCD
              delay(10);
              lcd.setCursor(0,1);
              lcd.print("Angle : ");
              lcd.print(i);
              lcd.print(" deg ");
              delay(2000);
          }
      }
      else
      {
          lcd.setCursor(0,0); //
          lcd.print("Distance: "); //
          lcd.print(distanceCm); //
          lcd.print(" cm ");
          delay(10);
          lcd.setCursor(0,1);
          lcd.print("Angle : ");
          lcd.print(i);
          lcd.print(" deg ");
          delay(80);
      }
    }

      
    }
    
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance()
  { 
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
    distance= duration*0.034/2;
    //distanceCm=duration*0.034/2;
    return distance;
  }
