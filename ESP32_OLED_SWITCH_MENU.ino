#include<EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MainMenuButton 27
#define SubMenuButton 15
#define SelectSubMenuValueButton 23
#define pagesButton 13


int MainMenuSelect = 0;
int SubMenuSelect = 0;
int SelectSubMenuValue = 0;
int pagesCount = 0;

int totalMenus = 6;
int totalSubMenus = 2;
int totalSubMenuValue = 2;
int totalPages = 3;


int led1 = 2;
int ledstate1 = 0;
int ledstate2 = 0;
int potvalue1;
int potvalue2;

byte led1_address = 1;
byte led2_address = 2;
byte pot1_address = 3;
byte pot2_address = 4;
//int led1_value;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(255);
  pinMode(MainMenuButton, INPUT_PULLUP);
  pinMode(SubMenuButton, INPUT_PULLUP);
  pinMode(SelectSubMenuValueButton, INPUT_PULLUP);
  pinMode(pagesButton, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//  display.clearDisplay();
//  display.setTextColor(WHITE);
//  display.setTextSize(1);
//  display.setCursor(35, 0);
//  display.println("DASHBOARD");
//  display.display();

ledstate1 = EEPROM.read(led1_address);
ledstate2 = EEPROM.read(led2_address);
potvalue1 = EEPROM.read(pot1_address);
potvalue2 = EEPROM.read(pot2_address);

}

void loop() {
  if (digitalRead(MainMenuButton) == LOW) {
    MainMenuSelect++;
    if (MainMenuSelect == totalMenus+1) {
      MainMenuSelect = 0;
    }
        Serial.println(MainMenuSelect);
//    displayMainMenu();
 }
  
  if (digitalRead(SubMenuButton) == LOW) {
    SubMenuSelect++;
    if (SubMenuSelect == totalSubMenus+1) {
      SubMenuSelect = 0;
    }
  }

  if (digitalRead(SelectSubMenuValueButton) == LOW) {
    SelectSubMenuValue++;
//    Serial.println(SelectSubMenuValue);
    if (SelectSubMenuValue == totalSubMenuValue+1) {
      SelectSubMenuValue = 0;
    }
  }

  if (digitalRead(pagesButton) == LOW) {
    pagesCount++;
//    Serial.println(SelectSubMenuValue);
    if (pagesCount == totalPages+1) {
      pagesCount = 0;
    }
  }
  
delay(150);


digitalWrite(led1, ledstate1);


switch(pagesCount){

  case 0:
        BUTTON();
        break;
}
 EEPROM.commit();
}



void BUTTON(){
          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(18, 0);//COL,ROW
          display.println("BUTTON & SWITCH");

          


         switch(MainMenuSelect){
            case 0:
                  display.setCursor(0,12);display.print(" SW1:");display.print("  ON");display.print("   OFF | ");display.print(ledstate1);
                  display.setCursor(0,21);display.print(" SW2:");display.print("  ON");display.print("   OFF | ");display.print(ledstate2); 
                  display.setCursor(0,32);display.print(" PT1:");display.print("  180");display.print("  255 | ");display.print(potvalue1);
                  display.setCursor(0,41);display.print(" PT2:");display.print("  180");display.print("  255 | ");display.print(potvalue2);
                                    
                  break;       
            case 1:
                  display.setCursor(0,12);display.print(">SW1:");display.print("  ON");display.print("   OFF | ");display.print(ledstate1);
                  display.setCursor(0,21);display.print(" SW2:");display.print("  ON");display.print("   OFF | ");display.print(ledstate2);
                  display.setCursor(0,32);display.print(" PT1:");display.print("  180");display.print("  255 | ");display.print(potvalue1);
                  display.setCursor(0,41);display.print(" PT2:");display.print("  180");display.print("  255 | ");display.print(potvalue2);
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(0,12);display.print(">SW1:");display.print("  ON");display.print("   OFF");
                                break;
                         case 1:
                                display.setCursor(0,12);display.print(">SW1:");display.print(" >ON");display.print("   OFF");
                                ledstate1 = 1;
                                EEPROM.write(led1_address, 1);
                                break;
                         case 2:
                                display.setCursor(0,12);display.print(">SW1:");display.print("  ON");display.print("  >OFF");
                                EEPROM.write(led1_address, 0);
                                ledstate1 = 0;
                                break;     
                  }  
                  break;                   
            case 2:
                  display.setCursor(0,12);display.print(" SW1:");display.print("  ON");display.print("   OFF | ");display.print(ledstate1);
                  display.setCursor(0,21);display.print(">SW2:");display.print("  ON");display.print("   OFF | ");display.print(ledstate2);
                  display.setCursor(0,32);display.print(" PT1:");display.print("  180");display.print("  255 | ");display.print(potvalue1);
                  display.setCursor(0,41);display.print(" PT2:");display.print("  180");display.print("  255 | ");display.print(potvalue2);
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(0,21);display.print(">SW2:");display.print("  ON");display.print("   OFF");
                                break;
                         case 1:
                                display.setCursor(0,21);display.print(">SW2:");display.print(" >ON");display.print("   OFF");
                                EEPROM.write(led2_address, 1);
                                break;
                         case 2:
                                display.setCursor(0,21);display.print(">SW2:");display.print("  ON");display.print("  >OFF");
                                EEPROM.write(led2_address, 0);
                                break;     
                  }  
                  break; 
            case 3:
                  display.setCursor(0,12);display.print(" SW1:");display.print("  ON");display.print("   OFF | ");display.print(ledstate1);
                  display.setCursor(0,21);display.print(" SW2:");display.print("  ON");display.print("   OFF | ");display.print(ledstate2);
                  display.setCursor(0,32);display.print(">PT1:");display.print("  180");display.print("  255 | ");display.print(potvalue1);
                  display.setCursor(0,41);display.print(" PT2:");display.print("  180");display.print("  255 | ");display.print(potvalue2);
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(0,32);display.print(">PT1:");display.print("  180");display.print("  255");
                                break;
                         case 1:
                                display.setCursor(0,32);display.print(">PT1:");display.print(" >180");display.print("  255");
                                EEPROM.write(pot1_address, 180);
                                break;
                         case 2:
                                display.setCursor(0,32);display.print(">PT1:");display.print("  180");display.print(" >255");
                                EEPROM.write(pot1_address, 255);
                                break;     
                  }  
                  break;  
            case 4:
                  display.setCursor(0,12);display.print(" SW1:");display.print("  ON");display.print("   OFF | ");display.print(ledstate1);
                  display.setCursor(0,21);display.print(" SW2:");display.print("  ON");display.print("   OFF | ");display.print(ledstate2);
                  display.setCursor(0,32);display.print(" PT1:");display.print("  180");display.print("  255 | ");display.print(potvalue1);
                  display.setCursor(0,41);display.print(">PT2:");display.print("  180");display.print("  255 | ");display.print(potvalue2);
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(0,41);display.print(">PT2:");display.print("  180");display.print("  255");
                                break;
                         case 1:
                                display.setCursor(0,41);display.print(">PT2:");display.print(" >180");display.print("  255");
                                EEPROM.write(pot2_address, 180);
                                break;
                         case 2:
                                display.setCursor(0,41);display.print(">PT2:");display.print("  180");display.print(" >255");
                                EEPROM.write(pot2_address, 255);
                                break;     
                  }  
                  break;  
                  
             case 5:
                 MainMenuSelect = 0;
                  break;
                  } 
                  display.display();    
}


