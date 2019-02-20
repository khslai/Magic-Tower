﻿/*******************************************************************************
* Map.h	マップヘッダーファイル
*******************************************************************************/
#ifndef	MAP_H
#define	MAP_H

/*******************************************************************************
* インクルードファイル
*******************************************************************************/


/*******************************************************************************
* マクロ定義
*******************************************************************************/


/*******************************************************************************
* 構造体定義
*******************************************************************************/


/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
void InitMap(void);
void UpdateMap(void);
void DrawMap(void);
void UninitMap(void);
char *GetMapAdr(int X, int Y);
char *GetMapColAdr(int Column);

#endif