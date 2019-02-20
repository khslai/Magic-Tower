/*******************************************************************************
* タイトル:		プレイヤーステータスプログラム
* プログラム名:	Status.cpp
* 作成者:		GP11B341 35 頼凱興
* 作成日:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "Status.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define Status_Height (23)		// プレイヤーステータス配列の高さ
#define Status_Width (25)		// プレイヤーステータス配列の横幅
#define StatusStart_X (52)		// プレイヤーステータス描画座標
#define StatusStart_Y (1)

// Player Statusを更新するときの位置
#define Level_EXPColumn (9)
#define HP_MPColumn (11)
#define ATKColumn (13)
#define DEFColumn (15)
#define AGIColumn (17)
#define MoneyColumn (19)
#define DoorKeyColumn (21)
/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/


/*******************************************************************************
* グローバル変数
*******************************************************************************/
// プレイヤーステータスの配列
char Status[Status_Height][Status_Width] = {
	"                        ",		// 0
	"       i＾ヽry/`ヽ、    ",		// 1
	"       ,'｀⌒ﾞ｀ヽ'     ",		// 2
	"      Ｌ(ﾉ八ﾉﾉＬi〉     ",		// 3
	"      il､ﾟヮﾟ[illλ     ",		// 4
	"       ﾉi` ﾑ´」,ﾍﾘ     ",		// 5
	"     〈／i.Tヽヾ､_〉    ",		// 6
	"      ﾞ''ｔ_ｧ_ｧ‐゛     ",		// 7
	"",								// 8
	"",								// 9
	"",								// 10
	"",								// 11
	"",								// 12
	"",								// 13
	"",								// 14
	"",								// 15
	"",								// 16
	"",								// 17
	"",								// 18
	"",								// 19
	"",								// 20
	"",								// 21
	"",								// 22
};


/*******************************************************************************
関数名:	void InitStatus(void)
引数:	void
戻り値:	void
説明:	プレイヤーステータスの初期化処理
*******************************************************************************/
void InitStatus(void)
{
	return;
}

/*******************************************************************************
関数名:	void UpdateStatus(void)
引数:	void
戻り値:	void
説明:	プレイヤーステータスの更新処理
*******************************************************************************/
void UpdateStatus(void)
{
	return;
}

/*******************************************************************************
関数名:	void DrawStatus(void)
引数:	void
戻り値:	void
説明:	プレイヤーステータスの描画処理
*******************************************************************************/
void DrawStatus(void)
{
	int i = 0;
	int X = 0;
	int Length = 0;
	char *DrawPostion = GetBGAdr(0, 0);
	PLAYER *Player = GetPlayerAdr();

	// プレイヤーのステータス更新
	sprintf(&Status[Level_EXPColumn][0], "Lv.%-3d EXP：%-3d", Player->Status.Level, Player->Status.EXP);
	sprintf(&Status[HP_MPColumn][0], "HP：%-5d MP：%d", Player->Status.HP, Player->Status.MP);
	sprintf(&Status[ATKColumn][0], "ATK：%-3d", Player->Status.ATK);
	sprintf(&Status[DEFColumn][0], "DEF：%-3d", Player->Status.DEF);
	sprintf(&Status[AGIColumn][0], "AGI：%-3d", Player->Status.AGI);
	sprintf(&Status[MoneyColumn][0], "持ち金：$%-3d", Player->Status.Money);
	sprintf(&Status[DoorKeyColumn][0], "扉の鍵 x %-3d", Player->Item.DoorKey);

	/* プレイヤーステータス描画処理 */
	// 図形の始点は(52,1)
	// (Status_ptr + i * Status_Width + 0) = &Status_ptr[i][0]
	// *(Status_ptr + i * Status_Width + 0) = Status_ptr[i][0]
	for (i = 0; i < Status_Height; i++)
	{
		if (Status[i][0] == NULL)
		{
			continue;
		}
		else
		{
			Length = strlen(&Status[i][0]);
			X = (Status_Width - Length) / 2;
			DrawPostion = GetBGAdr(StatusStart_X + X, StatusStart_Y + i);
			strncpy(DrawPostion, &Status[i][0], Length);
		}
	}
	return;
}

/*******************************************************************************
関数名:	void UninitStatus(void)
引数:	void
戻り値:	void
説明:	プレイヤーステータスの終了処理
*******************************************************************************/
void UninitStatus(void)
{
	return;
}