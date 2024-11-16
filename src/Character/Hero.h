#pragma once

//! @fule HeroPlayer.h
//! @brief �q�[���[�̃N���X
//! @brief �L�����N�^�[�x�[�X�N���X���p��

class Hero :public CharacterBase
{
public:


public:

	//-----------------------------------------------
	// �֐��̐錾
	//-----------------------------------------------
	//! @brief �R���X�g���N�^
	Hero();
	//! @brief �f�X�g���N�^
	~Hero();

	//-----------------------------------------------
   // �֐��̐錾
   //-----------------------------------------------


	//! �p���悩��̊֐��̃I�[�o�[���C�h
	//! @brief ��������
	void Init()override;
	//! @brief �X�V����
	//! @param �J�����̌���
	void Update(Vector3* camera_rot) override;

	//! @brief �����Ă鎞�̍X�V����
	//! @param �J�����̌���
	void LiveUpdate(Vector3* camera_rot) override;

	//! @brief ���񂾂Ƃ��̍X�V���� 
	void DieUpdate() override;


	//! @brief �`�揈��
	void Draw() override;
	//! @brief �I������
	void Exit() override;

	//! @brief �����蔻��̍X�V����
	void CDUpdate() override;

	//! @brief �X�e�[�^�X�o�[�̐ݒ�p�֐�
	void StatusBarInit() override;
	//! @brief �X�e�[�^�X�o�[�̕`��֐�
	void StatusBarDraw() override;

	//! @brief �����蔻����s���ė~�����^�C�~���O��ۑ�����֐�
	void SetHitTimeInit() override;

	//! @brief �A�j���[�V�����ǂݍ��݊֐�
	//! �U���A�j���[�V�����̎n�܂�A�j���[�V�����ԍ�
	void AnimLoadInit() override;

	//! @brief �v���C���[�̈ړ��p�֐�
	//! (�����A�j���[�V�����̔ԍ����������œn��)
	//void MoveAction(Vector3* camera_rot) override;

	//! @brief �v���C���[�̏��(�t���O)�Ǘ��֐�
	//! @param �v���C���[�̏��
	void PlayerMode(int mode) override;
public:

	//-----------------------------------------------
	// �萔�̐錾
	//-----------------------------------------------
	static constexpr float  PLAYER_MOVE_SPEED = 2.0f; //! �ړ��X�s�[�h
	static constexpr float  HERO_R = 5.0f;                   //! ��]�X�s�[�h
	static constexpr float PLAYER_ROLLING_SPEED = 1.1f;   //! �v���C���[�̃��[�����O�X�s�[�h 
	static constexpr int HP_MAX = 100;                               //! HP�̍ő�l
	static constexpr int PLAYER_HIT_R = 1;                         //! �v���C���[�̉~�̓����蔼�a�̔��a
	//-----------------------------------------------
	// �񋓑̂̐錾
	//-----------------------------------------------
public:
	//! �A�j���[�V�����̎�ޗp�̗񋓑�
	//! @detail �U���A�j���[�V�����̓R���{�̑����������Ԃɐݒ肷��
	enum Animation_Max
	{
		idle, //!< �ҋ@
		run, //!< ����
		rolling, //! ���[�����O
		hit_damage, //! �_���[�W���󂯂���
		die, //! �|���ꂽ��

		// ���N���b�N�U��
		attack_sword_anim_1,      //< �\�[�h�U���P
		attack_sword_anim_2,      //< �\�[�h�U���Q
		attack_sword_anim_3,      //< �\�[�h�U���R

		attack_sword_anim_4, //< �\�[�h�U���S
		attack_kick_anim_1,   //< �L�b�N�U��1
		attack_kick_anim_2,   //< �L�b�N�U��1

		counter_anim,              // �J�E���^�[�U��

		anim_max //!< �A�j���[�V�����̍ő吔
	};

	static constexpr int ATTACK_ANIM_STAR = attack_sword_anim_1;                     //! �A�j���[�V�����̍U���n�ȊO�̃A�j���[�V�����̐�
	static constexpr int ATTACK_ACTION = anim_max - ATTACK_ANIM_STAR; //! �U���A�j���[�V�����̍ő吔

	// �U���ԍ��̍Đݒ�
	enum AttackAnim
	{
		attack_sword_1 = attack_sword_anim_1 - ATTACK_ANIM_STAR,	   //< �U���Q
		attack_sword_2 = attack_sword_anim_2 - ATTACK_ANIM_STAR,	   //< �U���R
		attack_sword_3 = attack_sword_anim_3 - ATTACK_ANIM_STAR,    //< �U���P
		attack_sword_4 = attack_sword_anim_4 - ATTACK_ANIM_STAR, //< �L�b�N�U���P
		attack_kick_1 = attack_kick_anim_1 - ATTACK_ANIM_STAR,	//< �L�b�N�U���Q
		attack_kick_2 = attack_kick_anim_2 - ATTACK_ANIM_STAR,	//< �L�b�N�U���R

		attack_counter = counter_anim - ATTACK_ANIM_STAR,       //< �J�E���^�[�U��

		attack_max
	};

	// �����蔻����Ƃ��Ăق����t���[���̍\����
	struct AttackFrame
	{
		// �n�܂�̃t���[��
		float start_frame;
		// �I���̃t���[��
		float end_frame;
	};

	// �����蔻����s���Ăق����^�C�~���O�̐ݒ�
	// ���̂Ƃ��뉼
	// ��i�W�܂łɊ���������
	AttackFrame attack_frame[attack_max] =
	{
		// ���U���P
		{ 33.0f, 52.0f, },
		// ���U���Q
		{ 48.0f, 62.0f, },
		// ���U���R
		{	52.0f, 70.0f, },
		// ���U��4
		{	32.0f, 44.0f, },
		// �L�b�N1
		{	25.0f, 45.0f, },
		// �L�b�N2
		{	37.0f, 60.0f, },
		// �J�E���^�[�U��
		{   93.0f,  120.0f},
	};

	// �e�U���̃_���[�W
	int m_attack_damage[attack_max]
	{
		50,70,70,70,70,70,100,
	};


	//------------------------------------------
	// �R���{�֘A
	//------------------------------------------
	// �R���{�̍ő吔
	static constexpr int COMBO_MAX = 3;

	////=================
//// �o�[�^��UI
////=================
	UIBra m_hp;

public:
	//-----------------------------------------------
	// �N���X�̃I�u�W�F�N�g�̐錾
	//-----------------------------------------------


	//! �J�v�Z���R���W����
	//=================
	// �����蔻��
	//=================
	CapsuleCollision m_sword;     //!< �\�[�h�̓����蔻��

};
