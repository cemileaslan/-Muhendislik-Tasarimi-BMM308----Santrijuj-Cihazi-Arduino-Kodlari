//d2-9 arası keypad, erkanın vcc si d12 de, motor d11 de
#include <Wire.h>
// #include <LiquidCrystal_I2C.h> //eski kutuphanemiz
#include <FaBoLCD_PCF8574.h>
#include <Servo.h>
#include <Keypad.h>

// initialize the library
FaBoLCD_PCF8574 lcd;

const byte ROWS = 4;
const byte COLS = 4;
bool state=true;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
long int number=0;
int i=1;
Servo ESC;
int hiz;
// LiquidCrystal_I2C lcd(0x27, 16, 2); // buna da gerek yok
void setup() {
  ESC.attach(11,1000,2000); 
  yardir(-1); 
  state=true;
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  Serial.begin(9600);
    lcd.begin(16, 2);
//  lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("     BMM 308 ");
    lcd.setCursor(0,1);
    lcd.print("   Hosgeldiniz     ");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                    ");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print(" Hazir misiniz? ");
    lcd.setCursor(0,1);
    lcd.print("                     ");
    delay(2000);
    
    
    lcd.setCursor(0,1);
    lcd.print("                   ");
  
}

void loop() {
    
    if(state){
      lcd.setCursor(0,0);
      lcd.print(" Istenilen Hiz: ");
    }
    else if(!state){
      lcd.setCursor(0,0);
     lcd.print("   Motor Hizi    "); 
   }
    int key = keypad.getKey();  
  if (key){
      number=number*10;
    if(key==49 and state){
    number=number+1;
    i=i+1;    
    }
    
    if(key==50 and state){
    number=number+2;
    i=i+1;    
    }
  
    if(key==51 and state){
      number=number+3;
      i=i+1;
    }
    
     if(key==52 and state){
      number=number+4;
      i=i+1;
    }
    
    if(key==53 and state){
          number=number+5;
    i=i+1;
    }
    
    if(key==54 and state){
          number=number+6;
    i=i+1;
    }
    
    if(key==55 and state){
    number=number+7;
    i=i+1;
    }
    
     if(key==56 and state){
        number=number+8;
    i=i+1;
    }
    
    if(key==57 and state){
        number=number+9;
    i=i+1;
    }
    
    if(key==48 and state){
    number=number+0;
    i=i+1; 
    }
    
     
     if(key==65 and state){//A
      number=0;
      i=0;
      Serial.println("Sil");
      Serial.println(number);
    }
    
    if(key==66 and state){//B
    lcd.setCursor(0,0);
    lcd.print("Hizi ");
    lcd.setCursor(5,0);
    lcd.print(round(number/10));
    lcd.setCursor(9,0);
    lcd.print(" olarak");
    lcd.setCursor(0,1);
    lcd.print("   ayarlandi   ");
    delay(2000);
    number=floor(number/10);
    state=false;
    yardir(number);
    }
     if(key==67){//C
      Serial.println("STOP");
      number=0;
      lcd.setCursor(0,0);
      lcd.print("    Durdum     ");
      lcd.setCursor(0,1);
      lcd.print("                 ");
      yardir(-1);
      state=true;
      
      delay(1000);
    }
     if(key==68){
      Serial.println("BOŞ FONKSİYON");
    }
     if(key==42){
      Serial.println("BOŞ FONKSİYON");
    }
     if(key==35){
      Serial.println("BOŞ FONKSİYON");
    }
  }

 if(state){
  if(number>9999){
    number=9999;
  }
  lcd.setCursor(7,1);
  lcd.print(" RPM    ");
  
  if (number<10){
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(6,1);
  lcd.print(number);
  }
    if (number<100 and number>9){
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(5,1);
  lcd.print(number);
  }
    if (number<1000 and number>99){
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(4,1);
  lcd.print(number);
  }
    if (number<10000 and number>999){
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(3,1);
  lcd.print(number);
  }
 
 }
 
}


void yardir(int hiz){
  state=false;
  if (hiz==-1){
    ESC.write(0);
    }
  else{
    int hiz_RPM = map(hiz, 0, 16800,6, 180); 
    lcd.setCursor(0,0);
    
    lcd.print("   Motor Hizi   "); 
    lcd.setCursor(0,1);
    lcd.print("               ");
    Serial.println(hiz_RPM);
    for (i=0;i<hiz_RPM+1;i++){
      ESC.write(i);
      delay(150);
     int hizz = map(i, 6, 180,1, 16800);
    lcd.setCursor(0,1);
    lcd.print("     ");
    lcd.setCursor(4,1);
    lcd.print(hizz);
    if(hizz<10){
    lcd.setCursor(8,1);
    lcd.print(" RPM ")
    ;  
    }
    else if (hizz<100 and hizz>9){
    lcd.setCursor(8,1);
    lcd.print(" RPM ");
    }
    else if (hizz<1000 and hizz>99){
    lcd.setCursor(8,1);
    lcd.print(" RPM ");
    }
    
    else if (hizz<10000 and hizz>999){
    lcd.setCursor(8,1);
    lcd.print(" RPM ");
    }
    
    }
    lcd.setCursor(0,1);
    lcd.print("     ");
    lcd.setCursor(4,1);
    lcd.print(hiz);
    if(hiz_RPM<10){
    lcd.setCursor(8,1);
    lcd.print(" RPM ");
    }
    else if (hiz_RPM<100 and hiz_RPM>9){
    lcd.setCursor(8,1);
    lcd.print(" RPM ");
    }
    else if (hiz_RPM<1000 and hiz_RPM>99){
    lcd.setCursor(8,1);
    lcd.print(" RPM ");
    }
    
    else if (hiz_RPM<10000 and hiz_RPM>999){
    lcd.setCursor(8,1);
    lcd.print(" RPM ");
    }
    
  }
      
}
