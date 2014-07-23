
void serialEvent(Serial p) {
  // handle incoming serial data
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    println( inString );   // echo text string from Arduino
  }
}


void sendMessage(char tag, int index, int value) {
  // send the given index and value to the serial port
  myPort.write(HEADER);
  myPort.write(tag);

  char i = (char)(index / 256); // msb
  myPort.write(i);
  i = (char)(index & 0xff);  // lsb
  myPort.write(i);

  char c = (char)(value / 256); // msb
  myPort.write(c);
  c = (char)(value & 0xff);  // lsb
  myPort.write(c);
}

/**  Mensaje Ajuste inicial
 *
 */
void sendMessageAdjustment(char tag, int index, int value) {
  // send the given index and value to the serial port
  myPort.write(HEADER_ADJUSTMENT);
  myPort.write(tag);

  char i = (char)(index / 256); // msb
  myPort.write(i);
  i = (char)(index & 0xff);  // lsb
  myPort.write(i);

  char c = (char)(value / 256); // msb
  myPort.write(c);
  c = (char)(value & 0xff);  // lsb
  myPort.write(c);
}
