#define OK 0    // コード登録時にエラーなし
#define NG 1    // コード登録時にエラーあり

void SetCode_Init(void);    // コード登録画面の初期化
void SetCode_Disp(void);    // コード登録画面を描画
void Right_Move(void);       // カーソルを右に動かす
void Left_Move(void);        // カーソルを左に動かす
void Up_Move(void);          // カーソルを上に動かす
void Down_Move(void);        // カーソルを下に動かす
void Bit_Flip(void);         // ビットを反転させる

int Set_Code(void);          // コードを登録する
int Copy_CodeSet(int num);  // 登録されたコードをコード送信で使えるようにする
void Code_Reset(void);
void Default_Code(void);
