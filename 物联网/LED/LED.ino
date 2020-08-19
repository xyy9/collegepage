/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 21 Sep 2019 07:24:16 GMT
 */



void setup()
{

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}


void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED亮起");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED熄滅");
  delay(1000);
}