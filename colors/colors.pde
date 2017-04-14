import processing.serial.*;

PImage img;


Serial myPort;
String val;
color c = color(156,156,156);
float val2;

void setup(){
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  size(1024,768);
  img = loadImage("puppy.jpg");

  val2 = float(0);
  val = "0.00";
}
void draw(){

  if (myPort.available()>0){
    val = myPort.readStringUntil('\n');
      println(val);  
  }
  //image(img,0,0);
  val2 = float(val);
  background(img);
    if (str(val2) == "NaN"){
      println("miss");
    }
  
    else {
      if (val2 <= 80.0){
        tint(15,15,(256-(val2*(3.3125))), 126); //color is bluish
      }
      else if (val2 > 80.0 && val2 < 85.0){
        tint(256-((val2-80)*52.1),256-((val2-80)*52.1),10,126); //color is yellowish
      }
      else if (val2 >=85.0){
        tint(256 - (val2-85.0)*17,30,30,126); //color is red
      }
      else {
        println("null");
      }
    }
  }