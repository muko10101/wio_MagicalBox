#include "setcode.h"
#include "sw.h"

static int BinCode[8][4] = {{0,0,0,0},{0,0,1,1},{0,1,0,1},{0,1,1,0},{1,0,0,1},{1,0,1,0},{1,1,0,0},{1,1,1,1}};     // 二進で登録されているコード
static int BitPos;               // 選択されているビットが何番目か
static int OrderPos;             // 選択されている指令が何番目か
static int DecCode[8] = {0,3,5,6,9,10,12,15};           // 十進で登録されているコード

static uint32_t BitColor;            // ビットを描画する色

#define LEFT_XPOS 45                 // 左側の最初のビットのx座標
#define RIGHT_XPOS 205               // 右側の最初のビットのx座標
#define FIRST_YPOS 50                // 一番上の段のビットのy座標
#define SPACE_XPOS 30                // ビットの横の間隔
#define SPACE_YPOS 50                // ビットの縦の間隔
#define BIT_SIZE  20                 // ビットの正方形の大きさ
#define MIN_BIT 0                    // 先頭のビットを示す
#define MAX_BIT 3                    // 末尾のビットを示す
#define MIN_ORDER 0                  // 先頭の指令を示す
#define MAX_ORDER 7                  // 末尾の指令を示す
#define RIGHT_FIRST 4                // 右の列の最初を示す
#define LEFT_LAST 3                  // 左の列の最後を示す
#define BIT_OFF 0                    // ビットが0
#define BIT_ON 1                     // ビットが1

#define BACK_XPOS 0                  // 背景のx座標
#define BACK_YPOS 30                 // 背景のy座標
#define BACK_WIDTH 320               // 背景の広さ
#define BACK_HEIGHT 210              // 背景の高さ

#define BOX_WIDTH 159                // 指令を囲む四角の広さ
#define BOX_HEIGHT 51                // 指令を囲む四角の高さ
#define BOX_LEFT_XPOS 2              // 指令を囲む四角の左側のx座標
#define BOX_RIGHT_XPOS 160           // 指令を囲む四角の右側のx座標
#define BOX_YPOS 35                  // 指令を囲む四角のy座標

#define ICON_LEFT_XPOS 20            // 左側のアイコンのx座標
#define ICON_RIGHT_XPOS 180          // 右側のアイコンのx座標
#define ICON_FIRST_YPOS 60           // 一番上のアイコンのy座標
#define ICON_RADIUS 15               // アイコンの半径

#define ICON_ARROW_RECT_LONG 18      //
#define ICON_ARROW_RECT_SHORT 10     //
#define ICON_ARROW_SPACE 10          //

#define ICON_UP_RECT_XPOS 15         //
#define ICON_UP_RECT_YPOS 55         //
#define ICON_UP_TR_XPOS 10           //
#define ICON_UP_TR_YPOS 55           //

#define ICON_DOWN_RECT_XPOS 15       //
#define ICON_DOWN_RECT_YPOS 100      //
#define ICON_DOWN_TR_XPOS 10         //
#define ICON_DOWN_TR_YPOS 115        //

#define ICON_RIGHT_RECT_XPOS 10      //
#define ICON_RIGHT_RECT_YPOS 155     //
#define ICON_RIGHT_TR_XPOS 25        //
#define ICON_RIGHT_TR_YPOS 150       //

#define ICON_LEFT_RECT_XPOS 15       //
#define ICON_LEFT_RECT_YPOS 205      //
#define ICON_LEFT_TR_XPOS 15         //
#define ICON_LEFT_TR_YPOS 200        //

#define ICON_URL_SPACE_YPOS 15       //
#define ICON_URL_SPACE_XPOS 5        //
#define ICON_URL_ADJ_YPOS 12         // 右上左上(up right,left)の四角部分のy座標微調整

#define ICON_UR_RECT_XPOS 180        // 右上（up right)矢印の四角の左側(rect left)x座標の一つ目
#define ICON_UR_RECT_YPOS 70         // 
 
#define ICON_UR_TR1_XPOS 175         //
#define ICON_UR_TR1_YPOS 52          //
#define ICON_UR_TR2_XPOS 190         //
#define ICON_UR_TR2_YPOS 60          //
#define ICON_UR_TR3_XPOS 187         //
#define ICON_UR_TR3_YPOS 50          //
 
