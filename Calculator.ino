#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String num1 = "";
String num2 = "";
char op = 0;
bool enteringSecondNumber = false;

void setup() {
  Serial.begin(9600);
  Serial.println("شروع کنید!");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key >= '0' && key <= '9') {
      if (!enteringSecondNumber) {
        num1 += key;
        Serial.print(key);
      } else {
        num2 += key;
        Serial.print(key);
      }
    } else if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
      op = key;
      enteringSecondNumber = true;
      if (op == 'A') Serial.print("+");
      else if (op == 'B') Serial.print("-");
      else if (op == 'C') Serial.print("*");
      else if (op == 'D') Serial.print("/");
    } else if (key == '#') {
      int n1 = num1.toInt();
      int n2 = num2.toInt();
      float result = 0;
      bool valid = true;

      switch (op) {
        case 'A': result = n1 + n2; break;
        case 'B': result = n1 - n2; break;
        case 'C': result = n1 * n2; break;
        case 'D':
          if (n2 != 0) result = (float)n1 / n2;
          else {
            Serial.print("=error");
            valid = false;
          }
          break;
        default:
          Serial.println("عملیات نامعتبر");
          valid = false;
      }

      if (valid) {
        Serial.print("=");
        Serial.println(result);
      }

      num1 = "";
      num2 = "";
      op = 0;
      enteringSecondNumber = false;

    } else if (key == '*') {
      num1 = "";
      num2 = "";
      op = 0;
      enteringSecondNumber = false;
      Serial.println("پاک شد!");
    }
  }
}