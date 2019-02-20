/*******************************************************************************
* タイトル:		バトルプログラム
* プログラム名:	Battle.cpp
* 作成者:		GP11B341 35 頼凱興
* 作成日:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "Battle.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/

#define EnemyStart_X (3)		// エネミー描画座標
#define EnemyStart_Y (1)
#define PlayerStart_X (53)		// プレイヤー描画座標
#define PlayerStart_Y (1)
#define EnemyStatus_X (3)		// エネミーステータス描画座標
#define EnemyStatus_Y (18)
#define PlayerStatus_X (53)		// プレイヤーステータス描画座標
#define PlayerStatus_Y (18)
#define EstimateDamage_X (30)	// 予想ダメージ描画座標
#define EstimateDamage_Y (18)
#define EffectStart_X (10)		// ダメージエフェクト描画座標
#define EffectStart_Y (7)
#define MessageStart_X (3)		// メッセージ描画座標
#define MessageStart_Y (10)

#define Array_Height (16)		// プレイヤー、エネミー描画配列
#define Array_Width (40)		
#define StatusArr_Height (6)	// プレイヤー、エネミーのステータスの描画配列
#define StatusArr_Width (27)
#define DamageArr_Height (6)	// 予想ダメージ描画配列
#define DamageArr_Width (20)
#define EffectArr_Height (5)	// ダメージエフェクト描画配列
#define EffectArr_Width (25)
#define Message_Height (7)		// メッセージ描画配列
#define Message_Width (75)	

#define CriticalCheck (19)		// この数字以上ならクリティカルヒット
#define MissCheck (1)			// この数字以下なら攻撃ミス
#define DryadHealHP (10)		// 木の精毎回回復のHP数値

// ターンフェイス番号
enum Phase_No
{
	BeginningPhase = 0,
	SkillPhase,
	PlayerPhase,
	EnemyPhase,
	EndPhase,
};

// 攻撃した結果
enum AttackResult
{
	Miss = 0,
	NormalAttack,
	CriticalHit,
};

/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
void DrawSkill(void);


/*******************************************************************************
* グローバル変数
*******************************************************************************/
ENEMY Enemy;
int TurnPhase = 0;
int AttackResult = 0;

/*******************************************************************************
関数名:	bool BattleEvent(int Enemy_No)
引数:	int Enemy_No
戻り値:	bool
説明:	バトルイベントループ
*******************************************************************************/
bool BattleEvent(int Enemy_No)
{
	PLAYER *Player = GetPlayerAdr();
	bool KillEnemy = false;
	Enemy.Number = Enemy_No;

	// バトル初期化
	InitBattle();

	while (true)
	{
		if (_kbhit())
		{
			Player->HitKey = _getch();
			if ((Player->HitKey == 0) || (Player->HitKey == 224))
			{
				Player->HitKey = _getch();
			}
			// 撤退
			else if (Player->HitKey == 'q')
			{
				break;
			}
		}

		// バトル更新
		UpdateBattle();

		// バトル描画
		DrawBattle();

		// バトル終了
		if (TurnPhase == EndPhase)
		{
			// エネミー死んだら
			if (Enemy.HP <= 0)
			{
				KillEnemy = true;
			}
			break;
		}
	}

	return KillEnemy;
}

/*******************************************************************************
関数名:	void InitBattle(void)
引数:	void
戻り値:	void
説明:	バトルの初期化処理
*******************************************************************************/
void InitBattle(void)
{
	TurnPhase = BeginningPhase;
	// エネミーのステータス設定
	switch (Enemy.Number)
	{
	case Slime:
		strcpy(&Enemy.name[0], "スライム");
		strcpy(&Enemy.Ability[0], "なし");
		Enemy.HP = SlimeHP;
		Enemy.ATK = SlimeATK;
		Enemy.DEF = SlimeDEF;
		Enemy.AGI = SlimeAGI;
		Enemy.EXP = SlimeEXP;
		Enemy.Money = SlimeMoney;
		break;
	case Archer:
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
		strcpy(&Enemy.name[0], "サイクロプス");
		strcpy(&Enemy.Ability[0], "なし");
		Enemy.HP = CyclopsHP;
		Enemy.ATK = CyclopsATK;
		Enemy.DEF = CyclopsDEF;
		Enemy.AGI = CyclopsAGI;
		Enemy.EXP = CyclopsEXP;
		Enemy.Money = CyclopsMoney;
		break;
	case Boss:
		strcpy(&Enemy.name[0], "塔の支配者");
		strcpy(&Enemy.Ability[0], "魔法バリア");
		Enemy.HP = BossHP;
		Enemy.ATK = BossATK;
		Enemy.DEF = BossDEF;
		Enemy.AGI = BossAGI;
		Enemy.BossBarrier = BossBarrierHP;
		break;
	default:
		break;
	}
	return;
}

