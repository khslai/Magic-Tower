/*******************************************************************************
* タイトル:		メッセージプログラム
* プログラム名:	Message.cpp
* 作成者:		GP11B341 35 頼凱興
* 作成日:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "Message.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
// BackGroundの(3,6)からMessageBox配列描く始まる
#define MessageBox_Height (7)	// メッセージボックス配列の高さ
#define MessageBox_Width (49)	// メッセージボックス配列の横幅
#define Message_Height (5)		// メッセージ配列の高さ
#define Message_Width (41)		// メッセージ配列の横幅
#define Message_X (3)			// メッセージ描画の始点座標
#define Message_Y (6)


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
関数名:	void InitMessage(void)
引数:	void
戻り値:	void
説明:	メッセージの初期化処理
*******************************************************************************/
void InitMessage(void)
{
	return;
}

/*******************************************************************************
関数名:	void UpdateMessage(void)
引数:	void
戻り値:	void
説明:	メッセージの更新処理
*******************************************************************************/
void UpdateMessage(void)
{
	return;
}

/*******************************************************************************
関数名:	void DrawMessage(void)
引数:	void
戻り値:	void
説明:	メッセージの描画処理
*******************************************************************************/
void DrawMessage(void)
{
	int i = 0;
	int Length = 0;
	int X = 0;
	int Y = 0;
	int Column = 0;
	PLAYER *Player = GetPlayerAdr();
	int Event_No = Player->Event_No;	// 現在発生したイベント番号
	char *DrawPostion = GetBGAdr(0, 0);	// 背景に描画する座標
	// 空白のメッセージボックス
	char MessageBox[MessageBox_Height][MessageBox_Width] = {
		"------------------------------------------------",
		"                                                ",
		"                                                ",
		"                                                ",
		"                                                ",
		"                                                ",
		"------------------------------------------------",
	};
	// 表示したいメッセージ、最大全角20文字、5行
	char Message[Message_Height][Message_Width] = {};

	// どんなイベント
	switch (Event_No)
	{
		// 一時停止
	case PauseEvent:
		strcpy(Message[0], "PAUSE");
		break;
		// HPポーション
	case HP_Potion:
		sprintf(Message[0], "HP + %d", Item_Potion);
		break;
		// HPハイポーション
	case HP_HiPotion:
		sprintf(Message[0], "HP + %d", Item_HiPotion);
		break;
		// ATKアップ
	case ATKUp:
		sprintf(Message[0], "ATK + %d", Item_ATKUP);
		break;
		// DEFアップ
	case DEFUp:
		sprintf(Message[0], "DEF + %d", Item_DEFUP);
		break;
		// AGIアップ
	case AGIUp:
		sprintf(Message[0], "AGI + %d", Item_AGIUP);
		break;
		// EXPアップ
	case EXPEvent:
		sprintf(Message[0], "EXP + %d", Item_EXP);
		break;
		// 金を手に入れた
	case MoneyEvent:
		sprintf(Message[0], "$%d を手に入れた！", Item_Money);
		break;
		// 武器を手に入れた
	case SwordEvent:
		sprintf(Message[0], "%s を手に入れた！", &Player->Item.Sword[0]);
		strcpy(Message[1], " ");
		if (strcmp(Player->Item.Sword, Sword01) == 0)
		{
			sprintf(Message[2], "%s を装備して、ATK + %d", &Player->Item.Sword[0], Equip_Sword01);
		}
		else if (strcmp(Player->Item.Sword, Sword02) == 0)
		{
			sprintf(Message[2], "%s を装備して、ATK + %d", &Player->Item.Sword[0], Equip_Sword02);
		}
		else if (strcmp(Player->Item.Sword, Sword03) == 0)
		{
			sprintf(Message[2], "%s を装備して、ATK + %d", &Player->Item.Sword[0], Equip_Sword03);
		}
		break;
		// 防具を手に入れた
	case ArmorEvent:
		sprintf(Message[0], "%s を手に入れた！", &Player->Item.Armor[0]);
		strcpy(Message[1], " ");
		if (strcmp(&Player->Item.Armor[0], Armor01) == 0)
		{
			sprintf(Message[2], "%s を装備して、DEF + %d", &Player->Item.Armor[0], Equip_Armor01);
		}
		else if (strcmp(&Player->Item.Armor[0], Armor02) == 0)
		{
			sprintf(Message[2], "%s を装備して、DEF + %d", &Player->Item.Armor[0], Equip_Armor02);
		}
		else if (strcmp(&Player->Item.Armor[0], Armor03) == 0)
		{
			sprintf(Message[2], "%s を装備して、DEF + %d", &Player->Item.Armor[0], Equip_Armor03);
		}
		break;
		// 扉の鍵
	case DoorKey:
		strcpy(Message[0], "扉の鍵を手に入れた");
		break;
		// 鍵が足りない
	case KeyNoEnough:
		strcpy(Message[0], "鍵が足りない");
		break;
		// ダンジョンマップ
	case GetFloorMap:
		strcpy(Message[0], "ダンジョンのマップを手に入れた！");
		strcpy(Message[1], " ");
		strcpy(Message[2], "今から各階層の構造が見える");
		break;
		// 怪物図鑑
	case GetDictionary:
		strcpy(Message[0], "怪物図鑑を手に入れた！");
		strcpy(Message[1], "今から各エネミーの詳細情報が見える");
		strcpy(Message[2], "図鑑を読む → (E)");
		break;
		// 転送の翼
	case GetTeleport:
		strcpy(Message[0], "転送の翼を手に入れた！");
		strcpy(Message[1], "今から階層間がワープできます");
		strcpy(Message[2], "アイテムを使う → (T)");
		break;
		// 転送失敗
	case CantTeleport:
		strcpy(Message[0], "今は階段の中、転送できない！");
		break;
		// ゲーム終了
	case GameExit:
		strcpy(Message[0], "ゲームを終了してよろしいでしょうか(Y/N)");
		break;
		// スキル習得
	case SkillEvent:
		strcpy(Message[0], "おめでとう、今からスキルが使える   ");
		strcpy(Message[1], "使い方：戦闘開始前、スキル(S)を押す");
		strcpy(Message[2], "使ったら無条件勝利になる(ボス除外) ");
		strcpy(Message[3], "毎回使う後MP-1、MPは回復不能の数値 ");
		strcpy(Message[4], "だからよく考えて、使ってください   ");
		Player->Event_No = Nothing;
		break;
		// 隠しエリアのスイッチを押す
	case TreasureRoom:
		strcpy(Message[0], "スイッチを押した後、巨大な声が聞こえる");
		strcpy(Message[1], " ");
		strcpy(Message[2], "どうやらある階層は変化を起こしたみたい");
		break;
		// ボスの部屋に入る
	case EnterBossRoom:
		strcpy(Message[0], "これからは塔の最上層、入ったら戻れない");
		strcpy(Message[1], " ");
		strcpy(Message[2], "本当によろしいでしょうか(Y/N)");
		break;
		// ボスの会話
	case BossEvent:
		strcpy(Message[0], "....................");
		strcpy(Message[1], "....................");
		strcpy(Message[2], "....................");
		Player->InBossBattle = true;
		break;
		// ゲームクリア
	case GameClear:
		strcpy(Message[0], "Thank for your Playing");
		strcpy(Message[1], " ");
		strcpy(Message[2], "G A M E   C L E A R！");
		Player->ExitGame = true;
		break;
		// ゲームオーバー
	case GameOver:
		strcpy(Message[0], "G a m e   O v e r");
		Player->ExitGame = true;
		break;
	default:
		break;
	}

	// メッセージ行数の計算
	for (Column = 0; Message[Column][0] != NULL && Column < Message_Height; Column++)
	{
		;
	}
	// Y = メッセージボックス上から下までの真ん中
	Y = (MessageBox_Height - Column) / 2;
	for (i = 0; i < Message_Height && Message[i][0] != NULL; i++)
	{
		// X = メッセージボックス左から右までの真ん中
		X = (MessageBox_Width - strlen(&Message[i][0])) / 2;
		// メッセージボックスにメッセージを上書き
		strncpy(&MessageBox[Y + i][X], Message[i], strlen(Message[i]));
	}

	// 背景にメッセージボックスを上書き
	for (i = 0; i < MessageBox_Height && MessageBox[i][0] != NULL; i++)
	{
		Length = strlen(&MessageBox[i][0]);
		DrawPostion = GetBGAdr(Message_X, Message_Y + i);
		strncpy(DrawPostion, &MessageBox[i][0], Length);
	}

	return;
}

/*******************************************************************************
関数名:	void UninitMessage(void)
引数:	void
戻り値:	void
説明:	メッセージの終了処理
*******************************************************************************/
void UninitMessage(void)
{
	return;
}