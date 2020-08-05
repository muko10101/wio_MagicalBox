#define TITLE_TEXT_SIZE 4      // タイトル文字の大きさ         
#define TITLE_TEXT_XPOS 15     // タイトルのx座標
#define TITLE_TEXT_YPOS 40     // タイトルのy座標

#define MENU_TEXT_SIZE 3       // メニュー文字の大きさ
#define MENU_TEXT_XPOS 80      // メニュー文字のx座標
#define MENU_TEXT_YPOS 100     // メニュー文字の基準のy座標
#define MENU_TEXT_SPACE 40     // メニュー文字の間隔

#define SET_CODE 1             // set code選択
#define SET_TEMPO 2            // set tempo選択
#define SEND_CODE 3            // set code選択

#define SET_WIO 1
#define SET_WEB 2

void Title_Text(void);         // タイトルの文字を表示
void Select_Menu(int select);  // 選択状態のメニューを強調
void Title_SetWay(void);       // 登録方法のタイトルを表示
void Select_Way(int way);      // コード登録方法のメニューを強調
