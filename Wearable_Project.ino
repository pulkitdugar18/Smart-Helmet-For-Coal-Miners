#include <dht.h>
#define outPin 7
dht DHT;


int chk;
float hum;
float temp;
long duration;
long distance;
const int gasS = A0;
const int light = 6;
const int light2 = 5;
const int buzzer = 11;
const int trigPin = 8;
const int echoPin = 9;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  pinMode(light, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(gasS, INPUT);
  Serial.begin(9600);
  // dht.begin(); // starts the DHT22 sensor
}


void gasSensor() {
  int senStatus = analogRead(gasS);
  if (senStatus < 400) {
    Serial.println("*** Warning: Detected poisionous gases ***");
    digitalWrite(light2, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(light2, LOW);
    digitalWrite(buzzer, LOW);
  }
}
void temperature() {

  int readData = DHT.read11(outPin);

  float t = DHT.temperature;  // Read temperature
  float h = DHT.humidity;     // Read humidity

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print("°C | ");
  Serial.print((t * 9.0) / 5.0 + 32.0);  // Convert celsius to fahrenheit
  Serial.print("°F  ");
  Serial.print("  Humidity = ");
  Serial.print(h);
  Serial.println("% ");
  delay(2000);  //2 sec delay
  if (t > 30) {
    Serial.println("*** Warning: Temperature is above 30C ***");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  }
}

void ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 74 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" inches");
  if (distance < 7) {
    Serial.println("*** Warning: Tunnel is getting narrower ***");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  }
}


void loop() {
  temperature();
  delay(100);
  ultrasonic();
  delay(100);
  gasSensor();
  delay(100);
}
