/*******************************************************************************
* タイトル:		アイテムプログラム
* プログラム名:	Item.cpp
* 作成者:		GP11B341 35 頼凱興
* 作成日:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "Item.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
// 怪物図鑑
#define Page_Height (23)		// 図鑑の高さ
#define Page_Width (35)			// 図鑑の幅
#define PageStart_X (3)			// 図鑑描画座標
#define PageStart_Y (1)

// 転送の翼
#define Message_Height (7)		// メッセージ描画配列
#define Message_Width (75)	
#define MessageStart_X (3)		// メッセージ描画座標
#define MessageStart_Y (10)
// 各階層ワープした後の始点
enum FloorStartPostion
{
	Enterance_X = 22,
	Exterance_Y = 15,
	Floor1F_X = 22,
	Floor1F_Y = 3,
	Floor2F_X = 44,
	Floor2F_Y = 9,
	Floor3F_X = 10,
	Floor3F_Y = 3,
	Floor4F_X = 40,
	Floor4F_Y = 12,
	Floor5F_X = 22,
	Floor5F_Y = 13,
	Floor6F_X = 4,
	Floor6F_Y = 3,
	Floor7F_X = 42,
	Floor7F_Y = 3,
	Floor8F_X = 4,
	Floor8F_Y = 8,
	Floor9F_X = 40,
	Floor9F_Y = 8,
	Floor10F_X = 38,
	Floor10F_Y = 14,
};

/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
// 怪物図鑑
void Ditcionary(void);
void UpdateDictionary(void);
void DrawDictionary(void);
// 転送の翼
void TeleportItem(void);
void UpdateTeleport(void);
void DrawTeleport(void);

/*******************************************************************************
* グローバル変数
*******************************************************************************/
int Enemy_No = 0;		// 図鑑表示するエネミーの番号
int Destination = 0;	// 転送の目的地


/*******************************************************************************
関数名:	void UseItem(int Item_No)
引数:	int Item_No
戻り値:	void
説明:	アイテムを使う
*******************************************************************************/
void UseItem(int Item_No)
{
	int i = 0;
	int Length = 0;
	Enemy_No = 0;


	switch (Item_No)
	{
	case EnemyDictionary:
		Ditcionary();
		break;
	case TeleportWing:
		TeleportItem();
		break;
	default:
		break;
	}
	return;
}

/*******************************************************************************
関数名:	void Ditcionary(void)
引数:	void
戻り値:	void
説明:	怪物図鑑を使う関数
*******************************************************************************/
void Ditcionary(void)
{
	while (true)
	{
		if (_kbhit())
		{
			// 図鑑を表示するエネミー番号の更新
			UpdateDictionary();
			// 図鑑から離れる
			if (Enemy_No == ExitDictionary)
			{
				break;
			}
			// 図鑑の描画
			DrawDictionary();
		}
		// 関数に初めて入った
		else if (Enemy_No == 0)
		{
			Enemy_No = Slime;
			DrawDictionary();
		}
	}
	return;
}

/*******************************************************************************
関数名:	void UpdateDictionary(void)
引数:	void
戻り値:	void
説明:	図鑑を表示するエネミー番号の更新
*******************************************************************************/
void UpdateDictionary(void)
{
	int Key = 0;

	Key = _getch();
	if ((Key == 0) || (Key == 224))
	{
		Key = _getch();
	}

	switch (Key)
	{
	case 'a':
	case 0x4b:	// 左ページへ移動する
		Enemy_No -= 4;
		if (Enemy_No < Slime)
		{
			Enemy_No = Slime;
		}
		break;
	case 'd':
	case 0x4d:	// 右ページへ移動する
		if (Enemy_No > Cyclops)
		{
			Enemy_No = Dryad;
		}
		break;
	case 'q':	// 図鑑から離れる
		Enemy_No = ExitDictionary;
		break;
	default:	// 何もしない
		Enemy_No -= 2;
		if (Enemy_No < Slime)
		{
			Enemy_No = Slime;
		}
		break;
	}
	return;
}

