/*******************************************************************************
* �^�C�g��:		�Q�[�����v���O����
* �v���O������:	Information.cpp
* �쐬��:		GP11B341 35 ���M��
* �쐬��:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "Information.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define InfoTable_Height (6)	// �\���e�[�u���̍���
#define InfoTable_Width (49)	// �\���e�[�u���̕�
#define InfoTable_X (3)			// �e�[�u���`��̎n�_
#define InfoTable_Y (18)

/*******************************************************************************
* �\���̒�`
*******************************************************************************/


/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/


/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/

/*******************************************************************************
�֐���:	void InitInformation(void)
����:	void
�߂�l:	void
����:	�Q�[�����̏�����
*******************************************************************************/
void InitInformation(void)
{
	return;
}

/*******************************************************************************
�֐���:	void UpdateInformation(void)
����:	void
�߂�l:	void
����:	�Q�[�����̍X�V����
*******************************************************************************/
void UpdateInformation(void)
{
	return;
}

/*******************************************************************************
�֐���:	void DrawInformation(void)
����:	void
�߂�l:	void
����:	�Q�[�����̕`�揈��
*******************************************************************************/
void DrawInformation(void)
{
	int i = 0;
	int X = 0;
	int Length = 0;	// �z��̒���
	char *DrawPostion = GetBGAdr(0, 0);
	PLAYER *Player = GetPlayerAdr();
	// �Q�[�����̔z��
	char InfoTable[InfoTable_Height][InfoTable_Width] = {};

	if (Player->InStore == false)
	{
		switch (Player->InfoPage)
		{
			// �L������(1)
		case Symbol_p1:
			strcpy(&InfoTable[0][0], "(F)�� �L������(1) ��(G)");
			strcpy(&InfoTable[2][0], "�@�`�I�F�eLv.�����X�^�[     ��A���F�K�i    ");
			strcpy(&InfoTable[3][0], "���FHP�|�[�V����      �`�FATKUP   �r�FAGIUP ");
			strcpy(&InfoTable[4][0], "���FHP�n�C�|�[�V����  �c�FDEFUP   �j�F���̌�");
			break;
			// �L������(2)
		case Symbol_p2:
			strcpy(&InfoTable[0][0], "(F)�� �L������(2) ��(G)");
			strcpy(&InfoTable[2][0], "���F���X       �V�F����������               ");
			strcpy(&InfoTable[3][0], "���F���̑���   �Z�F�h��̑���               ");
			strcpy(&InfoTable[4][0], "�l�F�}�b�v     �}�F�����}��     ���F�]���̗�");
			break;
			// �����ƃA�C�e��
		case PlayerItem:
			strcpy(&InfoTable[0][0], "(F)�� �����ƃA�C�e�� ��(G)");
			strcpy(&InfoTable[1][0], "     ����                      �M�d�A�C�e��     ");
			if (Player->Item.FloorMap == true)
			{
				strcpy(&InfoTable[2][0], "                          �}�b�v");
			}
			else
			{
				strcpy(&InfoTable[2][0], "                          �H�H�H");
			}
			if (Player->Item.EnemyDictionary == true)
			{
				sprintf(&InfoTable[3][0], "����F%-16s         �����}��      ", &Player->Item.Sword[0]);
			}
			else
			{
				sprintf(&InfoTable[3][0], "����F%-16s          �H�H�H      ", &Player->Item.Sword[0]);
			}
			if (Player->Item.TeleportWing == true)
			{
				sprintf(&InfoTable[4][0], "�h��F%-16s         �]���̗�      ", &Player->Item.Armor[0]);
			}
			else
			{
				sprintf(&InfoTable[4][0], "�h��F%-16s          �H�H�H      ", &Player->Item.Armor[0]);
			}
			break;
			// �Q�[���̐���
		case GameHelp:
			strcpy(&InfoTable[0][0], "(F)�� �Q�[���̐��� ��(G)");
			strcpy(&InfoTable[2][0], "�ړ��FW,A,S,D              �ꎞ��~�FP");
			strcpy(&InfoTable[3][0], "�Q�[���I���FESC            �w���v�FH  ");
			if (Player->Item.EnemyDictionary == true && Player->Item.TeleportWing == true)
			{
				strcpy(&InfoTable[4][0], "�����}�ӁFE                �]���̗��FT");
			}
			else if (Player->Item.EnemyDictionary == true && Player->Item.TeleportWing == false)
			{
				strcpy(&InfoTable[4][0], "�����}�ӁFE                           ");
			}
			else if (Player->Item.EnemyDictionary == false && Player->Item.TeleportWing == true)
			{
				strcpy(&InfoTable[4][0], "�]���̗��FT                           ");
			}
			break;
		default:
			break;
		}

		// �w�i�Ƀe�[�u����`��
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
�֐���:	void UninitInformation(void)
����:	void
�߂�l:	void
����:	�Q�[�����̏I������
*******************************************************************************/
void UninitInformation(void)
{
	return;
}