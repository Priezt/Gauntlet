#define MODE_COUNT 3
#define RED_MODE 0
#define YELLOW_MODE 1
#define BLUE_MODE 2

#define KEY_COUNT 12
#define KEY_ESC 43
#define KEY_W 42
#define KEY_E 41
#define KEY_R 40
#define KEY_A 33
#define KEY_S 32
#define KEY_D 31
#define KEY_F 30
#define KEY_Z 11
#define KEY_X 10
#define KEY_C 9
#define KEY_V 8

#define KEY_DEAD_INTERVAL 200

int currentMode = RED_MODE;
int modeLEDs[] = {50, 51, 52};
int keyPINs[] = {8, 9 , 10, 11, 30, 31, 32, 33, 40, 41, 42, 43};
int keyPreviousStates[64];
unsigned long keyLastPressesTime[64];

void setup(){
  int i;
  Serial.begin(9600);
  for(i = 0; i < MODE_COUNT; i = i + 1){
    //Serial.println(("set pin to OUTPUT: " + String(modeLEDs[i])));
    pinMode(modeLEDs[i], OUTPUT);
  }
  for(i = 0; i < KEY_COUNT; i = i + 1){
    //Serial.println(("set pin to INPUT_PULLUP: " + String(modeLEDs[i])));
    pinMode(keyPINs[i], INPUT_PULLUP);
    keyPreviousStates[keyPINs[i]] = HIGH;
    keyLastPressesTime[keyPINs[i]] = millis();
  }
  switchMode(RED_MODE);
}

void loop(){
  if(checkKeyPressed(KEY_ESC)){
    int newMode = currentMode + 1;
    if(newMode >= MODE_COUNT){
      newMode = 0;
    }
    switchMode(newMode);
    return;
  }
}

void switchMode(int newMode){
  int i;
  currentMode = newMode;
  for(i = 0; i < MODE_COUNT; i = i + 1){
    if(i == currentMode){
      digitalWrite(modeLEDs[i], HIGH);
    }else{
      digitalWrite(modeLEDs[i], LOW);
    }
  }
}

boolean checkKeyPressed(int pin){
  int keyState = digitalRead(pin);
  boolean result = false;
  if(keyState != keyPreviousStates[pin]){
    if(millis() - keyLastPressesTime[pin] > KEY_DEAD_INTERVAL){
      if(keyState == LOW){
        result = true;
        keyLastPressesTime[pin] = millis();
      }
    }
  }
  keyPreviousStates[pin] = keyState;
  return result;
}
