#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define PIN_DIN1 2
#define PIN_DIN2 3
#define PIN_DIN5 4
#define PIN_DIN10 5
#define PIN_DIN20 6
#define PIN_BUTTON 8

#define EEPROM_TOTAL 0
#define EEPROM_1DIN 10
#define EEPROM_2DIN 20
#define EEPROM_5DIN 30
#define EEPROM_10DIN 40
#define EEPROM_20DIN 50

LiquidCrystal_I2C lcd(0x27, 16, 2);

long total;
long total_previous;

bool screen = true;

unsigned long time_start, time_end;

int individual_1din, individual_2din, individual_5din, individual_10din, individual_20din;

void setup() {
  pinMode(PIN_DIN1, INPUT);
  pinMode(PIN_DIN2, INPUT);
  pinMode(PIN_DIN5, INPUT);
  pinMode(PIN_DIN10, INPUT);
  pinMode(PIN_DIN20, INPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  

  EEPROM.get(EEPROM_TOTAL, total);
  EEPROM.get(EEPROM_1DIN, individual_1din);
  EEPROM.get(EEPROM_2DIN, individual_2din);
  EEPROM.get(EEPROM_5DIN, individual_5din);
  EEPROM.get(EEPROM_10DIN, individual_10din);
  EEPROM.get(EEPROM_20DIN, individual_20din);
  
  total_previous = total;

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd_print();
  
  Serial.begin(9600);
}

void lcd_print(){
  lcd.setCursor(0,0);
  lcd.clear();
  if(screen){
      lcd.print("Total: ");
      lcd.print(total);
  }else{
      lcd.print("1x");
      lcd.print(individual_1din);
      
      lcd.setCursor(6, 0);
      lcd.print("2x");
      lcd.print(individual_2din);
  
      lcd.setCursor(0, 1);
      lcd.print("5x");
      lcd.print(individual_5din);
  
      lcd.setCursor(6, 1);
      lcd.print("10x");
      lcd.print(individual_10din);
  
      lcd.setCursor(13, 0);
      lcd.print("20x");
      lcd.setCursor(13, 1);
      lcd.print(individual_20din);
  }
}

void loop() {
  if(digitalRead(PIN_BUTTON) == LOW){
    time_start = millis();
    screen = !screen;
    while(digitalRead(PIN_BUTTON) == LOW){}
    time_end = millis();

    //if button is held for more than 3 seconds, data is deleted
    if(time_end - time_start > 3000){
      screen = !screen;
      total = 0;
      individual_1din = 0;
      individual_2din = 0;
      individual_5din = 0;
      individual_10din = 0;
      individual_20din = 0;

      EEPROM.put(EEPROM_TOTAL, total);
      EEPROM.put(EEPROM_1DIN, individual_1din);
      EEPROM.put(EEPROM_2DIN, individual_2din);
      EEPROM.put(EEPROM_5DIN, individual_5din);
      EEPROM.put(EEPROM_10DIN, individual_10din);
      EEPROM.put(EEPROM_20DIN, individual_20din);

      for(int i = 0; i < 4; i++){
        lcd.clear();
        delay(200);
        lcd.setCursor(2, 0);
        lcd.print("DATA DELETED!");
        delay(350);
      }
    }
    lcd_print();
    delay(150);
  }

  //checks if coin is detected
  if(digitalRead(PIN_DIN1) == LOW){
    individual_1din += 1;
    total += 1;
    EEPROM.put(EEPROM_1DIN, individual_1din);
    delay(70);
  }
  if(digitalRead(PIN_DIN2) == LOW){
    individual_2din += 1;
    total += 2;
    EEPROM.put(EEPROM_2DIN, individual_2din);
    delay(70);
  }
  if(digitalRead(PIN_DIN5) == LOW){
    individual_5din += 1;
    total += 5;
    EEPROM.put(EEPROM_5DIN, individual_5din);
    delay(70);
  }
  if(digitalRead(PIN_DIN10) == LOW){
    individual_10din += 1;
    total += 10;
    EEPROM.put(EEPROM_10DIN, individual_10din);
    delay(70);
  }
  if(digitalRead(PIN_DIN20) == LOW){
    individual_20din += 1;
    total += 20;
    EEPROM.put(EEPROM_20DIN, individual_20din);
    delay(70);
  }

  //only if value changed, changes are written to EEPROM to reduce it's wear
  //can't use EEPROM.update() because it only works on one byte
  if(total != total_previous){
     EEPROM.put(EEPROM_1DIN, individual_1din);
     EEPROM.put(EEPROM_TOTAL, total);
     total_previous = total;
 
     lcd_print();
  }
}
