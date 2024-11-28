#pragma once
#pragma once

//! @fule Mutant.h
//! @brief �~���[�^���g�̃N���X
//! @brief �����X�^�[�x�[�X�N���X���p��

class Mutant :public MonsterBase
{
public:

public:

	//=========================================================================
	// �֐��̐錾
	//=========================================================================
	//! @brief �R���X�g���N�^
	Mutant();
	//! @brief �f�X�g���N�^
	~Mutant();

	//! �p���悩��̊֐��̃I�[�o�[���C�h
	//! @brief ��������
	void Init()override;
	//! @brief �X�V����
	//! @param �ړ��̎��̃^�[�Q�b�g�̍��W
	//! @param �^�[�Q�b�g�̔��a
	void Update(Transform* target_pos, float target_r) override;
	//! @brief �����Ă鎞�̍X�V����
	void LiveUpdate(Transform* target_pos, float target_r) override;
	//! @brief ���񂾂Ƃ��̍X�V���� 
	void DieUpdate() override;
	//! @brief �`�揈��
	void Draw() override;
	//! @brief �I������
	void Exit() override;

	//! @brief �o�ꉉ�o�p�̍X�V����
	void EntryUpdate() override;

	//! @brief HP�����܂Ō������Ƃ��̃��x���A�b�v����
	void ReinforceUpdate() override;

	//! @brief �����蔻��̍X�V����
	void CDUpdate() override;

	//! @brief �X�e�[�^�X�o�[�̐ݒ�p�֐�
	void StatusBarInit() override;
	//! @brief �X�e�[�^�X�o�[�̕`��֐�
	void StatusBarDraw() override;

	//! @brief �����蔻����s���ė~�����^�C�~���O��ۑ�����֐�
	void SetHitTimeInit() override;


	//! @brief �����X�^�[�̏��(�t���O)�Ǘ��֐�
	//! @param �����X�^�[�̏��
	void MonsterMode(int mode) override;


	//! @brief �A�j���[�V�����ǂݍ��݊֐�
	void AnimLoadInit() override;


	//=========================================================================
	// �萔�̐錾
	//=========================================================================
	static constexpr float MONSTER_MOVE_SPEED = 1.5f; //! �ړ��X�s�[�h
	static constexpr float MONSTER_ROT_SPEED = 0.5f;   //! ��]�X�s�[�h
	static constexpr float TARGET_DISTANCE = 100.0f;     //! �W�����v����Ƃ��̑���Ƃ̋���
	static constexpr float JUMP_UP_SPEED = 10.0f;          //! �W�����v�̎��̏㏸�X�s�[�h
	static constexpr float JUMP_DOWN_SPEED = 2.0f;      //! �W�����v�̎��̉��ɗ����Ăق����X�s�[�h 
	static constexpr int ROLLING_SPEED = 1.0f;               //! ���[�����O�X�s�[�h
	static constexpr int HP_VALUE_MAX = 500;                           //! HP�̍ő�l
	static constexpr int STUN_VALUE_MAX = 150;                       //! �X�^���l�̍ő�
	
	//=========================================================================
	// �񋓑̂̐錾
	//=========================================================================
	//! �A�j���[�V�����̎�ޗp�̗񋓑�
	//! @detail �U���A�j���[�V�����̓R���{�̑����������Ԃɐݒ肷��
	enum Animation_Max
	{
		idle, //!< �ҋ@
		run,  //!< ����
		die,   //!< ���S
		shout, //!< ����
		hit_damage, //!< �U�����󂯂���
		stun_down, //!< �X�^���œ|��鎞
		stun_up,  //!< �X�^���ŋN���オ��Ƃ�

		attack_1, //!< �U���P
		attack_2, //!< �U���Q
		attack_3, //!< �U���R
		attack_4, //!< �U���S
		rolling,    //!< ���[�����O
		jump,     //!< �W�����v�A�N�V����

		anim_max //!< �A�j���[�V�����̍ő吔
	};

	//! �U���A�j���[�V�����̈�ԍŏ�
	static constexpr int ATTACK_ANIM_START = attack_1;
	//! �U���A�j���[�V�����ő�l�ijump�𔲂������W�����v�𔲂��Ă����Ȃ��ƃR���{�U���̎��ȃo�O��j
	static constexpr int ATTACK_ANIM_MAX = rolling - ATTACK_ANIM_START;

	//! �U���A�N�V�����̐�
	static constexpr int ATTACK_ACTION_MAX = anim_max - attack_1;

	// �U���ԍ��̍Đݒ�
	enum AttackAnim
	{
		attack_punch_1 = attack_1 - ATTACK_ANIM_START,      //< �U���P
		attack_punch_2 = attack_2 - ATTACK_ANIM_START,	   //< �U���Q
		attack_punch_3 = attack_3 - ATTACK_ANIM_START,	   //< �U���R
		attack_punch_4 = attack_4 - ATTACK_ANIM_START,       //< �U���S
		attack_rolling = rolling - ATTACK_ANIM_START,      	//< �U���T
		attack_jump = jump - ATTACK_ANIM_START,

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

	// �����蔻����s���Ăق����^�C�~���O�̐ݒ�̕ϐ�
	// �܂��܂�������
	// ��i�W�܂łɊ���������
	AttackFrame attack_frame[attack_max] =
	{
		// �p���`�P
		{ 00.0f, 30.0f, },
		// �p���`�Q
		{ 0.0f, 90.0f, },
		// �p���`�R
		{ 0.0f, 80.0f, },
		// �p���`�S
		{ 0.0f, 70.0f, },
		// ���[�����O
		{  0.0f, 50.0f, },
		// �W�����v
		{ 00.0f, 40.0f, },

	};

	//! �e�U���̃_���[�W
	int m_attack_damage[attack_max]
	{
		10,20,20,20,20,20
	};
};
