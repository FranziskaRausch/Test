int LED=6;
int helligkeit= 1; 
int fadeschritte= 4;

void setup()

{
pinMode(LED, OUTPUT);
}

void loop()
{
analogWrite(LED, helligkeit);
helligkeit = helligkeit + fadeschritte;
delay(3000);
if (helligkeit == 1 || helligkeit == 250)
{
fadeschritte = -fadeschritte ;
}

}
