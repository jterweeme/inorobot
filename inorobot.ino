#include <Servo.h>
 
Servo panServo;
Servo tiltServo;

unsigned int afstandLinks = 0;
unsigned int afstandRechts = 0;

ISR(PCINT4_vect)
{
  afstandLinks++;
}

ISR(PCINT13_vect)
{
  afstandRechts++;
}

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
  pinMode(A1, OUTPUT);
  pinMode(A3, INPUT);
  digitalWrite(A0, HIGH);
  pinMode(13, OUTPUT);
  /*
  PCICR = (1<<PCIE0) | (1<<PCIE1);
  PCMSK0 = (1<<PCINT4);
  PCMSK1 = (1<<PCINT13);
  */
}

void command(char *cmd)
{
  char *commando = strtok((char *)cmd, " ,.-\r");
  char *parameter = strtok((char *)NULL, " ,.-");
  unsigned int deg = atoi(parameter);

  // pan  
  if (strcmp(commando, "p") == 0)
    panServo.write(deg);
    
  // tilt
  if (strcmp(commando, "t") == 0)
    tiltServo.write(deg);
    
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

  // afstand
  if (strcmp(commando, "o") == 0)
  {
    Serial.println(1);
    Serial.println(afstandLinks);
    Serial.println(afstandRechts);
    
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
  /*
  digitalWrite(A1, LOW);
  digitalWrite(A1, HIGH);
  unsigned long distanceMeasured = pulseIn(A3, LOW);
  distance = distanceMeasured / 50;
  delay(20);
  */
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