/*******************************************************************************
関数名:	void DrawDictionary(void)
引数:	void
戻り値:	void
説明:	図鑑の描画処理
*******************************************************************************/
void DrawDictionary(void)
{
	int i = 0;		// ループ計算用
	int HPtmp = 0;	// エネミーHPを記録する
	int Length = 0;	// メッセージの長さ
	int Column = 0;	// メッセージの行数
	int X = 0;		// 描画する時の補正
	int Y = 0;
	int Damage = 0;	// 予想ダメージ
	int Turn = 0;	// 予想ターン
	int Page = 0;	// 一回2ページを表示する
	int PageDistance = 0;	// 左ページと右ページ間の距離(描画位置を修正するため)
	static bool RightPage = false;	// 現在描画するのは左か？右か？
	ENEMY Enemy;
	PLAYER *Player = GetPlayerAdr();
	// 背景配列
	char DictionaryBG[Console_Height][Console_Width] = {
		"   ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿     ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿\n",
		" /|                                  `γ´                                 |ヽ\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n", //
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   │                                    ||\n",
		" ||                                   ∧                            Exit(Q)||\n",
		" ヽ―――――――――――――――――´ `―――――――――――――――――´",
	};
	// エネミー画像とステータスの配列
	char EnemyData[Page_Height][Page_Width] = {};


	for (Page = 0; Page < 2; Page++)
	{
		// 画像とステータス設定
		switch (Enemy_No)
		{
		case Slime:
			strcpy(&EnemyData[0][0], "         ｒ⌒,        ");
			strcpy(&EnemyData[1][0], "　    　 ﾉ:::丶       ");
			strcpy(&EnemyData[2][0], "　　,ー＿:::::＿ー､   ");
			strcpy(&EnemyData[3][0], "　／/) (・) (・):::丶 ");
			strcpy(&EnemyData[4][0], "`｜Ｕ (~ヽ＿_／~):::｜");
			strcpy(&EnemyData[5][0], "　＼ｏ ＼＿＿_／:::／ ");
			strcpy(&EnemyData[6][0], "　　`ーーーーーー-′  ");
			strcpy(&Enemy.name[0], "スライム");
			strcpy(&Enemy.Ability[0], "なし");
			Enemy.HP = SlimeHP;
			Enemy.ATK = SlimeATK;
			Enemy.DEF = SlimeDEF;
			Enemy.AGI = SlimeAGI;
			Enemy.EXP = SlimeEXP;
			Enemy.Money = SlimeMoney;
			strcpy(&EnemyData[21][0], "特殊能力：なし");
			break;
		case Archer:
			strcpy(&EnemyData[0][0], "　　 ／⌒＼         ");
			strcpy(&EnemyData[1][0], "　　/ ＿＿_)　／(   ");
			strcpy(&EnemyData[2][0], "　 ( (´∀`)／　|)  ");
			strcpy(&EnemyData[3][0], "　　) _]つ＜＝＝０⇒");
			strcpy(&EnemyData[4][0], "　 /　 ー _>＼　|)  ");
			strcpy(&EnemyData[5][0], "　(_＞ー＜_)　＼(   ");
			strcpy(&Enemy.name[0], "アーチャー");
			strcpy(&Enemy.Ability[0], "なし");
			Enemy.HP = ArcherHP;
			Enemy.ATK = ArcherATK;
			Enemy.DEF = ArcherDEF;
			Enemy.AGI = ArcherAGI;
			Enemy.EXP = ArcherEXP;
			Enemy.Money = ArcherMoney;
			break;
		case SlimeKnight:
			strcpy(&EnemyData[0][0], "　   　　彡ﾐl\"'ヽ　　　/i");
			strcpy(&EnemyData[1][0], "　   　　{[i]二三}　  // ");
			strcpy(&EnemyData[2][0], "　   　「＿ ~l　j,j、//  ");
			strcpy(&EnemyData[3][0], "　   　 ヽ_,ノ_　}  O`   ");
			strcpy(&EnemyData[4][0], "　　    ,'　U　ヽ>ヽ     ");
			strcpy(&EnemyData[5][0], "（（（ {　　・∀・}      ");
			strcpy(&EnemyData[6][0], "　　    `ー----ｰ'’      ");
			strcpy(&Enemy.name[0], "スライムナイト");
			strcpy(&Enemy.Ability[0], "なし");
			Enemy.HP = SlimeKnightHP;
			Enemy.ATK = SlimeKnightATK;
			Enemy.DEF = SlimeKnightDEF;
			Enemy.AGI = SlimeKnightAGI;
			Enemy.EXP = SlimeKnightEXP;
			Enemy.Money = SlimeKnightMoney;
			break;
		case Tiger:
			strcpy(&EnemyData[0][0], "   　 　 　 ｨﾐ彡ミ､_, --､_     ");
			strcpy(&EnemyData[1][0], "　　　　 　 　 　 ﾞｰ-‐‐､_ ＼   ");
			strcpy(&EnemyData[2][0], "　　　　　　 ,, ､　 , --､__,)　）");
			strcpy(&EnemyData[3][0], " 　　　　, -'　l ｀ｰ'-f　 ヽ _/  ");
			strcpy(&EnemyData[4][0], "  　 　 /　　 _ _　　 l　　 f    ");
			strcpy(&EnemyData[5][0], "　　　/ , -‐'　 ﾞｰ-ｧ.!｀l　l    ");
			strcpy(&EnemyData[6][0], "　　 /　r(^ｰ・・''^)ｨ ∧i　l     ");
			strcpy(&EnemyData[7][0], " 　 /　 t_|｀!::i´|_t\" ヽ l､    ");
			strcpy(&EnemyData[8][0], "　 i 　 / |/ｷ::ヽ|  ヽ   l-､ヽ   ");
			strcpy(&EnemyData[9][0], ", -'　 ｲ 　l､ｰ',l    l   ﾄ､ ¨   ");
			strcpy(&EnemyData[10][0], "ｰｔ^t^ﾞゝ　　￣　　  <_ｨ_Y_lゝ   ");
			strcpy(&Enemy.name[0], "サーベルタイガー");
			strcpy(&Enemy.Ability[0], "二回攻撃");
			Enemy.HP = TigerHP;
			Enemy.ATK = TigerATK;
			Enemy.DEF = TigerDEF;
			Enemy.AGI = TigerAGI;
			Enemy.EXP = TigerEXP;
			Enemy.Money = TigerMoney;
			break;
		case Magician:
			strcpy(&EnemyData[0][0], "　　　　--ミ          ");
			strcpy(&EnemyData[1][0], "　 .: :::::::｀:..、  ");
			strcpy(&EnemyData[2][0], "  /::/:::::::::   ヽ  ");
			strcpy(&EnemyData[3][0], " ':;ｲ:::::::::_:_::}  ");
			strcpy(&EnemyData[4][0], " : /　､:::::  くoﾆ{   ");
			strcpy(&EnemyData[5][0], " ⅱ　 ｢:::::::::V人   ");
			strcpy(&EnemyData[6][0], " 从　 l:::::＼  r‐ﾍ〕");
			strcpy(&EnemyData[7][0], "廴ﾉ  /ﾊｰ::::::} ヽﾉ:! ");
			strcpy(&EnemyData[8][0], "　　ｲ :ﾍ:::ィ´l:ｌ:j ");
			strcpy(&EnemyData[9][0], " __ﾉ|::_  乂_ノ:_:ﾉ(  ");
			strcpy(&EnemyData[10][0], "　ー=ﾆ :_:_:_:_:_:_彡 ");
			strcpy(&Enemy.name[0], "魔法使い");
			strcpy(&Enemy.Ability[0], "防御力無視");
			Enemy.HP = MagicianHP;
			Enemy.ATK = MagicianATK;
			Enemy.DEF = MagicianDEF;
			Enemy.AGI = MagicianAGI;
			Enemy.EXP = MagicianEXP;
			Enemy.Money = MagicianMoney;
			break;
		case GhostArmor:
			strcpy(&EnemyData[0][0], "   　　､ｨヽ(ヽ           ");
			strcpy(&EnemyData[1][0], "   　　､_ゞヽ|           ");
			strcpy(&EnemyData[2][0], "   　　νγγ￣ヽ_       ");
			strcpy(&EnemyData[3][0], "   　　`´ ﾉ""゛＿ゝ       ");
			strcpy(&EnemyData[4][0], "   γ⌒ヽノ　ＧｲIIII)／/ ");
			strcpy(&EnemyData[5][0], "   /　\"〟ヽノヾ::::／／ヽ");
			strcpy(&EnemyData[6][0], "   ＼＿＿ﾉ`ヽ_ニﾆ／∠ゝ::");
			strcpy(&EnemyData[7][0], "   `/＿/:.〝 .:／／|L_L|:");
			strcpy(&EnemyData[8][0], "   `＼￣＼＿､∠∠､ノ((uE}");
			strcpy(&EnemyData[9][0], "   　 ＼√/Lミ}￣T｜:::::");
			strcpy(&EnemyData[10][0], "   　　 `ﾆ∠／―´)ヾ:::ﾉ");
			strcpy(&EnemyData[11][0], "   　　/乙ヽ〝　γヽ`￣  ");
			strcpy(&EnemyData[12][0], "   　 /　`-|`￣^ヽﾉ￣ヽ  ");
			strcpy(&EnemyData[13][0], "   　/　\"〟|　　 | 〝\"|  ");
			strcpy(&EnemyData[14][0], "   ／⌒ヽ＿|　　 | γ￣ヽ");
			strcpy(&EnemyData[15][0], "   ｀――´　　　 ｀￣￣ ");
			strcpy(&Enemy.name[0], "亡霊の鎧");
			strcpy(&Enemy.Ability[0], "なし");
			Enemy.HP = GhostArmorHP;
			Enemy.ATK = GhostArmorATK;
			Enemy.DEF = GhostArmorDEF;
			Enemy.AGI = GhostArmorAGI;
			Enemy.EXP = GhostArmorEXP;
			Enemy.Money = GhostArmorMoney;
			break;
		case Phantom:
			strcpy(&EnemyData[0][0], "　　　　 , -- 、          ");
			strcpy(&EnemyData[1][0], "　　　 ｲ::;;;::ヽ         ");
			strcpy(&EnemyData[2][0], "　　　ノ::＋＋::ヽ        ");
			strcpy(&EnemyData[3][0], "　 ／:::;;;;;;:::l        ");
			strcpy(&EnemyData[4][0], "　 |::;;:::;;;::::l       ");
			strcpy(&EnemyData[5][0], "  /:;:,､:::;;:::r-､:;､    ");
			strcpy(&EnemyData[6][0], " /:;:/弋::::::::|　 ゝ:;ヽ");
			strcpy(&EnemyData[7][0], "l:;:/　　ヽ::::::ヽ ｀ｰﾚ' ");
			strcpy(&EnemyData[8][0], "|:;ゝ　　　ヽ:::::::l     ");
			strcpy(&EnemyData[9][0], " ^　　　　　 ヽ-:::::ヽ   ");
			strcpy(&EnemyData[10][0], "　 　　　　　　　 ~l::|   ");
			strcpy(&EnemyData[11][0], " 　 　　　　　　　　ﾉノ   ");
			strcpy(&EnemyData[12][0], " 　　　　　　　　 ∠'     ");
			strcpy(&Enemy.name[0], "ファントム");
			strcpy(&Enemy.Ability[0], "回避率上昇");
			Enemy.HP = PhantomHP;
			Enemy.ATK = PhantomATK;
			Enemy.DEF = PhantomDEF;
			Enemy.AGI = PhantomAGI;
			Enemy.EXP = PhantomEXP;
			Enemy.Money = PhantomMoney;
			break;
		case SlimeKing:
			strcpy(&EnemyData[0][0], "　　　　　/､          ");
			strcpy(&EnemyData[1][0], "　　　　　||          ");
			strcpy(&EnemyData[2][0], "　　　 ／ニニ＼       ");
			strcpy(&EnemyData[3][0], "　　 ＿――――＿     ");
			strcpy(&EnemyData[4][0], "　 ＼∨＼／＼／∨／   ");
			strcpy(&EnemyData[5][0], "　　＼＿＿＿＿＿／    ");
			strcpy(&EnemyData[6][0], "　　／￣ﾆ￣￣ﾆ￣＼    ");
			strcpy(&EnemyData[7][0], ".／　　(･)　(･)　　＼ ");
			strcpy(&EnemyData[8][0], "|　　ヽ､_　　_,ｒ　　|");
			strcpy(&EnemyData[9][0], "(　　ノ -ニニ- ﾍ　　 )");
			strcpy(&EnemyData[10][0], "|　　　　　　　　　　|");
			strcpy(&EnemyData[11][0], ".＼　　　　　　　　／ ");
			strcpy(&EnemyData[12][0], "　　＼＿＿＿＿＿／    ");
			strcpy(&Enemy.name[0], "キングスライム");
			strcpy(&Enemy.Ability[0], "なし");
			Enemy.HP = SlimeKingHP;
			Enemy.ATK = SlimeKingATK;
			Enemy.DEF = SlimeKingDEF;
			Enemy.AGI = SlimeKingAGI;
			Enemy.EXP = SlimeKingEXP;
			Enemy.Money = SlimeKingMoney;
			break;
		case Dryad:
			strcpy(&EnemyData[0][0], "ヽ　　　　　　,r ^= ｧ=-､ ,       ");
			strcpy(&EnemyData[1][0], " ||　　　 /` '　ヽr‐､,_.ヽ､,    ");
			strcpy(&EnemyData[2][0], " ヾ ､　__j　  __　 　　　 ﾚ'1    ");
			strcpy(&EnemyData[3][0], "　 ＼~　　 　 |::＼.._　　 r1    ");
			strcpy(&EnemyData[4][0], "　　　`ｰ､　　 |:::　::|　r'\":/ ､ ");
			strcpy(&EnemyData[5][0], "　　　　　`i 　ヽ::.../　ヽ;j ,j!");
			strcpy(&EnemyData[6][0], "　　　　　 j　 　 ￣　　   `ｰ'ｿ  ");
			strcpy(&EnemyData[7][0], "　　　　　/　　,r､r――v'´|-'   ");
			strcpy(&EnemyData[8][0], "　　　　/　　 ヽ　_r-―v(        ");
			strcpy(&EnemyData[9][0], "　r―‐'　　　 `' 　 　 !_       ");
			strcpy(&EnemyData[10][0], "∠r､_.　 /　　　　 　 　  `ｰ､    ");
			strcpy(&EnemyData[11][0], "　　　＞'　　　,､　､ 　,i―'￣`  ");
			strcpy(&EnemyData[12][0], "  _- ''  ＿ ノ  ヽヽ  ヽ､        ");
			strcpy(&EnemyData[13][0], "（　<￣￣　　　 　ヽj`ー､ヽ      ");
			strcpy(&EnemyData[14][0], " ヽ !　　　　　　　　　　ヽ!     ");
			strcpy(&EnemyData[15][0], "　 `'                            ");
			strcpy(&Enemy.name[0], "木の精");
			strcpy(&Enemy.Ability[0], "HP回復");
			Enemy.HP = DryadHP;
			Enemy.ATK = DryadATK;
			Enemy.DEF = DryadDEF;
			Enemy.AGI = DryadAGI;
			Enemy.EXP = DryadEXP;
			Enemy.Money = DryadMoney;
			break;
		case Cyclops:
			strcpy(&EnemyData[0][0], "　　　　　  A　　　　,(_c三)、");
			strcpy(&EnemyData[1][0], "　　　　∧/◎ヽ∧ _,-t;li /|| ");
			strcpy(&EnemyData[2][0], "　 _,.--ゞェｪｪェﾂ'\"  | // i/  ");
			strcpy(&EnemyData[3][0], " （∴∵ l `ー‐'\" ,lﾞ |l `;/  ");
			strcpy(&EnemyData[4][0], "　/ヾ：∴ヽ`、__,.ｲ`ｖ |l lﾞ  ");
			strcpy(&EnemyData[5][0], "　ヽ ヾ∵∴ヽ、　/　(r'⊥l_l  ");
			strcpy(&EnemyData[6][0], "　　〉 lﾆニ●ニﾆl  |`(＿,. |  ");
			strcpy(&EnemyData[7][0], ",.ヘ,< ∴-ニ-∵ヽ  `J(__,./   ");
			strcpy(&EnemyData[8][0], "( ヲ`^'WwwwwwW'^〈　 >ri‐\"   ");
			strcpy(&EnemyData[9][0], "(~`ｰ--､,）　ヽ,　　）`'\"      ");
			strcpy(&EnemyData[10][0], "(~'ヾ.. ヽ　ｒ^　 ノ          ");
			strcpy(&EnemyData[11][0], "`-'ー- ､_ﾉ　 ヽ '\"ミ          ");
			strcpy(&EnemyData[12][0], "　　　　　　  `ヾ`            ");
			strcpy(&Enemy.name[0], "サイクロプス");
			strcpy(&Enemy.Ability[0], "なし");
			Enemy.HP = CyclopsHP;
			Enemy.ATK = CyclopsATK;
			Enemy.DEF = CyclopsDEF;
			Enemy.AGI = CyclopsAGI;
			Enemy.EXP = CyclopsEXP;
			Enemy.Money = CyclopsMoney;
		default:
			break;
		}
		// 予想総ダメージ計算
		HPtmp = Enemy.HP;
		Turn = 0;
		while (true)
		{
			Damage = Player->Status.ATK - Enemy.DEF;
			// プレイヤーの攻撃力はエネミーの防御力より低い
			if (Damage <= 0)
			{
				// 敵を倒せない
				break;
			}
			Enemy.HP -= Damage;
			// エネミー死亡
			if (Enemy.HP <= 0)
			{
				// エネミーのHPを元に戻る
				Enemy.HP = HPtmp;
				break;
			}
			// 次のターン
			else
			{
				if (Enemy_No == Dryad)
				{
					Enemy.HP += 5;
				}
				Turn++;
			}
		}
		// エネミーに与えるダメージは0以下
		if (Damage <= 0)
		{
			// 予想総ダメージ = 99999 = 敵を倒せない
			Damage = 99999;
		}
		else
		{
			if (Enemy_No == Tiger)
			{
				Damage = (Enemy.ATK - Player->Status.DEF) * Turn * 2;
			}
			else if (Enemy_No == Magician)
			{
				Damage = Enemy.ATK * Turn;
			}
			else
			{
				Damage = (Enemy.ATK - Player->Status.DEF) * Turn;
			}
			// プレイヤーに与えるダメージは0以下
			if (Damage <= 0)
			{
				// ダメージなし
				Damage = 0;
			}
		}
		// ステータス描画
		sprintf(&EnemyData[17][0], "名前：%s", &Enemy.name[0]);
		sprintf(&EnemyData[18][0], "HP：%d   予想総ダメージ：%d", Enemy.HP, Damage);
		sprintf(&EnemyData[19][0], "ATK：%d   DEF：%d   AGI：%d", Enemy.ATK, Enemy.DEF, Enemy.AGI);
		sprintf(&EnemyData[20][0], "経験値：%d    ゴールド：$%d", Enemy.EXP, Enemy.Money);
		sprintf(&EnemyData[21][0], "特殊能力：%s", &Enemy.Ability[0]);
		sprintf(&EnemyData[22][0], "- %d / 10 -", Enemy_No);

		// 行数計算
		for (Column = 0; EnemyData[Column][0] != NULL; Column++)
		{
			;
		}
		// Y = 0行～15行の真ん中
		Y = (Console_Height - 9 - Column) / 2;
		// 現在描画しているのは右ページなら
		if (RightPage == true)
		{
			// 描画位置を修正
			PageDistance = Page_Width + 2;
			RightPage = false;
		}
		else
		{
			PageDistance = 0;
			RightPage = true;
		}
		// 背景に図鑑を描画
		for (i = 0; i < Page_Height; i++)
		{
			if (EnemyData[i][0] == NULL)
			{
				Y = 0;
				continue;
			}
			else
			{
				Length = strlen(&EnemyData[i][0]);
				X = (Page_Width - Length) / 2;
				strncpy(&DictionaryBG[PageStart_Y + i + Y][PageStart_X + PageDistance + X], &EnemyData[i][0], Length);
				strcpy(&EnemyData[i][0], "");
			}
		}
		// 次のエネミー番号
		Enemy_No++;
	}

	// 画面クリア
	system("cls");

	// 背景を描画
	for (i = 0; i < Console_Height; i++)
	{
		printf("%s", &DictionaryBG[i][0]);
	}

	return;
}

