/*******************************************************************************
* タイトル:		商店プログラム
* プログラム名:	Store.cpp
* 作成者:		GP11B341 35 頼凱興
* 作成日:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "Store.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define StoreBG_Height (21)		// 商店背景の高さ
#define StoreBG_Width (37)		// 商店背景の縦
#define StoreArr_Height (19)	// 商店の表現内容の高さ
#define StoreArr_Width (31)		// 商店の表現内容の縦
#define ArrowColumn (12)		// 矢印の初期座標
#define StoreStart_X (9)		// 背景に描画するための座標
#define StoreStart_Y (3)
#define MoneyStoreFloor (3)		// 商店の所在階層
#define EXPStoreFloor (5)		// 経験値商店の所在階層
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
関数名:	void InitStore(void)
引数:	void
戻り値:	void
説明:	商店の初期化処理
*******************************************************************************/
void InitStore(void)
{
	return;
}

/*******************************************************************************
関数名:	void UpdateStore(void)
引数:	void
戻り値:	void
説明:	商店の更新処理
*******************************************************************************/
void UpdateStore(void)
{
	return;
}

/*******************************************************************************
関数名:	void DrawStore(void)
引数:	void
戻り値:	void
説明:	商店の描画処理
*******************************************************************************/
void DrawStore(void)
{
	int i = 0;
	int X = 0;
	static int Y = 0;				// 矢印のY座標
	int Length = 0;					// 配列の長さ
	static bool FirstTime = true;	// 初めて商店を入る
	char *DrawPostion = GetBGAdr(StoreStart_X, StoreStart_Y);
	PLAYER *Player = GetPlayerAdr();
	// 商店の背景
	char StoreBG[StoreBG_Height][StoreBG_Width] = {
		"＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"|                                  |",
		"￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣",
	};
	// 商店の表現内容配列
	char StoreArr[StoreArr_Height][StoreArr_Width] = {};

	// 表示したい内容、最大全角15文字
	// 金の商店
	if (Player->CurrentFloor == MoneyStoreFloor)
	{
		strcpy(StoreArr[0], "　 ______                    ");
		strcpy(StoreArr[1], " ´>　　 ｀ヽ、              ");
		strcpy(StoreArr[2], "_,'-=[＞＜]=.,_  いらっしゃい");
		strcpy(StoreArr[3], " ヽi<ﾚﾉλﾉ)ﾚ〉             ");
		strcpy(StoreArr[4], "  ﾉﾚ§ﾟ ヮﾟﾉiゝ              ");
		strcpy(StoreArr[5], "｀k'_〉｀=' !つ              ");
		strcpy(StoreArr[6], "  i_ﾉ'i!￣i!>、              ");
		strcpy(StoreArr[7], "　 ~'i,ﾝT,ﾝ\"~                ");
		strcpy(StoreArr[8], "$20 を払えば、ステータス上昇");
		strcpy(StoreArr[9], "ができるよ～                ");
		strcpy(StoreArr[11], " HP + 500");
		strcpy(StoreArr[13], "ATK + 3");
		strcpy(StoreArr[15], "DEF + 3");
		strcpy(StoreArr[17], "Exit");
	}
	// 経験値の商店
	else if (Player->CurrentFloor == EXPStoreFloor)
	{
		strcpy(StoreArr[0], "　 ______                    ");
		strcpy(StoreArr[1], " ´>　　 ｀ヽ、              ");
		strcpy(StoreArr[2], "_,'-=[＞＜]=.,_  いらっしゃい");
		strcpy(StoreArr[3], " ヽi<ﾚﾉλﾉ)ﾚ〉             ");
		strcpy(StoreArr[4], "  ﾉﾚ§ﾟ ヮﾟﾉiゝ              ");
		strcpy(StoreArr[5], "｀k'_〉｀=' !つ              ");
		strcpy(StoreArr[6], "  i_ﾉ'i!￣i!>、              ");
		strcpy(StoreArr[7], "　 ~'i,ﾝT,ﾝ\"~                ");
		strcpy(StoreArr[8], "経験値を払えば、ステータス   ");
		strcpy(StoreArr[9], "上昇ができるよ～             ");
		strcpy(StoreArr[11], " Level + 1(Exp.25)");
		strcpy(StoreArr[13], "AGI + 1(Exp.15)");
		strcpy(StoreArr[15], "ATK&DEF + 1(Exp.15)");
		strcpy(StoreArr[17], "Exit");
	}
	// 矢印の描画
	if (Player->InPause == false && FirstTime == false)
	{
		switch (Player->HitKey)
		{
		case 'w':
		case 0x48:	// 上へ移動する
			Y -= 2;
			break;
		case 's':
		case 0x50:	// 下へ移動する
			Y += 2;
			break;
		case 0x0D:	// Enterキー
			// Exit
			if (Y == 6)
			{
				Y = 0;
				// 商店から出る
				Player->InStore = false;
				FirstTime = true;
			}
			else if (Player->CurrentFloor == MoneyStoreFloor)
			{
				if (Player->Status.Money >= 20)
				{
					// HP + 500
					if (Y == 0)
					{
						Player->Status.HP += 500;
					}
					// ATK + 3
					else if (Y == 2)
					{
						Player->Status.ATK += 3;
					}
					// DEF + 3
					else if (Y == 4)
					{
						Player->Status.DEF += 3;
					}
					Player->Status.Money -= 20;
				}
				else
				{
					strcpy(StoreArr[8], "");
					strcpy(StoreArr[9], "残念～金が足りない");
				}
			}
			else if (Player->CurrentFloor == EXPStoreFloor)
			{
				if (Player->Status.EXP >= 15)
				{
					// Level + 1
					if (Y == 0)
					{
						if (Player->Status.EXP >= 25)
						{
							Player->Status.Level++;
							Player->Status.HP =	(int)(Player->Status.HP * 1.2);
							Player->Status.ATK = (int)(Player->Status.ATK * 1.1);
							Player->Status.DEF = (int)(Player->Status.DEF * 1.1);
							Player->Status.EXP -= 25;
							// スキル習得
							if (Player->Status.Level == 3)
							{
								Player->Event_No = SkillEvent;
								Player->Status.GetSkill = true;
							}
						}
						else
						{
							strcpy(StoreArr[8], "");
							strcpy(StoreArr[9], "残念～経験値が足りない");
						}
					}
					// AGI + 1
					else if (Y == 2)
					{
						Player->Status.AGI += 1;
						Player->Status.EXP -= 15;
					}
					// ATK&DEF + 1
					else if (Y == 4)
					{
						Player->Status.ATK += 1;
						Player->Status.DEF += 1;
						Player->Status.EXP -= 15;
					}
				}
				else
				{
					strcpy(StoreArr[8], "");
					strcpy(StoreArr[9], "残念～経験値が足りない");
				}
			}
			break;
		default:
			break;
		}
		// 矢印位置の調整
		Y = (Y + 8) % 8;
		/*
		Y = Y < 0 ? 6 : Y;
		Y = Y > 6 ? 0 : Y;
		*/
	}

	// 商店背景に商店内容を上書き
	for (i = 0; i < StoreArr_Height; i++)
	{
		if (StoreArr[i][0] == NULL)
		{
			continue;
		}
		else
		{
			Length = strlen(&StoreArr[i][0]);
			X = (StoreBG_Width - Length) / 2;
			strncpy(&StoreBG[i + 1][X], &StoreArr[i][0], Length);
			// 矢印を描画
			if (i == ArrowColumn - 1)
			{
				strncpy(&StoreBG[ArrowColumn + Y][X - 3], "→", 2);
			}
		}
	}

	if (Player->InStore == true)
	{
		// ゲーム背景に商店配列を上書き
		for (i = 0; i < StoreBG_Height; i++)
		{
			Length = strlen(&StoreBG[i][0]);
			DrawPostion = GetBGAdr(StoreStart_X, StoreStart_Y + i);
			strncpy(DrawPostion, &StoreBG[i][0], Length);
		}
		FirstTime = false;
	}

	return;
}

/*******************************************************************************
関数名:	void UninitStore(void)
引数:	void
戻り値:	void
説明:	商店の終了処理
*******************************************************************************/
void UninitStore(void)
{
	return;
}