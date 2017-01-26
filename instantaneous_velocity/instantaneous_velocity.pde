import  processing.serial.*;

Serial  serial;
int[]   data;

void setup() {  
  size(1000, 1000);
  data = new int [width];
  serial = new Serial( this, Serial.list()[0], 250000 );
}

void draw() {
  background(10);
  strokeWeight(2); 
  stroke(0, 255, 0);

  // グラフの描画
  for (int i=0; i<data.length-1; i++) {
    line( i, convToGraphPoint(data[i]), i+1, convToGraphPoint(data[i+1]) );
  }
}

void serialEvent(Serial port) {  
  if ( port.available() >= 3 ) {
    if ( port.read() == 'H' ) {
      int high = port.read();      
      int low = port.read();
      int recv_data = high*256 + low;
      
      // 時系列データを更新
      for (int i=0; i<data.length-1; i++) {
        data[i] = data[i+1];
      }
      data[data.length-1] = recv_data;
    }
  }
}

float convToGraphPoint(int value) {
  return (height - value*height/1024.0);
}