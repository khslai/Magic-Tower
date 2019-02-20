/*******************************************************************************
* タイトル:		ゲーム情報プログラム
* プログラム名:	Information.cpp
* 作成者:		GP11B341 35 頼凱興
* 作成日:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "Information.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define InfoTable_Height (6)	// 表示テーブルの高さ
#define InfoTable_Width (49)	// 表示テーブルの幅
#define InfoTable_X (3)			// テーブル描画の始点
#define InfoTable_Y (18)

/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/


/*******************************************************************************
* グローバル変数
*******************************************************************************/

/*******************************************************************************
関数名:	void InitInformation(void)
引数:	void
戻り値:	void
説明:	ゲーム情報の初期化
*******************************************************************************/
void InitInformation(void)
{
	return;
}

/*******************************************************************************
関数名:	void UpdateInformation(void)
引数:	void
戻り値:	void
説明:	ゲーム情報の更新処理
*******************************************************************************/
void UpdateInformation(void)
{
	return;
}

/*******************************************************************************
関数名:	void DrawInformation(void)
引数:	void
戻り値:	void
説明:	ゲーム情報の描画処理
*******************************************************************************/
void DrawInformation(void)
{
	int i = 0;
	int X = 0;
	int Length = 0;	// 配列の長さ
	char *DrawPostion = GetBGAdr(0, 0);
	PLAYER *Player = GetPlayerAdr();
	// ゲーム情報の配列
	char InfoTable[InfoTable_Height][InfoTable_Width] = {};

	if (Player->InStore == false)
	{
		switch (Player->InfoPage)
		{
			// 記号説明(1)
		case Symbol_p1:
			strcpy(&InfoTable[0][0], "(F)← 記号説明(1) →(G)");
			strcpy(&InfoTable[2][0], "①～⑩：各Lv.モンスター     上、下：階段    ");
			strcpy(&InfoTable[3][0], "○：HPポーション      Ａ：ATKUP   Ｓ：AGIUP ");
			strcpy(&InfoTable[4][0], "◎：HPハイポーション  Ｄ：DEFUP   Ｋ：扉の鍵");
			break;
			// 記号説明(2)
		case Symbol_p2:
			strcpy(&InfoTable[0][0], "(F)← 記号説明(2) →(G)");
			strcpy(&InfoTable[2][0], "＄：商店       Ⅲ：かかった扉               ");
			strcpy(&InfoTable[3][0], "剣：剣の装備   鎧：防具の装備               ");
			strcpy(&InfoTable[4][0], "Ｍ：マップ     図：怪物図鑑     翼：転送の翼");
			break;
			// 装備とアイテム
		case PlayerItem:
			strcpy(&InfoTable[0][0], "(F)← 装備とアイテム →(G)");
			strcpy(&InfoTable[1][0], "     装備                      貴重アイテム     ");
			if (Player->Item.FloorMap == true)
			{
				strcpy(&InfoTable[2][0], "                          マップ");
			}
			else
			{
				strcpy(&InfoTable[2][0], "                          ？？？");
			}
			if (Player->Item.EnemyDictionary == true)
			{
				sprintf(&InfoTable[3][0], "武器：%-16s         怪物図鑑      ", &Player->Item.Sword[0]);
			}
			else
			{
				sprintf(&InfoTable[3][0], "武器：%-16s          ？？？      ", &Player->Item.Sword[0]);
			}
			if (Player->Item.TeleportWing == true)
			{
				sprintf(&InfoTable[4][0], "防具：%-16s         転送の翼      ", &Player->Item.Armor[0]);
			}
			else
			{
				sprintf(&InfoTable[4][0], "防具：%-16s          ？？？      ", &Player->Item.Armor[0]);
			}
			break;
			// ゲームの説明
		case GameHelp:
			strcpy(&InfoTable[0][0], "(F)← ゲームの説明 →(G)");
			strcpy(&InfoTable[2][0], "移動：W,A,S,D              一時停止：P");
			strcpy(&InfoTable[3][0], "ゲーム終了：ESC            ヘルプ：H  ");
			if (Player->Item.EnemyDictionary == true && Player->Item.TeleportWing == true)
			{
				strcpy(&InfoTable[4][0], "怪物図鑑：E                転送の翼：T");
			}
			else if (Player->Item.EnemyDictionary == true && Player->Item.TeleportWing == false)
			{
				strcpy(&InfoTable[4][0], "怪物図鑑：E                           ");
			}
			else if (Player->Item.EnemyDictionary == false && Player->Item.TeleportWing == true)
			{
				strcpy(&InfoTable[4][0], "転送の翼：T                           ");
			}
			break;
		default:
			break;
		}

		// 背景にテーブルを描画
		for (i = 0; i < InfoTable_Height; i++)
		{
			if (InfoTable[i][0] == NULL)
			{
				continue;
			}
			else
			{
				Length = strlen(&InfoTable[i][0]);
				X = (InfoTable_Width - Length) / 2;
				DrawPostion = GetBGAdr(InfoTable_X + X, InfoTable_Y + i);
				strncpy(DrawPostion, &InfoTable[i][0], Length);
			}
		}
	}

	return;
}

/*******************************************************************************
関数名:	void UninitInformation(void)
引数:	void
戻り値:	void
説明:	ゲーム情報の終了処理
*******************************************************************************/
void UninitInformation(void)
{
	return;
}