#define ICON_UL_RECT_XPOS 180        //
#define ICON_UL_RECT_YPOS 120        //

#define ICON_UL_TR1_XPOS 170         //
#define ICON_UL_TR1_YPOS 110         //
#define ICON_UL_TR2_XPOS 187         //
#define ICON_UL_TR2_YPOS 105         //
#define ICON_UL_TR3_XPOS 175         //
#define ICON_UL_TR3_YPOS 100         //

#define ICON_STOP_XPOS 173           //
#define ICON_STOP_YPOS 153           //
#define ICON_STOP_SIZE 15            //
 
#define ICON_LIGHT_RECT_LONG 10      //
#define ICON_LIGHT_RECT_SHORT 5      //
#define ICON_LIGHT_RECT_XPOS 177     //
#define ICON_LIGHT_RECT_YPOS 210     //

#define ICON_LIGHT_CIRCLE_XSPACE 13  //
#define ICON_LIGHT_CIRCLE_YSPACE 14  //
 
#define ICON_LIGHT_CIRCLE_SIZE 2     //
#define ICON_LIGHT_CIRCLE_XPOS 173   //
#define ICON_LIGHT_CIRCLE_YPOS 205   //
   


void SetCode_Init() {
  for (OrderPos = MIN_ORDER; OrderPos <= MAX_ORDER; OrderPos++) {
    for (BitPos = MIN_BIT; BitPos <= MAX_BIT; BitPos++) {
      BinCode[OrderPos][BitPos] = BIT_OFF;
    }
  }
  OrderPos = MIN_ORDER;
  BitPos = MIN_BIT;

  return;
}

void Code_Box(int pos, uint32_t color) {    // 指令を囲む四角を描画
  if (pos < RIGHT_FIRST){
    tft.drawRect(BOX_LEFT_XPOS, BOX_YPOS + (SPACE_YPOS * pos), BOX_WIDTH, BOX_HEIGHT, color);
  }
  else {
    tft.drawRect(BOX_RIGHT_XPOS, BOX_YPOS + (SPACE_YPOS * (pos - RIGHT_FIRST)), BOX_WIDTH, BOX_HEIGHT, color);
  }

  return;
}

