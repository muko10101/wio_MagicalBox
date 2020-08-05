#include "menu.h"

void Title_Text() {  // タイトルの表示
  tft.setTextColor(TFT_MAGENTA);
  tft.setTextSize(TITLE_TEXT_SIZE);
  tft.drawString("MENU", TITLE_TEXT_XPOS, TITLE_TEXT_YPOS);

  return;
}

void Title_SetWay() {  // タイトルの表示
  tft.setTextColor(TFT_MAGENTA);
  tft.setTextSize(TITLE_TEXT_SIZE);
  tft.drawString("SET WAY", TITLE_TEXT_XPOS, TITLE_TEXT_YPOS);

  return;
}

void Select_Menu(int select){  // 選択状態に対応するものを強調
  
  tft.setTextSize(MENU_TEXT_SIZE);
  
  switch(select){
    case SET_CODE:
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString("SET TEMPO", MENU_TEXT_XPOS, MENU_TEXT_YPOS + MENU_TEXT_SPACE);
      tft.drawString("SEND CODE", MENU_TEXT_XPOS, MENU_TEXT_YPOS + (MENU_TEXT_SPACE * 2));
      tft.setTextColor(TFT_BLACK, TFT_RED);
      tft.drawString("SET CODE", MENU_TEXT_XPOS, MENU_TEXT_YPOS);
      break;
      
    case SET_TEMPO:
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString("SET CODE", MENU_TEXT_XPOS, MENU_TEXT_YPOS);
      tft.drawString("SEND CODE", MENU_TEXT_XPOS, MENU_TEXT_YPOS + (MENU_TEXT_SPACE * 2));
      tft.setTextColor(TFT_BLACK, TFT_RED);
      tft.drawString("SET TEMPO", MENU_TEXT_XPOS, MENU_TEXT_YPOS + MENU_TEXT_SPACE);
      break;
      
    case SEND_CODE:
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.drawString("SET CODE", MENU_TEXT_XPOS, MENU_TEXT_YPOS);
      tft.drawString("SET TEMPO", MENU_TEXT_XPOS, MENU_TEXT_YPOS + MENU_TEXT_SPACE);
      tft.setTextColor(TFT_BLACK, TFT_RED);
      tft.drawString("SEND CODE", MENU_TEXT_XPOS, MENU_TEXT_YPOS + (MENU_TEXT_SPACE * 2));
      break;
  }

  return;
}

void Select_Way(int way){
  
  tft.setTextSize(MENU_TEXT_SIZE);
  
  if (way == SET_WIO) {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("WEB", MENU_TEXT_XPOS, MENU_TEXT_YPOS + (MENU_TEXT_SPACE * 2));
    tft.setTextColor(TFT_BLACK, TFT_RED);
    tft.drawString("WIO", MENU_TEXT_XPOS, MENU_TEXT_YPOS);
  }
  else {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString("WIO", MENU_TEXT_XPOS, MENU_TEXT_YPOS);
    tft.setTextColor(TFT_BLACK, TFT_RED);
    tft.drawString("WEB", MENU_TEXT_XPOS, MENU_TEXT_YPOS + (MENU_TEXT_SPACE * 2));
  }

  return;
}
