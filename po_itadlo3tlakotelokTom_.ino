#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display; 
#include <Fonts/FreeMono9pt7b.h>
//#define SCREEN_WIDTH 128 // OLED display width,  in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // create SSD1306 display object connected to I2C

const int buttonPin1 = 8, buttonPin2 = 3, buttonPinR = 2, buttonPinN = 6, buttonPinD = 4;  // the number of the pushbutton pins
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int button1_State = 0, button2_State = 0, buttonR_State = 0, buttonN_State = 0, buttonD_State = 0;  // variable for reading the pushbuttons status
int count_value  = 0;
int count_value1 = 150;
int prestate  = 0;
int prestate1 = 0;
int maximum = 200;
int minimum = 150;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output
  // LED flashes during both increment and decrement of counter
  // pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPinR, INPUT);
  pinMode(buttonPinN, INPUT);
  pinMode(buttonPinD, INPUT);
    
  delay(200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.setTextWrap(false);
  display.dim(0);
}
 

void loop() {
  // read the state of the pushbutton
  button1_State = digitalRead(buttonPin1);
  button2_State = digitalRead(buttonPin2);
  buttonR_State = digitalRead(buttonPinR);
  buttonN_State = digitalRead(buttonPinN);
  buttonD_State = digitalRead(buttonPinD);

  // reset value
  if (buttonR_State == HIGH) {
    count_value = 0;
  } 
  
  // counter increment if the pushbutton 1 is pressed.
  else if (button1_State == HIGH && prestate == 0) {
    count_value++;
    Serial.println(count_value);
    // turn LED on
    // digitalWrite(ledPin, HIGH);
    delay(100);
    // turn LED off
    // digitalWrite(ledPin, LOW);
    prestate = 1;
  }

  // counter decrement if the pushbutton 2 is pressed.
  else if (button2_State == HIGH && prestate == 0) {
    count_value--;
    Serial.println(count_value);
    // turn LED on
    // digitalWrite(ledPin, HIGH);
    delay(100);
    // turn LED off
    // digitalWrite(ledPin, LOW);
    prestate = 1;
  } 
  
  else if (button1_State == LOW && button2_State == LOW) {
    prestate = 0;
  }

  // counter nastavení gramů na otáčku šneku +
  if (buttonN_State == HIGH && prestate1 == 0) {
     count_value1++;
   //count_value1 += 10;

    // nast. max hodnoty??? nejde ---- pokud je count_value1 vetsi nez 200 -> count_value1 se nastavi zpet na 200
    if (count_value1 > 200) {
      count_value1 = 200;
    }
     
    Serial.println(count_value1);
    // turn LED on
    // digitalWrite(ledPin, HIGH);
    delay(100);
    // turn LED off
    // digitalWrite(ledPin, LOW);
    prestate1 = 1;
  }

  // counter nastavení gramů na otáčku šneku -
  if (buttonD_State == HIGH && prestate1 == 0) {
      count_value1--;
    //count_value1 -= 10;

    // nast. min hodnoty??? nejde ---- pokud je count_value1 mensi nez 150 -> count_value1 se nastavi zpet na 150
    if (count_value1 < 150) {
      count_value1 = 150;
    }

    Serial.println(count_value1);
    // turn LED on
    // digitalWrite(ledPin, HIGH);
    delay(100);
    // turn LED off
    // digitalWrite(ledPin, LOW);
    prestate1 = 1;
    }

  if (buttonN_State == LOW && buttonD_State == LOW) {
    prestate1 = 0;
  } 

  display.clearDisplay();

  //display.setFont(&FreeMonoBold9pt7b);
  //display.setFont(&FreeSerif9pt7b);
  display.setFont(&FreeMono9pt7b);
  //display.setTextSize(0);

  display.setCursor(0, 10);
  display.println("Tun:");
  display.setCursor(42, 10);
  display.print((count_value*count_value1)*0.000001, 6); // Nefunguje(množství ot*korekce v gramech
  //display.print((count_value*0.17)/1000000, 6);//Funguje
  display.setCursor(34, 28);
  display.println("g");
  display.setCursor(0, 28);
  display.print(count_value1);
  //display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(50, 28);
  display.println("/");
  display.setCursor(60 , 28);
  display.print(count_value);  //počet otáček šneku
  display.println();

  display.display();
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH); 
}
  
