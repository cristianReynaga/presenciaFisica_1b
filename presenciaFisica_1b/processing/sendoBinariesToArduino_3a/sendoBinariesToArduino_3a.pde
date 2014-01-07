/* SendingBinaryToArduino
 * Language: Processing
 
 *480 pasos en x
 
 */
import processing.serial.*;
import ddf.minim.*;

AudioPlayer player;
Minim minim;
int loopCounter;


Serial myPort;  // Create object from Serial class
public static final char HEADER = '|';
public static final char HEADER_ADJUSTMENT = '#';
public static final char FORWARD_X  = 'F';
public static final char BACKWARD_X  = 'B';
public static final char FORWARD_Y  = 'G';
public static final char BACKWARD_Y  = 'N';
public static final char ADJUSTMENT  = 'A';



// Ajustes
int xInitRaceForward=0;
int xEndRaceForward=1020; //full step = 500

int xInitRaceBackward=0;
int xEndRaceBackward=1017; //full step = 650

int yInitRaceForward=0;
int yEndRaceForward=1020; //full step = 500

int yInitRaceBackward=0;
int yEndRaceBackward=1017; //full step = 650


//dummy
int xPosMovil=0;
int yPosMovil=0;
int xPosDestino=0;
int yPosDestino=0;
int xLastPos=0;
int yLastPos=0;
int xOffset=10;
int yOffset=40;


boolean bXMove=true;
boolean bAdjustment=true;
boolean bAutoMode=false;
boolean bCalibration=true;
int fps=17;

//Lista
String[] lines;
int index = 0;

void setup()
{
  size(480, 400);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  rectMode(CENTER);

  minim = new Minim(this);
  player = minim.loadFile("groove.mp3", 2048);

  frameRate(fps);
  lines = loadStrings("positions.txt");
  //player.loop(2);
}

void draw() {
  background(100);
  
  if (bCalibration) {
    delay(1000);
    sendMessage(ADJUSTMENT, 0, 100);
    println("calibre");
    delay(5000);
  }
  bCalibration=false;
  bAutoMode=true;
  
  if (bAutoMode) {
    bXMove=true;

    //Lista
    if (index < lines.length) {
      String[] pieces = split(lines[index], '\t');
      if (pieces.length == 2) {
        int x = int(pieces[0]) * 2;
        int y = int(pieces[1]) * 2;

        xPosDestino=xOffset + int(pieces[0]) * 2;
        yPosDestino= yOffset + int(pieces[1]) * 2;

        point(x, y);
      }
      // Go to the next line for the next run through draw()
      index = index + 1;
      if (index==lines.length) {
        index=0;
      }
    }
  }
  /////
  //MOTOR1
  //Backward_X

  if (bXMove) {
    //println(xPosDestino);
    //Motor 1----------
    if ( xPosMovil < xPosDestino) {
      xLastPos=xPosMovil;   
      for (int i = xLastPos; i<xPosDestino; i++) {
        // println(i +"__"+xPosDestino+" amor");
        if (i==xPosDestino-1) {
          xPosMovil=xPosDestino;

          sendMessage(BACKWARD_X, xLastPos, xPosDestino);
          //println(lastPos +"---------__"+xPosDestino);

          bXMove=false;
          // println("LISSTOOO");
        }
      }
    }

    //
    // FORWARD_X

    if (xPosMovil > xPosDestino) { 
      xLastPos=xPosMovil;

      //println(xLastPos +"---------"+xPosDestino);
      for (int i =xLastPos; i> xPosDestino;i--) {
        //println(lastPos +"__"+xPosDestino);
        if (i==xPosDestino+1) {
          xPosMovil=xPosDestino-1;
          sendMessage(FORWARD_X, xPosDestino, xLastPos);
          bXMove=false;
          //println("Listoo");
        }
      }
    }
    //--------

    //Motor 2----
    //BACKWARD_Y
    if ( yPosMovil < yPosDestino) {
      yLastPos=yPosMovil;   
      for (int i = yLastPos; i<yPosDestino; i++) {
        //println(i +"__"+yPosDestino+" amor");
        if (i==yPosDestino-1) {
          yPosMovil=yPosDestino;

          sendMessage(BACKWARD_Y, yLastPos, yPosDestino);
          //println(lastPos +"---------__"+xPosDestino);

          bXMove=false;
          //println("LISSTOOO");
        }
      }
    }
    //Forward_Y
    if (yPosMovil > yPosDestino) { 
      yLastPos=yPosMovil;

      //println(yLastPos +"---------"+yPosDestino);
      //println("corazon");
      for (int i =yLastPos; i> yPosDestino;i--) {
        //println(lastPos +"__"+xPosDestino);
        if (i==yPosDestino+1) {
          yPosMovil=yPosDestino-1;
          sendMessage(FORWARD_Y, yPosDestino, yLastPos);


          bXMove=false;
          //println("Listoo");
        }
      }
    }
  }
  //movil
  fill(0xFF0000FF);
  rect(xPosMovil, yPosMovil, 20, 20);

  //posicion seteada
  fill(255);
  noStroke();
  ellipse(xPosDestino, yPosDestino, 80, 80);
  fill(255, 0, 0);

  //xPosDestino = mouseX;
  //yPosDestino = mouseY;
  delay(100);
}

void mousePressed() {
  xPosDestino = mouseX;
  yPosDestino = mouseY;
  bXMove=true;
}



void keyPressed() {
  if (key=='a') {
    sendMessage(ADJUSTMENT, 100, 100);
    println("AAAAA");
  }

  if (key=='f') {
    sendMessage(FORWARD_X, xInitRaceForward, xEndRaceForward);
    println("full");
  }

  if (key=='b') {
    sendMessage(BACKWARD_X, xInitRaceBackward, xEndRaceBackward);
    println("fulBack");
  }
  if (key=='s') {
    sendMessage(BACKWARD_X, 0, 0);
    println("stop");
  }

  if (key=='q') {
    //bCalibration=true;
    sendMessage(ADJUSTMENT, 0, 100);
  }
}


void ajuste() {
  sendMessage(ADJUSTMENT, 0, 0);
}



void stop()
{
  // always close Minim audio classes when you are done with them
  player.close();
  minim.stop();

  super.stop();
}

