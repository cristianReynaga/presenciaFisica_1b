//Motor 1
void avanzar(){
  digitalWrite(directionPin, LOW);
  digitalWrite(stepsPin, HIGH);  
  digitalWrite(stepsPin, LOW); 
  delayMicroseconds(velocity); 
}

void retroceder(){
  digitalWrite(directionPin, HIGH);
  digitalWrite(stepsPin, LOW);  
  digitalWrite(stepsPin, HIGH); 
  delayMicroseconds(velocity);    
}

//Motor 2
void avanzar2(){
  digitalWrite(directionPin2, LOW);
  digitalWrite(stepsPin2, HIGH);  
  digitalWrite(stepsPin2, LOW); 
  delayMicroseconds(velocity); 
}

void retroceder2(){
  digitalWrite(directionPin2, HIGH);
  digitalWrite(stepsPin2, LOW);  
  digitalWrite(stepsPin2, HIGH); 
  delayMicroseconds(velocity);    
}

void calibration(){
  //igual a avanzar
  digitalWrite(directionPin, LOW);
  digitalWrite(stepsPin, HIGH);  
  digitalWrite(stepsPin, LOW); 
  delayMicroseconds(velocityCal);
}
void calibration2(){
  //igual a avanzar2
 digitalWrite(directionPin2, LOW);
  digitalWrite(stepsPin2, HIGH);  
  digitalWrite(stepsPin2, LOW); 
  delayMicroseconds(velocityCal); 
}
