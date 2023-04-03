#include<EEPROM.h>
#include <WiFi.h>//for mac address
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#ifdef ARDUINO_AVR_NANO
  const int MainMenuButton = 27;
  const int SubMenuButton = 15;
  const int SelectSubMenuValueButton = 23;
  const int pagesButton = 13;
#elif defined(ESP32)
  const int MainMenuButton = 5;
  const int SubMenuButton = 3;
  const int SelectSubMenuValueButton = A2;
  const int pagesButton = 7;
#endif



int MainMenuSelect = 0;
int SubMenuSelect = 0;
int SelectSubMenuValue = 0;
int pagesCount = 0;

int totalMenus = 4;
int totalSubMenus = 2;
int totalSubMenuValue = 2;
int totalPages = 5;

int pot1_address = 1;
int pot2_address = 2;
int pot3_address = 3;
int pot4_address = 4;

int pot1Dir_address = 7;
int pot2Dir_address = 8;
int pot3Dir_address = 9;
int pot4Dir_address = 10;


byte pot1_value, pot2_value, pot3_value, pot4_value;
byte pot1Dir_value, pot2Dir_value, pot3Dir_value, pot4Dir_value;

String pot1Dir_Type;
String pot2Dir_Type;
String pot3Dir_Type;
String pot4Dir_Type;



int pot1 = 34;
int pot2 = 35;
int potentiometer1;
int potentiometer2;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(255);
  pinMode(MainMenuButton, INPUT_PULLUP);
  pinMode(SubMenuButton, INPUT_PULLUP);
  pinMode(SelectSubMenuValueButton, INPUT_PULLUP);
  pinMode(pagesButton, INPUT_PULLUP);

  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//  display.clearDisplay();
//  display.setTextColor(WHITE);
//  display.setTextSize(1);
//  display.setCursor(35, 0);
//  display.println("DASHBOARD");
//  display.display();

  pot1_value = EEPROM.read(pot1_address);//EEPROM.read(ADDRESS 0-255);
  pot2_value = EEPROM.read(pot2_address);//EEPROM.read(ADDRESS 0-255);
  pot3_value = EEPROM.read(pot3_address);//EEPROM.read(ADDRESS 0-255);
  pot4_value = EEPROM.read(pot4_address);//EEPROM.read(ADDRESS 0-255);

  pot1Dir_value = EEPROM.read(pot1Dir_address);//EEPROM.read(ADDRESS 0-255);
  pot2Dir_value = EEPROM.read(pot2Dir_address);//EEPROM.read(ADDRESS 0-255);
  pot3Dir_value = EEPROM.read(pot3Dir_address);//EEPROM.read(ADDRESS 0-255);
  pot4Dir_value = EEPROM.read(pot4Dir_address);//EEPROM.read(ADDRESS 0-255);
 }

void loop() 
{
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
    
  delay(100);
  
  
  pot1Dir_Type = (pot1Dir_value == 0)?"LFT":"RHT";
  pot2Dir_Type = (pot2Dir_value == 0)?"LFT":"RHT";
  pot3Dir_Type = (pot3Dir_value == 0)?"LFT":"RHT";
  pot4Dir_Type = (pot4Dir_value == 0)?"LFT":"RHT";

  
  
  
  
  if(pot1Dir_value == 1){//left control
  potentiometer1 = map(analogRead(pot1), 4095, 0, pot1_value, 0);
  }
  if(pot1Dir_value == 0){//right control
  potentiometer1 = map(analogRead(pot1), 4095, 0, 0, pot1_value);
  }
  if(pot2Dir_value == 1){//left control
  potentiometer2 = map(analogRead(pot2), 4095, 0, pot2_value, 0);
  }
  if(pot2Dir_value == 0){//right control
  potentiometer2 = map(analogRead(pot2), 4095, 0, 0, pot2_value);
  }
  
  
  
  switch(pagesCount){
  
    case 0:
          Serial.println("Dashboard");
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setTextSize(1);
            display.setCursor(35, 0);//COL,ROW
            display.println("DASHBOARD");
  //          display.setCursor(0,5);//COL,ROW
  //          display.println("---------------------");
  
           display.setCursor(0,12);display.print("POT1: ");display.print(potentiometer1);
           display.setCursor(0,22);display.print("POT2: ");display.print(potentiometer2); 
           display.display();
  
          break;
  
  //potentiometer page******************************************************************************************** 
    case 1:
          Serial.println("Page1");
          potentiometer();   
          break;
          
  //potentiometer settings page********************************************************************************************
    case 2:
          potentiometer_settings();
          break;
    
    case 3:
          settings();
          break;      
    case 4:
          deviceDetails();
          break;
    case 5:
          slaveDeviceDetails();
          break;
                     
  }
  
  EEPROM.commit(); 
}


