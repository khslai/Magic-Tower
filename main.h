/*******************************************************************************
* main.h	メインヘッダーファイル
*******************************************************************************/
#ifndef	MAIN_H
#define	MAIN_H

/*******************************************************************************
* scanf のwarning防止
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include <stdio.h>	// システムのヘッダーファイルは<>
#include <time.h>
#include <conio.h>
#include <Windows.h>


/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define Console_Height	(25)	// コンソール画面の高さ
#define Console_Width	(80)	// コンソール画面の横幅


// 各階層の番号
enum Floor_No
{
	Enterance = 0,
	Floor_1F,
	Floor_2F,
	Floor_3F,
	Floor_4F,
	Floor_5F,
	Floor_6F,
	Floor_7F,
	Floor_8F,
	Floor_9F,
	Floor_10F,
	BossRoom,
	Floor_Treasure,
	ExitTeleport = 99,
};

// 各イベントの番号
enum Message_No {
	Nothing = 0,
	PauseEvent,
	HP_Potion,
	HP_HiPotion,
	ATKUp,
	DEFUp,
	AGIUp,
	EXPEvent,
	MoneyEvent,
	SwordEvent,
	ArmorEvent,
	SkillEvent,
	DoorKey,
	KeyNoEnough,
	GetFloorMap,
	GetDictionary,
	GetTeleport,
	CantTeleport,
	StoreEvent,
	TreasureRoom,
	EnterBossRoom,
	BossEvent,
	GameClear,
	GameOver,
	GameExit = 99,
};

// 各アイテム上昇の数値と番号
// 装備の名前
#define Sword01 "長剣"			
#define Sword02 "真銀の剣"
#define Sword03 "妖精の剣"
#define Armor01 "革鎧"
#define Armor02 "板金鎧"
#define Armor03 "魔甲冑"
enum Item
{
	Item_Potion = 100,
	Item_HiPotion = 250,
	Item_ATKUP = 2,
	Item_DEFUP = 2,
	Item_AGIUP = 1,
	Item_EXP = 100,
	Item_Money = 100,
	Equip_Sword01 = 8,
	Equip_Sword02 = 11,
	Equip_Sword03 = 15,
	Equip_Armor01 = 5,
	Equip_Armor02 = 8,
	Equip_Armor03 = 10,
	EnemyDictionary = 0,
	TeleportWing = 1,
};

// 各エネミーの番号
enum EnemyType
{
	Slime = 1,
	Archer,
	SlimeKnight,
	Tiger,
	Magician,
	GhostArmor,
	Phantom,
	SlimeKing,
	Dryad,
	Cyclops,
	Boss,
	ExitDictionary = 99,
};

// 各エネミーのステータス
enum EnemyStatus
{
	// スライム
	SlimeHP = 50,
	SlimeATK = 25,
	SlimeDEF = 2,
	SlimeAGI = 0,
	SlimeEXP = 1,
	SlimeMoney = 1,
	//アーチャー
	ArcherHP = 50,
	ArcherATK = 35,
	ArcherDEF = 3,
	ArcherAGI = 3,
	ArcherEXP = 1,
	ArcherMoney = 2,
	// スライムナイト
	SlimeKnightHP = 70,
	SlimeKnightATK = 35,
	SlimeKnightDEF = 12,
	SlimeKnightAGI = 2,
	SlimeKnightEXP = 1,
	SlimeKnightMoney = 3,
	// サーベルタイガー
	TigerHP = 80,
	TigerATK = 35,
	TigerDEF = 20,
	TigerAGI = 4,
	TigerEXP = 1,
	TigerMoney = 4,
	// 魔法使い
	MagicianHP = 100,
	MagicianATK = 30,
	MagicianDEF = 30,
	MagicianAGI = 2,
	MagicianEXP = 1,
	MagicianMoney = 6,
	// 亡霊の鎧
	GhostArmorHP = 120,
	GhostArmorATK = 35,
	GhostArmorDEF = 45,
	GhostArmorAGI = 1,
	GhostArmorEXP = 2,
	GhostArmorMoney = 7,
	// ファントム
	PhantomHP = 140,
	PhantomATK = 40,
	PhantomDEF = 30,
	PhantomAGI = 15,
	PhantomEXP = 2,
	PhantomMoney = 8,
	// キングスライム
	SlimeKingHP = 160,
	SlimeKingATK = 50,
	SlimeKingDEF = 38,
	SlimeKingAGI = 3,
	SlimeKingEXP = 2,
	SlimeKingMoney = 10,
	// 木の精
	DryadHP = 180,
	DryadATK = 57,
	DryadDEF = 45,
	DryadAGI = 4,
	DryadEXP = 2,
	DryadMoney = 12,
	// サイクロプス
	CyclopsHP = 240,
	CyclopsATK = 70,
	CyclopsDEF = 50,
	CyclopsAGI = 5,
	CyclopsEXP = 2,
	CyclopsMoney = 15,
	// 塔の支配者
	BossHP = 500,
	BossBarrierHP = 250,
	BossATK = 80,
	BossDEF = 65,
	BossAGI = 8,
};

// ゲーム説明のページ番号
enum InfomationPage
{
	PageStart = 0,
	Symbol_p1,
	Symbol_p2,
	PlayerItem,
	GameHelp,
	PageEnd,
};

/*******************************************************************************
* 構造体定義
*******************************************************************************/
// プレイヤーテータス構造体
typedef struct
{
	char name[32];
	int Level;
	int EXP;
	int HP;
	int MP;
	int ATK;
	int DEF;
	int AGI;
	int Money;
	bool GetSkill;
}STATUS;

// プレイヤーアイテム構造体
typedef struct
{
	int DoorKey;
	char Sword[20];
	char Armor[20];
	bool FloorMap;
	bool EnemyDictionary;
	bool TeleportWing;
	bool TreasureRoomKey;
}ITEM;

// プレイヤー情報の構造体
typedef	struct
{
	STATUS Status;
	ITEM Item;
	int fx;
	int fy;
	int MaxFloor;
	int OldFloor;
	int CurrentFloor;
	int Event_No;
	int HitKey;
	int InfoPage;
	bool GameStart;
	bool TutorialOver;
	bool InPause;
	bool InTeleport;
	bool InStore;
	bool InStair;
	bool InBossBattle;
	bool ExitGame;
}PLAYER;

// エネミーステータスの構造体
typedef	struct
{
	char name[32];
	char Ability[11];	// エネミーの特殊能力(最大5全角文字)
	int Number;
	int EXP;
	int HP;
	int ATK;
	int DEF;
	int AGI;
	int Money;
	int BossBarrier;
}ENEMY;

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
void Anykey(void);
PLAYER *GetPlayerAdr(void);
char *GetBGAdr(int X, int Y);
char *GetMapAdr(int X, int Y);

#endif
