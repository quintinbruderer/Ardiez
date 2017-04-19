import processing.serial.*;
float[] numbers = new float[512];
int idx = 0;
boolean full = false;

//PImage img;
Serial myPort;
String val;
float val2;
color c = color(82);
//float c;
void setup(){
  val = "0.00";
  val2 = 79.00;
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  size(1024,768);
  //img = loadImage("puppy.jpg");
}

void draw(){
  background(c);
  if (myPort.available()>0){
    val = myPort.readStringUntil('\n');
    println(val);
    if (val != null) {
    numbers[idx] = float(val);
    idx++;
    
    if (idx >= 511){
      idx = 0;
      full = true;
    }
   }
  }
  
  else{
    val = "gary";
  }  
    if(full == true){
      float mean = 0;
      for (int i = 0; i < numbers.length; i++){
        mean = mean + numbers[i];
      }
      val2 = mean/512;
 //     val2 = float(val);
      if (str(val2) == "NaN"){
        c = color(30);
      }
      else if (val2 <= 75.00){
        c = color(15,15,200,10); //color is bluish
      }
      else if (val2 > 75.00 && val2 < 80.00){
        c = color(200,200,10,10); //color is yellowish
      }
      else if (val2 >=80.00){
        c = color(200,30,30,10); //color is red
      }
     c = map(val2, 70.0, 73.0, 0.0, 255.0);
     c = color(0,c,0);
    }
}
  