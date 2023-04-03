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

#define MainMenuButton 27
#define SubMenuButton 15
#define SelectSubMenuValueButton 23
#define pagesButton 13


int MainMenuSelect = 0;
int SubMenuSelect = 0;
int SelectSubMenuValue = 0;
byte pagesCount;

int totalMenus = 6;
int totalSubMenus = 2;
int totalSubMenuValue = 2;
int totalPages = 5;

int pot1_address = 1;
int pot2_address = 2;
int joyx_address = 3;
int joyy_address = 4;

int pot1Dir_address = 5;
int pot2Dir_address = 6;
int joyxDir_address = 7;
int joyyDir_address = 8;

int pagesCount_address = 9;

byte pot1_value, pot2_value, joyx_value, joyy_value;
byte pot1Dir_value, pot2Dir_value, joyxDir_value, joyyDir_value;

String pot1Dir_Type;
String pot2Dir_Type;
String joyxDir_Type;
String joyyDir_Type;



int pot1 = 32;//34;
int pot2 = 33;//35;
int joyx = 34;
int joyy = 35;
int potentiometer1;
int potentiometer2;
int joystickx;
int joysticky;


void oled_display_menu();
void potentiometer();
void potentiometer_settings();
void settings();
void deviceDetails();
void slaveDeviceDetails();


