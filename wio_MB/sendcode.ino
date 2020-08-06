#include "sendcode.h"
#include "settempo.h"
#include "hit.h"
#include "setcode.h"

#define TITLE_TEXT_SIZE 4      // タイトル文字の大きさ         
#define TITLE_TEXT_XPOS 15     // タイトルのx座標
#define TITLE_TEXT_YPOS 40     // タイトルのy座標

#define MEASURE_DISP_YPOS 80    // maesuring display y position (start position)
#define MEASURE_DISP_XPOS 10    // maesuring display x position (start position)
#define MEASURE_DISP_SIZE 5     // charactor size
#define MEASURE_DISP_SPACE 40   // charactor spacing ( x position increse by this value )

#define CODE_TEXT_SIZE 3      // コード表示の大きさ         
#define CODE_TEXT_XPOS 10     // コード表示のx座標
#define CODE_TEXT_YPOS 180     // コード表示のy座標

#define SAMPLE_TIMES    4       // sampling times
#define THE2ST          2       // the 2nd sample

static int codeval;
static int match = 100;

void NowTempo_Text() {  // テンポ表示時のタイトル表示
  tft.setTextColor(TFT_MAGENTA);
  tft.setTextSize(TITLE_TEXT_SIZE);
  tft.drawString("NOW TEMPO", TITLE_TEXT_XPOS, TITLE_TEXT_YPOS);

  return;
}

void SendCode_Text() {  // 指令入力時のタイトル表示
  tft.setTextColor(TFT_MAGENTA);
  tft.setTextSize(TITLE_TEXT_SIZE);
  tft.drawString("SEND CODE", TITLE_TEXT_XPOS, TITLE_TEXT_YPOS);

  return;
}

void SampleHits(){
  int i;
  int code[4];
  unsigned long pasttime;
  unsigned long interval;
  int waittime;
  int hit;
  int xpos = MEASURE_DISP_XPOS;
  
  interval = CheckTempo();
  waittime = interval / 2;

  tft.drawRect(xpos,120,40,40,TFT_ORANGE);
  tft.drawRect(xpos + MEASURE_DISP_SPACE, 120,40,40,TFT_PINK);
  tft.drawRect(xpos + (MEASURE_DISP_SPACE * 2),120,40,40,TFT_PINK);
  tft.drawRect(xpos + (MEASURE_DISP_SPACE * 3),120,40,40,TFT_PINK);
  
  delay(waittime); 
  
  tft.setTextColor( TFT_BLACK );
  tft.setTextSize( MEASURE_DISP_SIZE );
  
  pasttime = millis();

  code[0] = 0;
  hit = HITOFF;

  while(millis() - pasttime < interval){
    if ( hit == 0 ){
      tft.fillRect(xpos,120,(40 * (millis() - pasttime)) / interval,40,TFT_PINK);
    }
    else {
      tft.fillRect(xpos,120,(40 * (millis() - pasttime)) / interval,40,TFT_RED);
    }
    if(Check_Hit() == HITSOUND){
      hit = HITON;
      tft.drawString( "1", xpos, MEASURE_DISP_YPOS );
    }
  }
  if(hit == HITON){
    code[0] = 1;
  }
  else{
    tft.drawString( "0", xpos, MEASURE_DISP_YPOS );
  }

  hit = HITOFF;

  for(i = THE2ST; i <= SAMPLE_TIMES; i++){
    pasttime = millis();
    code[i-1] = 0;
    xpos += MEASURE_DISP_SPACE;
    
    while(millis() - pasttime < interval){
      if ( hit == HITOFF ){
        tft.fillRect(xpos,120,(40 * (millis() - pasttime)) / interval,40,TFT_PINK);
      }
      else {
        tft.fillRect(xpos,120,(40 * (millis() - pasttime)) / interval,40,TFT_RED);
      }
      if(Check_Hit() == HITSOUND){
        hit = HITON;
        tft.drawString( "1", xpos, MEASURE_DISP_YPOS );
      }
    }
    if(hit == HITON){
      code[i-1] = 1;
    }
    else{
      tft.drawString( "0", xpos, MEASURE_DISP_YPOS );
    }
    hit = HITOFF;
  }

  codeval = code[0]*8 + code[1]*4 + code[2]*2 + code[3];
  
  return;
}

void Send_Serial(){
  for(int i = 0; i < 8; i++){
    if(codeval == Copy_CodeSet(i)){
      match = i;
    }
  }

  tft.setTextSize( CODE_TEXT_SIZE );
  
  switch(match){
    case 0:
      Serial.write("Up");
      tft.drawString( "CODE : UP", CODE_TEXT_XPOS, CODE_TEXT_YPOS );
      break;
      
    case 1:
      Serial.write("Down");
      tft.drawString( "CODE : DOWN", CODE_TEXT_XPOS, CODE_TEXT_YPOS );
      break;

    case 2:
      Serial.write("Right");
      tft.drawString( "CODE : RIGHT", CODE_TEXT_XPOS, CODE_TEXT_YPOS );
      break;
      
    case 3:
      Serial.write("Left");
      tft.drawString( "CODE : LEFT", CODE_TEXT_XPOS, CODE_TEXT_YPOS );
      break;
      
    case 4:
      Serial.write("UpRight");
      tft.drawString( "CODE : UPRIGHT", CODE_TEXT_XPOS, CODE_TEXT_YPOS );
      break;
      
    case 5:
      Serial.write("UpLeft");
      tft.drawString( "CODE : UPLEFT", CODE_TEXT_XPOS, CODE_TEXT_YPOS );
      break;

    case 6:
      Serial.write("Enter");
      tft.drawString( "CODE : STOP", CODE_TEXT_XPOS, CODE_TEXT_YPOS );
      break;

    case 7:
      Serial.write("Space");
      tft.drawString( "CODE : FLASH", CODE_TEXT_XPOS, CODE_TEXT_YPOS );
      break;

    default:
      tft.drawString( "CODE : ERROR!!", CODE_TEXT_XPOS, CODE_TEXT_YPOS );
      break;
  }
  delay(3000);

  return;
  
}

void LoopSend(){
  switch(match){
    case 0:
      Serial.write("Up");
      break;
      
    case 1:
      Serial.write("Down");
      break;

    case 2:
      Serial.write("Right");
      break;
      
    case 3:
      Serial.write("Left");
      break;
      
    case 4:
      Serial.write("UpRight");
      break;
      
    case 5:
      Serial.write("UpLeft");
      break;

    case 6:
      Serial.write("Enter");
      break;

    case 7:
      Serial.write("Space");
      break;
  }
  return;
}