/*******************************************************************************
関数名:	void UpdateBattle(void)
引数:	void
戻り値:	void
説明:	バトルの更新処理
*******************************************************************************/
void UpdateBattle(void)
{
	int Damage = 0;	// 攻撃ダメージ
	PLAYER *Player = GetPlayerAdr();
	int AttackCheck = 0;		// 攻撃結果判定
	int AGIDifference = 0;		// プレイヤー、エネミーのAGI差の値

	// プレイヤーのターン
	if (TurnPhase == PlayerPhase)
	{
		AGIDifference = Player->Status.AGI - Enemy.AGI;
		AGIDifference = AGIDifference >= 10 ? 10 : AGIDifference;
		// 攻撃結果判定
		AttackCheck = rand() % (20 + 1) + AGIDifference;
		// ダメージ計算
		Damage = Player->Status.ATK - Enemy.DEF;
		Damage = Damage <= 0 ? 0 : Damage;
		// 普通攻撃
		AttackResult = NormalAttack;
		// クリティカルヒット
		if (AttackCheck > CriticalCheck)
		{
			Damage = Damage * 2;
			AttackResult = CriticalHit;
		}
		// ミス
		else if (AttackCheck < MissCheck)
		{
			Damage = 0;
			AttackResult = Miss;
		}
		// ボス戦は特殊処理、まずはバリア壊さなければならない
		if (Player->InBossBattle == false || Enemy.BossBarrier <= 0)
		{
			Enemy.HP -= Damage;
		}
		// 一般戦闘
		else
		{
			Enemy.BossBarrier -= Damage;
		}
	}
	// エネミーのターン
	else if (TurnPhase == EnemyPhase)
	{
		AGIDifference = Enemy.AGI - Player->Status.AGI;
		AGIDifference = AGIDifference >= 10 ? 10 : AGIDifference;
		AttackCheck = rand() % (20 + 1) + AGIDifference;
		if (Enemy.Number != Magician)
		{
			Damage = Enemy.ATK - Player->Status.DEF;
			Damage = Damage <= 0 ? 0 : Damage;
		}
		else
		{
			Damage = Enemy.ATK;
		}
		AttackResult = NormalAttack;
		if (AttackCheck > CriticalCheck)
		{
			Damage = Damage * 2;
			AttackResult = CriticalHit;
		}
		else if (AttackCheck < MissCheck)
		{
			Damage = 0;
			AttackResult = Miss;
		}
		Player->Status.HP -= Damage;
		if (Enemy.Number == Dryad)
		{
			Enemy.HP += DryadHealHP;
		}
	}
	if (Player->Status.HP <= 0 || Enemy.HP <= 0)
	{
		Player->Status.HP <= 0 ? Player->Status.HP = 0 : Enemy.HP = 0;
		TurnPhase = EndPhase;
	}
	return;
}

