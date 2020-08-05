#include "settempo.h"
#include "hit.h"

#define TITLE_TEXT_SIZE 4      // タイトル文字の大きさ         
#define TITLE_TEXT_XPOS 15     // タイトルのx座標
#define TITLE_TEXT_YPOS 40     // タイトルのy座標

#define MEASURE_DISP_YPOS 80 
#define MEASURE_DISP_XPOS 10    // maesuring display x position (start position)
#define MEASURE_DISP_SIZE 5     // charactor size
#define MEASURE_DISP_SPACE 40   // charactor spacing ( x position increse by this value )
#define TEMPO_DISP_TAIL   130

#define TEMPO_TEXT_SIZE 3      // テンポ表示の大きさ         
#define TEMPO_TEXT_XPOS 10     // テンポ表示のx座標
#define TEMPO_TEXT_YPOS 150     // テンポ表示のy座標

#define SAMPLE_TIMES    4       // sampling times
#define THE1ST          1       // the 1st sample
#define THE4TH          4       // the 4th sample

#define CHATTERING_TIME 50      // Time to pass the chatter (msec)

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
    //tft.setTextColor(TFT_RED);
    //tft.setTextSize(MEASURE_DISP_SIZE);
    //tft.drawString( "o", xpos, MEASURE_DISP_YPOS );
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
  //int rnd[8]; //乱数用配列

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
  //unsigned long pasttime;             // time measure var
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

    //Serial.print("kiteruyo");
    tft.drawString( "o", xbit, MEASURE_DISP_YPOS );
    //SoundNotes(times);

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
  tft.fillRect(49+(num-1)*50, 80, 2, 45, TFT_BLACK);
  tft.fillRect(49+(num-1)*50, 80, 5, 10, TFT_BLACK);
  tft.fillTriangle(54+(num-1)*50, 80, 54+(num-1)*50, 90, 70+(num-1)*50, 90, TFT_BLACK);
  tft.fillRoundRect(30+(num-1)*50, 115, 20, 15, 8, TFT_BLACK);

  return;
}

void Sendcode_Notes(int num){ //音符の描写
  int colornum;
  uint32_t colorlist[8] = { TFT_RED , TFT_BLUE , TFT_PURPLE , TFT_GREEN , TFT_ORANGE , TFT_YELLOW , TFT_GREENYELLOW , TFT_PINK };

  //colorlist = { "TFT_RED" , "TFT_BLUE" , "TFT_PURPLE" , "TFT_GREEN" , "TFT_RED" , "TFT_YELLOW" , "TFT_GREENYELLOW" , "TFT_PINK" };
  
  //randomSeed(analogRead(0));
  //random();
  //rannum = random(0,7);

  colornum = RandamList(num);
  
  tft.fillRect(49+(num-1)*50, 80, 2, 45, colorlist[colornum]);
  tft.fillRect(49+(num-1)*50, 80, 5, 10, colorlist[colornum]);
  tft.fillTriangle(54+(num-1)*50, 80, 54+(num-1)*50, 90, 70+(num-1)*50, 90, colorlist[colornum]);
  tft.fillRoundRect(30+(num-1)*50, 115, 20, 15, 8, colorlist[colornum]);

  return;
}
