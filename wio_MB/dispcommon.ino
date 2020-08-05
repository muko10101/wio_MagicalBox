#include "dispcommon.h"

/*screen_reset*/
void Screen_Reset() {
  tft.fillScreen(TFT_WHITE);

  return;
}

/*virtualbtn*/
void VirtualBtn_Blank() {    // メニュー画面での仮想ボタンを表示
  tft.fillRect(MIN_DISP_XPOS, MIN_DISP_YPOS, MAX_DISP_XPOS, BAR_HEIGHT, BAR_COLOR);
  tft.fillRoundRect(BTN1_XPOS, BTN_YPOS, BTN_WIDTH, BTN_HEIGHT, BTN_RADIUS, BTN_COLOR);
  tft.fillRoundRect(BTN1_XPOS + BTN_SPACE, BTN_YPOS, BTN_WIDTH, BTN_HEIGHT, BTN_RADIUS, BTN_COLOR);
  tft.fillRoundRect(BTN1_XPOS + (BTN_SPACE * 2), BTN_YPOS, BTN_WIDTH, BTN_HEIGHT, BTN_RADIUS, BTN_COLOR);

  return;
}

void VirtualBtn_SetCode_Wio() {

  VirtualBtn_Blank();
  
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(BTN_TEXT_SIZE);
  tft.drawString("ok", BTN1_TEXT2_XPOS, BTN_TEXT_YPOS);
  tft.drawString("reset", BTN2_TEXT5_XPOS, BTN_TEXT_YPOS);
  tft.drawString("menu", BTN3_TEXT4_XPOS, BTN_TEXT_YPOS);
  
  return;
}

void VirtualBtn_SetCode_Web() {

  VirtualBtn_Blank();
  
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(BTN_TEXT_SIZE);
  tft.drawString("ok", BTN1_TEXT2_XPOS, BTN_TEXT_YPOS);
  tft.drawString("menu", BTN3_TEXT4_XPOS, BTN_TEXT_YPOS);
  
  return;
}

void VirtualBtn_SetTempo() {

  VirtualBtn_Blank();

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(BTN_TEXT_SIZE);
  tft.drawString("start", BTN1_TEXT5_XPOS, BTN_TEXT_YPOS);
  tft.drawString("menu", BTN3_TEXT4_XPOS, BTN_TEXT_YPOS);

  return;
}

void VirtualBtn_OnlyMenu() {

  VirtualBtn_Blank();

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(BTN_TEXT_SIZE);
  tft.drawString("menu", BTN3_TEXT4_XPOS, BTN_TEXT_YPOS);

  return;
}
