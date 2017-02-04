//Arduino Pin - Rotary Encode
unsigned long time;//時間を格納する君
unsigned long t0 = 0;//ひとつ前の時間を格納する君
int dRotAPin = 2;//ロータリーエンコーダA相
int dRotBPin = 3;//ロータリーエンコーダB相
int N;//パルスの番号格納
int sign = 1;//回転方向
unsigned long PR;//Pulse Rate//
int PN;//Pulse Number//
unsigned long pre_PR;//ひとつ前の
volatile int m_nValueB = 0;//B相の値
volatile int m_nValueA = 0;//A相の値
void va();//velocityA//
void vb();//velocityB//
int number();//0,1,2,3//
float V;//最終エンコーダの速度出力


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
  //数字割り当て
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

  //numberに入る周期をPRとする
  PR = time-t0;
  t0 = time;
  if(PR > 1000){//周期が大きいときにのみ符号がどっちかを見る
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
  PN = N;//ナンバー割り当て
}

void loop() {
  time = micros();
  //Serial.println(time-tt0);
  //Serial.println(N);
  //Serial.print(m_nValueA);
  //Serial.print(m_nValueB);
  //Serial.println(PR);
  if(pre_PR != PR && PR != 0 && sign != 0){//前の値と変わったとき，取りこぼした時以外
    if(PR < 70000){//ほぼ止まってる状態の時以外>Vを計算
      //速度の単位[pluse/ms];
      //V = sign*1000/float(PR);//本来必要な指令だがシリアル用に改善
      V = 1000/float(PR);//本来いらない
    }
    else V = 0;
    
    V = 100*V;//100倍 = 速度の単位[100×pluse/ms]
    int value = V;
    Serial.write('H');             // ヘッダの送信
    Serial.write(highByte(value)); // 上位バイトの送信
    Serial.write(lowByte(value));  // 下位バイトの送信
    Serial.write(sign+1); //+-符号の送信
    //Serial.println();
    //Serial.write(V);
    pre_PR = PR;
  }
}
