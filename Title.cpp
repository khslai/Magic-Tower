/*******************************************************************************
* タイトル:		タイトルプログラム
* プログラム名:	Titlecpp
* 作成者:		GP11B341 35 頼凱興
* 作成日:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "Title.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define SlashColumn (10)	// 斬撃エフェクトの行数
#define StartColumn (19)	// ゲームスタート文字の行数
#define ExitColumn (21)		// ゲーム終了文字の行数
#define SkipColumn (20)		// アニメーションスキップ文字の行数


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
関数名:	void DrawTitle(void)
引数:	void
戻り値:	void
説明:	タイトルの描画処理
*******************************************************************************/
void DrawTitle(void)
{
	int i = 0, j = 0, k = 0;		// forループ計算用
	int Length = 0;
	int X = 0;
	static int Y = 0;				// 矢印調整
	int Key = 0;					// 入力されたキー
	static bool Skip = false;		// アニメーションをスキップ
	static bool Animation = true;	// タイトルアニメーションの状態
	PLAYER *Player = GetPlayerAdr();
	// 背景の配列
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
	// 空白の背景配列
	char BackGround_Clear[Console_Height][Console_Width] = {};
	// タイトル文字
	char Title[Console_Height][Console_Width] = {
		"",															// 0
		"",															// 1
		"",															// 2
		"",															// 3
		"",															// 4
		"/￣￣￣￣/ /__７  /''７/'７'７             /￣￣￣/",		// 5
		"￣￣ノ ／  /__７ /   / ー' ｰ' /７/７ /'７ / /￣/ / ",		// 6
		"  <  <     ＿__ノ  /         ＿'__'ノ / ー' _/ /  ",		// 7
		"   ヽ､_/  /＿___, ／        /＿___, ／     /_ ノ   ",		// 8
		"",															// 9
		"---＝＝二二二二二二二二二二二二二二二二二二二二二二＝＝---",	// 10
		"",															// 11
		"  /￣￣￣ /  /￣￣￣ /         ",							// 12
		" /  /二/ /  ｰ‐'￣/ /  ＿＿＿_ ",							// 13
		"/__,--, /   ＿__ノ /  /＿_＿＿/",							// 14
		"  /___ノ   /＿___／            ",							// 15
		"",															// 16
		"",															// 17
		"",															// 18
		"",															// 19
		"",															// 20
		"",															// 21
		"",															// 22
		"",															// 23
		"",															// 24
	};
	// タイトルの背景
	char Sword[Console_Height][Console_Width] = {
		"",
		"",
		"     〔 || 〕    ",
		"       |＝|      ",
		"       |＝|      ",
		"       |◇|      ",
		" 〈wl≦《》≧lw〉",
		"      l》《l     ",
		"    〔 l◆l 〕   ",
		"      } || {     ",
		"      | || |     ",
		"      | || |     ",
		"      | || |     ",
		"      | || |     ",
		"      | || |     ",
		"      | || |     ",
		"      ヽ||/      ",
		"        ∨       ",
	};

	//　空白背景をバックアップする
	for (i = 0; i < Console_Height; i++)
	{
		strcpy(&BackGround_Clear[i][0], &BackGround[i][0]);
	}

	// スキップしなかったら
	if (Skip == false)
	{
		// 背景の第SkipColumn行に"Press Any Key to Skip"を上書きする
		strcpy(&Title[SkipColumn][0], "Press Any Key to Skip");
		Length = strlen(&Title[SkipColumn][0]);
		X = (Console_Width - Length) / 2;
		strncpy(&BackGround[SkipColumn][X], &Title[SkipColumn][0], Length);

		// タイトル文字を背景に上書き
		for (i = 0; i < Console_Height; i++)
		{
			Length = strlen(&Title[i][0]);
			X = (Console_Width - Length) / 2;
			if (i == SlashColumn || i == StartColumn ||
				i == ExitColumn || i == SkipColumn || Title[i][0] == NULL)
			{
				continue;
			}
			else
			{
				for (j = 0; j < Length; j++)
				{
					strncpy(&BackGround[i][X + j], &Title[i][j], 1);
					system("cls");
					for (int k = 0; k < Console_Height; k++)
					{
						printf("%s", &BackGround[k][0]);
						// キーが入力されたら
						if (_kbhit())
						{
							// アニメーションをスキップ
							Skip = true;
							break;
						}
					}
					// アニメーションをスキップ
					if (Skip == true)
					{
						break;
					}
					Sleep(30);
				}
				// アニメーションをスキップ
				if (Skip == true)
				{
					break;
				}
			}
		}
		// スキップしなかったら
		if (Skip == false)
		{
			// 斬撃を描画
			Length = strlen(&Title[SlashColumn][0]);
			X = (Console_Width - Length) / 2;
			for (i = 0; i < Length; i++)
			{
				strncpy(&BackGround[SlashColumn][X + i], &Title[SlashColumn][i], 1);
				strncpy(&BackGround_Clear[SlashColumn][X + i], &Title[SlashColumn][i], 1);
				system("cls");
				for (j = 0; j < Console_Height; j++)
				{
					printf("%s", &BackGround_Clear[j][0]);
				}
			}
		}
	}

	// タイトルアニメーションを終わったら
	if (Animation == false)
	{
		// キー入力
		Key = _getch();
		if ((Key == 0) || (Key == 224))
		{
			Key = _getch();
		}
		switch (Key)
		{
		case 'w':
		case 0x48:	// 矢印を上へ移動する
			Y -= 2;
			break;
		case 's':
		case 0x50:	// 矢印を下へ移動する
			Y += 2;
			break;
		case 0x0D:	// Enterキー
			if (Y == 0)
			{
				// ゲームスタート
				Player->GameStart = true;
			}
			else if (Y == 2)
			{
				// ゲーム終了
				Player->ExitGame = true;
			}
			break;
		default:
			break;
		}
		// 矢印位置の調整
		Y = (Y + 4) % 4;
	}

	// "New Game"、"Exit Game"の文字を上書き
	strcpy(&Title[StartColumn][0], "New Game");
	strcpy(&Title[ExitColumn][0], "Exit Game");
	// "Press Any Key to Skip"を消す
	strcpy(&Title[SkipColumn][0], "");
	strcpy(&BackGround[SkipColumn][0], &BackGround[SkipColumn + 1][0]);
	// 背景にすべての配列を上書き
	for (i = 0; i < Console_Height; i++)
	{
		if (Title[i][0] == NULL && Sword[i][0] == NULL)
		{
			continue;
		}
		else
		{
			// 剣の描画
			Length = strlen(&Sword[i][0]);
			X = (Console_Width - Length) / 2;
			strncpy(&BackGround[i][X], &Sword[i][0], Length);
			// タイトル文字の描画
			Length = strlen(&Title[i][0]);
			X = (Console_Width - Length) / 2;
			strncpy(&BackGround[i][X], &Title[i][0], Length);
			// 矢印を描画
			if (i == StartColumn)
			{
				strncpy(&BackGround[i + Y][X - 5], "→", 2);
			}
		}
	}

	// 画面表示
	system("cls");
	for (i = 0; i < Console_Height; i++)
	{
		printf("%s", &BackGround[i][0]);
	}

	// タイトルアニメーションもう終わった
	if (Animation == true)
	{
		Anykey();
		Animation = false;
	}

	return;
}

