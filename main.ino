#include <Keypad.h>
#include <EEPROM.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
String pwd = "";
unsigned int zt = 0;
unsigned int err = 0;
int addr = 0;
int address = 0;
byte value;
String upwd;

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

void sound(unsigned int a) {
  unsigned char i, j; //定义发量
  for (i = 0; i < a; i++) { //输出一个频率的声音
    digitalWrite(11, HIGH); //发声音
    delay(1);//延时1ms
    digitalWrite(11, LOW); //不发声音
    delay(1);//延时ms
  }
  digitalWrite(11, HIGH); //发声音
}

void flash_w(int a) {
  int val = analogRead(0) / 4;
  EEPROM.write(addr, a);
  addr = addr + 1;
}

void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT); //设置数字IO脚模式，OUTPUT为输出
  pinMode(10, INPUT);
  digitalWrite(12, HIGH);
  sound(120);
  Serial.println("欢迎使用");
  if (err > 5 | value== 1) {
    flash_w(1);
    sound(60); sound(60); sound(60); sound(60); sound(60);
    Serial.println("已锁止");
    while (true);
  }

  if (digitalRead(10) == 1) {
    flash_w(0);
    sound(50);
    zt = 1;
    Serial.println("已解锁");
  }
}

void loop() {
  //  int x;
  //  for(x=0;x<8;x++){
  //    value[x] = EEPROM.read(address);
  //    address++;
  //    }
  //  upwd=value;
  //  Serial.print("密码为：");
  //  Serial.println(upwd.c_str());

  if (err > 5 | value == 1) {
    flash_w(1);
    sound(60); sound(60); sound(60); sound(60); sound(60);
    Serial.println("已锁止");
    while (true);
  }

  char key1 = keypad.getKey();
  if (key1 != NO_KEY) {
    int key = key1 - 48;
    Serial.print("你按下了编号为：");
    Serial.println(key);
    if (key == 1) {
      pwd = pwd + "1";
      sound(80);
    }
    else if (key == 4)  {
      pwd = pwd + "2";
      sound(80);
    }
    else if (key == 7)  {
      pwd = pwd + "3";
      sound(80);
    }
    else if (key == 2)  {
      pwd = pwd + "4";
      sound(80);
    }
    else if (key == 5)  {
      pwd = pwd + "5";
      sound(80);
    }
    else if (key == 8)  {
      pwd = pwd + "6";
      sound(80);
    }
    else if (key == 3) {
      pwd = pwd + "7";
      sound(80);
    }
    else if (key == 6) {
      pwd = pwd + "8";
      sound(80);
    }
    else if (key == 9) {
      pwd = pwd + "9";
      sound(80);
    }
    else if (key == 18) {
      pwd = pwd + "0";
      sound(80);
    }
    else if (key == 17) {
      pwd = "";
      sound(80);
      sound(80);
    }
    else if (key == -6) {
      Serial.print("你的密码：");
      Serial.println(pwd); sound(80);
      if (pwd == "20207979") {
        Serial.println("启动");
        sound(100);
        digitalWrite(12, LOW);
        delay(5000);
        digitalWrite(12, HIGH);
        sound(100);
        pwd = "";
      } else {
        Serial.println("密码错误");
        sound(100); sound(100); sound(100);
        err = err + 1;
        pwd="";
      }
      //    }else if (key==20 & zt==1){
      //      Serial.print("修改密码为：");
      //      Serial.println(pwd);
      //      pwd="0"+pwd;
      //      char *p=pwd.c_str(); ;
      //      int i;
      //      for(i=0;i<9;i++){
      //        flash_w(p[i]);
      //      }
      //      sound(80);
      //    }
    }
  }
}
