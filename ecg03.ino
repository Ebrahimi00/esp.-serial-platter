
 int ENA=10;
 int ENB=11;
 int pot1=A0;
 int pot2=A1;
 int reading1;
 int reading2; 
void setup() {
  pinMode (A0,INPUT);
  pinMode (A1,INPUT);
  pinMode (ENA,OUTPUT);
  pinMode (ENB,OUTPUT);
}

void loop() {
  { reading1 = analogRead(pot1);
    int p=map(reading1,0,1023,0,255); 
    analogWrite(ENA,p);
    reading2 = analogRead(pot2);
    int s= map (reading2,0,1023,0,255);
    analogWrite (ENB,s);
    }

}