void BackGround_Disp() {       // 背景を描画
  
  tft.fillRect(BACK_XPOS, BACK_YPOS, BACK_WIDTH, BACK_HEIGHT, TFT_BLACK);
  
  for (int i=0; i<8; i++) {
    Code_Box(i, TFT_WHITE);
    
    if (i < RIGHT_FIRST){
      tft.fillEllipse(ICON_LEFT_XPOS, ICON_FIRST_YPOS + (SPACE_YPOS * i), ICON_RADIUS, ICON_RADIUS, TFT_ORANGE);
    }
    else {
      tft.fillEllipse(ICON_RIGHT_XPOS, ICON_FIRST_YPOS + (SPACE_YPOS * (i - RIGHT_FIRST)), ICON_RADIUS, ICON_RADIUS, TFT_ORANGE);
    }
  }

  tft.fillRect(ICON_UP_RECT_XPOS, ICON_UP_RECT_YPOS, ICON_ARROW_RECT_SHORT, ICON_ARROW_RECT_LONG, TFT_BLUE);
  tft.fillTriangle(ICON_UP_TR_XPOS, ICON_UP_TR_YPOS, ICON_UP_TR_XPOS + (ICON_ARROW_SPACE * 2), ICON_UP_TR_YPOS, ICON_UP_TR_XPOS + ICON_ARROW_SPACE, ICON_UP_TR_YPOS - ICON_ARROW_SPACE, TFT_BLUE);

  tft.fillRect(ICON_DOWN_RECT_XPOS, ICON_DOWN_RECT_YPOS, ICON_ARROW_RECT_SHORT, ICON_ARROW_RECT_LONG, TFT_BLUE);
  tft.fillTriangle(ICON_DOWN_TR_XPOS, ICON_DOWN_TR_YPOS, ICON_DOWN_TR_XPOS + (ICON_ARROW_SPACE * 2), ICON_DOWN_TR_YPOS, ICON_DOWN_TR_XPOS + ICON_ARROW_SPACE, ICON_DOWN_TR_YPOS + ICON_ARROW_SPACE, TFT_BLUE);

  tft.fillRect(ICON_RIGHT_RECT_XPOS, ICON_RIGHT_RECT_YPOS, ICON_ARROW_RECT_LONG, ICON_ARROW_RECT_SHORT, TFT_BLUE);
  tft.fillTriangle(ICON_RIGHT_TR_XPOS, ICON_RIGHT_TR_YPOS, ICON_RIGHT_TR_XPOS, ICON_RIGHT_TR_YPOS + (ICON_ARROW_SPACE * 2), ICON_RIGHT_TR_XPOS + ICON_ARROW_SPACE, ICON_RIGHT_TR_YPOS + ICON_ARROW_SPACE, TFT_BLUE);

  tft.fillRect(ICON_LEFT_RECT_XPOS, ICON_LEFT_RECT_YPOS, ICON_ARROW_RECT_LONG, ICON_ARROW_RECT_SHORT, TFT_BLUE);
  tft.fillTriangle(ICON_LEFT_TR_XPOS, ICON_LEFT_TR_YPOS, ICON_LEFT_TR_XPOS, ICON_LEFT_TR_YPOS + (ICON_ARROW_SPACE * 2), ICON_LEFT_TR_XPOS - ICON_ARROW_SPACE, ICON_LEFT_TR_YPOS + ICON_ARROW_SPACE, TFT_BLUE);

  tft.fillTriangle(ICON_UR_RECT_XPOS - ICON_ARROW_SPACE, ICON_UR_RECT_YPOS, ICON_UR_RECT_XPOS, ICON_UR_RECT_YPOS, ICON_UR_RECT_XPOS, ICON_UR_RECT_YPOS - ICON_URL_SPACE_YPOS, TFT_BLUE);
  tft.fillTriangle(ICON_UR_RECT_XPOS, ICON_UR_RECT_YPOS - ICON_URL_SPACE_YPOS, ICON_UR_RECT_XPOS, ICON_UR_RECT_YPOS, ICON_UR_RECT_XPOS + ICON_URL_SPACE_XPOS, ICON_UR_RECT_YPOS - ICON_URL_ADJ_YPOS, TFT_BLUE);
  tft.fillTriangle(ICON_UR_TR1_XPOS, ICON_UR_TR1_YPOS, ICON_UR_TR2_XPOS, ICON_UR_TR2_YPOS, ICON_UR_TR3_XPOS, ICON_UR_TR3_YPOS, TFT_BLUE);

  tft.fillTriangle(ICON_UL_RECT_XPOS, ICON_UL_RECT_YPOS, ICON_UL_RECT_XPOS + ICON_ARROW_SPACE, ICON_UL_RECT_YPOS, ICON_UL_RECT_XPOS, ICON_UL_RECT_YPOS - ICON_URL_SPACE_YPOS, TFT_BLUE);
  tft.fillTriangle(ICON_UL_RECT_XPOS, ICON_UL_RECT_YPOS, ICON_UL_RECT_XPOS, ICON_UL_RECT_YPOS - ICON_URL_SPACE_YPOS, ICON_UL_RECT_XPOS - ICON_URL_SPACE_XPOS, ICON_UL_RECT_YPOS - ICON_URL_ADJ_YPOS, TFT_BLUE);
  tft.fillTriangle(ICON_UL_TR1_XPOS, ICON_UL_TR1_YPOS, ICON_UL_TR2_XPOS, ICON_UL_TR2_YPOS, ICON_UL_TR3_XPOS, ICON_UL_TR3_YPOS, TFT_BLUE);

  tft.fillRect(ICON_STOP_XPOS, ICON_STOP_YPOS, ICON_STOP_SIZE, ICON_STOP_SIZE, TFT_BLUE);
 
  tft.fillRect(ICON_LIGHT_RECT_XPOS, ICON_LIGHT_RECT_YPOS - ICON_LIGHT_RECT_LONG, ICON_LIGHT_RECT_SHORT, ICON_LIGHT_RECT_LONG, TFT_BLUE);
  tft.fillEllipse(ICON_LIGHT_CIRCLE_XPOS + ICON_LIGHT_CIRCLE_XSPACE, ICON_LIGHT_CIRCLE_YPOS, ICON_LIGHT_CIRCLE_SIZE, ICON_LIGHT_CIRCLE_SIZE, TFT_BLUE);
  tft.fillRect(ICON_LIGHT_RECT_XPOS + ICON_LIGHT_RECT_SHORT, ICON_LIGHT_RECT_YPOS, ICON_LIGHT_RECT_LONG, ICON_LIGHT_RECT_SHORT, TFT_BLUE);
  tft.fillEllipse(ICON_LIGHT_CIRCLE_XPOS + ICON_LIGHT_CIRCLE_XSPACE, ICON_LIGHT_CIRCLE_YPOS + ICON_LIGHT_CIRCLE_YSPACE, ICON_LIGHT_CIRCLE_SIZE, ICON_LIGHT_CIRCLE_SIZE, TFT_BLUE);
  tft.fillRect(ICON_LIGHT_RECT_XPOS, ICON_LIGHT_RECT_YPOS + ICON_LIGHT_RECT_SHORT, ICON_LIGHT_RECT_SHORT, ICON_LIGHT_RECT_LONG, TFT_BLUE);
  tft.fillEllipse(ICON_LIGHT_CIRCLE_XPOS, ICON_LIGHT_CIRCLE_YPOS + ICON_LIGHT_CIRCLE_YSPACE, ICON_LIGHT_CIRCLE_SIZE, ICON_LIGHT_CIRCLE_SIZE, TFT_BLUE);
  tft.fillRect(ICON_LIGHT_RECT_XPOS - ICON_LIGHT_RECT_LONG, ICON_LIGHT_RECT_YPOS, ICON_LIGHT_RECT_LONG, ICON_LIGHT_RECT_SHORT, TFT_BLUE);
  tft.fillEllipse(ICON_LIGHT_CIRCLE_XPOS, ICON_LIGHT_CIRCLE_YPOS, ICON_LIGHT_CIRCLE_SIZE, ICON_LIGHT_CIRCLE_SIZE, TFT_BLUE);

  return;
}

