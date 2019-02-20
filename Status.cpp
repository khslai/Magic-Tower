/*******************************************************************************
* �^�C�g��:		�v���C���[�X�e�[�^�X�v���O����
* �v���O������:	Status.cpp
* �쐬��:		GP11B341 35 ���M��
* �쐬��:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "Status.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define Status_Height (23)		// �v���C���[�X�e�[�^�X�z��̍���
#define Status_Width (25)		// �v���C���[�X�e�[�^�X�z��̉���
#define StatusStart_X (52)		// �v���C���[�X�e�[�^�X�`����W
#define StatusStart_Y (1)

// Player Status���X�V����Ƃ��̈ʒu
#define Level_EXPColumn (9)
#define HP_MPColumn (11)
#define ATKColumn (13)
#define DEFColumn (15)
#define AGIColumn (17)
#define MoneyColumn (19)
#define DoorKeyColumn (21)
/*******************************************************************************
* �\���̒�`
*******************************************************************************/


/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/


/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
// �v���C���[�X�e�[�^�X�̔z��
char Status[Status_Height][Status_Width] = {
	"                        ",		// 0
	"       i�O�Rry/`�R�A    ",		// 1
	"       ,'�M��ށM�R'     ",		// 2
	"      �k(ɔ��ɂki�r     ",		// 3
	"      il�߃��[ill��     ",		// 4
	"       �i` сL�v,��     ",		// 5
	"     �q�^i.T�R�S�_�r    ",		// 6
	"      �''��_�_��]�J     ",		// 7
	"",								// 8
	"",								// 9
	"",								// 10
	"",								// 11
	"",								// 12
	"",								// 13
	"",								// 14
	"",								// 15
	"",								// 16
	"",								// 17
	"",								// 18
	"",								// 19
	"",								// 20
	"",								// 21
	"",								// 22
};


/*******************************************************************************
�֐���:	void InitStatus(void)
����:	void
�߂�l:	void
����:	�v���C���[�X�e�[�^�X�̏���������
*******************************************************************************/
void InitStatus(void)
{
	return;
}

/*******************************************************************************
�֐���:	void UpdateStatus(void)
����:	void
�߂�l:	void
����:	�v���C���[�X�e�[�^�X�̍X�V����
*******************************************************************************/
void UpdateStatus(void)
{
	return;
}

/*******************************************************************************
�֐���:	void DrawStatus(void)
����:	void
�߂�l:	void
����:	�v���C���[�X�e�[�^�X�̕`�揈��
*******************************************************************************/
void DrawStatus(void)
{
	int i = 0;
	int X = 0;
	int Length = 0;
	char *DrawPostion = GetBGAdr(0, 0);
	PLAYER *Player = GetPlayerAdr();

	// �v���C���[�̃X�e�[�^�X�X�V
	sprintf(&Status[Level_EXPColumn][0], "Lv.%-3d EXP�F%-3d", Player->Status.Level, Player->Status.EXP);
	sprintf(&Status[HP_MPColumn][0], "HP�F%-5d MP�F%d", Player->Status.HP, Player->Status.MP);
	sprintf(&Status[ATKColumn][0], "ATK�F%-3d", Player->Status.ATK);
	sprintf(&Status[DEFColumn][0], "DEF�F%-3d", Player->Status.DEF);
	sprintf(&Status[AGIColumn][0], "AGI�F%-3d", Player->Status.AGI);
	sprintf(&Status[MoneyColumn][0], "�������F$%-3d", Player->Status.Money);
	sprintf(&Status[DoorKeyColumn][0], "���̌� x %-3d", Player->Item.DoorKey);

	/* �v���C���[�X�e�[�^�X�`�揈�� */
	// �}�`�̎n�_��(52,1)
	// (Status_ptr + i * Status_Width + 0) = &Status_ptr[i][0]
	// *(Status_ptr + i * Status_Width + 0) = Status_ptr[i][0]
	for (i = 0; i < Status_Height; i++)
	{
		if (Status[i][0] == NULL)
		{
			continue;
		}
		else
		{
			Length = strlen(&Status[i][0]);
			X = (Status_Width - Length) / 2;
			DrawPostion = GetBGAdr(StatusStart_X + X, StatusStart_Y + i);
			strncpy(DrawPostion, &Status[i][0], Length);
		}
	}
	return;
}

/*******************************************************************************
�֐���:	void UninitStatus(void)
����:	void
�߂�l:	void
����:	�v���C���[�X�e�[�^�X�̏I������
*******************************************************************************/
void UninitStatus(void)
{
	return;
}