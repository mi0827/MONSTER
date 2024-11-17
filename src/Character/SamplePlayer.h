#pragma once

//! @fule SamplePlayer.h
//! @brief �T���v���L�����̃N���X
//! @brief �L�����N�^�[�x�[�X�N���X���p��

class SamplePlayer :public CharacterBase
{
public:

	//-----------------------------------------------
	// �֐��̐錾
	//-----------------------------------------------
	//! @brief �R���X�g���N�^
	SamplePlayer();
	//! @brief �f�X�g���N�^
	~SamplePlayer();

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
	//! �A�j���[�V�����̎�ޗp�̗񋓑�
	//! @detail �U���A�j���[�V�����̓R���{�̑����������Ԃɐݒ肷��
	enum Animation_Max
	{
		idle, //!< �ҋ@
		run, //!< ����
		rolling, //!< ���[�����O
		hit_damage, //!< �_���[�W���󂯂���
		die,     //!< �|���ꂽ��

		attack_anim_1,      //< �U���P
		attack_anim_2,      //< �U���Q
		attack_anim_3,      //< �U���R

		attack_kick_anim_1, //< �L�b�N�U���P
		attack_kick_anim_2, //< �L�b�N�U���Q
		attack_kick_anim_3, //< �L�b�N�U���R

		counter_anim,       //< �J�E���^�[

		anim_max //!< �A�j���[�V�����̍ő吔
	};

	static constexpr int ATTACK_ANIM_STAR = attack_anim_1;                     //! �A�j���[�V�����̍U���n�ȊO�̃A�j���[�V�����̐�
	static constexpr int ATTACK_ACTION = anim_max - ATTACK_ANIM_STAR; //! �U���A�j���[�V�����̍ő吔
	//------------------------------------------
	// �R���{�֘A
	//------------------------------------------
	// �R���{�̍ő吔
	static constexpr int COMBO_MAX = 3;
	// �U���ԍ��̍Đݒ�
	enum AttackAnim
	{
		attack_punch_1 = attack_anim_1 - ATTACK_ANIM_STAR,    //< �U���P
		attack_punch_2 = attack_anim_2 - ATTACK_ANIM_STAR,	   //< �U���Q
		attack_punch_3 = attack_anim_3 - ATTACK_ANIM_STAR,	   //< �U���R
		attack_kick_1 = attack_kick_anim_1 - ATTACK_ANIM_STAR, //< �L�b�N�U���P
		attack_kick_2 = attack_kick_anim_2 - ATTACK_ANIM_STAR,	//< �L�b�N�U���Q
		attack_kick_3 = attack_kick_anim_3 - ATTACK_ANIM_STAR,	//< �L�b�N�U���R

		attack_counter = counter_anim - ATTACK_ANIM_STAR,       //!< �J�E���^�[�U��

		attack_max
	};

	// �����蔻����Ƃ��Ăق����t���[���̍\����
// �����蔻����Ƃ��Ăق����t���[���̍\����
	struct AttackTiming
	{
		// �n�܂�̃t���[��
		float start_frame;
		// �I���̃t���[��
		float end_frame;
		// �q�b�g�X�g�b�v���s���Ă������ǂ���
		bool can_hit_stop;
	};


	// �����蔻����s���Ăق����^�C�~���O�̐ݒ�
	// ���̂Ƃ��뉼
	// ��i�W�܂łɊ���������
	AttackTiming attack_frame[attack_max] =
	{
		// �p���`�P
		{ 0.0f, 30.0f, false},
		// �p���`�Q
		{ 15.0f, 50.0f, false},
		// �p���`�R
		{	50.0f, 90.0f, true},
		// �L�b�N�P
		{	20.0f, 55.0f, false},
		// �L�b�N�Q
		{	15.0f, 60.0f, false},
		// �L�b�N�R
		{	25.0f, 60.0f, true},
		// �J�E���^�[�U��
		{   10.0f, 60.0f, true},
	};

	// �e�U���̃_���[�W
	int m_attack_damage[attack_max]
	{
		50,70,70,70,70,70,70,
	};


	
	

public:

	////=================
	//// �o�[�^��UI
	////=================
	UIBra m_hp;

	//=================
	// �X�e�[�^�X
	//=================


	//-----------------------------------------------
	// �萔�̐錾
    //-----------------------------------------------
	static constexpr float PLAYER_MOVE_SPEED = 2.0f;       //! �v���C���[�̈ړ��X�s�[�h
	static constexpr float PLAYER_R = 5.0f;                //! �v���C���[�̉�]�X�s�[�h
	static constexpr float PLAYER_ROLLING_SPEED = 1.1f;    //! �v���C���[�̃��[�����O�X�s�[�h 
	static constexpr float PLAYER_HIT_R = 1.5;             //! �v���C���[�̉~�̓����蔼�a�̔��a
	static constexpr int HP_MAX = 100;                     //! HP�̍ő�l
	static constexpr int M_DEFENSE = 20;                   //! �h���
	//----------------------------------------------- 
	// �񋓑̂̐錾
	//-----------------------------------------------
};
