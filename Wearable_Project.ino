#include <dht.h>        
#define outPin 7        
dht DHT;     


int chk;
float hum; 
float temp; 
long duration;
long distance;
const int irS = 4;
const int light = 6;
const int light2 = 5;
const int buzzer = 11;
const int trigPin = 8;
const int echoPin = 9;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(light, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(irS, INPUT);
  Serial.begin(9600);
 // dht.begin(); // starts the DHT22 sensor
}


void lightSensor()
{
  int sensorValue = analogRead(A0);
  Serial.print("Light Sensor value is: ");
  Serial.println(sensorValue);
  if (sensorValue < 150)
  {
      Serial.println("*** Darkness detected, turning lights ON ***");
      digitalWrite(light, HIGH);
  }
  else 
    {
       digitalWrite(light, LOW);
    }
}

void irSensor()
{
  int senStatus = digitalRead(irS);
  if(senStatus == 0)
  { 
    Serial.println("*** Detected someone's presence, safety alarm ON ***");
    digitalWrite(light2, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(light2, LOW);
    digitalWrite(buzzer, LOW);
  }
}
void temperature()
{
  
  int readData = DHT.read11(outPin);

	float t = DHT.temperature;        // Read temperature
	float h = DHT.humidity;           // Read humidity

	Serial.print("Temperature = ");
	Serial.print(t);
	Serial.print("°C | ");
	Serial.print((t*9.0)/5.0+32.0);        // Convert celsius to fahrenheit
	Serial.print("°F  ");
	Serial.print("  Humidity = ");
	Serial.print(h);
	Serial.println("% ");
  delay(2000); //2 sec delay
    if(temp > 30)
    {
      Serial.println("*** Temperature is above 30C, turning AC on ***");
    }

}

void ultrasonic()
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration/74/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" inches");
if(distance < 7)
    {
      Serial.println("*** Water tank is going to be full, turning motor OFF ***");
    }
  else 
  {
    Serial.println("*** Water tank is still not full, turning motor ON ***");
  }
}


void loop()
{
    temperature();
    delay(100);
    ultrasonic();
    delay(100);
    lightSensor();
    delay(100);
    irSensor();
    delay(100);
    
}

   