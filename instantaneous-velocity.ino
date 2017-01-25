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
int f = 0;
int N;
int lastN;//last number
int PR[100];//Pulse Rate
int PN[100];//Pulse Number
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
  for(i=0;i>=f;i++){
    PR[i+1] = PR[i];
    PN[i+1] = PN[i];
  }
  PR[0] = time-t0;
  t0 = time;
  PN[0] = N;
  f++;
  /*if((m_nValueA == 1 && m_nValueB == 1 )||( m_nValueA == 0 && m_nValueB == 0)){
    degreeA += 0.5;
    degree += 0.25;
  }else if((m_nValueA == 1 && m_nValueB == 0 )||( m_nValueA == 0 && m_nValueB == 1)){
    degreeA -= 0.5;
    degree -= 0.25;
  }*/
}

void vb(){
  m_nValueB = digitalRead(dRotBPin);
  number();
  for(i=0;i<=f;i++){
    PR[i+1] = PR[i];
    PN[i+1] = PN[i];
  }
  PR[0] = time-t0;
  t0 = time;
  PN[0] = N;
  f++;
  /*if((m_nValueA == 1 && m_nValueB == 1 )||( m_nValueA == 0 && m_nValueB == 0)){
    degreeB -= 0.5;
    degree -= 0.25;
  }else if((m_nValueA == 1 && m_nValueB == 0 )||( m_nValueA == 0 && m_nValueB == 1)){
    degreeB += 0.5;
    degree += 0.25;
  }*/
}

/*int vCapture(){
  switch(i){
    case 1:v[0]=hozonnsitayatu 
  }
}*/

int number(){ 
  N = m_nValueA + 2 * m_nValueB;
  Serial.println("|");
  switch(N){
    case 2:
      N = 3;
      break;
    case 3:
      N = 2;
      break;
  }
}

/*int DM(){//missganaikadouka
  
}*/

void loop() {
  time = micros();
  
  f = 0;
  //Serial.println(time-tt0);
  //Serial.println(N);
  //Serial.print(m_nValueA);
  //Serial.print(m_nValueB);
  //Serial.print(" | ");
  Serial.println(PN[0]);
  /*if (time-tt0 >= 1000){
    for(i=0;i<=f;i++){
      Serial.println(PR[i]);
    }
    
    //Serial.print(" | ");
    //Serial.print(degreeB);
    //Serial.print(" | ");
    //Serial.println(degree);
    //degreeA=0;
    //degreeB=0;
    //degree=0;
    tt0=time;
  }*/
}
