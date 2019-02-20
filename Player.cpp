/*******************************************************************************
* タイトル:		プレイヤープログラム
* プログラム名:	Player.cpp
* 作成者:		GP11B341 35 頼凱興
* 作成日:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "Player.h"
#include "Battle.h"
#include "Item.h"
#include "Title.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define TreasureRoom_X (12)		// 隠しエリア入口の座標
#define TreasureRoom_Y (6)
#define TreasureRoomTP_X (32)	// 隠しエリア転移ポイントの座標
#define TreasureRoomTP_Y (6)
#define TreasureExit_X (10)		// 隠しエリア出口の座標
#define TreasureExit_Y (12)
#define BossRoomStart_X (22)	// ボス部屋入ったらの位置座標
#define BossRoomStart_Y (15)

// 10Fの転移ポイントの位置座標
// R = Right , L = Left , M = Middle , U = Up , D = Down
enum Floor10F_Teleport
{
	// 右下
	PointRD_RD_X = 44,
	PointRD_RD_Y = 14,
	PointRD_RU_X = 44,
	PointRD_RU_Y = 11,
	PointRD_LU_X = 38,
	PointRD_LU_Y = 11,
	// 右上
	PointRU_RD_X = 44,
	PointRU_RD_Y = 6,
	PointRU_RU_X = 44,
	PointRU_RU_Y = 3,
	PointRU_LU_X = 38,
	PointRU_LU_Y = 3,
	// 中央の上
	PointMU_R_X = 32,
	PointMU_R_Y = 3,
	PointMU_L_X = 14,
	PointMU_L_Y = 3,
	// 左上
	PointLU_RD_X = 8,
	PointLU_RD_Y = 6,
	PointLU_RU_X = 8,
	PointLU_RU_Y = 3,
	PointLU_LU_X = 2,
	PointLU_LU_Y = 3,
	// 左下
	PointLD_RD_X = 8,
	PointLD_RD_Y = 14,
	PointLD_RU_X = 8,
	PointLD_RU_Y = 11,
	PointLD_LU_X = 2,
	PointLD_LU_Y = 11,
	// 中央の下
	PointMD_L_X = 14,
	PointMD_L_Y = 13,
	// 真ん中
	PointMM_RD_X = 26,
	PointMM_RD_Y = 10,
	PointMM_LD_X = 18,
	PointMM_LD_Y = 10,
};

// TD = Teleport Destination、ワープを目的座標
// R = Right , L = Left , M = Middle , U = Up , D = Down
enum Floor10F_TD
{
	// 右下
	TD_RD_X = 38,
	TD_RD_Y = 13,
	// 右上
	TD_RU_X = 38,
	TD_RU_Y = 6,
	// 中間の上
	TD_MU_X = 22,
	TD_MU_Y = 3,
	// 左上
	TD_LU_X = 2,
	TD_LU_Y = 6,
	// 左下
	TD_LD_X = 2,
	TD_LD_Y = 14,
	// 中間の下
	TD_MD_X = 32,
	TD_MD_Y = 13,
	// 真ん中
	TD_MM_X = 26,
	TD_MM_Y = 6,
};

/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/


/*******************************************************************************
* グローバル変数
*******************************************************************************/
PLAYER Player;


/*******************************************************************************
関数名:	void InitPlayer()
引数:	void
戻り値:	void
説明:	プレイヤーの初期化処理
*******************************************************************************/
void InitPlayer(void)
{
	// ステータスの初期化処理
	Player.fx = 22;
	Player.fy = 15;
	Player.CurrentFloor = Enterance;
	Player.MaxFloor = Enterance;
	Player.Event_No = Nothing;
	Player.InfoPage = Symbol_p1;
	Player.GameStart = false;
	Player.TutorialOver = false;
	Player.InPause = false;
	Player.InTeleport = false;
	Player.InStore = false;
	Player.InStair = false;
	Player.InBossBattle = false;
	Player.ExitGame = false;
	Player.Status.HP = 1000;
	Player.Status.MP = 5;
	Player.Status.Level = 1;
	Player.Status.EXP = 0;
	Player.Status.ATK = 10;
	Player.Status.DEF = 10;
	Player.Status.AGI = 2;
	Player.Status.Money = 0;
	Player.Status.GetSkill = false;
	strcpy(&Player.Item.Sword[0], "なし");
	strcpy(&Player.Item.Armor[0], "なし");
	Player.Item.DoorKey = 0;
	Player.Item.FloorMap = false;
	Player.Item.EnemyDictionary = false;
	Player.Item.TeleportWing = false;
	return;
}

