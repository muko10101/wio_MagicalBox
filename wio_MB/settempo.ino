#include "settempo.h"
#include "hit.h"

#define TITLE_TEXT_SIZE 4      // タイトル文字の大きさ         
#define TITLE_TEXT_XPOS 15     // タイトルのx座標
#define TITLE_TEXT_YPOS 40     // タイトルのy座標

#define MEASURE_DISP_YPOS 80    // maesuring display y position (start position)
#define MEASURE_DISP_XPOS 10    // maesuring display x position (start position)
#define MEASURE_DISP_SIZE 5     // charactor size
#define MEASURE_DISP_SPACE 40   // charactor spacing ( x position increse by this value )

#define TEMPO_TEXT_SIZE 3      // テンポ表示の大きさ         
#define TEMPO_TEXT_XPOS 10     // テンポ表示のx座標
#define TEMPO_TEXT_YPOS 150     // テンポ表示のy座標

#define SAMPLE_TIMES    4       // sampling times
#define THE1ST          1       // the 1st sample
#define THE4TH          4       // the 4th sample

#define CHATTERING_TIME 50      // Time to pass the chatter (msec)

#define NOTES_TRI_XPOS     54  //音符の三角形部分の第一頂点のx座標
#define NOTES_TRI_YPOS     80  //音符の三角形部分の第一頂点のy座標
#define NOTES_TRI_YPOS_2ND 90  //音符の三角形部分の第二頂点のy座標
#define NOTES_TRI_YPOS_3RD 70  //音符の三角形部分の第三頂点のy座標
#define NOTES_SQU_XPOS     49  //音符の四角形部分のx座標
#define NOTES_SQU_YPOS     80  //音符の四角形部分のy座標
#define NOTES_SQU_HEIGHT   10  //音符の四角形部分の高さ
#define NOTES_SQU_WIDTH    5   //音符の四角形部分の横幅
#define NOTES_LINE_HEIGHT  45  //音符の線部分の高さ
#define NOTES_LINE_WIDTH   2   //音符の線部分の横幅
#define NOTES_ROUND_XPOS   30  //音符の楕円部分のx座標
#define NOTES_ROUND_YPOS   115 //音符の楕円部分のy座標
#define NOTES_ROUND_HEIGHT 20  //音符の楕円部分の高さ
#define NOTES_ROUND_WIDTH  15  //音符の楕円部分の横幅
#define NOTES_ROUND_RADIUS 8   //音符の楕円部分の半径
#define NOTES_SPACE        50  //音符の間隔

static int xpos;  // メニュー画面での選択項目
static int tempotimes = THE1ST;
static unsigned long nowtime;
static unsigned long pasttime = 500;
static int rnd[8];

void LastTempo_Text() {  // タイトルの表示
  tft.setTextColor(TFT_MAGENTA);
  tft.setTextSize(TITLE_TEXT_SIZE);
  tft.drawString("LAST TEMPO", TITLE_TEXT_XPOS, TITLE_TEXT_YPOS);

  return;
}

void SetTempo_Text() {  // タイトルの表示
  tft.setTextColor(TFT_MAGENTA);
  tft.setTextSize(TITLE_TEXT_SIZE);
  tft.drawString("SET TEMPO", TITLE_TEXT_XPOS, TITLE_TEXT_YPOS);

  return;
}

void Tempo_Init() {
  xpos = MEASURE_DISP_XPOS;
  tempotimes = THE1ST;
  return;
}

unsigned long CheckTempo() {
  return pasttime;
}

void Tempo_Disp(int tempover) {
  char  TempoStr[20]; 
  unsigned long interval;

  interval = CheckTempo();
  
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(TEMPO_TEXT_SIZE);
  sprintf(TempoStr, "TEMPO : %lums", interval); 
  tft.drawString(TempoStr, TEMPO_TEXT_XPOS, TEMPO_TEXT_YPOS);
  
  if (millis() - nowtime >= interval){
    nowtime = millis();
    if(tempotimes == THE1ST){
      tft.fillRect(0, MEASURE_DISP_YPOS, 320, 50, TFT_WHITE);
    }
    if(tempover == 1){
      Settempo_Notes(tempotimes);
    }
    else{
      Sendcode_Notes(tempotimes);
    }
    tempotimes++;
    xpos += MEASURE_DISP_SPACE;
    if(tempotimes > SAMPLE_TIMES){
      xpos = MEASURE_DISP_XPOS;
      tempotimes = THE1ST;
    }
  }

  return;
}