void potentiometer(){
          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(17, 0);//COL,ROW
          display.println("*POTENTIOMETER*");
//          display.setCursor(0,5);//COL,ROW
//          display.println("---------------------");
          display.setCursor(0,12);display.print("POT1: ");display.print(pot1_value);
          display.setCursor(70,12);display.print("POT2: ");display.print(pot2_value);   
          display.setCursor(0,21);display.print("POT3: ");display.print(pot3_value);
          display.setCursor(70,21);display.print("POT4: ");display.println(pot4_value);

            switch(MainMenuSelect){
            case 0:
                  display.setCursor(0,40);display.print("   P1");display.print("   P2");display.print("   P3");display.print("   P4");      
                  display.setCursor(0,55);display.print("Press To Select Menu");
                  display.display();
                  break;       
            case 1:
                  display.setCursor(0,40);display.print(" =>P1");display.print("   P2");display.print("   P3");display.print("   P4");      
                  switch(SubMenuSelect){
                         case 0:
//                                EEPROM.write(pot1_address, pot1_value);
                                display.setCursor(10,55);display.print("  [180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 1:
                                EEPROM.write(pot1_address, 180);
                                display.setCursor(10,55);display.print("=>[180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 2:
                                EEPROM.write(pot1_address, 255);
                                display.setCursor(10,55);display.print("  [180]");display.print("  =>[255]");
                                display.display(); 
                                break;     
                  }  
                  break;                   
            case 2:
                  display.setCursor(0,40);display.print("   P1");display.print(" =>P2");display.print("   P3");display.print("   P4");      
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(10,55);display.print("  [180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 1:
                                EEPROM.write(pot2_address, 180);
                                display.setCursor(10,55);display.print("=>[180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 2:
                                EEPROM.write(pot2_address, 255);
                                display.setCursor(10,55);display.print("  [180]");display.print("  =>[255]");
                                display.display(); 
                                break;     
                  }  
                  break;  
            case 3:
                  display.setCursor(0,40);display.print("   P1");display.print("   P2");display.print(" =>P3");display.print("   P4");      
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(10,55);display.print("  [180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 1:
                                EEPROM.write(pot3_address, 180);
                                display.setCursor(10,55);display.print("=>[180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 2:
                                EEPROM.write(pot3_address, 255);
                                display.setCursor(10,55);display.print("  [180]");display.print("  =>[255]");
                                display.display(); 
                                break;     
                  }  
                  break;                    
            case 4:
                  display.setCursor(0,40);display.print("   P1");display.print("   P2");display.print("   P3");display.print(" =>P4");      
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(10,55);display.print("  [180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 1:
                                EEPROM.write(pot4_address, 180);
                                display.setCursor(10,55);display.print("=>[180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 2:
                                EEPROM.write(pot4_address, 255);
                                display.setCursor(10,55);display.print("  [180]");display.print("  =>[255]");
                                display.display(); 
                                break;     
                  }  
                  break; 

            case 5:
                  MainMenuSelect = 0;
                  break;                         
                  }     
}



void potentiometer_settings(){
          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(17, 0);//COL,ROW
          display.println("*POT SETTINGS*");

          display.setCursor(0,12);display.print("POT1: ");display.print(pot1Dir_Type);
          display.setCursor(70,12);display.print("POT2: ");display.print(pot2Dir_Type);   
          display.setCursor(0,21);display.print("POT3: ");display.print(pot3Dir_Type);
          display.setCursor(70,21);display.print("POT4: ");display.println(pot4Dir_Type);


           switch(MainMenuSelect){
            case 0:
                  display.setCursor(0,40);display.print("   P1");display.print("   P2");display.print("   P3");display.print("   P4");     
                  display.setCursor(0,55);display.print("Select Pot Direction");
                  display.display();
                  break;          
              
          case 1:
              display.setCursor(0,40);display.print(" =>P1");display.print("   P2");display.print("   P3");display.print("   P4");      
              switch(SubMenuSelect){
                     case 0:
        //                  EEPROM.write(pot1_address, pot1_value);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 1:
                            EEPROM.write(pot1Dir_address, 0);
                            display.setCursor(10,55);display.print("=>LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 2:
                            EEPROM.write(pot1Dir_address, 1);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("=>RIGHT");
                            display.display(); 
                            break;     
              }  
              break;                   
        case 2:
              display.setCursor(0,40);display.print("   P1");display.print(" =>P2");display.print("   P3");display.print("   P4");      
              switch(SubMenuSelect){
                     case 0:
        //                  EEPROM.write(pot1_address, pot1_value);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 1:
                            EEPROM.write(pot2Dir_address, 0);
                            display.setCursor(10,55);display.print("=>LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 2:
                            EEPROM.write(pot2Dir_address, 1);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("=>RIGHT");
                            display.display(); 
                            break;     
              }   
              break;  
        case 3:
              display.setCursor(0,40);display.print("   P1");display.print("   P2");display.print(" =>P3");display.print("   P4");      
              switch(SubMenuSelect){
                     case 0:
        //                  EEPROM.write(pot1_address, pot1_value);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 1:
                            EEPROM.write(pot3Dir_address, 0);
                            display.setCursor(10,55);display.print("=>LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 2:
                            EEPROM.write(pot3Dir_address, 1);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("=>RIGHT");
                            display.display(); 
                            break;     
              }  
              break;                    
        case 4:
              display.setCursor(0,40);display.print("   P1");display.print("   P2");display.print("   P3");display.print(" =>P4");      
              switch(SubMenuSelect){
                     case 0:
        //                  EEPROM.write(pot1_address, pot1_value);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 1:
                            EEPROM.write(pot4Dir_address, 0);
                            display.setCursor(10,55);display.print("=>LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 2:
                            EEPROM.write(pot4Dir_address, 1);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("=>RIGHT");
                            display.display(); 
                            break;     
              }   
              break;                    
            case 5:
                  MainMenuSelect = 0;
                  break;   
              }  
}

void settings(){

          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(17, 0);//COL,ROW
          display.println("SETTINGS");
//          display.setCursor(0,5);//COL,ROW
//          display.println("---------------------");
          

          
         switch(MainMenuSelect){
            case 0:
                  display.setCursor(0,12);display.print(" Factory Reset");
                  display.setCursor(0,22);display.print(" menu1"); 
                  display.setCursor(0,32);display.print(" menu2"); 
                  display.display();
                  break;       
            case 1:
                  display.setCursor(0,12);display.print(">Factory Reset");
                  display.setCursor(0,22);display.print(" menu1"); 
                  display.setCursor(0,32);display.print(" menu2");   
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(10,55);display.print("  [YES] ");display.print("   [NO]");
                                display.display(); 
                                break;
                         case 1:
                               EEPROM.write(pot1_address, 180);
                               EEPROM.write(pot2_address, 180);
                               EEPROM.write(pot3_address, 255);
                               EEPROM.write(pot4_address, 255);
      
                               EEPROM.write(pot1Dir_address, 1);
                               EEPROM.write(pot2Dir_address, 1);
                               EEPROM.write(pot3Dir_address, 0);
                               EEPROM.write(pot4Dir_address, 0);

                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
                                display.display(); 
                                break;
                         case 2:
                               EEPROM.write(pot1_address, pot1_value);
                               EEPROM.write(pot2_address, pot2_value);
                               EEPROM.write(pot3_address, pot3_value);
                               EEPROM.write(pot4_address, pot4_value);
      
                               EEPROM.write(pot1Dir_address, pot1Dir_value);
                               EEPROM.write(pot2Dir_address, pot2Dir_value);
                               EEPROM.write(pot3Dir_address, pot3Dir_value);
                               EEPROM.write(pot4Dir_address, pot4Dir_value);
                                display.setCursor(10,55);display.print("  [YES] ");display.print(" =>[NO]");
                                display.display(); 
                                break;     
                  }  
                  break;                   
            case 2:
                  display.setCursor(0,12);display.print(" Factory Reset");
                  display.setCursor(0,22);display.print(">menu1"); 
                  display.setCursor(0,32);display.print(" menu2");                  
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(10,55);display.print("  [YES] ");display.print("   [NO]");
                                display.display(); 
                                break;
                         case 1:
                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
                                display.display(); 
                                break;
                         case 2:
                                display.setCursor(10,55);display.print("  [YES] ");display.print(" =>[NO]");
                                display.display(); 
                                break;     
                  }  
                  break;  
            case 3:
                  display.setCursor(0,12);display.print(" Factory Reset");
                  display.setCursor(0,22);display.print(" menu1"); 
                  display.setCursor(0,32);display.print(">menu2");                  
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(10,55);display.print("  [YES] ");display.print("   [NO]");
                                display.display(); 
                                break;
                         case 1:
                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
                                display.display(); 
                                break;
                         case 2:
                                display.setCursor(10,55);display.print("  [YES] ");display.print(" =>[NO]");
                                display.display(); 
                                break;     
                  }  
                  break;  
                  }        
            
               
}



void deviceDetails(){

          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(10, 0);//COL,ROW
          display.println("DEVICE DETAILS");
//          display.setCursor(0,5);//COL,ROW
//          display.println("---------------------");
          

          
         switch(MainMenuSelect){
            case 0:
                  display.setCursor(0,12);display.print(" MAC-ID");
                  display.setCursor(0,22);display.print(" menu1"); 
                  display.setCursor(0,32);display.print(" menu2"); 
                  
                  break;       
            case 1:
                  display.setCursor(0,12);display.print(">MAC-ID");
                  display.setCursor(0,22);display.print(" menu1"); 
                  display.setCursor(0,32);display.print(" menu2");  
                  display.setCursor(10,55);display.print(WiFi.macAddress()); 
//                  switch(SubMenuSelect){
//                         case 0:
//                                display.setCursor(10,55);display.print("  [YES] ");display.print("   [NO]");
//                                display.display(); 
//                                break;
//                         case 1:
//                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
//                                display.display(); 
//                                break;
//                         case 2:
//                                display.setCursor(10,55);display.print("  [YES] ");display.print(" =>[NO]");
//                                display.display(); 
//                                break;     
//                  }  
                  break;                   
            case 2:
                  display.setCursor(0,12);display.print(" MAC-ID");
                  display.setCursor(0,22);display.print(">menu1"); 
                  display.setCursor(0,32);display.print(" menu2");                  
//                  switch(SubMenuSelect){
//                         case 0:
//                                display.setCursor(10,55);display.print("  [YES] ");display.print("   [NO]");
//                                display.display(); 
//                                break;
//                         case 1:
//                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
//                                display.display(); 
//                                break;
//                         case 2:
//                                display.setCursor(10,55);display.print("  [YES] ");display.print(" =>[NO]");
//                                display.display(); 
//                                break;     
//                  }  
                  break;  
            case 3:
                  display.setCursor(0,12);display.print(" MAC-ID");
                  display.setCursor(0,22);display.print(" menu1"); 
                  display.setCursor(0,32);display.print(">menu2");  
                                  
//                  switch(SubMenuSelect){
//                         case 0:
//                                display.setCursor(10,55);display.print("  [YES] ");display.print("   [NO]");
//                                display.display(); 
//                                break;
//                         case 1:
//                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
//                                display.display(); 
//                                break;
//                         case 2:
//                                display.setCursor(10,55);display.print("  [YES] ");display.print(" =>[NO]");
//                                display.display(); 
//                                break;     
//                  }  
                  break;  
                  }        
            
           display.display();    
}

void slaveDeviceDetails(){

          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(0, 0);//COL,ROW
          display.println("SLAVE DEVICE DETAILS");
//          display.setCursor(0,5);//COL,ROW
//          display.println("---------------------");
          
           display.setCursor(0,12);display.print("MAC : ");display.print("EC62609B1F14");
           display.setCursor(0,22);display.print("Batt: ");display.print("3.3");display.print(" V");
           display.setCursor(0,32);display.print("RSSI: ");display.print("50");display.print(" dBm"); 
           display.setCursor(0,42);display.print("Temp: ");display.print("35");
           display.setCursor(0,52);display.print("Acce: ");display.print("35");

          
//         switch(MainMenuSelect){
//            case 0:
//                  display.setCursor(0,12);display.print(" MAC-ID");
//                  display.setCursor(0,22);display.print(" menu1"); 
//                  display.setCursor(0,32);display.print(" menu2"); 
//                  
//                  break;       
//            case 1:
//                  display.setCursor(0,12);display.print(">MAC-ID");
//                  display.setCursor(0,22);display.print(" menu1"); 
//                  display.setCursor(0,32);display.print(" menu2");  
//                  display.setCursor(10,55);display.print(WiFi.macAddress()); 
////                  switch(SubMenuSelect){
////                         case 0:
////                                display.setCursor(10,55);display.print("  [YES] ");display.print("   [NO]");
////                                display.display(); 
////                                break;
////                         case 1:
////                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
////                                display.display(); 
////                                break;
////                         case 2:
////                                display.setCursor(10,55);display.print("  [YES] ");display.print(" =>[NO]");
////                                display.display(); 
////                                break;     
////                  }  
//                  break;                   
//            case 2:
//                  display.setCursor(0,12);display.print(" MAC-ID");
//                  display.setCursor(0,22);display.print(">menu1"); 
//                  display.setCursor(0,32);display.print(" menu2");                  
////                  switch(SubMenuSelect){
////                         case 0:
////                                display.setCursor(10,55);display.print("  [YES] ");display.print("   [NO]");
////                                display.display(); 
////                                break;
////                         case 1:
////                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
////                                display.display(); 
////                                break;
////                         case 2:
////                                display.setCursor(10,55);display.print("  [YES] ");display.print(" =>[NO]");
////                                display.display(); 
////                                break;     
////                  }  
//                  break;  
//            case 3:
//                  display.setCursor(0,12);display.print(" MAC-ID");
//                  display.setCursor(0,22);display.print(" menu1"); 
//                  display.setCursor(0,32);display.print(">menu2");                  
////                  switch(SubMenuSelect){
////                         case 0:
////                                display.setCursor(10,55);display.print("  [YES] ");display.print("   [NO]");
////                                display.display(); 
////                                break;
////                         case 1:
////                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
////                                display.display(); 
////                                break;
////                         case 2:
////                                display.setCursor(10,55);display.print("  [YES] ");display.print(" =>[NO]");
////                                display.display(); 
////                                break;     
////                  }  
//                  break;  
//                  }        
            
           display.display();    
}
