#include  "hit.h"

int Check_Hit() {
  boolean hit = digitalRead(USIN);        // 超音波が発生したかどうかを読み取る
  if ( hit == SPN_HIT ) {        // 超音波を観測
    return HITSOUND;
  }
  else {
    return IGNORE;
  }
}