/*******************************************************************************
関数名:	void DrawTutorial(void)
引数:	void
戻り値:	void
説明:	チュートリアルの描画処理
*******************************************************************************/
void DrawTutorial(void)
{
	int i = 0, j = 0;
	int Length = 0;
	int X = 0;
	int Key = 0;
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
	char SkipQuestion[Console_Width] = "チュートリアルをスキップしますか？(Y/N)";
	char PressAnyKey[Console_Width] = "Press Any Key";
	char Message[Console_Height][Console_Width] = {};

	// チュートリアルを終わらなかったら
	if (Player->TutorialOver != true)
	{
		system("cls");
		// スキップの質問
		Length = strlen(&SkipQuestion[0]);
		X = (Console_Width - Length) / 2;
		strncpy(&BackGround[12][X], &SkipQuestion[0], Length);
		for (i = 0; i < Console_Height; i++)
		{
			printf("%s", &BackGround[i][0]);
		}

		Key = _getch();
		if ((Key == 0) || (Key == 224))
		{
			Key = _getch();
		}
	}

	if (Key != 'y' || Player->TutorialOver == true)
	{
		// "Press Any Key"を上書きする
		Length = strlen(&PressAnyKey[0]);
		X = (Console_Width - Length) / 2;
		strncpy(&BackGround[22][X], &PressAnyKey[0], Length);
		// 質問の文字を消す
		strcpy(&BackGround[12][0], &BackGround[13][0]);
		// チュートリアルの内容
		strcpy(&Message[3][0], "1. 必ず英小文字モードで遊んでください                          ");
		strcpy(&Message[5][0], "2. でも、メインプログラマーのくだらない理由によって            ");
		strcpy(&Message[6][0], "   ゲーム中の説明全部大文字になります                          ");
		strcpy(&Message[8][0], "3. W,A,S,D(及び方向キー)：移動   ESC：ゲーム終了   P：一時停止 ");
		strcpy(&Message[10][0], "4. いろんなアイテムを集まって、どんどん強くなる、目指すは最上階");
		strcpy(&Message[12][0], "5. レベルアップしたい時、5階の魔法商店に頼んでください         ");
		strcpy(&Message[14][0], "6. Lv.3になる時、スキルを習得します。スキルはとても強力な魔法  ");
		strcpy(&Message[15][0], "   スキルを使ったらMP-1、MPは回復不能の数値、慎重に使いましょう");
		strcpy(&Message[17][0], "7. アイテムについて：扉の鍵ーかかった扉を開けます              ");
		strcpy(&Message[18][0], "   怪物図鑑(E)ー取った後、モンスターのステータスが調べられます ");
		strcpy(&Message[19][0], "   地図ー取った後、各階層の構造が見えます                      ");
		strcpy(&Message[20][0], "   転送の翼(T)ー取った後、階層間がワープできます               ");
		strcpy(&Message[22][0], "以上の内容はヘルプ(H)の中も見えます");
		//　チュートリアルの描画、初めて見る
		if (Player->TutorialOver != true)
		{
			// 背景に描画
			for (i = 0; i < Console_Height; i++)
			{
				if (Message[i][0] == NULL)
				{
					continue;
				}
				else
				{
					Length = strlen(&Message[i][0]);
					X = (Console_Width - Length) / 2;
					strncpy(&BackGround[i][X], &Message[i][0], Length);
					// 画面クリア
					system("cls");
					// チュートリアルの描画
					for (j = 0; j < Console_Height; j++)
					{
						printf("%s", &BackGround[j][0]);
					}
					// キー入力待ち
					Anykey();
				}
			}
			// チュートリアル終了
			Player->TutorialOver = true;
		}
		// 二度目以降見る 
		else
		{
			// 背景に描画
			for (i = 0; i < Console_Height; i++)
			{
				if (Message[i][0] == NULL)
				{
					continue;
				}
				else
				{
					Length = strlen(&Message[i][0]);
					X = (Console_Width - Length) / 2;
					strncpy(&BackGround[i][X], &Message[i][0], Length);
				}
			}
			// 画面クリア
			system("cls");
			// チュートリアルの描画
			for (i = 0; i < Console_Height; i++)
			{
				printf("%s", &BackGround[i][0]);
			}
			// キー入力待ち
			Anykey();
		}
	}

	return;
}