##define HITON  1  //打音観測した
#define HITOFF 0  //打音観測しない

void NowTempo_Text(void); //今のテンポを表示しているときのタイトル
void SendCode_Text(void); //指令入力中のタイトル
void SampleHits(void);    //指令入力
void Send_Serial(void);   //PCに指令送信
void LoopSend(void);      //断続的なPCへの指令送信
