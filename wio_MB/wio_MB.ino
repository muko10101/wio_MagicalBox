#include "TFT_eSPI.h"
#include "sw.h"
#include "dispcommon.h"
#include "menu.h"
#include "setcode.h"
#include "settempo.h"
#include "sendcode.h"
#include "hit.h"

TFT_eSPI tft = TFT_eSPI();      // 画面表示ライブラリ

enum{STATE_MENU,STATE_SET,STATE_TEMPO,STATE_SEND};    // 状態名


#define SELECT 0  // 登録方法選択画面
#define WIO 1     // wioでコード登録
#define WEB 2     // webでコード登録
#define LASTTEMPO 1
#define NOWTEMPO  2

static int CurState;    // 現在の状態
static int SelectMode;  // メニュー画面での選択項目
static int SetCodeState; // コード登録での状態
static int SetWay;      // コード登録方法

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(3);      // 画面の向きを調整
  pinMode( USIN, INPUT );
  pinMode( WIO_KEY_A, INPUT_PULLUP );
  pinMode( WIO_KEY_B, INPUT_PULLUP );
  pinMode( WIO_KEY_C, INPUT_PULLUP );
  pinMode( WIO_5S_UP, INPUT_PULLUP );
  pinMode( WIO_5S_DOWN, INPUT_PULLUP );
  pinMode( WIO_5S_LEFT, INPUT_PULLUP );
  pinMode( WIO_5S_RIGHT, INPUT_PULLUP );
  pinMode( WIO_5S_PRESS, INPUT_PULLUP );

  Sw_Init();     // SWの初期化
  //SetCode_Init();
  Screen_Reset();    // スクリーンの初期化

  CurState = STATE_MENU;    // 初期状態はメニュー画面
  SetCodeState = SELECT;     

}
void loop() {
  switch ( CurState ) {

    /*メニュー画面*/
    case STATE_MENU:

      /*entry*/
      VirtualBtn_Blank();  // 仮想ボタンをメニュー画面用に変更
      Title_Text();             // タイトルの文字を表示
      SelectMode = STATE_SET;  // set code選択状態
      Select_Menu(SelectMode);  // 選択されているものを強調

      do {
        if ( Sw_5wayUp() == SW_PUSHED ) {    // 上ボタンで選択を上に移動
          if ( SelectMode == STATE_SET ) {   // 一番上まで行ったら一番下に移動
            SelectMode = STATE_SEND;
          }
          else {
            SelectMode--;
          }
          Select_Menu(SelectMode);       // 選択されているものを強調
        }
        else if ( Sw_5wayDown() == SW_PUSHED ) {    // 下ボタンで選択を下に移動
          if ( SelectMode == STATE_SEND ) {         // 一番下まで行ったら一番上に移動
            SelectMode = STATE_SET;
          }
          else {
            SelectMode++;
          }
          Select_Menu(SelectMode);        // 選択されているものを強調
        }
        else if ( Sw_5wayEnter() == SW_PUSHED ) {
          CurState = SelectMode;
        }
      } while ( CurState == STATE_MENU );

      /*exit*/
      Screen_Reset();

      break;


    /*コード登録*/
    case STATE_SET:
    
      /*entry*/
      SetCodeState = SELECT;
      Title_SetWay();
      SetWay = WIO;
      Select_Way(SetWay);
      VirtualBtn_OnlyMenu();
      
      do {
        if ( Sw_Btn3() == SW_PUSHED ) {
          CurState = STATE_MENU;
        }

        switch(SetCodeState) {
          case SELECT:
            if ( Sw_5wayUp() == SW_PUSHED ) {    // 上ボタンで選択を移動
              if ( SetWay == WIO ) {   
                SetWay = WEB;
              }
              else {
                SetWay = WIO;
              }
              Select_Way(SetWay);       // 選択されているものを強調
            }
            else if ( Sw_5wayDown() == SW_PUSHED ) {    // 下ボタンで選択を移動
              if ( SetWay == WIO ) {   
                SetWay = WEB;
              }
              else {
                SetWay = WIO;
              }
              Select_Way(SetWay);       // 選択されているものを強調
            }
            else if ( Sw_5wayEnter() == SW_PUSHED ) {
              SetCodeState = SetWay;
              Screen_Reset();
              if (SetWay == WIO){
                VirtualBtn_SetCode_Wio();
                SetCode_Disp();
              }
              else{
                VirtualBtn_SetCode_Web();
              }
            }
            break;
            
          case WIO:
            
            if ( Sw_Btn1() == SW_PUSHED ) {
              if (Set_Code() == OK) {
                CurState = STATE_MENU;
              }
            }
            if ( Sw_Btn2() == SW_PUSHED ) {
              Code_Reset();
            }
            if ( Sw_5wayRight() == SW_PUSHED ) {
              Right_Move();
            }
            if ( Sw_5wayLeft() == SW_PUSHED ) {
              Left_Move();
            }
            if ( Sw_5wayUp() == SW_PUSHED ) {
              Up_Move();
            }
            if ( Sw_5wayDown() == SW_PUSHED ) {
              Down_Move();
            }
            if ( Sw_5wayEnter() == SW_PUSHED ) {
              Bit_Flip();
            }
            break;
            
          case WEB:

            break;
        }
      } while ( CurState == STATE_SET );

      /*exit*/
      Screen_Reset();

      break;


    /*テンポ登録*/
    case STATE_TEMPO:

      /*entry*/
      VirtualBtn_SetTempo();
      LastTempo_Text();
      Tempo_Init();

      do {
        Tempo_Disp(LASTTEMPO);
        if ( Sw_Btn3() == SW_PUSHED ) {
          CurState = STATE_MENU;
        }
        if ( Sw_Btn1() == SW_PUSHED ) {
          Screen_Reset();
          VirtualBtn_Blank();
          SetTempo_Text();
          Measure();
          CurState = STATE_SEND;
        }
      } while ( CurState == STATE_TEMPO );

      /*exit*/
      Screen_Reset();

      break;


    /*指令*/
    case STATE_SEND:

      /*entry*/
      VirtualBtn_OnlyMenu();
      NowTempo_Text();
      Tempo_Init();

      do {
        Tempo_Disp(NOWTEMPO);
        if ( Sw_Btn3() == SW_PUSHED ) {
          CurState = STATE_MENU;
        }
        if ( Check_Hit() == HITSOUND ) {
          Screen_Reset();
          VirtualBtn_Blank();
          SendCode_Text();
          SampleHits();
          Send_Serial();
          Screen_Reset();
          VirtualBtn_OnlyMenu();
          NowTempo_Text();
          Tempo_Init();
        }        
      } while ( CurState == STATE_SEND );

      /*exit*/
      Screen_Reset();

      break;      
  }
}
