#include <Adafruit_CircuitPlayground.h>


int capIndex[5] = {3,2,0,1,6};
float pitches[20] = {65, 131, 262, 523, 1047,
                     82, 165, 330, 659, 1318,
                     87, 175, 349, 698, 1397,
                     98, 196, 392, 784, 1568,
                     };
int key = 0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

}

void loop() {
  for (int i=0; i<5; i++) {
    if(CircuitPlayground.readCap(capIndex[i])>600){
      CircuitPlayground.speaker.enable(true);
      CircuitPlayground.playTone(pitches[i+key],100,false);


    } 
  }
  Serial.print("X: "); Serial.print(CircuitPlayground.motionX());
  Serial.print(" \tY: "); Serial.print(CircuitPlayground.motionY());
  Serial.print(" \tZ: "); Serial.print(CircuitPlayground.motionZ());
  Serial.println(" ");
  if (CircuitPlayground.motionY()>=7){
    key = 15;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,100,255,170);
    }
      
  } else if (CircuitPlayground.motionY()>=0 && CircuitPlayground.motionY()<7 ){
    key = 10;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,0,100,200);
    }
  } else if (CircuitPlayground.motionY()<0 && CircuitPlayground.motionY()>-7 ){
    key = 5;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,170,150,255);
    }
  } else if (CircuitPlayground.motionY()<= -7 ){
    key = 0;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,255,100,170);
    }
  }
    

    
}
