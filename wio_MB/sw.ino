#include "sw.h"

static boolean PrevSwUp;     // 上ボタンの前回の状態
static boolean PrevSwDown;   // 下ボタンの前回の状態
static boolean PrevSwRight;  // 右ボタンの前回の状態
static boolean PrevSwLeft;   // 左ボタンの前回の状態
static boolean PrevSwEnter;  // 決定ボタンの前回の状態
static boolean PrevSwBtn1;   // ボタン1の前回の状態
static boolean PrevSwBtn2;   // ボタン2の前回の状態
static boolean PrevSwBtn3;   // ボタン3の前回の状態

void Sw_Init() {          // SWの初期状態はOFF
  PrevSwUp = SW_OFF;
  PrevSwDown = SW_OFF;
  PrevSwRight = SW_OFF;
  PrevSwLeft = SW_OFF;
  PrevSwEnter = SW_OFF;
  PrevSwBtn1 = SW_OFF;
  PrevSwBtn2 = SW_OFF;
  PrevSwBtn3 = SW_OFF;

  return;
}

int Sw_5wayUp() {
  boolean NewSwUp = digitalRead(WIO_5S_UP);        // 現在のスイッチの状態を読み取る
  if ( NewSwUp == SW_ON ) {        // 現在のスイッチがON
    if ( PrevSwUp == SW_ON ) {     // 前回もONならSWを認識しない
      PrevSwUp = NewSwUp;
      return SW_IGNORE;
    }
    else {                         // 前回がOFFなら押された判定
      PrevSwUp = NewSwUp;
      delay(CHATTER);                   // チャタリング処理
      return SW_PUSHED;
    }
  }
  else {                           // 現在のスイッチがOFFならSWを認識しない
    PrevSwUp = NewSwUp;
    return SW_IGNORE;
  }
}

int Sw_5wayDown() {
  boolean NewSwDown = digitalRead(WIO_5S_DOWN);       // 現在のスイッチの状態を読み取る
  if ( NewSwDown == SW_ON ) {       // 現在のスイッチがON
    if ( PrevSwDown == SW_ON ) {    // 前回もONならSWを認識しない
      PrevSwDown = NewSwDown;
      return SW_IGNORE;
    }
    else {                         // 前回がOFFなら押された判定
      PrevSwDown = NewSwDown;
      delay(CHATTER);                   // チャタリング処理
      return SW_PUSHED;
    }
  }
  else {                           // 現在のスイッチがOFFならSWを認識しない
    PrevSwDown = NewSwDown;
    return SW_IGNORE;
  }
}

int Sw_5wayRight() {
  boolean NewSwRight = digitalRead(WIO_5S_RIGHT);       // 現在のスイッチの状態を読み取る
  if ( NewSwRight == SW_ON ) {       // 現在のスイッチがON
    if ( PrevSwRight == SW_ON ) {    // 前回もONならSWを認識しない
      PrevSwRight = NewSwRight;
      return SW_IGNORE;
    }
    else {                         // 前回がOFFなら押された判定
      PrevSwRight = NewSwRight;
      delay(CHATTER);                   // チャタリング処理
      return SW_PUSHED;
    }
  }
  else {                           // 現在のスイッチがOFFならSWを認識しない
    PrevSwRight = NewSwRight;
    return SW_IGNORE;
  }
}

int Sw_5wayLeft() {
  boolean NewSwLeft = digitalRead(WIO_5S_LEFT);       // 現在のスイッチの状態を読み取る
  if ( NewSwLeft == SW_ON ) {       // 現在のスイッチがON
    if ( PrevSwLeft == SW_ON ) {    // 前回もONならSWを認識しない
      PrevSwLeft = NewSwLeft;
      return SW_IGNORE;
    }
    else {                         // 前回がOFFなら押された判定
      PrevSwLeft = NewSwLeft;
      delay(CHATTER);                   // チャタリング処理
      return SW_PUSHED;
    }
  }
  else {                           // 現在のスイッチがOFFならSWを認識しない
    PrevSwLeft = NewSwLeft;
    return SW_IGNORE;
  }
}

int Sw_5wayEnter() {
  boolean NewSwEnter = digitalRead(WIO_5S_PRESS);       // 現在のスイッチの状態を読み取る
  if ( NewSwEnter == SW_ON ) {       // 現在のスイッチがON
    if ( PrevSwEnter == SW_ON ) {    // 前回もONならSWを認識しない
      PrevSwEnter = NewSwEnter;
      return SW_IGNORE;
    }
    else {                         // 前回がOFFなら押された判定
      PrevSwEnter = NewSwEnter;
      delay(CHATTER);                   // チャタリング処理
      return SW_PUSHED;
    }
  }
  else {                           // 現在のスイッチがOFFならSWを認識しない
    PrevSwEnter = NewSwEnter;
    return SW_IGNORE;
  }
}

int Sw_Btn1() {
  boolean NewSwBtn1 = digitalRead(WIO_KEY_C);       // 現在のスイッチの状態を読み取る
  if ( NewSwBtn1 == SW_ON ) {       // 現在のスイッチがON
    if ( PrevSwBtn1 == SW_ON ) {    // 前回もONならSWを認識しない
      PrevSwBtn1 = NewSwBtn1;
      return SW_IGNORE;
    }
    else {                         // 前回がOFFなら押された判定
      PrevSwBtn1 = NewSwBtn1;
      delay(CHATTER);                   // チャタリング処理
      return SW_PUSHED;
    }
  }
  else {                           // 現在のスイッチがOFFならSWを認識しない
    PrevSwBtn1 = NewSwBtn1;
    return SW_IGNORE;
  }
}

int Sw_Btn2() {
  boolean NewSwBtn2 = digitalRead(WIO_KEY_B);       // 現在のスイッチの状態を読み取る
  if ( NewSwBtn2 == SW_ON ) {       // 現在のスイッチがON
    if ( PrevSwBtn2 == SW_ON ) {    // 前回もONならSWを認識しない
      PrevSwBtn2 = NewSwBtn2;
      return SW_IGNORE;
    }
    else {                         // 前回がOFFなら押された判定
      PrevSwBtn2 = NewSwBtn2;
      delay(CHATTER);                   // チャタリング処理
      return SW_PUSHED;
    }
  }
  else {                           // 現在のスイッチがOFFならSWを認識しない
    PrevSwBtn2 = NewSwBtn2;
    return SW_IGNORE;
  }
}

int Sw_Btn3() {
  boolean NewSwBtn3 = digitalRead(WIO_KEY_A);       // 現在のスイッチの状態を読み取る
  if ( NewSwBtn3 == SW_ON ) {       // 現在のスイッチがON
    if ( PrevSwBtn3 == SW_ON ) {    // 前回もONならSWを認識しない
      PrevSwBtn3 = NewSwBtn3;
      return SW_IGNORE;
    }
    else {                         // 前回がOFFなら押された判定
      PrevSwBtn3 = NewSwBtn3;
      delay(CHATTER);                   // チャタリング処理
      return SW_PUSHED;
    }
  }
  else {                           // 現在のスイッチがOFFならSWを認識しない
    PrevSwBtn3 = NewSwBtn3;
    return SW_IGNORE;
  }
}
