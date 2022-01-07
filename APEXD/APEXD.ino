#include <dht.h>
#include <LiquidCrystal_I2C.h> 
#include <Wire.h> 
#include<Servo.h>
dht DHT;

#define DHT11_PIN 2     
LiquidCrystal_I2C lcd(0x27,16,2);  

float hum;  
float temp; 

Servo myservo1;

int sensor_pin = A0;

int output_value ;

int dataIn = 12;

int load = 10;

int clock = 11;

byte max7219_reg_noop = 0x00;

byte max7219_reg_digit0 = 0x01;

byte max7219_reg_digit1 = 0x02;

byte max7219_reg_digit2 = 0x03;

byte max7219_reg_digit3 = 0x04;

byte max7219_reg_digit4 = 0x05;

byte max7219_reg_digit5 = 0x06;

byte max7219_reg_digit6 = 0x07;

byte max7219_reg_digit7 = 0x08;

byte max7219_reg_decodeMode = 0x09;

byte max7219_reg_intensity = 0x0a;

byte max7219_reg_scanLimit = 0x0b;

byte max7219_reg_shutdown = 0x0c;

byte max7219_reg_displayTest = 0x0f;

int e = 0;

void putByte(byte data) {

byte i = 8;

byte mask;

while(i > 0) {

mask = 0x01 << (i - 1); // get bitmask

digitalWrite( clock, LOW); // tick

if (data & mask){ // choose bit

digitalWrite(dataIn, HIGH);// send 1

}else{

digitalWrite(dataIn, LOW); // send 0

}

digitalWrite(clock, HIGH); // tock

--i; // move to lesser bit

}

}

void maxAll(byte reg, byte col) {

digitalWrite(load, LOW); // begin

putByte(reg); // specify register

putByte(col);//((data & 0x01) * 256) + data >> 1); // put data

digitalWrite(load, LOW);

digitalWrite(load,HIGH);

}

void maxSingle(byte reg, byte col) {

digitalWrite(load, LOW); // begin

putByte(reg); // specify register

putByte(col);//((data & 0x01) * 256) + data >> 1); // put data

digitalWrite(load, LOW); // and load da stuff

digitalWrite(load,HIGH);

}

void setup()

{

Serial.begin(9600);

pinMode(0, OUTPUT);
pinMode(1, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(13, OUTPUT);

pinMode(dataIn, OUTPUT);

pinMode(clock, OUTPUT);

pinMode(load, OUTPUT);

maxAll(max7219_reg_scanLimit, 0x07);

maxAll(max7219_reg_decodeMode, 0x00);

maxAll(max7219_reg_shutdown, 0x01);

maxAll(max7219_reg_displayTest, 0x00);

for (e=1; e<=8; e++) { maxAll(e,0);}

maxAll(max7219_reg_intensity, 0x0f & 0x0f);

lcd.init();                     

lcd.backlight();

lcd.setBacklight(HIGH);

Serial.println("Reading From the Sensor ...");


delay(2000);

}

void loop()

{
  digitalWrite(0, HIGH);   
                       
  digitalWrite(1, HIGH);    

  digitalWrite(3, HIGH);   
                       
  digitalWrite(4, HIGH);    

  digitalWrite(5, HIGH);   
              
  digitalWrite(6, HIGH);    

  digitalWrite(7, HIGH);   
                       
  digitalWrite(8, HIGH);    

  digitalWrite(9, HIGH);   
                      
  digitalWrite(13, HIGH);    
  

int chk = DHT.read11(DHT11_PIN);
    delay(1500);
    //Read data and store it to variables hum and temp
    hum = DHT.humidity;
    delay(2000);
    temp= DHT.temperature;
    delay(1500);
    //Print temp and humidity values to LCD
    lcd.setCursor(0,0);
    lcd.print("Humidity: ");
    lcd.print(hum);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Temp: "); 
    lcd.print(temp);
    lcd.println("Celcius");
    delay(2000);

// detect soil humidity
output_value= analogRead(sensor_pin);

output_value = map(output_value,550,0,0,100);

Serial.print("Mositure : ");

Serial.print(output_value);

Serial.println("%");

delay(2000);


if ((output_value < 30)&&(hum >=50)&&((temp > 15) &&(temp < 30))) {
  
// lack water
// sad face

maxSingle(1,0);maxSingle(2,102);maxSingle(3,102);maxSingle(4,0);maxSingle(5,60);maxSingle(6,66);maxSingle(7,66);maxSingle(8,0);

delay(1000);

} 
else {

// happy face

maxSingle(1,0);maxSingle(2,102);maxSingle(3,102);maxSingle(4,0);maxSingle(5,126);maxSingle(6,66);maxSingle(7,36);maxSingle(8,24);


}
}
