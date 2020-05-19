#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char pwd = "0";
unsigned int zt = 0;

//Define the keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {6, 7, 8, 9};

// Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.
byte colPins[COLS] = {2, 3, 4, 5}; //connect to column pinouts

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT); //设置数字IO脚模式，OUTPUT为输出
}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    Serial.println(pwd);
    Serial.println(key);
    unsigned char i, j; //定义发量
    for (i = 0; i < 80; i++) { //输出一个频率的声音
      digitalWrite(11, HIGH); //发声音
      delay(1);//延时1ms
      digitalWrite(11, LOW); //不发声音
      delay(1);//延时ms
    }
    if (key == "*") {
      zt = 1;
    }
    if (pwd != 0 & key == "*") {
      Serial.println(pwd);
      if (pwd == "020207979") {
        for (i = 0; i < 80; i++) { //输出一个频率的声音
          digitalWrite(11, HIGH); //发声音
          delay(1);//延时1ms
          digitalWrite(11, LOW); //不发声音
          delay(1);//延时ms
        }
        digitalWrite(12, HIGH);
        delay(1000);
        digitalWrite(12, LOW);
        for (i = 0; i < 80; i++) { //输出一个频率的声音
          digitalWrite(11, HIGH); //发声音
          delay(1);//延时1ms
          digitalWrite(11, LOW); //不发声音
          delay(1);//延时ms
        }
        pwd = "0";
        zt = 0;
      } else {
        unsigned char i, j; //定义发量
        for (i = 0; i < 80; i++) { //输出一个频率的声音
          digitalWrite(11, HIGH); //发声音
          delay(1);//延时1ms
          digitalWrite(11, LOW); //不发声音
          delay(1);//延时ms
        }
        delay(100);
        for (i = 0; i < 80; i++) { //输出一个频率的声音
          digitalWrite(11, HIGH); //发声音
          delay(1);//延时1ms
          digitalWrite(11, LOW); //不发声音
          delay(1);//延时ms
        }
        delay(100);
        for (i = 0; i < 80; i++) { //输出一个频率的声音
          digitalWrite(11, HIGH); //发声音
          delay(1);//延时1ms
          digitalWrite(11, LOW); //不发声音
          delay(1);//延时ms
        }
      }
      if (zt == 1) {
        if (key == "1") strcat(pwd, "1");
        else if (key == "4") strcat(pwd, "2");
        else if (key == "7") strcat(pwd, "3");
        else if (key == "2") strcat(pwd, "4");
        else if (key == "5") strcat(pwd, "5");
        else if (key == "8") strcat(pwd, "6");
        else if (key == "3") strcat(pwd, "7");
        else if (key == "6") strcat(pwd, "8");
        else if (key == "9") strcat(pwd, "9");
        else if (key == "B") strcat(pwd, "0");
        else if (key == "A") pwd = "0";
      }
    }
  }
}
