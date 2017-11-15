const int LEFT_BUTTON = 12;
const int LEFT_LED = 11;
const int UP_BUTTON = 10;
const int UP_LED = 9;
const int DOWN_BUTTON = 8;
const int DOWN_LED = 7;
const int RIGHT_BUTTON = 6;
const int RIGHT_LED = 5;
const int ENTER_BUTTON = 4;
const int ENTER_LED = 3;
bool leftPushed, upPushed, downPushed, rightPushed, enterPushed;

void setup() {
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_LED, OUTPUT);
  pinMode(UP_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  pinMode(DOWN_LED, OUTPUT);
  pinMode(ENTER_LED, OUTPUT);



}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEFT_LED, LOW);
  digitalWrite(UP_LED, LOW);
  digitalWrite(DOWN_LED, LOW);
  digitalWrite(RIGHT_LED, LOW);
  digitalWrite(ENTER_LED, LOW);
  leftPushed = digitalRead(LEFT_BUTTON);
  upPushed = digitalRead(UP_BUTTON);
  downPushed = digitalRead(DOWN_BUTTON);
  rightPushed = digitalRead(RIGHT_BUTTON);
  enterPushed = digitalRead(ENTER_BUTTON);
  if (!leftPushed) {
    digitalWrite(LEFT_LED, HIGH);
    delay(250);
  }
  if (!upPushed) {
    digitalWrite(UP_LED, HIGH);
    delay(250);
  }
  if (!downPushed) {
    digitalWrite(DOWN_LED, HIGH);
    delay(250);
  }
  if (!rightPushed) {
    digitalWrite(RIGHT_LED, HIGH);
    delay(250);
  }
  if (!enterPushed) {
    digitalWrite(ENTER_LED, HIGH);
    delay(250);
  }
}
