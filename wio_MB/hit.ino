#include  "hit.h"

int Check_Hit() {
  boolean hit = digitalRead(USIN);        // 現在のスイッチの状態を読み取る
  if ( hit == SPN_HIT ) {        // 現在のスイッチがON
    return HITSOUND;
  }
  else {
    return IGNORE;
  }
}