/*******************************************************************************
関数名:	void DrawBattle(void)
引数:	void
戻り値:	void
説明:	バトルの描画処理
*******************************************************************************/
void DrawBattle(void)
{
	int i = 0, j = 0;	// forループ計算用
	int X = 0, Y = 0;	// メッセージ調整用
	int Length = 0;		// 配列の長さを記録する
	int Column = 0;		// メッセージの行数を記録する
	int Distance = 0;	// プレイヤーとエネミー間の距離(ダメージエフェクト位置を修正するため)
	int EstimateDamage = 0;	// 予想ダメージ
	static bool SecondAttack = false;	// 二回攻撃の判断
	static bool UseSkill = false;		// スキル使用済み
	static bool DestoryBarrier = false;	// ボスのバリア破壊済み
	static bool BarrierEvent = false;	// バリア発生済み
	PLAYER *Player = GetPlayerAdr();
	// バトル背景
	char BattleBG[Console_Height][Console_Width] = {
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
		"  |￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣|\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                   撤退(Q)|\n",
		"  ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣",
	};
	// エネミー描画用配列
	char EnemyArray[Array_Height][Array_Width] = {};
	// プレイヤー描画用配列
	char PlayerArray[Array_Height][Array_Width] = {};
	// ステータス描画用配列
	char StatusArray[StatusArr_Height][StatusArr_Width] = {};
	// ダメージエフェクト描画用配列
	char EffectArray[EffectArr_Height][EffectArr_Width] = {};
	// 予想ダメージ描画用配列
	char DamageArray[DamageArr_Height][DamageArr_Width] = {
		"                   ",
		"                   ",
		"                   ",
		"                   ",
		"                   ",
		"                   ",
	};
	// メッセージ描画用配列
	char Message[Message_Height][Message_Width] = {
		"--------------------------------------------------------------------------",
		"                                                                          ",
		"                                                                          ",
		"                                                                          ",
		"                                                                          ",
		"                                                                          ",
		"--------------------------------------------------------------------------",
	};


	// 画面クリア
	system("cls");

	// =============================================================
	// ========================エネミーの描画========================
	// =============================================================
	switch (Enemy.Number)
	{
	case Slime:
		strcpy(&EnemyArray[0][0], "         ｒ⌒,            ");
		strcpy(&EnemyArray[1][0], "　    　 ﾉ:::丶           ");
		strcpy(&EnemyArray[2][0], "　　,ー＿:::::＿ー､       ");
		strcpy(&EnemyArray[3][0], "　／/) (・) (・):::丶     ");
		strcpy(&EnemyArray[4][0], "`｜Ｕ (~ヽ＿_／~):::｜    ");
		strcpy(&EnemyArray[5][0], "　＼ｏ ＼＿＿_／:::／     ");
		strcpy(&EnemyArray[6][0], "　　`ーーーーーー-′      ");
		break;
	case Archer:
		strcpy(&EnemyArray[0][0], "　　 ／⌒＼             ");
		strcpy(&EnemyArray[1][0], "　　/ ＿＿_)　／(       ");
		strcpy(&EnemyArray[2][0], "　 ( (´∀`)／　|)      ");
		strcpy(&EnemyArray[3][0], "　　) _]つ＜＝＝０⇒    ");
		strcpy(&EnemyArray[4][0], "　 /　 ー _>＼　|)      ");
		strcpy(&EnemyArray[5][0], "　(_＞ー＜_)　＼(       ");
		break;
	case SlimeKnight:
		strcpy(&EnemyArray[0][0], "　   　　彡ﾐl\"'ヽ　　　/i          ");
		strcpy(&EnemyArray[1][0], "　   　　{[i]二三}　  //           ");
		strcpy(&EnemyArray[2][0], "　   　「￣ ~l　j,j、//            ");
		strcpy(&EnemyArray[3][0], "　   　 ヽ_,ノ_　}  O`             ");
		strcpy(&EnemyArray[4][0], "　　    ,'　U　ヽ>ヽ               ");
		strcpy(&EnemyArray[5][0], "（（（ {　　・∀・}                ");
		strcpy(&EnemyArray[6][0], "　　    `ー----ｰ'’                ");
		break;
	case Tiger:
		strcpy(&EnemyArray[0][0], "   　 　 　 ｨﾐ彡ミ､_, --､_     ");
		strcpy(&EnemyArray[1][0], "　　　　 　 　 　 ﾞｰ-‐‐､_ ＼   ");
		strcpy(&EnemyArray[2][0], "　　　　　　 ,, ､　 , --､__,)　）");
		strcpy(&EnemyArray[3][0], " 　　　　, -'　l ｀ｰ'-f　 ヽ _/  ");
		strcpy(&EnemyArray[4][0], "  　 　 /　　 _ _　　 l　　 f    ");
		strcpy(&EnemyArray[5][0], "　　　/ , -‐'　 ﾞｰ-ｧ.!｀l　l    ");
		strcpy(&EnemyArray[6][0], "　　 /　r(^ｰ・・''^)ｨ ∧i　l     ");
		strcpy(&EnemyArray[7][0], " 　 /　 t_|｀!::i´|_t\" ヽ l､    ");
		strcpy(&EnemyArray[8][0], "　 i 　 / |/ｷ::ヽ|  ヽ   l-､ヽ   ");
		strcpy(&EnemyArray[9][0], ", -'　 ｲ 　l､ｰ',l    l   ﾄ､ ¨   ");
		strcpy(&EnemyArray[10][0], "ｰｔ^t^ﾞゝ　　￣　　  <_ｨ_Y_lゝ   ");
		break;
	case Magician:
		strcpy(&EnemyArray[0][0], "　　　　--ミ              ");
		strcpy(&EnemyArray[1][0], "　 .: :::::::｀:..、      ");
		strcpy(&EnemyArray[2][0], "  /::/:::::::::   ヽ      ");
		strcpy(&EnemyArray[3][0], " ':;ｲ:::::::::_:_::}      ");
		strcpy(&EnemyArray[4][0], " : /　､:::::  くoﾆ{       ");
		strcpy(&EnemyArray[5][0], " ⅱ　 ｢:::::::::V人       ");
		strcpy(&EnemyArray[6][0], " 从　 l:::::＼  r‐ﾍ〕    ");
		strcpy(&EnemyArray[7][0], "廴ﾉ  /ﾊｰ::::::} ヽﾉ:!     ");
		strcpy(&EnemyArray[8][0], "　　ｲ :ﾍ:::ィ´l:ｌ:j     ");
		strcpy(&EnemyArray[9][0], " __ﾉ|::_  乂_ノ:_:ﾉ(      ");
		strcpy(&EnemyArray[10][0], "　ー=ﾆ :_:_:_:_:_:_彡     ");
		break;
	case GhostArmor:
		strcpy(&EnemyArray[0][0], "   　　､ｨヽ(ヽ               ");
		strcpy(&EnemyArray[1][0], "   　　､_ゞヽ|               ");
		strcpy(&EnemyArray[2][0], "   　　νγγ￣ヽ_           ");
		strcpy(&EnemyArray[3][0], "   　　`´ ﾉ""゛＿ゝ           ");
		strcpy(&EnemyArray[4][0], "   γ⌒ヽノ　ＧｲIIII)／/     ");
		strcpy(&EnemyArray[5][0], "   /　\"〟ヽノヾ::::／／ヽ    ");
		strcpy(&EnemyArray[6][0], "   ＼＿＿ﾉ`ヽ_ニﾆ／∠ゝ::    ");
		strcpy(&EnemyArray[7][0], "   `/＿/:.〝 .:／／|L_L|:    ");
		strcpy(&EnemyArray[8][0], "   `＼￣＼＿､∠∠､ノ((uE}    ");
		strcpy(&EnemyArray[9][0], "   　 ＼√/Lミ}￣T｜:::::    ");
		strcpy(&EnemyArray[10][0], "   　　 `ﾆ∠／―´)ヾ:::ﾉ    ");
		strcpy(&EnemyArray[11][0], "   　　/乙ヽ〝　γヽ`￣      ");
		strcpy(&EnemyArray[12][0], "   　 /　`-|`￣^ヽﾉ￣ヽ      ");
		strcpy(&EnemyArray[13][0], "   　/　\"〟|　　 | 〝\"|      ");
		strcpy(&EnemyArray[14][0], "   ／⌒ヽ＿|　　 | γ￣ヽ    ");
		strcpy(&EnemyArray[15][0], "   ｀――´　　　 ｀￣￣     ");
		break;
	case Phantom:
		strcpy(&EnemyArray[0][0], "　　　　 , -- 、             ");
		strcpy(&EnemyArray[1][0], "　　　 ｲ::;;;::ヽ            ");
		strcpy(&EnemyArray[2][0], "　　　ノ::＋＋::ヽ           ");
		strcpy(&EnemyArray[3][0], "　 ／:::;;;;;;:::l           ");
		strcpy(&EnemyArray[4][0], "　 |::;;:::;;;::::l          ");
		strcpy(&EnemyArray[5][0], "  /:;:,､:::;;:::r-､:;､       ");
		strcpy(&EnemyArray[6][0], " /:;:/弋::::::::|　 ゝ:;ヽ   ");
		strcpy(&EnemyArray[7][0], "l:;:/　　ヽ::::::ヽ ｀ｰﾚ'    ");
		strcpy(&EnemyArray[8][0], "|:;ゝ　　　ヽ:::::::l        ");
		strcpy(&EnemyArray[9][0], " ^　　　　　 ヽ-:::::ヽ      ");
		strcpy(&EnemyArray[10][0], "　 　　　　　　　 ~l::|      ");
		strcpy(&EnemyArray[11][0], " 　 　　　　　　　　ﾉノ      ");
		strcpy(&EnemyArray[12][0], " 　　　　　　　　 ∠'        ");
		break;
	case SlimeKing:
		strcpy(&EnemyArray[0][0], "　　　　　/､            ");
		strcpy(&EnemyArray[1][0], "　　　　　||            ");
		strcpy(&EnemyArray[2][0], "　　　 ／ニニ＼        ");
		strcpy(&EnemyArray[3][0], "　　 ＿――――＿       ");
		strcpy(&EnemyArray[4][0], "　 ＼∨＼／＼／∨／     ");
		strcpy(&EnemyArray[5][0], "　　＼＿＿＿＿＿／      ");
		strcpy(&EnemyArray[6][0], "　　／￣ﾆ￣￣ﾆ￣＼      ");
		strcpy(&EnemyArray[7][0], ".／　　(･)　(･)　　＼   ");
		strcpy(&EnemyArray[8][0], "|　　ヽ､_　　_,ｒ　　|  ");
		strcpy(&EnemyArray[9][0], "(　　ノ -ニニ- ﾍ　　 )  ");
		strcpy(&EnemyArray[10][0], "|　　　　　　　　　　|  ");
		strcpy(&EnemyArray[11][0], ".＼　　　　　　　　／   ");
		strcpy(&EnemyArray[12][0], "　　＼＿＿＿＿＿／      ");
		break;
	case Dryad:
		strcpy(&EnemyArray[0][0], "ヽ　　　　　　,r ^= ｧ=-､ ,        ");
		strcpy(&EnemyArray[1][0], " ||　　　 /` '　ヽr‐､,_.ヽ､,     ");
		strcpy(&EnemyArray[2][0], " ヾ ､　__j　  __　 　　　 ﾚ'1     ");
		strcpy(&EnemyArray[3][0], "　 ＼~　　 　 |::＼.._　　 r1     ");
		strcpy(&EnemyArray[4][0], "　　　`ｰ､　　 |:::　::|　r'\":/ ､  ");
		strcpy(&EnemyArray[5][0], "　　　　　`i 　ヽ::.../　ヽ;j ,j! ");
		strcpy(&EnemyArray[6][0], "　　　　　 j　 　 ￣　　   `ｰ'ｿ   ");
		strcpy(&EnemyArray[7][0], "　　　　　/　　,r､r――v'´|-'    ");
		strcpy(&EnemyArray[8][0], "　　　　/　　 ヽ　_r-―v(         ");
		strcpy(&EnemyArray[9][0], "　r―‐'　　　 `' 　 　 !_        ");
		strcpy(&EnemyArray[10][0], "∠r､_.　 /　　　　 　 　  `ｰ､     ");
		strcpy(&EnemyArray[11][0], "　　　＞'　　　,､　､ 　,i―'￣`   ");
		strcpy(&EnemyArray[12][0], "  _- ''  ＿ ノ  ヽヽ  ヽ､         ");
		strcpy(&EnemyArray[13][0], "（　<￣￣　　　 　ヽj`ー､ヽ       ");
		strcpy(&EnemyArray[14][0], " ヽ !　　　　　　　　　　ヽ!      ");
		strcpy(&EnemyArray[15][0], "　 `'                             ");
		break;
	case Cyclops:
		strcpy(&EnemyArray[0][0], "　　　　　  A　　　　,(_c三)、");
		strcpy(&EnemyArray[1][0], "　　　　∧/◎ヽ∧ _,-t;li /|| ");
		strcpy(&EnemyArray[2][0], "　 _,.--ゞェｪｪェﾂ'\"  | // i/  ");
		strcpy(&EnemyArray[3][0], " （∴∵ l `ー‐'\" ,lﾞ |l `;/  ");
		strcpy(&EnemyArray[4][0], "　/ヾ：∴ヽ`、__,.ｲ`ｖ |l lﾞ  ");
		strcpy(&EnemyArray[5][0], "　ヽ ヾ∵∴ヽ、　/　(r'⊥l_l  ");
		strcpy(&EnemyArray[6][0], "　　〉 lﾆニ●ニﾆl  |`(＿,. |  ");
		strcpy(&EnemyArray[7][0], ",.ヘ,< ∴-ニ-∵ヽ  `J(__,./   ");
		strcpy(&EnemyArray[8][0], "( ヲ`^'WwwwwwW'^〈　 >ri‐\"   ");
		strcpy(&EnemyArray[9][0], "(~`ｰ--､,）　ヽ,　　）`'\"      ");
		strcpy(&EnemyArray[10][0], "(~'ヾ.. ヽ　ｒ^　 ノ          ");
		strcpy(&EnemyArray[11][0], "`-'ー- ､_ﾉ　 ヽ '\"ミ          ");
		strcpy(&EnemyArray[12][0], "　　　　　　  `ヾ`            ");
		break;
	case Boss:
		strcpy(&EnemyArray[0][0], " 　 　  ,. --‐- .、         ");
		strcpy(&EnemyArray[1][0], "　    ／.:.:.:.:.:.＼        ");
		strcpy(&EnemyArray[2][0], "     /:.:.:.:.:.:.:.:ﾍ       ");
		strcpy(&EnemyArray[3][0], "    '.:{:.:./l.:/ヽ、:'      ");
		strcpy(&EnemyArray[4][0], "   l:.:ヽrｎレ' ｎＶ:.:l     ");
		strcpy(&EnemyArray[5][0], "  八:.:.:)l｣　　l｣).:.:八    ");
		strcpy(&EnemyArray[6][0], "（::ﾊ:.: 人   ｰ  人:.:(::)   ");
		strcpy(&EnemyArray[7][0], "  ヽ: : : :≧rｭ≦ : ::〃     ");
		strcpy(&EnemyArray[8][0], "  ﾉ. : : ;<l:又:!>: ::人     ");
		strcpy(&EnemyArray[9][0], "（ r'ヽ／yl:lＸl:!x＼rヽ）   ");
		strcpy(&EnemyArray[10][0], "  　 ‘ｰ／ /   ∧ ＼ｰ’      ");
		strcpy(&EnemyArray[11][0], " 　 　 <｀T′    T´>        ");
		strcpy(&EnemyArray[12][0], "　　　  ｀¨ TTT ¨´        ");
		strcpy(&EnemyArray[13][0], "　　　　    ｀´             ");
		break;
	default:
		break;
	}

	// 行数の計算
	for (Column = 0; EnemyArray[Column][0] != NULL && Column <= Array_Height; Column++)
	{
		;
	}
	// Y = EnemyArray上から下までの真ん中
	Y = (Array_Height - Column) / 2;
	for (i = 0; i < Array_Height && EnemyArray[i][0] != NULL; i++)
	{
		// X = EnemyArray左から右までの真ん中
		Length = strlen(&EnemyArray[i][0]);
		X = (Array_Width - Length) / 2;
		strncpy(&BattleBG[EnemyStart_Y + Y + i][EnemyStart_X + X], EnemyArray[i], Length);
	}

	// ===============================================================
	// ========================プレイヤーの描画========================
	// ===============================================================
	strcpy(&PlayerArray[0][0], "  i＾ヽry/`ヽ、    ");
	strcpy(&PlayerArray[1][0], "  ,'｀⌒ﾞ｀ヽ'     ");
	strcpy(&PlayerArray[2][0], " Ｌ(ﾉ八ﾉﾉＬi〉     ");
	strcpy(&PlayerArray[3][0], " il､ﾟヮﾟ[illλ     ");
	strcpy(&PlayerArray[4][0], "  ﾉi` ﾑ´」,ﾍﾘ     ");
	strcpy(&PlayerArray[5][0], "〈／i.Tヽヾ､_〉    ");
	strcpy(&PlayerArray[6][0], "ﾞ''ｔ_ｧ_ｧ‐゛     ");

	// 行数の計算
	for (Column = 0; PlayerArray[Column][0] != NULL && Column <= Array_Height; Column++)
	{
		;
	}
	// Y = PlayerArray上から下までの真ん中
	Y = (Array_Height - Column) / 2;
	for (i = 0; i < Array_Height && PlayerArray[i][0] != NULL; i++)
	{
		Length = strlen(&PlayerArray[i][0]);
		strncpy(&BattleBG[PlayerStart_Y + Y + i][PlayerStart_X], PlayerArray[i], Length);
	}

	// ====================================================================
	// ========================エネミーステータスの描画======================
	// ====================================================================
	sprintf(&StatusArray[0][0], "      %s", &Enemy.name[0]);
	sprintf(&StatusArray[1][0], "      HP：%d", Enemy.HP);
	sprintf(&StatusArray[2][0], "      ATK：%d", Enemy.ATK);
	sprintf(&StatusArray[3][0], "      DEF：%d", Enemy.DEF);
	sprintf(&StatusArray[4][0], "      AGI：%d", Enemy.AGI);
	sprintf(&StatusArray[5][0], "      特殊能力：%s", &Enemy.Ability[0]);
	for (i = 0; i < StatusArr_Height && StatusArray[i][0] != NULL; i++)
	{
		Length = strlen(&StatusArray[i][0]);
		X = (StatusArr_Width - Length) / 2;
		strncpy(&BattleBG[EnemyStatus_Y + i][EnemyStatus_X + X], StatusArray[i], Length);
	}

	// ====================================================================
	// ==========================ダメージ予想の描画=========================
	// ====================================================================
	if (TurnPhase != BeginningPhase && TurnPhase != SkillPhase)
	{
		// プレイヤー
		if (TurnPhase == PlayerPhase || (TurnPhase == EndPhase && Player->Status.HP > 0))
		{
			EstimateDamage = Player->Status.ATK - Enemy.DEF;
			sprintf(&DamageArray[3][0], "<-----------------");
		}
		// エネミー
		else if (TurnPhase == EnemyPhase || TurnPhase == EndPhase)
		{
			if (Enemy.Number != Magician)
			{
				EstimateDamage = Enemy.ATK - Player->Status.DEF;
			}
			else
			{
				EstimateDamage = Enemy.ATK;
			}
			sprintf(&DamageArray[3][0], "----------------->");
		}
		EstimateDamage = EstimateDamage >= 0 ? EstimateDamage : 0;
		if (AttackResult == Miss)
		{
			EstimateDamage = 0;
			sprintf(&DamageArray[2][0], "攻撃ミス");
		}
		else
		{
			if (AttackResult == CriticalHit)
			{
				sprintf(&DamageArray[1][0], "Critical Hit！");
				EstimateDamage = EstimateDamage * 2;
			}
			if (Player->InBossBattle && TurnPhase == PlayerPhase && DestoryBarrier == false)
			{
				EstimateDamage = 0;
			}
			sprintf(&DamageArray[2][0], "ダメージ：%d点", EstimateDamage);
		}
		// 描画
		if (Player->InBossBattle == true)
		{
			for (i = 0; i < DamageArr_Height && DamageArray[i][0] != NULL; i++)
			{
				Length = strlen(&DamageArray[i][0]);
				X = (DamageArr_Width - Length) / 2;
				strncpy(&BattleBG[EstimateDamage_Y + i][EstimateDamage_X + X], DamageArray[i], Length);
			}
		}
		else
		{
			if (UseSkill == false)
			{
				for (i = 0; i < DamageArr_Height && DamageArray[i][0] != NULL; i++)
				{
					Length = strlen(&DamageArray[i][0]);
					X = (DamageArr_Width - Length) / 2;
					strncpy(&BattleBG[EstimateDamage_Y + i][EstimateDamage_X + X], DamageArray[i], Length);
				}
			}
		}

	}

	// ====================================================================
	// =======================ダメージエフェクトの描画=======================
	// ====================================================================
	if (TurnPhase != BeginningPhase && TurnPhase != SkillPhase && AttackResult != Miss)
	{
		if (AttackResult == NormalAttack)
		{
			strcpy(&EffectArray[0][0], " ＼ ,,_人､ノヽ ");
			strcpy(&EffectArray[1][0], "  )ヽ　　　（  ");
			strcpy(&EffectArray[2][0], "＜　　　　　 ＞");
			strcpy(&EffectArray[3][0], "  )　　　　て  ");
			strcpy(&EffectArray[4][0], " ／^⌒`Y´^＼  ");
		}
		else if (AttackResult == CriticalHit)
		{
			strcpy(&EffectArray[0][0], "  　　､ 　 ﾉヾ        ");
			strcpy(&EffectArray[1][0], "　　　)ヽ/　 ヽ､ﾉ|ノ´");
			strcpy(&EffectArray[2][0], "=＝二　　　      二＝=");
			strcpy(&EffectArray[3][0], "　　　)　　　　　（   ");
			strcpy(&EffectArray[4][0], "　　　 '´⌒`Y´⌒` ､ ");
		}
		if (TurnPhase == PlayerPhase || (TurnPhase == EndPhase && Player->Status.HP > 0))
		{
			Distance = 0;
		}
		else if (TurnPhase == EnemyPhase || TurnPhase == EndPhase)
		{
			// プレイヤーとエネミー間の距離
			Distance = 42;
		}
		if (Player->InBossBattle == true)
		{
			for (i = 0; i < EffectArr_Height && EffectArray[i][0] != NULL; i++)
			{
				Length = strlen(&EffectArray[i][0]);
				strncpy(&BattleBG[EffectStart_Y + i][EffectStart_X + Distance], EffectArray[i], Length);
			}
		}
		else
		{
			if (UseSkill == false)
			{
				for (i = 0; i < EffectArr_Height && EffectArray[i][0] != NULL; i++)
				{
					Length = strlen(&EffectArray[i][0]);
					strncpy(&BattleBG[EffectStart_Y + i][EffectStart_X + Distance], EffectArray[i], Length);
				}
			}
		}
	}

	// ====================================================================
	// ========================プレイヤーステータスの描画====================
	// ====================================================================
	sprintf(&StatusArray[0][0], "     勇者");
	sprintf(&StatusArray[1][0], "   HP：%d", Player->Status.HP);
	sprintf(&StatusArray[2][0], "   MP：%d", Player->Status.MP);
	sprintf(&StatusArray[3][0], "   ATK：%d", Player->Status.ATK);
	sprintf(&StatusArray[4][0], "   DEF：%d", Player->Status.DEF);
	sprintf(&StatusArray[5][0], "   AGI：%d", Player->Status.AGI);
	for (i = 0; i < StatusArr_Height && StatusArray[i][0] != NULL; i++)
	{
		Length = strlen(&StatusArray[i][0]);
		strncpy(&BattleBG[PlayerStatus_Y + i][PlayerStatus_X], StatusArray[i], Length);
	}

	// ===========================================================
	// ========================メッセージの描画====================
	// ===========================================================
	if (TurnPhase != PlayerPhase && TurnPhase != EnemyPhase)
	{
		// ターンフェイス = 準備フェイス
		if (TurnPhase == BeginningPhase)
		{
			if (Player->Status.GetSkill == true)
			{
				if (Player->HitKey == 's' && Player->Status.MP <= 0)
				{
					strcpy(Message[2], "MPが足りない");
					strcpy(Message[4], "代わりに戦闘開始する");
				}
				else if (Player->InBossBattle == false)
				{
					strcpy(Message[2], "エネミーが現れた！");
					strcpy(Message[4], "戦闘開始(Anykey) or スキル(S) or 撤退(Q)");
				}
				else if (Player->InBossBattle == true)
				{
					strcpy(Message[2], "謎の人が現れた！");
					strcpy(Message[4], "戦闘開始(Anykey) or スキル(S)");
				}
			}
			else
			{
				if (Player->InBossBattle == false)
				{
					strcpy(Message[2], "エネミーが現れた！");
					strcpy(Message[4], "戦闘開始(Anykey) or 撤退(Q)");
				}
				else
				{
					strcpy(Message[2], "謎の人が現れた！");
					strcpy(Message[4], "戦闘開始(Anykey)");
				}
			}
		}
		// ターンフェイス = スキルフェイス
		if (TurnPhase == SkillPhase)
		{
			if (UseSkill == false)
			{
				strcpy(Message[3], "エクスプロージョン！");
			}
			else if (UseSkill == true && Player->InBossBattle == true)
			{
				strcpy(Message[2], "強大の魔法を使ってもこの人が倒せない              ");
				strcpy(Message[3], "この人の周りにバリアみたいな物を纏っているようです");
				strcpy(Message[4], "どうやら先にこのバリア解除しなければいけない      ");
			}
		}
		// ターンフェイス = 終了フェイス
		if (TurnPhase == EndPhase)
		{
			// 戦闘勝利
			if (Enemy.HP <= 0)
			{
				if (Player->InBossBattle == false)
				{
					strcpy(Message[2], "戦闘勝利");
					sprintf(Message[4], "%d点経験値 と $%d を手に入れた", Enemy.EXP, Enemy.Money);
					Player->Status.EXP += Enemy.EXP;
					Player->Status.Money += Enemy.Money;
				}

				else
				{
					strcpy(Message[2], "おめでとうございます！");
					strcpy(Message[4], "あなたはこの魔法の塔の支配者を倒した");
					Player->Event_No = GameClear;
				}
			}
			// 戦闘負け
			else
			{
				strcpy(Message[3], "あなたはモンスターに倒された......");
				Player->Event_No = GameOver;
			}
			UseSkill = false;
		}

		// メッセージ描画
		for (i = 0; i < Message_Height && Message[i][0] != NULL; i++)
		{
			// X = Message左から右までの真ん中
			Length = strlen(&Message[i][0]);
			X = (Message_Width - Length) / 2;
			for (j = 0; j < X; j++)
			{
				strncpy(&BattleBG[MessageStart_Y + i][MessageStart_X + j], " ", 1);
			}
			strncpy(&BattleBG[MessageStart_Y + i][MessageStart_X + X], Message[i], Length);
		}
	}

	// ボスバリア`のイベント
	if (Player->InBossBattle == true && Enemy.BossBarrier <= 0 && DestoryBarrier == false)
	{
		strcpy(Message[3], "あなたの攻撃によって、魔法バリアが破られた");
		// メッセージ描画
		for (i = 0; i < Message_Height && Message[i][0] != NULL; i++)
		{
			// X = Message左から右までの真ん中
			Length = strlen(&Message[i][0]);
			X = (Message_Width - Length) / 2;
			for (j = 0; j < X; j++)
			{
				strncpy(&BattleBG[MessageStart_Y + i][MessageStart_X + j], " ", 1);
			}
			strncpy(&BattleBG[MessageStart_Y + i][MessageStart_X + X], Message[i], Length);
		}
		DestoryBarrier = true;
		BarrierEvent = true;
		strcpy(&Enemy.Ability[0], "なし");
	}


	// ===========================================================
	// ======================すべての画面を描く====================
	// ===========================================================
	for (i = 0; i < Console_Height; i++)
	{
		printf("%s", &BattleBG[i][0]);
	}

	// ===========================================================
	// ======================次のフェイスを判断====================
	// ===========================================================
	switch (TurnPhase)
	{
	case BeginningPhase:
		Player->HitKey = _getch();
		if ((Player->HitKey == 0) || (Player->HitKey == 224))
		{
			Player->HitKey = _getch();
		}
		// スキルを使う
		if (Player->HitKey == 's' && Player->Status.GetSkill == true)
		{
			if (Player->Status.MP > 0)
			{
				TurnPhase = SkillPhase;
				Player->Status.MP -= 1;
			}
		}
		// 戦闘前撤退
		else if (Player->HitKey == 'q' && Player->InBossBattle == false)
		{
			TurnPhase = EndPhase;
		}
		// 戦闘開始
		else
		{
			TurnPhase = PlayerPhase;
		}
		break;
	case SkillPhase:
		Anykey();
		if (Player->InBossBattle == true && UseSkill == true)
		{
			TurnPhase = PlayerPhase;
		}
		else
		{
			DrawSkill();
			UseSkill = true;
		}
		break;
	case PlayerPhase:
		if (BarrierEvent == true)
		{
			Anykey();
			BarrierEvent = false;
		}
		TurnPhase = Enemy.HP <= 0 ? EndPhase : EnemyPhase;
		SecondAttack = false;
		Sleep(500);
		break;
	case EnemyPhase:
		if (Enemy.Number != Tiger || SecondAttack == true)
		{
			TurnPhase = Player->Status.HP <= 0 ? EndPhase : PlayerPhase;
		}
		// 特殊能力：二回攻撃
		else
		{
			TurnPhase = Player->Status.HP <= 0 ? EndPhase : EnemyPhase;
			SecondAttack = true;
		}
		Sleep(500);
		break;
	case EndPhase:
		Anykey();
		break;
	default:
		break;
	}
	return;
}

