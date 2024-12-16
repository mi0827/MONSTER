#pragma once
#pragma once

//! @file SamplePlayer.h
//! @brief �����X�^�[�̃N���X
//! @brief �����X�^�[�x�[�X�N���X���p��

class Monster :public MonsterBase
{
public:
	//=========================================================================
	// �萔�̐錾
	//=========================================================================
	static constexpr float MONSTER_MOVE_SPEED = 1.5f;   //! �ړ��X�s�[�h
	static constexpr float MONSTER_ROT_SPEED = 0.5f;    //! ��]�X�s�[�h
	static constexpr float TARGET_DISTANCE = 170.0f;    //! �^�[�Q�b�g�Ƃ̋���
	static constexpr float JUMP_UP_SPEED = 5.0f;        //! �W�����v�̎��̏㏸�X�s�[�h
	static constexpr float JUMP_DOWN_SPEED = 2.0f;      //! �W�����v�̎��̉��ɗ����Ăق����X�s�[�h 
	static constexpr int HP_MAX = 500;                  //! HP�̍ő�l
	//=========================================================================
	// �񋓑̂̐錾
	//=========================================================================
public:
	//! �A�j���[�V�����̎�ޗp�̗񋓑�
	//! @detail �U���A�j���[�V�����̓R���{�̑����������Ԃɐݒ肷��
	enum Animation_Max
	{
		idle, //!< �ҋ@
		run,  //!< ����
		attack_1, //!< �U���P
		rolling,  //!< ���[�����O
		jump,     //!< �W�����v�A�N�V����

		anim_max //!< �A�j���[�V�����̍ő吔
	};

	//! �U���A�j���[�V�����̈�ԍŏ�
	static constexpr int ATTACK_ANIM_START = attack_1;
	//! �U���A�j���[�V�����ő�l
	static constexpr int ATTACK_ANIM_MAX = jump - ATTACK_ANIM_START;


	//! �����X�^�[�̏��
	enum MonsterMode
	{
		IDLE,      //!< �ҋ@
		RUN,       //!< ������
		ATTACK,    //!< �U��
	};

	enum Jump
	{
		STANDBY,     //! �X�^���o�C
		GOUP,           //! �オ��^�C�~���O
		MOVE,           //! �W�����v���̈ړ��̃^�C�~���O
		DROPDOWN,  //! �����Ă���^�C�~���O

		max
	};
	//! �W�����v�̏�Ԃ�ۑ�����ϐ�
	int jump_num = 0;
public:

	//=========================================================================
	// �֐��̐錾
	//=========================================================================
	
	//! @brief �R���X�g���N�^
	Monster();
	//! @brief �f�X�g���N�^
	~Monster();

	//! �p���悩��̊֐��̃I�[�o�[���C�h
	//! @brief ��������
	void Init()override;
	//! @brief �X�V����
	//! @param �ړ��̎��̃^�[�Q�b�g�̍��W
	//! @param �^�[�Q�b�g�̔��a
	void Update(Transform* traget_pos, float target_r) override;
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

	//! @brief �A�j���[�V�����ǂݍ��݊֐�
	void Anima_Load_Init();

	//! @brief �v���C���[�̈ړ��p�֐�
	void Move_Update();

	//! @brief �U���J�n�������łȂ����𔻒f����֐�
	void Attack_First();

	//! @brief �U���p�̊֐�
	void Attack_Update();

	//! @brief �W�����v�U���p�̊֐�
	void Attack_Jump();

	//! @brief �W�����v�U���̍X�V����
	void Jump_Update();

	//! @brief �R���{�֐�
	void Combo_Update();

	//! @drief �s�������A�j���[�V�����������_���őI�Ԃ��߂̊֐�
	int Set_Rand_Attack();

public:
	//-----------------------------------------------
	// �ϐ��̐錾
	//-----------------------------------------------
	//! �A�C�h����Ԃ��̃t���O
	bool m_idle_flag = false;
	//! �����Ă����ȉ��̃t���O
	bool m_run_flag = false;

	//! �U����Ԃ��ǂ����̃t���O
	bool m_attack_flag = false;
	//! �v���C���[�̃��[�h���Ǘ�����ϐ�
	int m_monster_mode = -1;
	//! ���̃A�j���[�V�����ԍ���ۑ�����p�̕ϐ�
	int m_now_attack_anim = -1;


	//! �ǎC�蔻��̂��߂ɂ���������W��ۑ����Ă����ϐ�
	Vector3 m_before_pos = { 0.0f,0.0f,0.0f };
	//! �ړ��̍ۂ̓����蔻��p�̃T�C�Y
	Vector3 move_hit_size = { 1.0f ,0.0f,1.0f };

	//------------------------------------------
	// �R���{�֘A
	//------------------------------------------
	// �R���{�̍ő吔
	static constexpr int COMBO_MAX = 3;
	//! �R���{�p�t���O
	bool m_combo_flag = false;

	//! �����Ăق������̃t���O

	//! ���̃A�j���[�V�����ԍ���ۑ�
	int m_next_anim = -1;
	//! �R���{����߂Ăق������̃t���O
	bool m_stop_combo_flag = false;



public:



	//=================
	// �o�[�^��UI
	//=================
	UIBra m_hp;
	// HP�̎c��
	int m_hp_value = HP_MAX;
};
