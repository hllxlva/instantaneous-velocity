import processing.serial.*;

Serial  serial;
int[]   data;
int[]   mani_data;//manipulated data
int[]   mani_data2;
int[]   n = new int [5];
int     min_n;
int     max_n;
int     pre_data;
int     sign;
float   r = 0.75;//
int     t;

void setup(){
  size(2500,1300,P3D);
  data = new int [width];
  mani_data = new int [width];
  mani_data2 = new int [width];
  serial = new Serial( this, Serial.list()[0], 250000 );
  background(0);
  stroke(0,255,0);
}

void draw(){
  background(0);
  translate(0, height/2.0);
  rotateX(PI);
  stroke(0,0,255);
  for (int i=0; i<data.length-1; i++) {
    line( i, data[i], i+1, data[i+1] );
  }
  stroke(0,255,0);
  for (int i=0; i<mani_data.length-1; i++) {
    line( i, mani_data[i], i+1, mani_data[i+1] );
  }
  stroke(255,0,0);
  for (int i=0; i<mani_data2.length-1; i++) {
    line( i, mani_data2[i], i+1, mani_data2[i+1] );
  }
}

void serialEvent(Serial port) {  
  if ( port.available() >= 4 ) {
    if ( port.read() == 'H' ) {
      int high = port.read();
      int low = port.read();
      int Sign = port.read();
      int recv_data = high*256 + low;
      
      // 時系列データを更新
      for (int i=0; i<data.length-1; i++) {
        data[i] = data[i+1];
      }
      sign = Sign-1;//0,2のデータから1,-1に
      data[data.length-1] = recv_data*sign;
      
      //5つデータを取ってきて最大値最小値を削除したうえで平均を取る
      for(int i = 1; i <= 5; i++){
        n[i-1] = data[data.length-i];//最新の5つのデータを取得
      }
      int max = n[0];  //とりあえず最大値をn[0]に設定して変数maxに代入
      max_n = 0;
      int min = n[0];  //とりあえず最小値をn[0]に設定して変数minに代入
      min_n = 0;
      for (int i=0; i<5; i++) {
        if (max < n[i]) {  //現在の最大値よりも大きい値が出たら
          max = n[i];  //変数maxに値を入れ替える
          max_n = i;  //maxが何番か
        }
        else if (min > n[i]) {  //現在の最小値よりも小さい値が出たら
          min = n[i];  //変数minに値を入れ替える
          min_n =i;  //minが何番か
        }
      }
      
      //操作したデータを更新
      for (int i=0; i<mani_data.length-1; i++) {
        mani_data[i] = mani_data[i+1];
      }
      //最大値最小値を削除したうえで平均を取る
      mani_data[mani_data.length-1] = 0;
      for (int i=0; i<5; i++) {
        if(i != min_n && i != max_n){
          mani_data[mani_data.length-1] += n[i];
        }
      }
      mani_data[mani_data.length-1] = mani_data[mani_data.length-1]/3;
      //pre_data = data;
      
      //操作したデータを更新2回目
      for (int i=0; i<mani_data2.length-1; i++) {
        mani_data2[i] = mani_data2[i+1];
      }
      //一次ローパスフィルター
      mani_data2[mani_data.length-1] = int(mani_data2[mani_data.length-1]*r+mani_data[mani_data.length-1]*(1-r));
    }
  }
}