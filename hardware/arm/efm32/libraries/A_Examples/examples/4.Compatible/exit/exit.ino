/* EXIT template
   huaweiwx@sina.com 2017.12.26
*/

#define pbIn PF0
#define led LED_BUILTIN

bool state = LOW;

void setup()
{
  pinMode(led, OUTPUT);

  /* setup alternate location default is 0# */
  Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
  Serial.begin(115200);
  delay(1000);

  Serial.println("EXTI demo");
  digitalWrite(pbIn, HIGH);
  pinMode(pbIn, INPUT);
  attachInterrupt(pbIn, pbIncallback, CHANGE);
}

void loop()
{
  digitalWrite(led, state);
}

void pbIncallback()
{
  state = !state;
}
