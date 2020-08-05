#define SW_ON LOW     // SWが押されている
#define SW_OFF HIGH   // SWが押されていない

#define SW_PUSHED 1   // SWが押された判定
#define SW_IGNORE    0   // SWを認識しない

#define CHATTER 20    // チャタリング除去時間

void Sw_Init(void);   // SWの初期化

int Sw_5wayUp(void);     // 5way上ボタンの判定
int Sw_5wayDown(void);   // 5way下ボタンの判定
int Sw_5wayRight(void);  // 5way右ボタンの判定
int Sw_5wayLeft(void);   // 5way左ボタンの判定
int Sw_5wayEnter(void);  // 5way押したときの判定
int Sw_Btn1(void);       // ボタン1の判定
int Sw_Btn2(void);       // ボタン2の判定
int Sw_Btn3(void);       // ボタン3の判定
