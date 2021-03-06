/*******************************************************************************
* ^Cg:		Q[îñvO
* vO¼:	Information.cpp
* ì¬Ò:		GP11B341 35 M»
* ì¬ú:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* CN[ht@C
*******************************************************************************/
#include "main.h"
#include "Information.h"

/*******************************************************************************
* }Nè`
*******************************************************************************/
#define InfoTable_Height (6)	// \¦e[uÌ³
#define InfoTable_Width (49)	// \¦e[uÌ
#define InfoTable_X (3)			// e[u`æÌn_
#define InfoTable_Y (18)

/*******************************************************************************
* \¢Ìè`
*******************************************************************************/


/*******************************************************************************
* vg^Cvé¾
*******************************************************************************/


/*******************************************************************************
* O[oÏ
*******************************************************************************/

/*******************************************************************************
Ö¼:	void InitInformation(void)
ø:	void
ßèl:	void
à¾:	Q[îñÌú»
*******************************************************************************/
void InitInformation(void)
{
	return;
}

/*******************************************************************************
Ö¼:	void UpdateInformation(void)
ø:	void
ßèl:	void
à¾:	Q[îñÌXV
*******************************************************************************/
void UpdateInformation(void)
{
	return;
}

/*******************************************************************************
Ö¼:	void DrawInformation(void)
ø:	void
ßèl:	void
à¾:	Q[îñÌ`æ
*******************************************************************************/
void DrawInformation(void)
{
	int i = 0;
	int X = 0;
	int Length = 0;	// zñÌ·³
	char *DrawPostion = GetBGAdr(0, 0);
	PLAYER *Player = GetPlayerAdr();
	// Q[îñÌzñ
	char InfoTable[InfoTable_Height][InfoTable_Width] = {};

	if (Player->InStore == false)
	{
		switch (Player->InfoPage)
		{
			// Là¾(1)
		case Symbol_p1:
			strcpy(&InfoTable[0][0], "(F)© Là¾(1) ¨(G)");
			strcpy(&InfoTable[2][0], "@`IFeLv.X^[     ãAºFKi    ");
			strcpy(&InfoTable[3][0], "FHP|[V      `FATKUP   rFAGIUP ");
			strcpy(&InfoTable[4][0], "FHPnC|[V  cFDEFUP   jFàÌ®");
			break;
			// Là¾(2)
		case Symbol_p2:
			strcpy(&InfoTable[0][0], "(F)© Là¾(2) ¨(G)");
			strcpy(&InfoTable[2][0], "F¤X       VF©©Á½à               ");
			strcpy(&InfoTable[3][0], "FÌõ   ZFhïÌõ               ");
			strcpy(&InfoTable[4][0], "lF}bv     }Fö¨}Ó     F]Ì");
			break;
			// õÆACe
		case PlayerItem:
			strcpy(&InfoTable[0][0], "(F)© õÆACe ¨(G)");
			strcpy(&InfoTable[1][0], "     õ                      MdACe     ");
			if (Player->Item.FloorMap == true)
			{
				strcpy(&InfoTable[2][0], "                          }bv");
			}
			else
			{
				strcpy(&InfoTable[2][0], "                          HHH");
			}
			if (Player->Item.EnemyDictionary == true)
			{
				sprintf(&InfoTable[3][0], "íF%-16s         ö¨}Ó      ", &Player->Item.Sword[0]);
			}
			else
			{
				sprintf(&InfoTable[3][0], "íF%-16s          HHH      ", &Player->Item.Sword[0]);
			}
			if (Player->Item.TeleportWing == true)
			{
				sprintf(&InfoTable[4][0], "hïF%-16s         ]Ì      ", &Player->Item.Armor[0]);
			}
			else
			{
				sprintf(&InfoTable[4][0], "hïF%-16s          HHH      ", &Player->Item.Armor[0]);
			}
			break;
			// Q[Ìà¾
		case GameHelp:
			strcpy(&InfoTable[0][0], "(F)© Q[Ìà¾ ¨(G)");
			strcpy(&InfoTable[2][0], "Ú®FW,A,S,D              êâ~FP");
			strcpy(&InfoTable[3][0], "Q[I¹FESC            wvFH  ");
			if (Player->Item.EnemyDictionary == true && Player->Item.TeleportWing == true)
			{
				strcpy(&InfoTable[4][0], "ö¨}ÓFE                ]ÌFT");
			}
			else if (Player->Item.EnemyDictionary == true && Player->Item.TeleportWing == false)
			{
				strcpy(&InfoTable[4][0], "ö¨}ÓFE                           ");
			}
			else if (Player->Item.EnemyDictionary == false && Player->Item.TeleportWing == true)
			{
				strcpy(&InfoTable[4][0], "]ÌFT                           ");
			}
			break;
		default:
			break;
		}

		// wiÉe[uð`æ
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
Ö¼:	void UninitInformation(void)
ø:	void
ßèl:	void
à¾:	Q[îñÌI¹
*******************************************************************************/
void UninitInformation(void)
{
	return;
}