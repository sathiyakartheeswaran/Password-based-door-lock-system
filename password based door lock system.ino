#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

// LCD setup (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(13, A0, A1, A2, A3, A4);

// Servo
Servo myServo;

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password
String password = "1234";
String input = "";

// Pins
int buzzer = 11;
int led = 12;

void setup() {
  Serial.begin(9600);

  myServo.attach(10);
  myServo.write(0);

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Enter Password");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    input += key;

    lcd.setCursor(0,1);
    lcd.print(input);

    if (input.length() == 4) {
      checkPassword();
      input = "";
      delay(1000);
      lcd.clear();
      lcd.print("Enter Password");
    }
  }
}

void checkPassword() {
  if (input == password) {
    lcd.clear();
    lcd.print("Access Granted");

    digitalWrite(led, HIGH);
    myServo.write(90);

    delay(3000);

    myServo.write(0);
    digitalWrite(led, LOW);
  } 
  else {
    lcd.clear();
    lcd.print("Wrong Password");

    for (int i = 0; i < 3; i++) {
      digitalWrite(buzzer, HIGH);
      delay(300);
      digitalWrite(buzzer, LOW);
      delay(300);
    }
  }
}