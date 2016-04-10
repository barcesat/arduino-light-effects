#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

boolean DBG = false;

//Serial Receive
byte inByte = 0;         // incoming serial byte
//unsigned int Buffer[RAWBUF];

// RF Receive
RH_ASK ASKRX;
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    uint8_t msg[RH_ASK_MAX_MESSAGE_LEN] = {0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x32 };//"hello2"
    uint8_t msg1[RH_ASK_MAX_MESSAGE_LEN] = {0x65, 0x79, 0x65, 0x65, 0x79, 0x65 };//"eyeeye"
    uint8_t msg1[RH_ASK_MAX_MESSAGE_LEN] = {0x79, 0x65, 0x6C, 0x6C, 0x6F, 0x31 };//"yello1"
    
// Led strip
byte redled1 = 26;
byte redled2 = 24;
byte redled3 = 28;
byte redled4 = 5;
byte redled5 = 6;
byte redled6 = 7;
byte greenled1 = 30;
byte greenled2 = 9;
byte greenled3 = 10;
byte greenled4 = 49;
byte greenled5 = 40;
byte greenled6 = 42;


boolean ledState = HIGH;   

void setup() {
Serial.begin(9600);
    if (!ASKRX.init())   Serial.println("init failed");
  pinMode(redled1, OUTPUT);    
  pinMode(redled2, OUTPUT);   
  pinMode(redled3, OUTPUT);    
  pinMode(greenled1, OUTPUT);
  pinMode(greenled2, OUTPUT);
  pinMode(greenled3, OUTPUT);  
  pinMode(blueled1, OUTPUT);     
  pinMode(blueled2, OUTPUT);     
  pinMode(blueled3, OUTPUT);     
  digitalWrite(greenled1, HIGH);
  digitalWrite(greenled2, HIGH);
  digitalWrite(greenled3, HIGH);
  digitalWrite(redled1, LOW);
  digitalWrite(redled2, LOW);
  digitalWrite(redled3, LOW);
  digitalWrite(blueled1, LOW);
  digitalWrite(blueled2, LOW);
  digitalWrite(blueled3, LOW);
}

void loop() {
    if (ASKRX.recv(buf, &buflen)) // Non-blocking
    {//	int i;
	// Message with a good checksum received, dump it.
 	//ASKRX.printBuffer("Got:", buf, buflen);
 if (DBG) {
         Serial.print("got: ");
        for ( uint8_t i = 0; i < buflen; i++)  {
   	if (i % 16 == 15) //if i==255 go down a line
	    Serial.println(buf[i], HEX);
	else
	{  Serial.print(buf[i], HEX);
	    Serial.print(' ');
	}
    }
    Serial.println("");
 }
    
    //compare with trigger code
    if (buf[0] == msg[0] && buf[1] == msg[1] && buf[2] == msg[2] && buf[3] == msg[3] && buf[4] == msg[4] && buf[5] == msg[5]) {
    //light up fixture 1
    //rotating green (or fixed) - normal
    }
    else if (buf[0] == msg1[0] && buf[1] == msg1[1] && buf[2] == msg1[2] && buf[3] == msg1[3] && buf[4] == msg1[4] && buf[5] == msg1[5]) {
  //light up fixture 2
  // flashing yellow - locking
    }
    
      //light up fixture 3
  // rotating yellow - escaping
  
    //light up fixture 3
  // flashing red - hit
    }
}

void serialEvent() {
  while (Serial.available()) {
       inByte = Serial.read();
     if (DBG) {Serial.println(inByte, HEX);}
      if (inByte == 0x31) { // Send targetcode
       
      }
      else if (inByte == 0x32) { // Send owncode
      
      }
      else if (inByte == 0x33) { // Send lockcode
      
      }
      
      if (DBG) {Serial.println("cmd rec");}

	} 
}