int RandamList(int num){
  int swap=0; //シャッフルで使用する変数
  int temp=0; //シャッフルで使用する変数

  if(num == 1){
    //配列に1から25までの数字を順番に入れて初期化
    for (int i=0; i<8; i++){
      rnd[i] = i; 
    }
  
    //Fisher-Yatesのシャッフルアルゴリズム
    for(int i=8; i>0; i--){
      swap = random(i);
      temp = rnd[i-1];
      rnd[i-1] = rnd[swap];
      rnd[swap] = temp;
    }
  }

  return rnd[num];
}

unsigned long Measure() {
  int times ;                          // sound pulse counter
  int xbit = MEASURE_DISP_XPOS;
  char  TimeStr[10];                  // for time value diaplay

  tft.setTextSize( MEASURE_DISP_SIZE );
  tft.setTextColor( TFT_RED );

  for ( times = THE1ST ; times <= SAMPLE_TIMES ; times++) {
    while ( Check_Hit() == IGNORE ) {     // wait the sound comes
      ;
    }

    if ( times == THE1ST ) {
      pasttime = millis();                    // get current time
    }
    else if ( times == THE4TH ) {
      pasttime = millis() - pasttime;         // get totla time
    }

    tft.drawString( "o", xbit, MEASURE_DISP_YPOS );
    
    if ( times < THE4TH ) {
      xbit += MEASURE_DISP_SPACE;
      delay( CHATTERING_TIME );               // pass chattering time

      while ( Check_Hit() == HITSOUND ) {    // pass the sound pulse
        ;
      }
    }
  }

  pasttime /= ( SAMPLE_TIMES - 1 );           // get average
    // This is a bogus process.
    // Properly, the interval between each of the four sound pulses should be measured.
    // This code measures only the sum of the four sound times.                                            // to here takes 2msec
  return pasttime;
}

void Settempo_Notes(int num){ //音符の描写
  tft.fillRect(NOTES_SQU_XPOS+(num-1)*NOTES_SPACE, NOTES_SQU_YPOS, NOTES_LINE_WIDTH, NOTES_LINE_HEIGHT, TFT_BLACK);
  tft.fillRect(NOTES_SQU_XPOS+(num-1)*NOTES_SPACE, NOTES_SQU_YPOS, NOTES_SQU_WIDTH, NOTES_SQU_HEIGHT, TFT_BLACK);
  tft.fillTriangle(NOTES_TRI_XPOS+(num-1)*NOTES_SPACE, NOTES_TRI_YPOS, NOTES_TRI_XPOS+(num-1)*NOTES_SPACE, NOTES_TRI_YPOS_2ND, NOTES_TRI_YPOS_3RD+(num-1)*NOTES_SPACE, NOTES_TRI_YPOS_2ND, TFT_BLACK);
  tft.fillRoundRect(NOTES_ROUND_XPOS+(num-1)*NOTES_SPACE, NOTES_ROUND_YPOS, NOTES_ROUND_HEIGHT, NOTES_ROUND_WIDTH, NOTES_ROUND_RADIUS, TFT_BLACK);

  return;
}

void Sendcode_Notes(int num){ //音符の描写
  int colornum;
  uint32_t colorlist[8] = { TFT_RED , TFT_BLUE , TFT_PURPLE , TFT_GREEN , TFT_ORANGE , TFT_CYAN , TFT_GREENYELLOW , TFT_PINK };

  colornum = RandamList(num);
  
  tft.fillRect(NOTES_SQU_XPOS+(num-1)*NOTES_SPACE, NOTES_SQU_YPOS, NOTES_LINE_WIDTH, NOTES_LINE_HEIGHT, colorlist[colornum]);
  tft.fillRect(NOTES_SQU_XPOS+(num-1)*NOTES_SPACE, NOTES_SQU_YPOS, NOTES_SQU_WIDTH, NOTES_SQU_HEIGHT, colorlist[colornum]);
  tft.fillTriangle(NOTES_TRI_XPOS+(num-1)*NOTES_SPACE, NOTES_TRI_YPOS, NOTES_TRI_XPOS+(num-1)*NOTES_SPACE, NOTES_TRI_YPOS_2ND, NOTES_TRI_YPOS_3RD+(num-1)*NOTES_SPACE, NOTES_TRI_YPOS_2ND, colorlist[colornum]);
  tft.fillRoundRect(NOTES_ROUND_XPOS+(num-1)*NOTES_SPACE, NOTES_ROUND_YPOS, NOTES_ROUND_HEIGHT, NOTES_ROUND_WIDTH, NOTES_ROUND_RADIUS, colorlist[colornum]);

  return;
}