/*******************************************************************************
関数名:	void UninitBattle(void)
引数:	void
戻り値:	void
説明:	バトルの終了処理
*******************************************************************************/
void UninitBattle(void)
{
	return;
}

/*******************************************************************************
関数名:	void DrawSkill(void)
引数:	void
戻り値:	void
説明:	スキルの描画処理
*******************************************************************************/
void DrawSkill(void)
{
	PLAYER *Player = GetPlayerAdr();

	// ===========================================================
	// ==========================スキルの描画======================
	// ===========================================================
	system("cls");
	printf("　　 　  ,-'   _,,-''\"　　　　　　         \"''-,,_    ￣\"''-,,__　   ''--,,__\n");
	printf("　　　　　 ,,-''\"  ,, ---''\"\"\"  ニ_―――― -    _ ''-,,_　　　 ゞ　　       \"- \n");
	printf("　　　　 て　　　／   ,,-\"---''i|　　    ￣￣￣|i''-､　 ヾ　　　{\n");
	printf("　　　 （\"    .／ 　  i　{;;;;;i|             .|i;;;;）,ノ　　　 ii\n");
	printf(",,　　　　　 （　　　 l,　 `'-i|　　　        　|i;-'　　　　 ,-'\"　　　_,,-\"\n");
	printf("  \"'-,,　　　　`-,,,,-'--'':::￣￣:::::::::''ニ;-==,______　'\"　　 _,--''\"\n");
	printf("　     ￣\"''-- _-'::::\"￣::::::::;;;;;;;;;;;;;;----;;:::::`::\"''::---,,___,,-''\"\n");
	printf("　　　  ._,,-ニ-''ニ--''\"￣￣.i|￣￣　　      　|i-----,,￣`''-;;:::''-`-,,\n");
	printf("　  ,,-''::二-''\"　　　.--    i|               .|i　　    　　　　　 \"-;;:::`､\n");
	printf(" _,-\":::／　　　￣\"''---　   i|　　　        　　|i　　　　　　　  　　  ヽ::i\n");
	printf("(:::{(i(___　　　　　　　　  i|　　　       　　.|i　　　　　       　_,,-'/:}\n");
	printf("  `'-_ヽ::'-,,__,, 　_______i|　　　　　         .|i---__,,----..--''\":::ノ,-'\n");
	printf("  　　\"--;;;;;;;;;;\"\"''--;;i|                     .|i二;;;;:---;;;;;::--''\"~\n");
	printf("  　　　　　　　　 ￣￣\"...i|                     .|i\n");
	printf("  　　　　　　　　　　    i|　　　　　　　          |i\n");
	printf("  　　　　　　　　　　　 i|　　　　　　　　          |i\n");
	printf("  　　　　　　　　　　　i|　　 　 　　　　           .|i\n");
	printf("  　　　　　　　　　　 i|　　　　　　　　　          ..|i\n");
	printf("  　　　　　　　　　  i|  　　　　 　　　　　　         |i\n");
	printf("  　　　　　　　　　 i|　　　　　　      ,,-､　    ､　　 |i\n");
	printf("  　　　　　　　　　i|　　　　　　      ノ:::i::::トiヽ､..|i\n");
	printf("  　　　　　　  _,,i|/\"\"\"\"ヽ／:iヽ!:::::ﾉ::::::::::::Λ::ヽ|i___n､ト､\n");
	printf("    ,,／^ヽ,-'\"::i／::::::／:::::|i／;::;/::;:::::;;;ノ⌒ヽノ:::::::ヽ,_Λ\n");
	printf("    ;;;;;;:::::;;;;;;;;::/:::;;;;;;;;:::/;;;;;;::::::;;;;;;;;:;;;;:::::::ヽ");
	Anykey();
	if (Player->InBossBattle == false)
	{
		Enemy.HP = 0;
	}
	// ボス戦なら、ボスのHPが半分になる
	else
	{
		Enemy.HP = Enemy.HP / 2;
	}
	return;
}