/*******************************************************************************
関数名:	void TeleportItem(void)
引数:	void
戻り値:	void
説明:	転送の翼を使う関数
*******************************************************************************/
void TeleportItem(void)
{
	// 初期化する、入口から表示
	Destination = Enterance;


	DrawTeleport();
	while (true)
	{
		if (_kbhit())
		{
			UpdateTeleport();
			if (Destination == ExitTeleport)
			{
				break;
			}
			DrawTeleport();
		}
	}
	return;
}

/*******************************************************************************
関数名:	void UpdateTeleport(void)
引数:	void
戻り値:	void
説明:	転送の翼の更新処理
*******************************************************************************/
void UpdateTeleport(void)
{
	int Key = 0;
	PLAYER *Player = GetPlayerAdr();


	Key = _getch();
	if ((Key == 0) || (Key == 224))
	{
		Key = _getch();
	}

	switch (Key)
	{
	case 'w':
	case 0x48:	// 上へ移動する
		Destination++;
		if (Destination > Player->MaxFloor)
		{
			Destination = Enterance;
		}
		break;

	case 's':
	case 0x50:	// 下へ移動する
		Destination--;
		if (Destination < Enterance)
		{
			Destination = Player->MaxFloor;
		}
		break;

	case 'q':	// 離れる
		Destination = ExitTeleport;
		break;

	case 0x0D:	// Enter
		Player->CurrentFloor = Destination;
		Player->OldFloor = Destination;
		// 目的地
		switch (Destination)
		{
		case Enterance:
			Player->fx = Enterance_X;
			Player->fy = Exterance_Y;
			break;
		case Floor_1F:
			Player->fx = Floor1F_X;
			Player->fy = Floor1F_Y;
			break;
		case Floor_2F:
			Player->fx = Floor2F_X;
			Player->fy = Floor2F_Y;
			break;
		case Floor_3F:
			Player->fx = Floor3F_X;
			Player->fy = Floor3F_Y;
			break;
		case Floor_4F:
			Player->fx = Floor4F_X;
			Player->fy = Floor4F_Y;
			break;
		case Floor_5F:
			Player->fx = Floor5F_X;
			Player->fy = Floor5F_Y;
			break;
		case Floor_6F:
			Player->fx = Floor6F_X;
			Player->fy = Floor6F_Y;
			break;
		case Floor_7F:
			Player->fx = Floor7F_X;
			Player->fy = Floor7F_Y;
			break;
		case Floor_8F:
			Player->fx = Floor8F_X;
			Player->fy = Floor8F_Y;
			break;
		case Floor_9F:
			Player->fx = Floor9F_X;
			Player->fy = Floor9F_Y;
			break;
		case Floor_10F:
			Player->fx = Floor10F_X;
			Player->fy = Floor10F_Y;
			break;
		default:
			break;
		}
		Destination = ExitTeleport;
		Player->InTeleport = true;
		break;
	default:	// 何もしない
		break;
	}

	return;
}

