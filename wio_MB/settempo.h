void LastTempo_Text(void);     //今のテンポを表示しているときのタイトル
void SetTempo_Text(void);      //テンポを入力しているときのタイトル
void Tempo_Init(void);         //テンポ表示をはじめの位置からにする
void Settempo_Notes(int num);  //テンポ入力前のテンポ表示画面の音符表示
void Sendcode_Notes(int num);  //指令入力前のテンポ表示画面の音符表示
unsigned long CheckTempo(void);//今の間隔時間（テンポ）を取得
void Tempo_Disp(int tempover); //テンポ表示
unsigned long Measure(void);   //テンポを設定する
int RandamList(int num);       //ランダムで音符の色を変えるためにリスト内をランダムに入れ替える
