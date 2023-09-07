const int T1=5000;    //duration of green light
const int T2=2000;    //duration of yellow light
const int T3=3000;    //duration of emergency crossing
const int T4=1000;    //duration of siren when someone violates traffic rules
volatile byte state1 = LOW,state2=LOW;
long a=0,b=0;
void setup() {
 pinMode(2,INPUT);
 pinMode(3,INPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);
 pinMode(11,OUTPUT);
 pinMode(12,OUTPUT);
 pinMode(13,OUTPUT);
 attachInterrupt(digitalPinToInterrupt(3), cross,CHANGE );
 attachInterrupt(digitalPinToInterrupt(2), check, FALLING);
}

void loop() {
  if(state1==HIGH) emergency();
  unsigned long T=millis();
  T-=T3*a+b;
  T=T%(4*(T1+T2));
  if(T<T1)
  {
    alloff();
    signal1green();
    if(state2 == HIGH) 
{
  delay(50);
  b+=50;
  if(digitalRead(3)==HIGH) siren();
}
  }
  else if(T1<=T && T<(T1+T2))
  {
    alloff();
    signal1yellow();
    if(state2 == HIGH) 
{
  delay(50);
  b+=50;
  if(digitalRead(3)==HIGH) siren();
}
  }
  if(state1==HIGH) emergency();
   else if((T1+T2)<=T && T<(2*T1+T2))
  {
    alloff();
    signal2green();
   if(state2 == HIGH) 
{
  delay(50);
  b+=50;
  if(digitalRead(3)==HIGH) siren();
}
  }
   else if((2*T1+T2)<=T && T<(2*(T1+T2)))
  {
    alloff();
    signal2yellow();
    if(state2 == HIGH) 
{
  delay(50);
  b+=50;
  if(digitalRead(3)==HIGH) siren();
}
  }
  
   else if((2*(T1+T2))<=T && T<(3*T1+2*T2))
  {
    if(digitalRead(3)==LOW)
    {
    alloff();
    signal3green();
    }
    else {a=a-((3*T1+2*T2)-T)/T3;}
  }
   else if((3*T1+2*T2)<=T && T<(3*T1+3*T2))
  {
   
    alloff();
    signal3yellow();
    state2=LOW;
   

  }
  if(state1==HIGH) emergency();
   else if((3*T1+3*T2)<=T && T<(4*T1+3*T2))
  {
    alloff();
    signal4green();
    if(state2 == HIGH) 
{
  delay(50);
  b+=50;
  if(digitalRead(3)==HIGH) siren();
}
  }
   else if((4*T1+3*T2)<=T && T<(4*T1+4*T2))
  {
    alloff();
    signal4yellow();
   if(state2 == HIGH) 
{
  delay(50);
  b+=50;
  if(digitalRead(3)==HIGH) siren();
}
  }
 if(state1==HIGH) emergency();
 
}
void check()
{
  state1=HIGH;
}
void cross()
{
  
  state2=HIGH;
 
}

void signal1green()
{
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(11,HIGH);
  
}
void signal1yellow()
{
  analogWrite(A3,255);
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(11,HIGH);
}
void signal2green()
{
  digitalWrite(7,HIGH);
  analogWrite(A4,255);
  digitalWrite(8,HIGH);
  digitalWrite(11,HIGH);
  
}
void signal2yellow()
{
  analogWrite(A4,255);
  digitalWrite(6,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(11,HIGH);
}
void signal3green()
{
  analogWrite(A4,255);
  digitalWrite(5,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(11,HIGH);
  
}
void signal3yellow()
{
  analogWrite(A4,255);
  digitalWrite(5,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(11,HIGH);
}
void signal4green()
{
  
  analogWrite(A5,255);
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  analogWrite(A4,255);
  
}
void signal4yellow()
{
 analogWrite(A4,255);
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(10,HIGH);
}
void allred()
{
   analogWrite(A4,255);
  digitalWrite(5,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(11,HIGH);
}
void alloff()
{
  analogWrite(A4,0);
 analogWrite(A3,0);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  analogWrite(A5,0);
}
void siren()
{
  for(int i=0;i<(T4/200);i++)
  {
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
  }
  state2=LOW;
}
void emergency()
{
  alloff();
  allred();
  delay(T3);
  alloff();
  a++;
  state1=LOW;
}
