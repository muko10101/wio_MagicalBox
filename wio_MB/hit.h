#define USIN 0

#define SPN_HIT   LOW     // スプーンが叩かれた
#define SPN_UNHIT HIGH   // スプーンが叩かれていない

#define HITSOUND  1   // 超音波が認識された判定
#define IGNORE    0   // 超音波を認識しない

int Check_Hit(void);  //　超音波観測
