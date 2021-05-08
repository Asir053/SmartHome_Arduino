int led = 13;
int smokeA0 = A5;
int sensorThres = 200;


const int trigPin = 9;
const int echoPin = 10;
String voice;
int ac=4;
int light=5;
int fan=6;
int tv=7;
long duration;
int distance;

void setup() {
Serial.begin(9600);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);


  pinMode(smokeA0, INPUT);
  
pinMode(ac, OUTPUT);

pinMode(light, OUTPUT);

pinMode(fan, OUTPUT);

pinMode(tv, OUTPUT);

pinMode(led,OUTPUT);

}



void loop() {

//sonar start
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);


if(distance<=30)
{
  digitalWrite(ac,HIGH);

  //smoke start
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  if (analogSensor > sensorThres)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
     digitalWrite(led,LOW);
  }
  //smoke end
   //bluetooth start 
while(Serial.available()) {

delay(10);
char c=Serial.read();
if(c=='#')
{
  break;  
  }
voice += c;
}
//light
if(voice =="light on"){
digitalWrite(light,HIGH);
}
else if(voice =="light off" || voice =="light of"){
digitalWrite(light,LOW);
}

//fan
else if(voice =="fan on"){
digitalWrite(fan,HIGH);
}
else if(voice =="fan off" || voice == "fan of"){
digitalWrite(fan,LOW);
}

//tv
else if(voice =="television on"){
digitalWrite(tv,HIGH);
}
else if(voice =="television off" || voice == "television of"){
digitalWrite(tv,LOW);
}

voice="";
//bluetooth end
delay(1000);
}
else
{
  digitalWrite(ac,LOW);
}
//sonar end


 
}
