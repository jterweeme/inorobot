#include <Servo.h>
 
Servo panServo;
Servo tiltServo;

String inputString;
boolean stringComplete = false;
unsigned int distance = 0;
 
int pos = 0;    // variable to store the servo position 

void setup() 
{ 
  inputString.reserve(200);
  panServo.attach(3);
  tiltServo.attach(11);
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A2, INPUT);
  digitalWrite(A0, HIGH);
  pinMode(13, OUTPUT);
}

void command(char *cmd)
{
  char *commando = strtok((char *)cmd, " ,.-\r");
  char *parameter = strtok((char *)NULL, " ,.-");
  unsigned int deg = atoi(parameter);
  
  if (strcmp(commando, "p") == 0)
    PORTB ^= (1<<5);
    
  // linksvooruit
  if (strcmp(commando, "q") == 0)
  {
    digitalWrite(4, HIGH);
    analogWrite(5, deg);
  }
  
  // linksachteruit
  if (strcmp(commando, "a") == 0)
  {
    digitalWrite(4, LOW);
    analogWrite(5, deg);
  }
  
  // rechtsvooruit
  if (strcmp(commando, "w") == 0)
  {
    digitalWrite(7, HIGH);
    analogWrite(6, deg);
  }
  
  // rechtsachteruit
  if (strcmp(commando, "s") == 0)
  {
    digitalWrite(7, LOW);
    analogWrite(6, deg);
  }
  
  // sonic
  if (strcmp(commando, "d") == 0)
  {
    String uitvoer = "d";
    uitvoer += distance;
    uitvoer += "d";
    Serial.println(uitvoer);
  }
}

void loop()
{
  digitalWrite(A0, LOW);
  digitalWrite(A0, HIGH);
  unsigned long distanceMeasured = pulseIn(A2, LOW);
  distance = distanceMeasured / 50;
  delay(20);
}

void serialEvent()
{
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    if (inChar == '\n')
    {
  
      char foo[90];
      inputString.toCharArray(foo, 90);
      inputString = "";
      command(foo);
    }
  }
}