void setup() {
  Serial.begin(115200);
  EEPROM.begin(255);
  pinMode(MainMenuButton, INPUT_PULLUP);
  pinMode(SubMenuButton, INPUT_PULLUP);
  pinMode(SelectSubMenuValueButton, INPUT_PULLUP);
  pinMode(pagesButton, INPUT_PULLUP);

  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  pinMode(joyx, INPUT);
  pinMode(joyy, INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


  pot1_value = EEPROM.read(pot1_address);//EEPROM.read(ADDRESS 0-255);
  pot2_value = EEPROM.read(pot2_address);//EEPROM.read(ADDRESS 0-255);
  joyx_value = EEPROM.read(joyx_address);//EEPROM.read(ADDRESS 0-255);
  joyy_value = EEPROM.read(joyy_address);//EEPROM.read(ADDRESS 0-255);


  pot1Dir_value = EEPROM.read(pot1Dir_address);//EEPROM.read(ADDRESS 0-255);
  pot2Dir_value = EEPROM.read(pot2Dir_address);//EEPROM.read(ADDRESS 0-255);
  joyxDir_value = EEPROM.read(joyxDir_address);//EEPROM.read(ADDRESS 0-255);
  joyyDir_value = EEPROM.read(joyyDir_address);//EEPROM.read(ADDRESS 0-255);

  // MainMenuSelect = EEPROM.read(MainMenuSelect_address);//EEPROM.read(ADDRESS 0-255);
  // SubMenuSelect = EEPROM.read(SubMenuSelect_address);//EEPROM.read(ADDRESS 0-255);
  pagesCount = EEPROM.read(pagesCount_address);//EEPROM.read(ADDRESS 0-255);



}

void loop() 
{

 oled_display_menu();

}


void oled_display_menu(){

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



//if(pagesCount == 1 || pagesCount == 2 || pagesCount == 3 || pagesCount == 4 || pagesCount == 5){
//  SubMenuSelect = 0;
//}


  
  
  
  pot1Dir_Type = (pot1Dir_value == 0)?"L":"R";
  pot2Dir_Type = (pot2Dir_value == 0)?"L":"R";
  joyxDir_Type = (joyxDir_value == 0)?"L":"R";
  joyyDir_Type = (joyyDir_value == 0)?"L":"R";

  
  

//*****potentiometer1**********************************
     if(pot1Dir_value == 1 && pot1_value == 180){potentiometer1 = map(analogRead(pot1), 4095, 0, 180, 0);}
else if(pot1Dir_value == 0 && pot1_value == 180){potentiometer1 = map(analogRead(pot1), 4095, 0, 0, 180);}
else if(pot1Dir_value == 1 && pot1_value == 255){potentiometer1 = map(analogRead(pot1), 4095, 0, 255, 0);}
else if(pot1Dir_value == 0 && pot1_value == 255){potentiometer1 = map(analogRead(pot1), 4095, 0, 0, 255);}

//*****potentiometer2**********************************
     if(pot2Dir_value == 1 && pot2_value == 180){potentiometer2 = map(analogRead(pot2), 4095, 0, 180, 0);}
else if(pot2Dir_value == 0 && pot2_value == 180){potentiometer2 = map(analogRead(pot2), 4095, 0, 0, 180);}
else if(pot2Dir_value == 1 && pot2_value == 255){potentiometer2 = map(analogRead(pot2), 4095, 0, 255, 0);}
else if(pot2Dir_value == 0 && pot2_value == 255){potentiometer2 = map(analogRead(pot2), 4095, 0, 0, 255);}

//*****joystick x**********************************
     if(joyxDir_value == 1 && joyx_value == 180){joystickx = map(analogRead(joyx), 4095, 0, 180, 0);}
else if(joyxDir_value == 0 && joyx_value == 180){joystickx = map(analogRead(joyx), 4095, 0, 0, 180);}
else if(joyxDir_value == 1 && joyx_value == 255){joystickx = map(analogRead(joyx), 4095, 0, 255, 0);}
else if(joyxDir_value == 0 && joyx_value == 255){joystickx = map(analogRead(joyx), 4095, 0, 0, 255);}

//*****joystick y**********************************
     if(joyyDir_value == 1 && joyy_value == 180){joysticky = map(analogRead(joyy), 4095, 0, 180, 0);}
else if(joyyDir_value == 0 && joyy_value == 180){joysticky = map(analogRead(joyy), 4095, 0, 0, 180);}
else if(joyyDir_value == 1 && joyy_value == 255){joysticky = map(analogRead(joyy), 4095, 0, 255, 0);}
else if(joyyDir_value == 0 && joyy_value == 255){joysticky = map(analogRead(joyy), 4095, 0, 0, 255);}




  
  
  switch(pagesCount){
  
    case 0:
    EEPROM.write(pagesCount_address, 0);
            Serial.println("Dashboard");
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setTextSize(1);
            display.setCursor(0, 0);//COL,ROW
            display.print("DASHBOARD");
            display.setCursor(110, 0);display.print(pagesCount);display.print("/");display.print(totalPages);
            display.setCursor(0,12); display.print("POT1:");display.print(potentiometer1);display.print(pot1Dir_Type);
            display.setCursor(0,22); display.print("POT2:");display.print(potentiometer2);display.print(pot2Dir_Type); 
            display.setCursor(60,12);display.print("JOYX:");display.print(joystickx);display.print(joyxDir_Type);
            display.setCursor(60,22);display.print("JOYY:");display.print(joysticky);display.print(joyyDir_Type); 
            display.display();
          break;
  
  //potentiometer page******************************************************************************************** 
    case 1:
          EEPROM.write(pagesCount_address, 1);
          Serial.println("Page1");
          potentiometer();
          break;
          
  //potentiometer settings page********************************************************************************************
    case 2:
          EEPROM.write(pagesCount_address, 2);
          potentiometer_settings();
          break;
    
    case 3:
          EEPROM.write(pagesCount_address, 3);
          settings();
          break;      
    case 4:
          EEPROM.write(pagesCount_address, 4);
          deviceDetails();
          break;
    case 5:
          EEPROM.write(pagesCount_address, 5);
          slaveDeviceDetails();
          break;
                     
  }
  
  EEPROM.commit(); 
}



void potentiometer(){
          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(0, 0);//COL,ROW
          display.println("POTENTIOMETER");
          display.setCursor(110, 0);display.print(pagesCount);display.print("/");display.print(totalPages);
          display.setCursor(0,12); display.print("POT1:");display.print(pot1_value);
          display.setCursor(60,12);display.print("POT2:");display.print(pot2_value);   
          display.setCursor(0,22); display.print("JOYX:");display.print(joyx_value);
          display.setCursor(60,22);display.print("JOYY:");display.println(joyy_value);
 

            switch(MainMenuSelect){
            case 0:
                  display.setCursor(0,40);display.print(" P1");display.print(" P2");display.print(" JX");display.print(" JY");      
                  display.setCursor(0,55);display.print("Press To Select Menu");
                  display.display();
                  break;       
            case 1:
                  display.setCursor(0,40);display.print(">P1");display.print(" P2");display.print(" JX");display.print(" JY");      
                  switch(SubMenuSelect){
                         case 0:
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
                  display.setCursor(0,40);display.print(" P1");display.print(">P2");display.print(" JX");display.print(" JY");      
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
                  display.setCursor(0,40);display.print(" P1");display.print(" P2");display.print(">JX");display.print(" JY");      
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(10,55);display.print("  [180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 1:
                                EEPROM.write(joyx_address, 180);
                                display.setCursor(10,55);display.print("=>[180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 2:
                                EEPROM.write(joyx_address, 255);
                                display.setCursor(10,55);display.print("  [180]");display.print("  =>[255]");
                                display.display(); 
                                break;     
                  }  
                  break;                    
            case 4:
                  display.setCursor(0,40);display.print(" P1");display.print(" P2");display.print(" JX");display.print(">JY");      
                  switch(SubMenuSelect){
                         case 0:
                                display.setCursor(10,55);display.print("  [180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 1:
                                EEPROM.write(joyy_address, 180);
                                display.setCursor(10,55);display.print("=>[180]");display.print("    [255]");
                                display.display(); 
                                break;
                         case 2:
                                EEPROM.write(joyy_address, 255);
                                display.setCursor(10,55);display.print("  [180]");display.print("  =>[255]");
                                display.display(); 
                                break;     
                  }  
                  break;                    
                  }     
}

void potentiometer_settings(){
          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(0, 0);//COL,ROW
          display.println("POT SETTINGS");
          display.setCursor(110, 0);display.print(pagesCount);display.print("/");display.print(totalPages);
          display.setCursor(0,12);display.print("POT1:");display.print(pot1Dir_Type);
          display.setCursor(60,12);display.print("POT2:");display.print(pot2Dir_Type);   
          display.setCursor(0,22);display.print("JOYX:");display.print(joyxDir_Type);
          display.setCursor(60,22);display.print("JOYY:");display.println(joyyDir_Type);


           switch(MainMenuSelect){
            case 0:
                  display.setCursor(0,40);display.print(" P1");display.print(" P2");display.print(" JX");display.print(" JY");      
                  display.setCursor(0,55);display.print("Select Pot Direction");
                  display.display();
                  break;          
              
          case 1:
              display.setCursor(0,40);display.print(">P1");display.print(" P2");display.print(" JX");display.print(" JY");      
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
              display.setCursor(0,40);display.print(" P1");display.print(">P2");display.print(" JX");display.print(" JY");      
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
              display.setCursor(0,40);display.print(" P1");display.print(" P2");display.print(">JX");display.print(" JY");      
              switch(SubMenuSelect){
                     case 0:
        //                  EEPROM.write(pot1_address, pot1_value);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 1:
                            EEPROM.write(joyxDir_address, 0);
                            display.setCursor(10,55);display.print("=>LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 2:
                            EEPROM.write(joyxDir_address, 1);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("=>RIGHT");
                            display.display(); 
                            break;     
              }  
              break;                    
        case 4:
              display.setCursor(0,40);display.print(" P1");display.print(" P2");display.print(" JX");display.print(">JY");     
              switch(SubMenuSelect){
                     case 0:
        //                  EEPROM.write(pot1_address, pot1_value);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 1:
                            EEPROM.write(joyyDir_address, 0);
                            display.setCursor(10,55);display.print("=>LEFT");display.setCursor(60,55);display.print("  RIGHT");
                            display.display(); 
                            break;
                     case 2:
                            EEPROM.write(joyyDir_address, 1);
                            display.setCursor(10,55);display.print("  LEFT");display.setCursor(60,55);display.print("=>RIGHT");
                            display.display(); 
                            break;     
              }   
              break;                    
              }  
}


void settings(){

          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(1);
          display.setCursor(0, 0);//COL,ROW
          display.println("SETTINGS");
          display.setCursor(110, 0);display.print(pagesCount);display.print("/");display.print(totalPages);

          

          
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
                         EEPROM.write(joyx_address, 180);
                         EEPROM.write(joyy_address, 255);

                         EEPROM.write(pot1Dir_address, 1);
                         EEPROM.write(pot2Dir_address, 1);
                         EEPROM.write(joyxDir_address, 1);
                         EEPROM.write(joyyDir_address, 0);

                                display.setCursor(10,55);display.print("=>[YES] ");display.print("   [NO]");
                                display.display(); 
                                break;
                         case 2:
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
  display.setCursor(0, 0);//COL,ROW
  display.println("DEVICE DETAILS");
  display.setCursor(110, 0);display.print(pagesCount);display.print("/");display.print(totalPages);
          
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
    display.println("SLAVE DETAILS");
    display.setCursor(110, 0);display.print(pagesCount);display.print("/");display.print(totalPages);
    display.setCursor(0,12);display.print("MAC : ");display.print("EC62609B1F14");
    display.setCursor(0,22);display.print("Batt: ");display.print("3.3");display.print(" V");
    display.setCursor(0,32);display.print("RSSI: ");display.print("50");display.print(" dBm"); 
    display.setCursor(0,42);display.print("Temp: ");display.print("35");
    display.setCursor(0,52);display.print("Acce: ");display.print("35");
    display.display();    
}
