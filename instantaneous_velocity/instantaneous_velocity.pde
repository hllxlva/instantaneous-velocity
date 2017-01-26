// シリアルライブラリを取り入れる
import processing.serial.*;

//インスタンスを用意
Serial myPort;

int x=100; //図形のx座標の変数を用意

void setup(){
  size(256,256);
  
  //シリアルポートの設定
  //"/dev/tty.usbmodem1411"の部分を前述の「シリアポートを選択する」で選択したシリアルポートに合わせて書き換える
  myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw(){
  background(225);
  
  ellipse(x,100,50,50);
}

void serialEvent(Serial p){
  //変数xにシリアル通信で読み込んだ値を代入
  x = p.read();
  println(x);