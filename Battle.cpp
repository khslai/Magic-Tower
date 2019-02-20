/*******************************************************************************
* �^�C�g��:		�o�g���v���O����
* �v���O������:	Battle.cpp
* �쐬��:		GP11B341 35 ���M��
* �쐬��:		2018/06/29
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "Battle.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/

#define EnemyStart_X (3)		// �G�l�~�[�`����W
#define EnemyStart_Y (1)
#define PlayerStart_X (53)		// �v���C���[�`����W
#define PlayerStart_Y (1)
#define EnemyStatus_X (3)		// �G�l�~�[�X�e�[�^�X�`����W
#define EnemyStatus_Y (18)
#define PlayerStatus_X (53)		// �v���C���[�X�e�[�^�X�`����W
#define PlayerStatus_Y (18)
#define EstimateDamage_X (30)	// �\�z�_���[�W�`����W
#define EstimateDamage_Y (18)
#define EffectStart_X (10)		// �_���[�W�G�t�F�N�g�`����W
#define EffectStart_Y (7)
#define MessageStart_X (3)		// ���b�Z�[�W�`����W
#define MessageStart_Y (10)

#define Array_Height (16)		// �v���C���[�A�G�l�~�[�`��z��
#define Array_Width (40)		
#define StatusArr_Height (6)	// �v���C���[�A�G�l�~�[�̃X�e�[�^�X�̕`��z��
#define StatusArr_Width (27)
#define DamageArr_Height (6)	// �\�z�_���[�W�`��z��
#define DamageArr_Width (20)
#define EffectArr_Height (5)	// �_���[�W�G�t�F�N�g�`��z��
#define EffectArr_Width (25)
#define Message_Height (7)		// ���b�Z�[�W�`��z��
#define Message_Width (75)	

#define CriticalCheck (19)		// ���̐����ȏ�Ȃ�N���e�B�J���q�b�g
#define MissCheck (1)			// ���̐����ȉ��Ȃ�U���~�X
#define DryadHealHP (10)		// �؂̐�����񕜂�HP���l

// �^�[���t�F�C�X�ԍ�
enum Phase_No
{
	BeginningPhase = 0,
	SkillPhase,
	PlayerPhase,
	EnemyPhase,
	EndPhase,
};

// �U����������
enum AttackResult
{
	Miss = 0,
	NormalAttack,
	CriticalHit,
};

/*******************************************************************************
* �\���̒�`
*******************************************************************************/


/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
void DrawSkill(void);


/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
ENEMY Enemy;
int TurnPhase = 0;
int AttackResult = 0;

