//ARRAY
int IR1=12;
int IR2=11;
int IR3=10;
int IR4=9;
int IR5=8;//Define Syntax #define parameter
int IR6=7;
int IR7=6;
int IR8=4;
int LED=13;
 //MOTOR
int IN1=A3;//Define motor inputs
int IN2=A2;
int IN3=A1;
int IN4=A0;
int ir1=0,ir2=0,ir3=0,ir4=0,ir5=0,ir6=0,ir7=0,ir8=0;
 //Enable pins (PWM Values)
  int R=3;// speed motor
 int L=5;
 boolean flag1,flag8;
 int count=0;
 int special=0;
 void read()
 {
   ir1=digitalRead(IR1);
   ir2=digitalRead(IR2);
   ir3=digitalRead(IR3);
   ir4=digitalRead(IR4);
   ir5=digitalRead(IR5);
   ir6=digitalRead(IR6);
   ir7=digitalRead(IR7);
   ir8=digitalRead(IR8);
 }
void setup() {
  Serial.begin(9600);
  //IR ARRAY
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(IR4,INPUT);
  pinMode(IR5,INPUT);
  pinMode(IR6,INPUT);
  pinMode(IR7,INPUT);
  pinMode(IR8,INPUT);
  pinMode(LED,OUTPUT);
 
  //MOTOR
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);//
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);//
 
  //ENABLE PIN
  pinMode(R,OUTPUT);
  pinMode(L,OUTPUT);
 
 
}
int S=0,l=1;//BLACK(L)=1(LINE),LOW(SURFACE)S=0,HIGH

void trackinvert()
{
  read();
  if((ir1==l && ir7==l) && (ir3==S || ir4==S || ir5==S || ir6==S))//last 2 sensors get line at the same time and any other middle sensor gets surface we track invert
  {
    int temp=S;
    S=l;
    l=temp;
  }
}
void loop()
{
  read();
  trackinvert();
  if (count==0)
  {
    go();
    delay(300);
    count=1;
  }
  else
  {
  //flag trigger
  if(ir2==l)
  flag1=true;
  if(ir8==l)
  flag8=true;
  if(flag1==true && flag8==true)
  {
    flag1=false;
    flag8=false;
  }

  if(ir2==l && ir3==l && ir4==l && ir5==l && ir6==l && ir7==l)
  {
    digitalWrite(LED,HIGH);
    delay(75);
    flag1=false;//new
    flag8=false;//new
    read();
   
   
      if((ir6==l && ir7== l) && (ir1==S && ir2==S))
    {
      sharpright();
      special==1;
    }
   
    }
    else if(ir1==l && ir2==l && ir3==l && ir4==l && ir5==l && ir6==l && ir7==l && ir8==l)
    {
      stop();
      delay(5000);
    }
    else
    {
    digitalWrite(LED,LOW);
    }
   
  }
 
  else if(ir4==l || ir5==l)
  {
    go();
  }
  else if((ir5==l && ir6==l))
  {
    sharpright();//mediumright
  }
  else if((ir3==l && ir4==l))
  {
    mediumleft();//lowleft
  }
  else if((ir6==l || ir7==l))
  {
    sharpright();//sharpright
  }
  else if((ir2==l || ir3==l))
  {
    sharpleft();//mediumright
  }
 
  else if( ir2==S || ir3==S || ir4==S || ir5==S || ir6==S || ir7==S || ir8==S)
  {
    while(flag1==true)
    {
      sharpleft();
      read();
      if(ir4==l || ir5==l)//changed
      {
        flag1=false;
        flag8=false;
        break;
      }
    }

    while(flag8==true)
    {
      sharpright();
      read();
      if(ir5==l || ir4==l)//changed
      {
        flag8=false;
        flag1=false;
        break;
      }
    }
  }
}
}
void go()
{
  analogWrite(R, 195);//185
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(L, 230);//220
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void stop()
{
  analogWrite(R, 180);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  analogWrite(L,180);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
}

void sharpleft()
{
  analogWrite(R,120);//120
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(L,120);//120
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void mediumleft()
{
  analogWrite(R,150);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(L, 0);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void lowleft()
{
  analogWrite(R,100);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(L, 0);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void sharpright()
{
  analogWrite(R, 120);//110//115
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(L, 120);//110//115
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void mediumright()
{
  analogWrite(R, 0);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(L, 150);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void lowright()
{
  analogWrite(R, 0);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(L, 100);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
