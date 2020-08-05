/*virtualbtn*/
#define BAR_COLOR 0x87E0       // 仮想ボタンバーの色
#define BTN_COLOR 0x5D1C       // 仮想ボタンの色
#define MIN_DISP_YPOS 0        // ディスプレイの上端
#define MIN_DISP_XPOS 0        // ディスプレイの左端
#define MAX_DISP_XPOS 320      // ディスプレイの右端
#define BAR_HEIGHT 30          // 仮想ボタンバーの高さ
#define BTN1_XPOS 10           // 一つ目のボタンのx座標
#define BTN_YPOS 5             // ボタンのy座標
#define BTN_WIDTH 75           // ボタンの幅 (60)
#define BTN_HEIGHT 20          // ボタンの高さ
#define BTN_RADIUS 5           // ボタンの端の半径　　　
#define BTN_SPACE 85           // ボタンの間隔 (70)
#define BTN_TEXT_SIZE 2        // ボタン内のテキストのサイズ
#define BTN1_TEXT2_XPOS 35      // ボタン1内2文字テキストのx座標
#define BTN1_TEXT5_XPOS 15
#define BTN2_TEXT5_XPOS 105      // ボタン2内5文字テキストのx座標
#define BTN3_TEXT4_XPOS 195     // ボタン3内4文字テキストのx座標
#define BTN_TEXT_YPOS 6        // ボタン内テキストのy座標

void VirtualBtn_Blank(void);           // 文字の無い仮想ボタンを表示
void VirtualBtn_SetCode_Wio(void);    // wioでのコード登録画面の仮想ボタンを表示
void VirtualBtn_SetCode_Web(void);    // webでのコード登録画面の仮想ボタンを表示
void VirtualBtn_SetTempo(void);    // リズム登録画面の仮想ボタンを表示
void VirtualBtn_OnlyMenu(void);    // メニューに戻るだけの仮想ボタンを表示


/*screen_reset*/
void Screen_Reset(void);        // スクリーンをリセットする