/*******************************************************************************
�֐���:	bool BattleEvent(int Enemy_No)
����:	int Enemy_No
�߂�l:	bool
����:	�o�g���C�x���g���[�v
*******************************************************************************/
bool BattleEvent(int Enemy_No)
{
	PLAYER *Player = GetPlayerAdr();
	bool KillEnemy = false;
	Enemy.Number = Enemy_No;

	// �o�g��������
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
			// �P��
			else if (Player->HitKey == 'q')
			{
				break;
			}
		}

		// �o�g���X�V
		UpdateBattle();

		// �o�g���`��
		DrawBattle();

		// �o�g���I��
		if (TurnPhase == EndPhase)
		{
			// �G�l�~�[���񂾂�
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
�֐���:	void InitBattle(void)
����:	void
�߂�l:	void
����:	�o�g���̏���������
*******************************************************************************/
void InitBattle(void)
{
	TurnPhase = BeginningPhase;
	// �G�l�~�[�̃X�e�[�^�X�ݒ�
	switch (Enemy.Number)
	{
	case Slime:
		strcpy(&Enemy.name[0], "�X���C��");
		strcpy(&Enemy.Ability[0], "�Ȃ�");
		Enemy.HP = SlimeHP;
		Enemy.ATK = SlimeATK;
		Enemy.DEF = SlimeDEF;
		Enemy.AGI = SlimeAGI;
		Enemy.EXP = SlimeEXP;
		Enemy.Money = SlimeMoney;
		break;
	case Archer:
		strcpy(&Enemy.name[0], "�A�[�`���[");
		strcpy(&Enemy.Ability[0], "�Ȃ�");
		Enemy.HP = ArcherHP;
		Enemy.ATK = ArcherATK;
		Enemy.DEF = ArcherDEF;
		Enemy.AGI = ArcherAGI;
		Enemy.EXP = ArcherEXP;
		Enemy.Money = ArcherMoney;
		break;
	case SlimeKnight:
		strcpy(&Enemy.name[0], "�X���C���i�C�g");
		strcpy(&Enemy.Ability[0], "�Ȃ�");
		Enemy.HP = SlimeKnightHP;
		Enemy.ATK = SlimeKnightATK;
		Enemy.DEF = SlimeKnightDEF;
		Enemy.AGI = SlimeKnightAGI;
		Enemy.EXP = SlimeKnightEXP;
		Enemy.Money = SlimeKnightMoney;
		break;
	case Tiger:
		strcpy(&Enemy.name[0], "�T�[�x���^�C�K�[");
		strcpy(&Enemy.Ability[0], "���U��");
		Enemy.HP = TigerHP;
		Enemy.ATK = TigerATK;
		Enemy.DEF = TigerDEF;
		Enemy.AGI = TigerAGI;
		Enemy.EXP = TigerEXP;
		Enemy.Money = TigerMoney;
		break;
	case Magician:
		strcpy(&Enemy.name[0], "���@�g��");
		strcpy(&Enemy.Ability[0], "�h��͖���");
		Enemy.HP = MagicianHP;
		Enemy.ATK = MagicianATK;
		Enemy.DEF = MagicianDEF;
		Enemy.AGI = MagicianAGI;
		Enemy.EXP = MagicianEXP;
		Enemy.Money = MagicianMoney;
		break;
	case GhostArmor:
		strcpy(&Enemy.name[0], "�S��̊Z");
		strcpy(&Enemy.Ability[0], "�Ȃ�");
		Enemy.HP = GhostArmorHP;
		Enemy.ATK = GhostArmorATK;
		Enemy.DEF = GhostArmorDEF;
		Enemy.AGI = GhostArmorAGI;
		Enemy.EXP = GhostArmorEXP;
		Enemy.Money = GhostArmorMoney;
		break;
	case Phantom:
		strcpy(&Enemy.name[0], "�t�@���g��");
		strcpy(&Enemy.Ability[0], "��𗦏㏸");
		Enemy.HP = PhantomHP;
		Enemy.ATK = PhantomATK;
		Enemy.DEF = PhantomDEF;
		Enemy.AGI = PhantomAGI;
		Enemy.EXP = PhantomEXP;
		Enemy.Money = PhantomMoney;
		break;
	case SlimeKing:
		strcpy(&Enemy.name[0], "�L���O�X���C��");
		strcpy(&Enemy.Ability[0], "�Ȃ�");
		Enemy.HP = SlimeKingHP;
		Enemy.ATK = SlimeKingATK;
		Enemy.DEF = SlimeKingDEF;
		Enemy.AGI = SlimeKingAGI;
		Enemy.EXP = SlimeKingEXP;
		Enemy.Money = SlimeKingMoney;
		break;
	case Dryad:
		strcpy(&Enemy.name[0], "�؂̐�");
		strcpy(&Enemy.Ability[0], "HP��");
		Enemy.HP = DryadHP;
		Enemy.ATK = DryadATK;
		Enemy.DEF = DryadDEF;
		Enemy.AGI = DryadAGI;
		Enemy.EXP = DryadEXP;
		Enemy.Money = DryadMoney;
		break;
	case Cyclops:
		strcpy(&Enemy.name[0], "�T�C�N���v�X");
		strcpy(&Enemy.Ability[0], "�Ȃ�");
		Enemy.HP = CyclopsHP;
		Enemy.ATK = CyclopsATK;
		Enemy.DEF = CyclopsDEF;
		Enemy.AGI = CyclopsAGI;
		Enemy.EXP = CyclopsEXP;
		Enemy.Money = CyclopsMoney;
		break;
	case Boss:
		strcpy(&Enemy.name[0], "���̎x�z��");
		strcpy(&Enemy.Ability[0], "���@�o���A");
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
�֐���:	void UpdateBattle(void)
����:	void
�߂�l:	void
����:	�o�g���̍X�V����
*******************************************************************************/
void UpdateBattle(void)
{
	int Damage = 0;	// �U���_���[�W
	PLAYER *Player = GetPlayerAdr();
	int AttackCheck = 0;		// �U�����ʔ���
	int AGIDifference = 0;		// �v���C���[�A�G�l�~�[��AGI���̒l

	// �v���C���[�̃^�[��
	if (TurnPhase == PlayerPhase)
	{
		AGIDifference = Player->Status.AGI - Enemy.AGI;
		AGIDifference = AGIDifference >= 10 ? 10 : AGIDifference;
		// �U�����ʔ���
		AttackCheck = rand() % (20 + 1) + AGIDifference;
		// �_���[�W�v�Z
		Damage = Player->Status.ATK - Enemy.DEF;
		Damage = Damage <= 0 ? 0 : Damage;
		// ���ʍU��
		AttackResult = NormalAttack;
		// �N���e�B�J���q�b�g
		if (AttackCheck > CriticalCheck)
		{
			Damage = Damage * 2;
			AttackResult = CriticalHit;
		}
		// �~�X
		else if (AttackCheck < MissCheck)
		{
			Damage = 0;
			AttackResult = Miss;
		}
		// �{�X��͓��ꏈ���A�܂��̓o���A�󂳂Ȃ���΂Ȃ�Ȃ�
		if (Player->InBossBattle == false || Enemy.BossBarrier <= 0)
		{
			Enemy.HP -= Damage;
		}
		// ��ʐ퓬
		else
		{
			Enemy.BossBarrier -= Damage;
		}
	}
	// �G�l�~�[�̃^�[��
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
�֐���:	void DrawBattle(void)
����:	void
�߂�l:	void
����:	�o�g���̕`�揈��
*******************************************************************************/
void DrawBattle(void)
{
	int i = 0, j = 0;	// for���[�v�v�Z�p
	int X = 0, Y = 0;	// ���b�Z�[�W�����p
	int Length = 0;		// �z��̒������L�^����
	int Column = 0;		// ���b�Z�[�W�̍s�����L�^����
	int Distance = 0;	// �v���C���[�ƃG�l�~�[�Ԃ̋���(�_���[�W�G�t�F�N�g�ʒu���C�����邽��)
	int EstimateDamage = 0;	// �\�z�_���[�W
	static bool SecondAttack = false;	// ���U���̔��f
	static bool UseSkill = false;		// �X�L���g�p�ς�
	static bool DestoryBarrier = false;	// �{�X�̃o���A�j��ς�
	static bool BarrierEvent = false;	// �o���A�����ς�
	PLAYER *Player = GetPlayerAdr();
	// �o�g���w�i
	char BattleBG[Console_Height][Console_Width] = {
		"  �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q\n",
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
		"  |�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P|\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                          |\n",
		"  |                                                                   �P��(Q)|\n",
		"  �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P",
	};
	// �G�l�~�[�`��p�z��
	char EnemyArray[Array_Height][Array_Width] = {};
	// �v���C���[�`��p�z��
	char PlayerArray[Array_Height][Array_Width] = {};
	// �X�e�[�^�X�`��p�z��
	char StatusArray[StatusArr_Height][StatusArr_Width] = {};
	// �_���[�W�G�t�F�N�g�`��p�z��
	char EffectArray[EffectArr_Height][EffectArr_Width] = {};
	// �\�z�_���[�W�`��p�z��
	char DamageArray[DamageArr_Height][DamageArr_Width] = {
		"                   ",
		"                   ",
		"                   ",
		"                   ",
		"                   ",
		"                   ",
	};
	// ���b�Z�[�W�`��p�z��
	char Message[Message_Height][Message_Width] = {
		"--------------------------------------------------------------------------",
		"                                                                          ",
		"                                                                          ",
		"                                                                          ",
		"                                                                          ",
		"                                                                          ",
		"--------------------------------------------------------------------------",
	};


	// ��ʃN���A
	system("cls");

	// =============================================================
	// ========================�G�l�~�[�̕`��========================
	// =============================================================
	switch (Enemy.Number)
	{
	case Slime:
		strcpy(&EnemyArray[0][0], "         ����,            ");
		strcpy(&EnemyArray[1][0], "�@    �@ �:::��           ");
		strcpy(&EnemyArray[2][0], "�@�@,�[�Q:::::�Q�[�       ");
		strcpy(&EnemyArray[3][0], "�@�^/) (�E) (�E):::��     ");
		strcpy(&EnemyArray[4][0], "`�b�t (~�R�Q_�^~):::�b    ");
		strcpy(&EnemyArray[5][0], "�@�_�� �_�Q�Q_�^:::�^     ");
		strcpy(&EnemyArray[6][0], "�@�@`�[�[�[�[�[�[-��      ");
		break;
	case Archer:
		strcpy(&EnemyArray[0][0], "�@�@ �^�܁_             ");
		strcpy(&EnemyArray[1][0], "�@�@/ �Q�Q_)�@�^(       ");
		strcpy(&EnemyArray[2][0], "�@ ( (�L��`)�^�@|)      ");
		strcpy(&EnemyArray[3][0], "�@�@) _]�������O��    ");
		strcpy(&EnemyArray[4][0], "�@ /�@ �[ _>�_�@|)      ");
		strcpy(&EnemyArray[5][0], "�@(_���[��_)�@�_(       ");
		break;
	case SlimeKnight:
		strcpy(&EnemyArray[0][0], "�@   �@�@�c�l\"'�R�@�@�@/i          ");
		strcpy(&EnemyArray[1][0], "�@   �@�@{[i]��O}�@  //           ");
		strcpy(&EnemyArray[2][0], "�@   �@�u�P ~l�@j,j�A//            ");
		strcpy(&EnemyArray[3][0], "�@   �@ �R_,�m_�@}  O`             ");
		strcpy(&EnemyArray[4][0], "�@�@    ,'�@U�@�R>�R               ");
		strcpy(&EnemyArray[5][0], "�i�i�i {�@�@�E�́E}                ");
		strcpy(&EnemyArray[6][0], "�@�@    `�[----�'�f                ");
		break;
	case Tiger:
		strcpy(&EnemyArray[0][0], "   �@ �@ �@ �Мc�~�_, --�_     ");
		strcpy(&EnemyArray[1][0], "�@�@�@�@ �@ �@ �@ ް-�]�]�_ �_   ");
		strcpy(&EnemyArray[2][0], "�@�@�@�@�@�@ ,, ��@ , --�__,)�@�j");
		strcpy(&EnemyArray[3][0], " �@�@�@�@, -'�@l �M�'-f�@ �R _/  ");
		strcpy(&EnemyArray[4][0], "  �@ �@ /�@�@ _ _�@�@ l�@�@ f    ");
		strcpy(&EnemyArray[5][0], "�@�@�@/ , -�]'�@ ް-�.!�Ml�@l    ");
		strcpy(&EnemyArray[6][0], "�@�@ /�@r(^��E�E''^)� ��i�@l     ");
		strcpy(&EnemyArray[7][0], " �@ /�@ t_|�M!::i�L|_t\" �R l�    ");
		strcpy(&EnemyArray[8][0], "�@ i �@ / |/�::�R|  �R   l-��R   ");
		strcpy(&EnemyArray[9][0], ", -'�@ � �@l��',l    l   Ĥ �N   ");
		strcpy(&EnemyArray[10][0], "���^t^ށT�@�@�P�@�@  <_�_Y_l�T   ");
		break;
	case Magician:
		strcpy(&EnemyArray[0][0], "�@�@�@�@--�~              ");
		strcpy(&EnemyArray[1][0], "�@ .: :::::::�M:..�A      ");
		strcpy(&EnemyArray[2][0], "  /::/:::::::::   �R      ");
		strcpy(&EnemyArray[3][0], " ':;�:::::::::_:_::}      ");
		strcpy(&EnemyArray[4][0], " : /�@�:::::  ��o�{       ");
		strcpy(&EnemyArray[5][0], " �A�@ �:::::::::V�l       ");
		strcpy(&EnemyArray[6][0], " ���@ l:::::�_  r�]́l    ");
		strcpy(&EnemyArray[7][0], "�M�  /ʰ::::::} �R�:!     ");
		strcpy(&EnemyArray[8][0], "�@�@� :�:::�B�Ll:��:j     ");
		strcpy(&EnemyArray[9][0], " __�|::_  ��_�m:_:�(      ");
		strcpy(&EnemyArray[10][0], "�@�[=� :_:_:_:_:_:_�c     ");
		break;
	case GhostArmor:
		strcpy(&EnemyArray[0][0], "   �@�@���R(�R               ");
		strcpy(&EnemyArray[1][0], "   �@�@�_�U�R|               ");
		strcpy(&EnemyArray[2][0], "   �@�@�˃����P�R_           ");
		strcpy(&EnemyArray[3][0], "   �@�@`�L �""�J�Q�T           ");
		strcpy(&EnemyArray[4][0], "   ���܁R�m�@�f�IIII)�^/     ");
		strcpy(&EnemyArray[5][0], "   /�@\"���R�m�S::::�^�^�R    ");
		strcpy(&EnemyArray[6][0], "   �_�Q�Q�`�R_�jƁ^�ځT::    ");
		strcpy(&EnemyArray[7][0], "   `/�Q/:.�� .:�^�^|L_L|:    ");
		strcpy(&EnemyArray[8][0], "   `�_�P�_�Q��ځڤ�m((uE}    ");
		strcpy(&EnemyArray[9][0], "   �@ �_��/L�~}�PT�b:::::    ");
		strcpy(&EnemyArray[10][0], "   �@�@ `Ɓځ^�\�L)�S:::�    ");
		strcpy(&EnemyArray[11][0], "   �@�@/���R���@���R`�P      ");
		strcpy(&EnemyArray[12][0], "   �@ /�@`-|`�P^�RɁP�R      ");
		strcpy(&EnemyArray[13][0], "   �@/�@\"��|�@�@ | ��\"|      ");
		strcpy(&EnemyArray[14][0], "   �^�܁R�Q|�@�@ | ���P�R    ");
		strcpy(&EnemyArray[15][0], "   �M�\�\�L�@�@�@ �M�P�P     ");
		break;
	case Phantom:
		strcpy(&EnemyArray[0][0], "�@�@�@�@ , -- �A             ");
		strcpy(&EnemyArray[1][0], "�@�@�@ �::;;;::�R            ");
		strcpy(&EnemyArray[2][0], "�@�@�@�m::�{�{::�R           ");
		strcpy(&EnemyArray[3][0], "�@ �^:::;;;;;;:::l           ");
		strcpy(&EnemyArray[4][0], "�@ |::;;:::;;;::::l          ");
		strcpy(&EnemyArray[5][0], "  /:;:,�:::;;:::r-�:;�       ");
		strcpy(&EnemyArray[6][0], " /:;:/�T::::::::|�@ �T:;�R   ");
		strcpy(&EnemyArray[7][0], "l:;:/�@�@�R::::::�R �M��'    ");
		strcpy(&EnemyArray[8][0], "|:;�T�@�@�@�R:::::::l        ");
		strcpy(&EnemyArray[9][0], " ^�@�@�@�@�@ �R-:::::�R      ");
		strcpy(&EnemyArray[10][0], "�@ �@�@�@�@�@�@�@ ~l::|      ");
		strcpy(&EnemyArray[11][0], " �@ �@�@�@�@�@�@�@�@Ƀm      ");
		strcpy(&EnemyArray[12][0], " �@�@�@�@�@�@�@�@ ��'        ");
		break;
	case SlimeKing:
		strcpy(&EnemyArray[0][0], "�@�@�@�@�@/�            ");
		strcpy(&EnemyArray[1][0], "�@�@�@�@�@||            ");
		strcpy(&EnemyArray[2][0], "�@�@�@ �^�j�j�_        ");
		strcpy(&EnemyArray[3][0], "�@�@ �Q�\�\�\�\�Q       ");
		strcpy(&EnemyArray[4][0], "�@ �_�Ɂ_�^�_�^�Ɂ^     ");
		strcpy(&EnemyArray[5][0], "�@�@�_�Q�Q�Q�Q�Q�^      ");
		strcpy(&EnemyArray[6][0], "�@�@�^�PƁP�PƁP�_      ");
		strcpy(&EnemyArray[7][0], ".�^�@�@(�)�@(�)�@�@�_   ");
		strcpy(&EnemyArray[8][0], "|�@�@�R�_�@�@_,���@�@|  ");
		strcpy(&EnemyArray[9][0], "(�@�@�m -�j�j- ́@�@ )  ");
		strcpy(&EnemyArray[10][0], "|�@�@�@�@�@�@�@�@�@�@|  ");
		strcpy(&EnemyArray[11][0], ".�_�@�@�@�@�@�@�@�@�^   ");
		strcpy(&EnemyArray[12][0], "�@�@�_�Q�Q�Q�Q�Q�^      ");
		break;
	case Dryad:
		strcpy(&EnemyArray[0][0], "�R�@�@�@�@�@�@,r ^= �=-� ,        ");
		strcpy(&EnemyArray[1][0], " ||�@�@�@ /` '�@�Rr�]�,_.�R�,     ");
		strcpy(&EnemyArray[2][0], " �S ��@__j�@  __�@ �@�@�@ �'1     ");
		strcpy(&EnemyArray[3][0], "�@ �_~�@�@ �@ |::�_.._�@�@ r1     ");
		strcpy(&EnemyArray[4][0], "�@�@�@`���@�@ |:::�@::|�@r'\":/ �  ");
		strcpy(&EnemyArray[5][0], "�@�@�@�@�@`i �@�R::.../�@�R;j ,j! ");
		strcpy(&EnemyArray[6][0], "�@�@�@�@�@ j�@ �@ �P�@�@   `�'�   ");
		strcpy(&EnemyArray[7][0], "�@�@�@�@�@/�@�@,r�r�\�\v'�L|-'    ");
		strcpy(&EnemyArray[8][0], "�@�@�@�@/�@�@ �R�@_r-�\v(         ");
		strcpy(&EnemyArray[9][0], "�@r�\�]'�@�@�@ `' �@ �@ !_        ");
		strcpy(&EnemyArray[10][0], "��r�_.�@ /�@�@�@�@ �@ �@  `��     ");
		strcpy(&EnemyArray[11][0], "�@�@�@��'�@�@�@,��@� �@,i�\'�P`   ");
		strcpy(&EnemyArray[12][0], "  _- ''  �Q �m  �R�R  �R�         ");
		strcpy(&EnemyArray[13][0], "�i�@<�P�P�@�@�@ �@�Rj`�[��R       ");
		strcpy(&EnemyArray[14][0], " �R !�@�@�@�@�@�@�@�@�@�@�R!      ");
		strcpy(&EnemyArray[15][0], "�@ `'                             ");
		break;
	case Cyclops:
		strcpy(&EnemyArray[0][0], "�@�@�@�@�@  A�@�@�@�@,(_c�O)�A");
		strcpy(&EnemyArray[1][0], "�@�@�@�@��/���R�� _,-t;li /|| ");
		strcpy(&EnemyArray[2][0], "�@ _,.--�U�F���F�'\"  | // i/  ");
		strcpy(&EnemyArray[3][0], " �i���� l `�[�]'\" ,l� |l `;/  ");
		strcpy(&EnemyArray[4][0], "�@/�S�F���R`�A__,.�`�� |l l�  ");
		strcpy(&EnemyArray[5][0], "�@�R �S�恈�R�A�@/�@(r'��l_l  ");
		strcpy(&EnemyArray[6][0], "�@�@�r lƃj���j�l  |`(�Q,. |  ");
		strcpy(&EnemyArray[7][0], ",.�w,< ��-�j-��R  `J(__,./   ");
		strcpy(&EnemyArray[8][0], "( ��`^'WwwwwwW'^�q�@ >ri�]\"   ");
		strcpy(&EnemyArray[9][0], "(~`�--�,�j�@�R,�@�@�j`'\"      ");
		strcpy(&EnemyArray[10][0], "(~'�S.. �R�@��^�@ �m          ");
		strcpy(&EnemyArray[11][0], "`-'�[- �_Ɂ@ �R '\"�~          ");
		strcpy(&EnemyArray[12][0], "�@�@�@�@�@�@  `�S`            ");
		break;
	case Boss:
		strcpy(&EnemyArray[0][0], " �@ �@  ,. --�]- .�A         ");
		strcpy(&EnemyArray[1][0], "�@    �^.:.:.:.:.:.�_        ");
		strcpy(&EnemyArray[2][0], "     /:.:.:.:.:.:.:.:�       ");
		strcpy(&EnemyArray[3][0], "    '.:{:.:./l.:/�R�A:'      ");
		strcpy(&EnemyArray[4][0], "   l:.:�Rr����' ���u:.:l     ");
		strcpy(&EnemyArray[5][0], "  ��:.:.:)l��@�@l�).:.:��    ");
		strcpy(&EnemyArray[6][0], "�i::�:.: �l   �  �l:.:(::)   ");
		strcpy(&EnemyArray[7][0], "  �R: : : :��r��� : ::�V     ");
		strcpy(&EnemyArray[8][0], "  �. : : ;<l:��:!>: ::�l     ");
		strcpy(&EnemyArray[9][0], "�i r'�R�^yl:l�wl:!x�_r�R�j   ");
		strcpy(&EnemyArray[10][0], "  �@ �e��^ /   �� �_��f      ");
		strcpy(&EnemyArray[11][0], " �@ �@ <�MT��    T�L>        ");
		strcpy(&EnemyArray[12][0], "�@�@�@  �M�N TTT �N�L        ");
		strcpy(&EnemyArray[13][0], "�@�@�@�@    �M�L             ");
		break;
	default:
		break;
	}

	// �s���̌v�Z
	for (Column = 0; EnemyArray[Column][0] != NULL && Column <= Array_Height; Column++)
	{
		;
	}
	// Y = EnemyArray�ォ�牺�܂ł̐^��
	Y = (Array_Height - Column) / 2;
	for (i = 0; i < Array_Height && EnemyArray[i][0] != NULL; i++)
	{
		// X = EnemyArray������E�܂ł̐^��
		Length = strlen(&EnemyArray[i][0]);
		X = (Array_Width - Length) / 2;
		strncpy(&BattleBG[EnemyStart_Y + Y + i][EnemyStart_X + X], EnemyArray[i], Length);
	}

	// ===============================================================
	// ========================�v���C���[�̕`��========================
	// ===============================================================
	strcpy(&PlayerArray[0][0], "  i�O�Rry/`�R�A    ");
	strcpy(&PlayerArray[1][0], "  ,'�M��ށM�R'     ");
	strcpy(&PlayerArray[2][0], " �k(ɔ��ɂki�r     ");
	strcpy(&PlayerArray[3][0], " il�߃��[ill��     ");
	strcpy(&PlayerArray[4][0], "  �i` сL�v,��     ");
	strcpy(&PlayerArray[5][0], "�q�^i.T�R�S�_�r    ");
	strcpy(&PlayerArray[6][0], "�''��_�_��]�J     ");

	// �s���̌v�Z
	for (Column = 0; PlayerArray[Column][0] != NULL && Column <= Array_Height; Column++)
	{
		;
	}
	// Y = PlayerArray�ォ�牺�܂ł̐^��
	Y = (Array_Height - Column) / 2;
	for (i = 0; i < Array_Height && PlayerArray[i][0] != NULL; i++)
	{
		Length = strlen(&PlayerArray[i][0]);
		strncpy(&BattleBG[PlayerStart_Y + Y + i][PlayerStart_X], PlayerArray[i], Length);
	}

	// ====================================================================
	// ========================�G�l�~�[�X�e�[�^�X�̕`��======================
	// ====================================================================
	sprintf(&StatusArray[0][0], "      %s", &Enemy.name[0]);
	sprintf(&StatusArray[1][0], "      HP�F%d", Enemy.HP);
	sprintf(&StatusArray[2][0], "      ATK�F%d", Enemy.ATK);
	sprintf(&StatusArray[3][0], "      DEF�F%d", Enemy.DEF);
	sprintf(&StatusArray[4][0], "      AGI�F%d", Enemy.AGI);
	sprintf(&StatusArray[5][0], "      ����\�́F%s", &Enemy.Ability[0]);
	for (i = 0; i < StatusArr_Height && StatusArray[i][0] != NULL; i++)
	{
		Length = strlen(&StatusArray[i][0]);
		X = (StatusArr_Width - Length) / 2;
		strncpy(&BattleBG[EnemyStatus_Y + i][EnemyStatus_X + X], StatusArray[i], Length);
	}

	// ====================================================================
	// ==========================�_���[�W�\�z�̕`��=========================
	// ====================================================================
	if (TurnPhase != BeginningPhase && TurnPhase != SkillPhase)
	{
		// �v���C���[
		if (TurnPhase == PlayerPhase || (TurnPhase == EndPhase && Player->Status.HP > 0))
		{
			EstimateDamage = Player->Status.ATK - Enemy.DEF;
			sprintf(&DamageArray[3][0], "<-----------------");
		}
		// �G�l�~�[
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
			sprintf(&DamageArray[2][0], "�U���~�X");
		}
		else
		{
			if (AttackResult == CriticalHit)
			{
				sprintf(&DamageArray[1][0], "Critical Hit�I");
				EstimateDamage = EstimateDamage * 2;
			}
			if (Player->InBossBattle && TurnPhase == PlayerPhase && DestoryBarrier == false)
			{
				EstimateDamage = 0;
			}
			sprintf(&DamageArray[2][0], "�_���[�W�F%d�_", EstimateDamage);
		}
		// �`��
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
	// =======================�_���[�W�G�t�F�N�g�̕`��=======================
	// ====================================================================
	if (TurnPhase != BeginningPhase && TurnPhase != SkillPhase && AttackResult != Miss)
	{
		if (AttackResult == NormalAttack)
		{
			strcpy(&EffectArray[0][0], " �_ ,,_�l��m�R ");
			strcpy(&EffectArray[1][0], "  )�R�@�@�@�i  ");
			strcpy(&EffectArray[2][0], "���@�@�@�@�@ ��");
			strcpy(&EffectArray[3][0], "  )�@�@�@�@��  ");
			strcpy(&EffectArray[4][0], " �^^��`Y�L^�_  ");
		}
		else if (AttackResult == CriticalHit)
		{
			strcpy(&EffectArray[0][0], "  �@�@� �@ ɁS        ");
			strcpy(&EffectArray[1][0], "�@�@�@)�R/�@ �R��|�m�L");
			strcpy(&EffectArray[2][0], "=����@�@�@      ��=");
			strcpy(&EffectArray[3][0], "�@�@�@)�@�@�@�@�@�i   ");
			strcpy(&EffectArray[4][0], "�@�@�@ '�L��`Y�L��` � ");
		}
		if (TurnPhase == PlayerPhase || (TurnPhase == EndPhase && Player->Status.HP > 0))
		{
			Distance = 0;
		}
		else if (TurnPhase == EnemyPhase || TurnPhase == EndPhase)
		{
			// �v���C���[�ƃG�l�~�[�Ԃ̋���
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
	// ========================�v���C���[�X�e�[�^�X�̕`��====================
	// ====================================================================
	sprintf(&StatusArray[0][0], "     �E��");
	sprintf(&StatusArray[1][0], "   HP�F%d", Player->Status.HP);
	sprintf(&StatusArray[2][0], "   MP�F%d", Player->Status.MP);
	sprintf(&StatusArray[3][0], "   ATK�F%d", Player->Status.ATK);
	sprintf(&StatusArray[4][0], "   DEF�F%d", Player->Status.DEF);
	sprintf(&StatusArray[5][0], "   AGI�F%d", Player->Status.AGI);
	for (i = 0; i < StatusArr_Height && StatusArray[i][0] != NULL; i++)
	{
		Length = strlen(&StatusArray[i][0]);
		strncpy(&BattleBG[PlayerStatus_Y + i][PlayerStatus_X], StatusArray[i], Length);
	}

	// ===========================================================
	// ========================���b�Z�[�W�̕`��====================
	// ===========================================================
	if (TurnPhase != PlayerPhase && TurnPhase != EnemyPhase)
	{
		// �^�[���t�F�C�X = �����t�F�C�X
		if (TurnPhase == BeginningPhase)
		{
			if (Player->Status.GetSkill == true)
			{
				if (Player->HitKey == 's' && Player->Status.MP <= 0)
				{
					strcpy(Message[2], "MP������Ȃ�");
					strcpy(Message[4], "����ɐ퓬�J�n����");
				}
				else if (Player->InBossBattle == false)
				{
					strcpy(Message[2], "�G�l�~�[�����ꂽ�I");
					strcpy(Message[4], "�퓬�J�n(Anykey) or �X�L��(S) or �P��(Q)");
				}
				else if (Player->InBossBattle == true)
				{
					strcpy(Message[2], "��̐l�����ꂽ�I");
					strcpy(Message[4], "�퓬�J�n(Anykey) or �X�L��(S)");
				}
			}
			else
			{
				if (Player->InBossBattle == false)
				{
					strcpy(Message[2], "�G�l�~�[�����ꂽ�I");
					strcpy(Message[4], "�퓬�J�n(Anykey) or �P��(Q)");
				}
				else
				{
					strcpy(Message[2], "��̐l�����ꂽ�I");
					strcpy(Message[4], "�퓬�J�n(Anykey)");
				}
			}
		}
		// �^�[���t�F�C�X = �X�L���t�F�C�X
		if (TurnPhase == SkillPhase)
		{
			if (UseSkill == false)
			{
				strcpy(Message[3], "�G�N�X�v���[�W�����I");
			}
			else if (UseSkill == true && Player->InBossBattle == true)
			{
				strcpy(Message[2], "����̖��@���g���Ă����̐l���|���Ȃ�              ");
				strcpy(Message[3], "���̐l�̎���Ƀo���A�݂����ȕ���Z���Ă���悤�ł�");
				strcpy(Message[4], "�ǂ�����ɂ��̃o���A�������Ȃ���΂����Ȃ�      ");
			}
		}
		// �^�[���t�F�C�X = �I���t�F�C�X
		if (TurnPhase == EndPhase)
		{
			// �퓬����
			if (Enemy.HP <= 0)
			{
				if (Player->InBossBattle == false)
				{
					strcpy(Message[2], "�퓬����");
					sprintf(Message[4], "%d�_�o���l �� $%d ����ɓ��ꂽ", Enemy.EXP, Enemy.Money);
					Player->Status.EXP += Enemy.EXP;
					Player->Status.Money += Enemy.Money;
				}

				else
				{
					strcpy(Message[2], "���߂łƂ��������܂��I");
					strcpy(Message[4], "���Ȃ��͂��̖��@�̓��̎x�z�҂�|����");
					Player->Event_No = GameClear;
				}
			}
			// �퓬����
			else
			{
				strcpy(Message[3], "���Ȃ��̓����X�^�[�ɓ|���ꂽ......");
				Player->Event_No = GameOver;
			}
			UseSkill = false;
		}

		// ���b�Z�[�W�`��
		for (i = 0; i < Message_Height && Message[i][0] != NULL; i++)
		{
			// X = Message������E�܂ł̐^��
			Length = strlen(&Message[i][0]);
			X = (Message_Width - Length) / 2;
			for (j = 0; j < X; j++)
			{
				strncpy(&BattleBG[MessageStart_Y + i][MessageStart_X + j], " ", 1);
			}
			strncpy(&BattleBG[MessageStart_Y + i][MessageStart_X + X], Message[i], Length);
		}
	}

	// �{�X�o���A`�̃C�x���g
	if (Player->InBossBattle == true && Enemy.BossBarrier <= 0 && DestoryBarrier == false)
	{
		strcpy(Message[3], "���Ȃ��̍U���ɂ���āA���@�o���A���j��ꂽ");
		// ���b�Z�[�W�`��
		for (i = 0; i < Message_Height && Message[i][0] != NULL; i++)
		{
			// X = Message������E�܂ł̐^��
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
		strcpy(&Enemy.Ability[0], "�Ȃ�");
	}


	// ===========================================================
	// ======================���ׂẲ�ʂ�`��====================
	// ===========================================================
	for (i = 0; i < Console_Height; i++)
	{
		printf("%s", &BattleBG[i][0]);
	}

	// ===========================================================
	// ======================���̃t�F�C�X�𔻒f====================
	// ===========================================================
	switch (TurnPhase)
	{
	case BeginningPhase:
		Player->HitKey = _getch();
		if ((Player->HitKey == 0) || (Player->HitKey == 224))
		{
			Player->HitKey = _getch();
		}
		// �X�L�����g��
		if (Player->HitKey == 's' && Player->Status.GetSkill == true)
		{
			if (Player->Status.MP > 0)
			{
				TurnPhase = SkillPhase;
				Player->Status.MP -= 1;
			}
		}
		// �퓬�O�P��
		else if (Player->HitKey == 'q' && Player->InBossBattle == false)
		{
			TurnPhase = EndPhase;
		}
		// �퓬�J�n
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
		// ����\�́F���U��
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
�֐���:	void UninitBattle(void)
����:	void
�߂�l:	void
����:	�o�g���̏I������
*******************************************************************************/
void UninitBattle(void)
{
	return;
}

/*******************************************************************************
�֐���:	void DrawSkill(void)
����:	void
�߂�l:	void
����:	�X�L���̕`�揈��
*******************************************************************************/
void DrawSkill(void)
{
	PLAYER *Player = GetPlayerAdr();

	// ===========================================================
	// ==========================�X�L���̕`��======================
	// ===========================================================
	system("cls");
	printf("�@�@ �@  ,-'   _,,-''\"�@�@�@�@�@�@         \"''-,,_    �P\"''-,,__�@   ''--,,__\n");
	printf("�@�@�@�@�@ ,,-''\"  ,, ---''\"\"\"  �j_�\�\�\�\ -    _ ''-,,_�@�@�@ �U�@�@       \"- \n");
	printf("�@�@�@�@ �ā@�@�@�^   ,,-\"---''i|�@�@    �P�P�P|i''-��@ �S�@�@�@{\n");
	printf("�@�@�@ �i\"    .�^ �@  i�@{;;;;;i|             .|i;;;;�j,�m�@�@�@ ii\n");
	printf(",,�@�@�@�@�@ �i�@�@�@ l,�@ `'-i|�@�@�@        �@|i;-'�@�@�@�@ ,-'\"�@�@�@_,,-\"\n");
	printf("  \"'-,,�@�@�@�@`-,,,,-'--'':::�P�P:::::::::''�j;-==,______�@'\"�@�@ _,--''\"\n");
	printf("�@     �P\"''-- _-'::::\"�P::::::::;;;;;;;;;;;;;;----;;:::::`::\"''::---,,___,,-''\"\n");
	printf("�@�@�@  ._,,-�j-''�j--''\"�P�P.i|�P�P�@�@      �@|i-----,,�P`''-;;:::''-`-,,\n");
	printf("�@  ,,-''::��-''\"�@�@�@.--    i|               .|i�@�@    �@�@�@�@�@ \"-;;:::`�\n");
	printf(" _,-\":::�^�@�@�@�P\"''---�@   i|�@�@�@        �@�@|i�@�@�@�@�@�@�@  �@�@  �R::i\n");
	printf("(:::{(i(___�@�@�@�@�@�@�@�@  i|�@�@�@       �@�@.|i�@�@�@�@�@       �@_,,-'/:}\n");
	printf("  `'-_�R::'-,,__,, �@_______i|�@�@�@�@�@         .|i---__,,----..--''\":::�m,-'\n");
	printf("  �@�@\"--;;;;;;;;;;\"\"''--;;i|                     .|i��;;;;:---;;;;;::--''\"~\n");
	printf("  �@�@�@�@�@�@�@�@ �P�P\"...i|                     .|i\n");
	printf("  �@�@�@�@�@�@�@�@�@�@    i|�@�@�@�@�@�@�@          |i\n");
	printf("  �@�@�@�@�@�@�@�@�@�@�@ i|�@�@�@�@�@�@�@�@          |i\n");
	printf("  �@�@�@�@�@�@�@�@�@�@�@i|�@�@ �@ �@�@�@�@           .|i\n");
	printf("  �@�@�@�@�@�@�@�@�@�@ i|�@�@�@�@�@�@�@�@�@          ..|i\n");
	printf("  �@�@�@�@�@�@�@�@�@  i|  �@�@�@�@ �@�@�@�@�@�@         |i\n");
	printf("  �@�@�@�@�@�@�@�@�@ i|�@�@�@�@�@�@      ,,-��@    ��@�@ |i\n");
	printf("  �@�@�@�@�@�@�@�@�@i|�@�@�@�@�@�@      �m:::i::::�gi�R�..|i\n");
	printf("  �@�@�@�@�@�@  _,,i|/\"\"\"\"�R�^:i�R!:::::�::::::::::::��::�R|i___n��g�\n");
	printf("    ,,�^^�R,-'\"::i�^::::::�^:::::|i�^;::;/::;:::::;;;�m�܁R�m:::::::�R,_��\n");
	printf("    ;;;;;;:::::;;;;;;;;::/:::;;;;;;;;:::/;;;;;;::::::;;;;;;;;:;;;;:::::::�R");
	Anykey();
	if (Player->InBossBattle == false)
	{
		Enemy.HP = 0;
	}
	// �{�X��Ȃ�A�{�X��HP�������ɂȂ�
	else
	{
		Enemy.HP = Enemy.HP / 2;
	}
	return;
}