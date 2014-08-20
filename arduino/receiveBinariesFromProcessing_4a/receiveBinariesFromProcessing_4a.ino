//BinaryDataFromProcessing
//Versi´n estable compatible con processing: sendoBinariesToArduino_3b

#define HEADER        '|'
#define HEADER_ADJUSTMENT  '#'
#define FORWARD_X       'F'
#define BACKWARD_X      'B'
#define FORWARD_Y       'G'
#define BACKWARD_Y      'N'
#define ADJUSTMENT    'A'

#define MESSAGE_BYTES  6  // the total bytes in a message
int velocityCal= 5000; //4400 @ 20fps

//Motor1
int velocity= 2500; //4400 @ 20fps
int directionPin = 4;
int stepsPin = 3;
int resetPin = 2;
int halfStepPin=5;

int pasos = 200;

//Motor 2

int directionPin2 = 9;
int stepsPin2 = 8;
int resetPin2 = 7;
int halfStepPin2=6;


int ledPin=13;

//Switch
int sensorPin=11;
int sensorPin2=10;
boolean bSensor=false;
boolean bSensor2=false;
boolean bAdjustment=true;
boolean bCalibration=false;
boolean bCalibration2=false;

int posDestino=150;
int posMovil=0;
int contadorPasos=0;
//Ajuste
int inicioAjuste=0;
int finalAjuste=500;

void setup()
{
  pinMode(directionPin, OUTPUT); 
  pinMode(stepsPin, OUTPUT); 
  pinMode(resetPin, OUTPUT);
  pinMode(halfStepPin, OUTPUT);

  pinMode(directionPin2, OUTPUT); 
  pinMode(stepsPin2, OUTPUT); 
  pinMode(resetPin2, OUTPUT);
  pinMode(halfStepPin2, OUTPUT);

  pinMode(sensorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop(){
  bSensor= digitalRead(sensorPin);
  digitalWrite(halfStepPin, HIGH);
  digitalWrite(halfStepPin2, HIGH);  


  if ( Serial.available() >= MESSAGE_BYTES){
    digitalWrite(resetPin, HIGH); 
    digitalWrite(resetPin2, HIGH); 


     if( Serial.read() == HEADER){
      char tag = Serial.read();
      
      ///////////////
      
      if(tag == ADJUSTMENT){
        bAdjustment=true;
        Serial.print(bAdjustment);
        Serial.println("Inicio Ajuste... ");

        while(bAdjustment==true){
          bCalibration=true;
          bCalibration2=true;

          while(bCalibration==true){
            bSensor= digitalRead(sensorPin);
            calibration();

            if(bSensor==HIGH){
              bCalibration=false;
              Serial.println("sensor 1");
              break;
            }
          }
          while(bCalibration2==true){
            bSensor2= digitalRead(sensorPin2);
            calibration2();

            if(bSensor2==HIGH){
              bCalibration=false;
              Serial.println("sensor 2");
              break;
            }   
          }
          break;
          delay(50);


        }  
      }
      //////////////////

     else if(tag == FORWARD_X){
        int xPos=Serial.read()*256;
        xPos = xPos+ Serial.read();

        int xPosDestino = Serial.read() * 256;
        xPosDestino = xPosDestino + Serial.read();

        Serial.print("Forward_X. Received mouse msg, index = ");
        Serial.print(xPos);
        Serial.print(", value  ");
        Serial.println(xPosDestino);

        for(int i=xPos;i<xPosDestino;i++){
          avanzar();
        }
      }
      //-------
      else if(tag==BACKWARD_X){

        int xPos=Serial.read()*256;
        xPos = xPos+ Serial.read();

        int xPosDestino = Serial.read() * 256;
        xPosDestino = xPosDestino + Serial.read();

        Serial.print("Backward. Received mouse msg, index = ");
        Serial.print(xPos);
        Serial.print(", value  ");
        Serial.println(xPosDestino);

        for(int i=xPos;i<xPosDestino;i++){
          retroceder();
        }
      }

      ///Motor 2 Forward
      else if(tag == FORWARD_Y){
        int xPos=Serial.read()*256;
        xPos = xPos+ Serial.read();

        int xPosDestino = Serial.read() * 256;
        xPosDestino = xPosDestino + Serial.read();

        Serial.print("Forward. Received mouse msg, index = ");
        Serial.print(xPos);
        Serial.print(", value  ");
        Serial.println(xPosDestino);

        for(int i=xPos;i<xPosDestino;i++){
          avanzar2();
        }
      }
      //Motor 2 Backward
      else if(tag==BACKWARD_Y){

        int xPos=Serial.read()*256;
        xPos = xPos+ Serial.read();

        int xPosDestino = Serial.read() * 256;
        xPosDestino = xPosDestino + Serial.read();

        Serial.print("Backward. Received mouse msg, index = ");
        Serial.print(xPos);
        Serial.print(", value  ");
        Serial.println(xPosDestino);

        for(int i=xPos;i<xPosDestino;i++){
          retroceder2();
        }
      }

      //-------
      else if(tag==ADJUSTMENT){

        Serial.println("Inicio ajuste. Received mouse msg ADJUSTMENT.");
        bAdjustment=true;
        if(bAdjustment){
          digitalWrite(resetPin, HIGH);
          retroceder();
          Serial.println("dentro de bAdjustment.");

          if(bSensor){  
            Serial.print("dentro de bSensor.");
            digitalWrite(ledPin, HIGH);

            bAdjustment=false;
            digitalWrite(resetPin, LOW);

          }
          else{
            digitalWrite(ledPin, LOW);    

          }
        }
      }
      else{ 
        Serial.print("got message with unknown tag ");
        Serial.println(tag);
        digitalWrite(resetPin, LOW);         
        digitalWrite(resetPin2, LOW); 
      }
    }
   
  }
  else{
    digitalWrite(resetPin, LOW);         
        digitalWrite(resetPin2, LOW); 
      }
        
}















