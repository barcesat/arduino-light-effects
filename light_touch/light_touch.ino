#include <LEDFader.h>


int leds[2] = {
  //A RGB
  5,6
};

LEDFader ledR_A; LEDFader ledG_A; 

const int buttonPin1 = 2;     // the number of the pushbutton pin
const int buttonPin2 = 3;     // the number of the pushbutton pin


int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0; 


//byte color = 0;
byte R_A,G_A = 0;

int duration_A = 2000;
int duration_B = 2000;
int a = 0;

void setup() {
    // initialize the serial communication:
  Serial.begin(9600);
  //pinMode(ledPin1, OUTPUT);   
  //pinMode(ledPin2, OUTPUT);   
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT_PULLUP);     
  pinMode(buttonPin2, INPUT_PULLUP);     



ledR_A = LEDFader(leds[0]);
ledG_A = LEDFader(leds[1]);
}

void loop() {
//a=0;
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  
  if (buttonState1 == LOW && buttonState2 == LOW) a = 0; 
  if (buttonState1 == HIGH && buttonState2 == LOW) a = 1;
  if (buttonState1 == LOW && buttonState2 == HIGH) a = 2;
  if (buttonState1 == HIGH && buttonState2 == HIGH) a = 3;
  //else ledfade1 = 0;

  //else ledfade2 = 0;
  Serial.println(a);
 //CONDITIONS TO UPDATE FADE   
    if (a==0){duration_A = 0; duration_B = 0; R_A = 255; G_A = 255; } //f R
    else if (a==1){duration_A = 500;  duration_B = 0; R_A = 255; G_A = 255; } //f R
    else if (a==2){duration_A = 0;  duration_B = 500; R_A = 255; G_A = 255; } //f R
    else if (a==3){duration_A = 500;  duration_B = 500; R_A = 255; G_A = 255; } //f R
    //CHECK AND SET UPDATE OF FADES
    if (ledR_A.is_fading() == false) {
      if (ledR_A.get_value() == 0) ledR_A.fade(R_A, duration_A);
      else ledR_A.fade(0, duration_A);}
    
    if (ledG_A.is_fading() == false) {
      if (ledG_A.get_value() == 0) ledG_A.fade(G_A, duration_B);
      else ledG_A.fade(0, duration_B);}
    
    

// call to update
    ledR_A.update(); ledG_A.update(); 
 
}