/*******************************************************************************
関数名:	void UpdatePlayer(void)
引数:	void
戻り値:	void
説明:	プレイヤーの更新処理
*******************************************************************************/
void UpdatePlayer(void)
{
	int old_x, old_y;	// プレイヤーの古い座標を記録する
	char *Postion = GetMapAdr(Player.fx, Player.fy);	// 現在プレイヤーの位置

	// 一時停止
	if (Player.HitKey == 'p' && Player.InPause == false)
	{
		Player.InPause = true;
		Player.Event_No = PauseEvent;
	}
	// 一時停止解除
	else if (Player.HitKey == 'p' && Player.InPause == true)
	{
		Player.InPause = false;
		Player.Event_No = Nothing;
	}
	// ボス部屋を入る
	else if (Player.HitKey == 'y' && Player.Event_No == EnterBossRoom)
	{
		Player.fx = BossRoomStart_X;
		Player.fy = BossRoomStart_Y;
		Player.CurrentFloor++;
	}


	if (Player.InPause == false && Player.InStore == false)
	{
		// 前回の表示位置の消去
		strncpy(Postion, "  ", 2);
		// Event_NO初期化
		Player.Event_No = Nothing;

		// プレイヤーの位置判定
		old_x = Player.fx;
		old_y = Player.fy;
		switch (Player.HitKey)
		{
		case 'a':
		case 0x4b:	// 左へ移動する
			Player.fx -= 2;
			break;

		case 'd':
		case 0x4d:	// 右へ移動する
			Player.fx += 2;
			break;

		case 'w':
		case 0x48:	// 上へ移動する
			Player.fy--;
			break;

		case 's':
		case 0x50:	// 下へ移動する
			Player.fy++;
			break;

			// 怪物図鑑
		case 'e':
			if (Player.Item.EnemyDictionary == true)
			{
				UseItem(EnemyDictionary);
			}
			break;

			// 転送の翼	
		case 't':
			if (Player.Item.TeleportWing == true)
			{
				if (Player.InStair == false)
				{
					UseItem(TeleportWing);
				}
				else
				{
					Player.Event_No = CantTeleport;
				}
			}
			break;

			// チュートリアル
		case 'h':
			DrawTutorial();
			break;

			// ゲーム説明のページが変わる
		case 'f':
			Player.InfoPage--;
			Player.InfoPage = Player.InfoPage == PageStart ? PageEnd - 1 : Player.InfoPage;
			break;

		case 'g':
			Player.InfoPage++;
			Player.InfoPage = Player.InfoPage == PageEnd ? PageStart + 1 : Player.InfoPage;
			break;

			// ゲーム終了
		case 0x1B:	// Esc
			Player.Event_No = GameExit;
			break;

		default:	// 移動しない
			break;
		}


		// 現在位置更新
		if (Player.InTeleport == false)
		{
			Postion = GetMapAdr(Player.fx, Player.fy);
		}


		// 移動した先はどんな所？
		// 壁
		if (strncmp(Postion, "■", 2) == 0)
		{
			Player.fx = old_x;
			Player.fy = old_y;
		}
		// 上り階段
		else if (strncmp(Postion, "上", 2) == 0)
		{
			Player.CurrentFloor++;
			if (Player.CurrentFloor > Player.MaxFloor && Player.CurrentFloor != TreasureRoom)
			{
				// 転移可能の最大階層をプラス
				Player.MaxFloor++;
			}
			// ボス部屋入るかのイベント
			if (Player.CurrentFloor == BossRoom)
			{
				Player.Event_No = EnterBossRoom;
				Player.fx = old_x;
				Player.fy = old_y;
				Player.CurrentFloor--;
			}
		}
		// 下り階段
		else if (strncmp(Postion, "下", 2) == 0)
		{
			Player.CurrentFloor--;
		}
		// かかった扉
		else if (strncmp(Postion, "Ⅲ", 2) == 0)
		{
			// 鍵が足りない
			if (Player.Item.DoorKey < 1)
			{
				Player.fx = old_x;
				Player.fy = old_y;
				Player.Event_No = KeyNoEnough;
			}
			else
			{
				Player.Item.DoorKey -= 1;
			}
		}
		// 転送ポイント
		else if (strncmp(Postion, "◆", 2) == 0)
		{
			Warp();
		}
		else if (strncmp(Postion, "◇", 2) == 0)
		{
			Warp();
		}
		// HPポーション
		else if (strncmp(Postion, "○", 2) == 0)
		{
			Player.Status.HP += Item_Potion;
			Player.Event_No = HP_Potion;
		}
		// HPハイポーション
		else if (strncmp(Postion, "◎", 2) == 0)
		{
			Player.Status.HP += Item_HiPotion;
			Player.Event_No = HP_HiPotion;
		}
		// ATKアップ
		else if (strncmp(Postion, "Ａ", 2) == 0)
		{
			Player.Status.ATK += Item_ATKUP;
			Player.Event_No = ATKUp;
		}
		// DEFアップ
		else if (strncmp(Postion, "Ｄ", 2) == 0)
		{
			Player.Status.DEF += Item_DEFUP;
			Player.Event_No = DEFUp;
		}
		// AGIアップ
		else if (strncmp(Postion, "Ｓ", 2) == 0)
		{
			Player.Status.AGI += Item_AGIUP;
			Player.Event_No = AGIUp;
		}
		// アイテム：扉の鍵
		else if (strncmp(Postion, "Ｋ", 2) == 0)
		{
			Player.Item.DoorKey += 1;
			Player.Event_No = DoorKey;
		}
		// 商店イベント
		else if (strncmp(Postion, "＄", 2) == 0)
		{
			Player.fx = old_x;
			Player.fy = old_y;
			Player.InStore = true;
		}
		// モンスター：スライム
		else if (strncmp(Postion, "①", 2) == 0)
		{

			if (BattleEvent(Slime) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// モンスター：アーチャー
		else if (strncmp(Postion, "②", 2) == 0)
		{
			if (BattleEvent(Archer) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// モンスター：スライムナイト
		else if (strncmp(Postion, "③", 2) == 0)
		{
			if (BattleEvent(SlimeKnight) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// モンスター：サーベルタイガー
		else if (strncmp(Postion, "④", 2) == 0)
		{
			if (BattleEvent(Tiger) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// モンスター：魔法使い
		else if (strncmp(Postion, "⑤", 2) == 0)
		{
			if (BattleEvent(Magician) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// モンスター：亡霊の鎧
		else if (strncmp(Postion, "⑥", 2) == 0)
		{
			if (BattleEvent(GhostArmor) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// モンスター：ファントム
		else if (strncmp(Postion, "⑦", 2) == 0)
		{
			if (BattleEvent(Phantom) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// モンスター：キングスライム
		else if (strncmp(Postion, "⑧", 2) == 0)
		{
			if (BattleEvent(SlimeKing) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// モンスター：木の精
		else if (strncmp(Postion, "⑨", 2) == 0)
		{
			if (BattleEvent(Dryad) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// モンスター：サイクロプス
		else if (strncmp(Postion, "⑩", 2) == 0)
		{
			if (BattleEvent(Cyclops) == false)
			{
				Player.fx = old_x;
				Player.fy = old_y;
			}
		}
		// 装備：武器
		else if (strncmp(Postion, "剣", 2) == 0)
		{
			if (strcmp(Player.Item.Sword, "なし") == 0)
			{
				strcpy(Player.Item.Sword, Sword01);
				Player.Status.ATK += Equip_Sword01;
			}
			else if (strcmp(Player.Item.Sword, Sword01) == 0)
			{
				strcpy(Player.Item.Sword, Sword02);
				Player.Status.ATK += Equip_Sword02;
			}
			else if (strcmp(Player.Item.Sword, Sword02) == 0)
			{
				strcpy(Player.Item.Sword, Sword03);
				Player.Status.ATK += Equip_Sword03;
			}
			Player.Event_No = SwordEvent;

		}
		// 装備：防具
		else if (strncmp(Postion, "鎧", 2) == 0)
		{
			if (strcmp(Player.Item.Armor, "なし") == 0)
			{
				strcpy(Player.Item.Armor, Armor01);
				Player.Status.DEF += Equip_Armor01;
			}
			else if (strcmp(Player.Item.Armor, Armor01) == 0)
			{
				strcpy(Player.Item.Armor, Armor02);
				Player.Status.DEF += Equip_Armor02;

			}
			else if (strcmp(Player.Item.Armor, Armor02) == 0)
			{
				strcpy(Player.Item.Armor, Armor03);
				Player.Status.DEF += Equip_Armor03;

			}
			Player.Event_No = ArmorEvent;
		}
		// アイテム：ダンジョンマップ
		else if (strncmp(Postion, "Ｍ", 2) == 0)
		{
			Player.Item.FloorMap = true;
			Player.Event_No = GetFloorMap;
		}
		// アイテム：怪物図鑑
		else if (strncmp(Postion, "図", 2) == 0)
		{
			Player.Item.EnemyDictionary = true;
			Player.Event_No = GetDictionary;
		}
		// アイテム：転送の翼
		else if (strncmp(Postion, "翼", 2) == 0)
		{
			Player.Item.TeleportWing = true;
			Player.Event_No = GetTeleport;
		}
		// 隠しエリアのスイッチ
		else if (strncmp(Postion, "↑", 2) == 0)
		{
			strncpy(GetMapAdr(Player.fx, Player.fy), "←", 2);
			Player.Item.TreasureRoomKey = true;
			Player.Event_No = TreasureRoom;
			Player.fx = old_x;
			Player.fy = old_y;
		}
		// 隠しエリア
		else if (strncmp(Postion, "隠", 2) == 0)
		{
			Player.CurrentFloor = Floor_Treasure;
			// プレイヤー初めての位置
			Player.fx = TreasureRoom_X;
			Player.fy = TreasureRoom_Y;
		}
		// 隠しエリア-金
		else if (strncmp(Postion, "金", 2) == 0)
		{
			Player.Event_No = MoneyEvent;
			Player.Status.Money += Item_Money;
		}
		// 隠しエリア-経験値
		else if (strncmp(Postion, "経", 2) == 0)
		{
			Player.Event_No = EXPEvent;
			Player.Status.EXP += Item_EXP;
		}
		// 隠しエリアの出口
		else if (strncmp(Postion, "出", 2) == 0)
		{
			Player.CurrentFloor = Enterance;
			// 隠しエリアから出た位置
			Player.fx = TreasureExit_X;
			Player.fy = TreasureExit_Y;
		}
		// ボスイベント
		else if (Player.CurrentFloor == BossRoom && Player.fy == 6 && Player.InBossBattle == false)
		{
			Player.Event_No = BossEvent;
		}
		// ボスバトル
		else if (Player.InBossBattle == true)
		{
			BattleEvent(Boss);
		}
		// 以上の場所じゃない、それに通れる道じゃない
		else if (
			strncmp(Postion, "  ", 2) != 0
			|| Player.fx < 0 || Player.fx > 48 || Player.fy < 0 || Player.fy > 15)
		{
			// NGなら移動前の場所に戻す
			Player.fx = old_x;
			Player.fy = old_y;
		}
	}

	return;
}

/*******************************************************************************
関数名:	void DrawPlayer(void)
引数:	void
戻り値:	void
説明:	プレイヤーの描画処理
*******************************************************************************/
void DrawPlayer(void)
{
	// 以BG的(0,0)為起點
	//strncpy(GetBGAdr(Player.X + 3, Player.Y + 1), "Ｐ", 2);

	// 以Map的(0,0)為起點
	strncpy(GetMapAdr(Player.fx, Player.fy), "Ｐ", 2);

	return;
}

/*******************************************************************************
関数名:	PLAYER *GetPlayerAdr(void)
引数:	void
戻り値:	PLAYER *
説明:	プレイヤー構造体のポインタをもらう
*******************************************************************************/
PLAYER *GetPlayerAdr(void)
{
	return &Player;
}

/*******************************************************************************
関数名:	void Warp(void)
引数:	void
戻り値:	void
説明:	10Fと隠しエリアの転移ポイントを処理する関数
*******************************************************************************/
void Warp(void)
{
	if (Player.CurrentFloor == Floor_10F)
	{
		if (Player.fx >= 24)
		{
			if (Player.fy >= 8)
			{
				if (Player.fx == PointRD_RD_X && Player.fy == PointRD_RD_Y)
				{
					Player.fx = TD_LU_X;
					Player.fy = TD_LU_Y;
				}
				else if (Player.fx == PointRD_RU_X && Player.fy == PointRD_RU_Y)
				{
					Player.fx = TD_MM_X;
					Player.fy = TD_MM_Y;
				}
				else if (Player.fx == PointRD_LU_X && Player.fy == PointRD_LU_Y)
				{
					Player.fx = TD_MU_X;
					Player.fy = TD_MU_Y;
				}
				else if (Player.fx == PointMM_RD_X && Player.fy == PointMM_RD_Y)
				{
					Player.fx = TD_RD_X;
					Player.fy = TD_RD_Y;
				}
			}
			else
			{
				if (Player.fx == PointRU_RD_X && Player.fy == PointRU_RD_Y)
				{
					Player.fx = TD_RD_X;
					Player.fy = TD_RD_Y;
				}
				else if (Player.fx == PointRU_RU_X && Player.fy == PointRU_RU_Y)
				{
					Player.fx = TD_MM_X;
					Player.fy = TD_MM_Y;
					strncpy(GetMapAdr(PointRD_RU_X, PointRD_RU_Y), "◇", 2);
				}
				else if (Player.fx == PointRU_LU_X && Player.fy == PointRU_LU_Y)
				{
					Player.fx = TD_LU_X;
					Player.fy = TD_LU_Y;
				}
				else if (Player.fx == PointMU_R_X && Player.fy == PointMU_R_Y)
				{
					Player.fx = TD_LD_X;
					Player.fy = TD_LD_Y;
				}
			}
		}
		else
		{
			if (Player.fy >= 8)
			{
				if (Player.fx == PointLD_RD_X && Player.fy == PointLD_RD_Y)
				{
					Player.fx = TD_RU_X;
					Player.fy = TD_RU_Y;
				}
				else if (Player.fx == PointLD_RU_X && Player.fy == PointLD_RU_Y)
				{
					Player.fx = TD_MU_X;
					Player.fy = TD_MU_Y;
				}
				else if (Player.fx == PointLD_LU_X && Player.fy == PointLD_LU_Y)
				{
					Player.fx = TD_LU_X;
					Player.fy = TD_LU_Y;
				}
				else if (Player.fx == PointMD_L_X && Player.fy == PointMD_L_Y)
				{
					Player.fx = TD_MM_X;
					Player.fy = TD_MM_Y;
				}
				else if (Player.fx == PointMM_LD_X && Player.fy == PointMM_LD_Y)
				{
					Player.fx = TD_MD_X;
					Player.fy = TD_MD_Y;
				}
			}
			else
			{
				if (Player.fx == PointMU_L_X && Player.fy == PointMU_L_Y)
				{
					Player.fx = TD_LU_X;
					Player.fy = TD_LU_Y;
				}
				else if (Player.fx == PointLU_RD_X && Player.fy == PointLU_RD_Y)
				{
					Player.fx = TD_RD_X;
					Player.fy = TD_RD_Y;
				}
				else if (Player.fx == PointLU_RU_X && Player.fy == PointLU_RU_Y)
				{
					Player.fx = TD_RU_X;
					Player.fy = TD_RU_Y;
				}
				else if (Player.fx == PointLU_LU_X && Player.fy == PointLU_LU_Y)
				{
					Player.fx = TD_LD_X;
					Player.fy = TD_LD_Y;
				}
			}
		}
	}
	else if(Player.CurrentFloor == Floor_Treasure)
	{
		if (Player.fx == TreasureRoomTP_X && Player.fy == TreasureRoomTP_Y)
		{
			Player.fx = 16;
			Player.fy = 13;
		}
	}

	return;
}