/*******************************************************************************
関数名:	void DrawTeleport(void)
引数:	void
戻り値:	void
説明:	転送の翼の描画処理
*******************************************************************************/
void DrawTeleport(void)
{
	int i = 0;
	int Length = 0;
	int X = 0;
	int Y = 0;
	int Column = 0;
	PLAYER *Player = GetPlayerAdr();
	char BackGround[Console_Height][Console_Width] = {
		"  ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣",
	};

	// メッセージ描画用配列
	char Message[Message_Height][Message_Width] = {
		"--------------------------------------------------------------------------",
		"                                                                          ",
		"                                                                          ",
		"                                                                          ",
		"                                                                          ",
		"                                                       Exit(Q)            ",
		"--------------------------------------------------------------------------",
	};

	strcpy(&Message[2][0], "目的の階層を選んでください");
	if (Destination == Enterance)
	{
		sprintf(&Message[4][0], "- 入口 -");
	}
	else
	{
		sprintf(&Message[4][0], "- 第 %d 層 -", Destination);
	}

	// メッセージ描画
	for (i = 0; i < Message_Height && Message[i][0] != NULL; i++)
	{
		// X = Message左から右までの真ん中
		Length = strlen(&Message[i][0]);
		X = (Message_Width - Length) / 2;
		strncpy(&BackGround[MessageStart_Y + i][MessageStart_X + X], Message[i], Length);
	}

	// 背景を表示
	for (i = 0; i < Console_Height; i++)
	{
		printf("%s", &BackGround[i][0]);
	}

	return;
}