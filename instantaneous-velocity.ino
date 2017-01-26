//Arduino Pin - Rotary Encode
unsigned long time;
unsigned long t0 = 0;
unsigned long tt0 = 0;
int dRotAPin = 2;
int dRotBPin = 3;
int countB = 1;
int countA = 1;
int tempB = 0;
int tempA = 0;
int i = 0;
int N;
int pre_N;
int sign = 1;
int lastN;//last number
unsigned long PR;//Pulse Rate
int PN;//Pulse Number
unsigned long pre_PR;//
int pre_PN;
double degreeB = 0;
double degreeA = 0;
double degree = 0;
volatile int m_nValueB = 0;
volatile int m_nValueA = 0;
long wa;//omega 
long wb; 
void va();//velocityA
void vb();//vekicityB
int DM();//Discover Missing
int number();//0,1,2,3
float V;
float pre_V;


void setup() {
  //INPUT Mode
  Serial.begin(250000);
  pinMode(dRotAPin, INPUT);
  pinMode(dRotBPin, INPUT);

  //Pull Up
  digitalWrite(dRotAPin, HIGH);
  digitalWrite(dRotBPin, HIGH);
  attachInterrupt(0, va, CHANGE);
  attachInterrupt(1, vb, CHANGE);
}

void va(){
  m_nValueA = digitalRead(dRotAPin);
  //0123nobaaiwakenitobu
  number();
}

void vb(){
  m_nValueB = digitalRead(dRotBPin);
  number();
}

int number(){ 
  N = m_nValueA + 2 * m_nValueB;
  //Serial.print("|");
  switch(N){
    case 2:
      N = 3;
      break;
    case 3:
      N = 2;
      break;
  }
  PR = time-t0;
  t0 = time;
  if(PR > 5000){
    switch(N){
      case 0:
        if(PN == 3)sign = 1;
        else if(PN == 1)sign = -1;
        else sign = 0;
        break;
      case 1:
        if(PN == 0)sign = 1;
        else if(PN == 2)sign = -1;
        else sign = 0;
        break;
      case 2:
        if(PN == 1)sign = 1;
        else if(PN == 3)sign = -1;
        else sign = 0;
        break;
      case 3:
        if(PN == 2)sign = 1;
        else if(PN == 0)sign = -1;
        else sign = 0;
        break;
    }
  }
  PN = N;
}

/*int differentValue(float value){
  float pre_value;
  if(pre_value != value){
    Serial.println(value);
    pre_value = value;
  }
}*/

void loop() {
  time = micros();
  //Serial.println(time-tt0);
  //Serial.println(N);
  //Serial.print(m_nValueA);
  //Serial.print(m_nValueB);
  //Serial.println(PR);
  //differentValue(PR);
  if(pre_PR != PR && PR != 0 && sign != 0){
    if(PR < 70000){//ほぼ止まってる状態の時以外>Vを計算
      V = sign*1000/float(PR);
    }
    else V = 0;
    if(abs(V-pre_V) > 0.5){//加速度がaを越えたとき値を反映しない
      V = pre_V;
    }
    pre_V = V;
    Serial.println(V);
    pre_PR = PR;
  }
}



