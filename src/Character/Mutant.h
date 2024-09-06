#pragma once
#pragma once

//! @fule Mutant.h
//! @brief �~���[�^���g�̃N���X
//! @brief �����X�^�[�x�[�X�N���X���p��

class Mutant :public MonsterBase
{
public:
	//=========================================================================
	// �萔�̐錾
	//=========================================================================
	static constexpr float MONSTER_MOVE_SPEED = 1.5f; //! �ړ��X�s�[�h
	static constexpr float MONSTER_ROT_SPEED = 0.5f;   //! ��]�X�s�[�h
	static constexpr float TARGET_DISTANCE = 100.0f;     //! �W�����v����Ƃ��̑���Ƃ̋���
	static constexpr float JUMP_UP_SPEED = 10.0f;          //! �W�����v�̎��̏㏸�X�s�[�h
	static constexpr float JUMP_DOWN_SPEED = 2.0f;      //! �W�����v�̎��̉��ɗ����Ăق����X�s�[�h 
	static constexpr int HP_MAX = 500;                           //! HP�̍ő�l
	static constexpr int ROLLING_SPEED = 1.0f;               //! ���[�����O�X�s�[�h
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
		attack_2, //!< �U���Q
		attack_3, //!< �U���R
		attack_4, //!< �U���S
		rolling,    //!< ���[�����O
		jump,     //!< �W�����v�A�N�V����

		anim_max //!< �A�j���[�V�����̍ő吔
	};

	//! �U���A�j���[�V�����̈�ԍŏ�
	static constexpr int ATTACK_ANIM_START = attack_1;
	//! �U���A�j���[�V�����ő�l�ijump�𔲂������j
	static constexpr int ATTACK_ANIM_MAX = jump - ATTACK_ANIM_START;

	//! �U���A�N�V�����̐�
	static constexpr int ATTACK_ACTION_MAX = anim_max - attack_1;
	
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
	int jump_num=0;
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
	void Update(Transform* traget_pos, float target_r) override;
	//! @brief �`�揈��
	void Draw() override;
	//! @brief �I������
	void Exit() override;

	
	//! @brief �����蔻��̍X�V����
	void CDUpdate() override;

	//! @brief �X�e�[�^�X�o�[�̐ݒ�p�֐�
	void Status_Bar_Init() override;
	//! @brief �X�e�[�^�X�o�[�̕`��֐�
	void Status_Bar_Draw() override;

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
	

	

	

public:
	//-----------------------------------------------
	// �N���X�̃I�u�W�F�N�g�̐錾
	//-----------------------------------------------

	////! ���f���N���X�̃I�u�W�F�N�g
	//Model m_model;
	////! �A�j���[�V�����N���X�̃I�u�W�F�N�g
	//Animation m_animation;
	////! �R���{�N���X
	//Combo m_combo;
	////! �J�v�Z���R���W����
	////=================
	//// �����蔻��
	////=================
	//CapsuleCollision m_left_hand; //!< ����̂����蔻��
	//CapsuleCollision m_right_hand; //!< �E��̓����蔻��
	//CapsuleCollision m_body;       //!< �{�̂̂����蔻��

	//==================================
	// �U�����̓����蔻��ƃ_���[�W�̐ݒ蓖���蔻��
	//==================================
	// ���̃J�v�Z���̓����蔻���ۑ����邱�Ƃ����܂��ł��Ȃ�
	Attack_Hit_Damage attack_hit_damage[ATTACK_ACTION_MAX];

	//=================
	// �o�[�^��UI
	//=================
	UIBra m_hp;
	
};