void SetBit_Color() {    // ビットを描く際の色を指定
  if (BitPos == MAX_BIT) {
    BitColor = TFT_WHITE;
  }
  else {
    BitColor = TFT_RED;
  }

  return;
}

void Fill_Bit(uint32_t color) {      // ビットを塗りつぶす
  if (OrderPos < RIGHT_FIRST) {
    tft.fillRect(LEFT_XPOS + (SPACE_XPOS * BitPos), FIRST_YPOS + (SPACE_YPOS * OrderPos), BIT_SIZE, BIT_SIZE, color);
  }
  else {
    tft.fillRect(RIGHT_XPOS + (SPACE_XPOS * BitPos), FIRST_YPOS + (SPACE_YPOS * (OrderPos - RIGHT_FIRST)), BIT_SIZE, BIT_SIZE, color);
  }

  return;
}

void Draw_Bit(uint32_t color) {     // ビットの枠を描く
  if (OrderPos < RIGHT_FIRST) {
    tft.drawRect(LEFT_XPOS + (SPACE_XPOS * BitPos), FIRST_YPOS + (SPACE_YPOS * OrderPos), BIT_SIZE, BIT_SIZE, color);
  }
  else {
    tft.drawRect(RIGHT_XPOS + (SPACE_XPOS * BitPos), FIRST_YPOS + (SPACE_YPOS * (OrderPos - RIGHT_FIRST)), BIT_SIZE, BIT_SIZE, color);
  }

  return;
}

void SetCode_Disp() {

  BackGround_Disp();

  for (OrderPos = 0; OrderPos <= MAX_ORDER; OrderPos++) {
    for (BitPos = 0; BitPos <= MAX_BIT; BitPos++) {

      SetBit_Color();

      if (BinCode[OrderPos][BitPos] == BIT_ON) {
        Fill_Bit(BitColor);
      }
      else {
        Draw_Bit(BitColor);
      }
    }
  }
  OrderPos = MIN_ORDER;
  BitPos = MIN_BIT;
  Draw_Bit(TFT_YELLOW);

  return;
}