//
//
//void MENU(String pageName, String subMenuValue1,String subMenuValue2, int savedValue1, int savedValue2, int address1, int address2, int value1, int value2, String subMenu1,String subMenu2){
//          display.clearDisplay();
//          display.setTextColor(WHITE);
//          display.setTextSize(1);
//          display.setCursor(17, 0);//COL,ROW
//          display.println(pageName);
////          display.setCursor(0,5);//COL,ROW
////          display.println("---------------------");
//
//          
//          display.setCursor(0,12);display.print(subMenu1+":");display.print(savedValue1);
//          display.setCursor(64,12);display.print(subMenu2+":");display.print(savedValue2); 
//
//         switch(MainMenuSelect){
//            case 0:
//                  display.setCursor(0,40);display.print(" "+subMenu1);display.print(" "+subMenu2);      
//                  display.setCursor(0,55);display.print("Press To Select Menu");
//                  display.display();
//                  break;       
//            case 1:
//                  display.setCursor(0,40);display.print(">"+subMenu1);display.print(" "+subMenu2);   
//                  switch(SubMenuSelect){
//                         case 0:
////                                EEPROM.write(pot1_address, pot1_value);
//                                display.setCursor(10,55);display.print("  ["+subMenuValue1+"] ");display.print("   ["+subMenuValue2+"]");
//                                display.display(); 
//                                break;
//                         case 1:
//                                EEPROM.write(address1, value1);
//                                display.setCursor(10,55);display.print("=>["+subMenuValue1+"] ");display.print("   ["+subMenuValue2+"]");
//                                display.display(); 
//                                break;
//                         case 2:
//                                EEPROM.write(address1, value2);
//                                display.setCursor(10,55);display.print("  ["+subMenuValue1+"] ");display.print(" =>["+subMenuValue2+"]");
//                                display.display(); 
//                                break;     
//                  }  
//                  break;                   
//            case 2:
//                  display.setCursor(0,40);display.print(" "+subMenu1);display.print(">"+subMenu2);      
//                  switch(SubMenuSelect){
//                         case 0:
//                                display.setCursor(10,55);display.print("  ["+subMenuValue1+"] ");display.print("   ["+subMenuValue2+"]");
//                                display.display(); 
//                                break;
//                         case 1:
//                                EEPROM.write(address2, value1);
//                                display.setCursor(10,55);display.print("=>["+subMenuValue1+"] ");display.print("   ["+subMenuValue2+"]");
//                                display.display(); 
//                                break;
//                         case 2:
//                                EEPROM.write(address2, value2);
//                                display.setCursor(10,55);display.print("  ["+subMenuValue1+"] ");display.print(" =>["+subMenuValue2+"]");
//                                display.display(); 
//                                break;     
//                  }  
//                  break;  
//
//                  }     
//}
