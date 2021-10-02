#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
const short max_weight = 127, max_height = 31;
unsigned int readResistor_now;
unsigned int readResistor_last;
unsigned long time_now;
unsigned long time_last; 

Adafruit_SSD1306 OLED(OLED_RESET);

struct Bar{
    unsigned int lenght;
    unsigned int posX;
    unsigned int posY;
    unsigned int turn;
    unsigned int last_posX;
} myBar;

void setup(){
    randomSeed(analogRead(A0));
    Serial.begin(115200);
    OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    OLED.display();

    //Set up myBar
    myBar.lenght = 25;
    myBar.posY = 31;
    // myBar.turn = 1;
    myBar.last_posX = 0;
    //Set up controller
    pinMode(A2, INPUT);
    readResistor_last = 0;
}

void loop() {
    time_now = millis();
    readResistor_now = analogRead(A2);
    const long double voltageSet = 1024/((max_weight - 1) - myBar.lenght);

    OLED.clearDisplay();
    // Moving
    // Serial.println(readResistor);

    // if(time_now - time_last > 10){
    //     time_last = time_now;
    //     if((unsigned int)(readResistor_now - readResistor_last) < voltageSet) {
    //         Serial.println(readResistor_now);
    //         myBar.posX = readResistor_now / voltageSet;
    //         readResistor_last = readResistor_now;
    //     }
    //     else 
    // myBar.last_posX = myBar.posX;
    // }
    Serial.println(analogRead(A0));
    myBar.posX = readResistor_now / voltageSet;
    OLED.drawLine(myBar.posX, myBar.posY, (myBar.posX + myBar.lenght), myBar.posY, WHITE);
    OLED.display();
}