void Right_Move() {

  SetBit_Color();

  if (BitPos == MAX_BIT){
    Draw_Bit(BitColor);
    if (OrderPos < RIGHT_FIRST){
      OrderPos += RIGHT_FIRST;
    }
    else {
      OrderPos -= RIGHT_FIRST;
    }
    BitPos = MIN_BIT;
    Draw_Bit(TFT_YELLOW);
  }
  else {
    Draw_Bit(BitColor);
    BitPos++;
    Draw_Bit(TFT_YELLOW);
  }

  return;
}

void Left_Move() {

  SetBit_Color();
  
  if (BitPos == MIN_BIT){
    Draw_Bit(BitColor);
    if (OrderPos < RIGHT_FIRST){
      OrderPos += RIGHT_FIRST;
    }
    else {
      OrderPos -= RIGHT_FIRST;
    }
    BitPos = MAX_BIT;
    Draw_Bit(TFT_YELLOW);
  }
  else {
    Draw_Bit(BitColor);
    BitPos--;
    Draw_Bit(TFT_YELLOW);
  }

  return;
}

void Up_Move() {

  SetBit_Color();

  Draw_Bit(BitColor);
  
  if (OrderPos == MIN_ORDER){
    OrderPos = LEFT_LAST;
  }
  else if (OrderPos == RIGHT_FIRST){
    OrderPos = MAX_ORDER;
  }
  else {
    OrderPos--;
  }
  
  Draw_Bit(TFT_YELLOW);

  return;
}

void Down_Move() {

  SetBit_Color();

  Draw_Bit(BitColor);
  
  if (OrderPos == LEFT_LAST){
    OrderPos = MIN_ORDER;
  }
  else if (OrderPos == MAX_ORDER){
    OrderPos = RIGHT_FIRST;
  }
  else {
    OrderPos++;
  }
  
  Draw_Bit(TFT_YELLOW);

  return;
}

void Bit_Flip() {

  SetBit_Color();

  if (BinCode[OrderPos][BitPos] == BIT_OFF) {
    Fill_Bit(BitColor);
    Draw_Bit(TFT_YELLOW);
    BinCode[OrderPos][BitPos] = BIT_ON;
  }
  else {
    Fill_Bit(TFT_BLACK);
    Draw_Bit(BitColor);
    Draw_Bit(TFT_YELLOW);
    BinCode[OrderPos][BitPos] = BIT_OFF;
  }

  return;
}

int Set_Code() {
  int ErrorFlag = OK;
  int CheckParity = 0;

  for (int i=0; i<8; i++) {
    Code_Box(i, TFT_WHITE);
  }
  
  for (int i = 0; i < 8; i++) {
    CheckParity = 0;
    for (int j = 0; j < 3; j++) {
      CheckParity += BinCode[i][j];
    }
    switch (CheckParity) {
      case 0:
        if (BinCode[i][3] == BIT_ON) {
          Code_Box(i, TFT_PINK);
          ErrorFlag = NG;
        }
        break;
      case 1:
        if (BinCode[i][3] == BIT_OFF) {
          Code_Box(i, TFT_PINK);
          ErrorFlag = NG;
        }
        break;
      case 2:
        if (BinCode[i][3] == BIT_ON) {
          Code_Box(i, TFT_PINK);
          ErrorFlag = NG;
        }
        break;
      case 3:
        if (BinCode[i][3] == BIT_OFF) {
          Code_Box(i, TFT_PINK);
          ErrorFlag = NG;
        }
        break;
    }
  }
    
  for (int i = 0; i < 8; i++) {
    DecCode[i] = BinCode[i][0] * 8 + BinCode[i][1] * 4 + BinCode[i][2] * 2 + BinCode[i][3];
  }
  for (int j = 0; j < 8; j++) {
    for (int k = j + 1; k < 8; k++) {
      if (DecCode[j] == DecCode[k]) {
        Code_Box(j, TFT_YELLOW);
        Code_Box(k, TFT_YELLOW);
        ErrorFlag = NG;
      }
    }
  }
  
  return ErrorFlag;
}

void Code_Reset() {
  SetCode_Init();
  SetCode_Disp();

  return;
}

int Copy_CodeSet(int num){
  return DecCode[num];
}
