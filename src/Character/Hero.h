#pragma once

//! @fule HeroPlayer.h
//! @brief �q�[���[�̃N���X
//! @brief �L�����N�^�[�x�[�X�N���X���p��

class Hero :public CharacterBase
{
public:
	//-----------------------------------------------
	// �萔�̐錾
	//-----------------------------------------------
	static constexpr float  HERO_MOVE_SPEED = 2.0f; //! �ړ��X�s�[�h
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
		attack_1,      //< �U���P
		attack_2,      //< �U���Q
		attack_3,      //< �U���R

		attack_kick_1, //< �L�b�N�U���Q
		attack_kick_2, //< �L�b�N�U���R
		attack_4,      //< �U��4

		anim_max //!< �A�j���[�V�����̍ő吔
	};

	//! �q�[���[�̏��
	enum HeroMode
	{
		IDLE,      // �ҋ@
		RUN,       // ������
		ATTACK,    // �U��
	};


public:

	//-----------------------------------------------
	// �֐��̐錾
	//-----------------------------------------------
	//! @brief �R���X�g���N�^
	Hero();
	//! @brief �f�X�g���N�^
	~Hero();

	//! �p���悩��̊֐��̃I�[�o�[���C�h
	//! @brief ��������
	void Init()override;
	//! @brief �X�V����
	//! @param �J�����̌���
	void Update(Vector3* camera_rot) override;
	//! @brief �`�揈��
	void Draw() override;
	//! @brief �I������
	void Exit() override;

	//! @brief �����蔻��̍X�V����
	void CDUpdate() override;

	//! @brief �X�e�[�^�X�o�[�̕`��֐�
	void StatusBarDraw() override;

	//! @brief �A�j���[�V�����ǂݍ��݊֐�
	void Anima_Load_Init();

	//! @brief �v���C���[�̈ړ��p�֐�
	void Move_Update(Vector3* camera_rot);

	//! @brief �v���C���[�̏�ԊǗ��֐�
	//! @param �v���C���[�̏��
	void Hero_Mode(int mode);

	//! �U���J�n�������łȂ����𔻒f����֐�
	void Attack_First();

	//! @brief �U���p�̊֐�
	void Attack_Update();

	//! @brief �R���{�֐�
	void Combo_Update();

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
	int m_hero_mode = -1;
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
	// �R���{�̍ۃ}�E�X�̂ǂ���������ꂽ��
	int m_mouse_flag = 0; // MOUSE_INPUT_RIGHT : �E�{�^���AMOUSE_INPUT_LEFT : ���{�^�� 
	// �R���{�����񑱂��Ă��邩�̃J�E���g
	int m_combo_count = 0;
	// ���̃A�j���[�V�����ԍ���ۑ�
	int m_next_anim = -1;
	// �R���{����߂Ăق������̃t���O
	bool m_stop_combo_flag = false;

public:
	//-----------------------------------------------
	// �N���X�̃I�u�W�F�N�g�̐錾
	//-----------------------------------------------

	//! ���f���N���X�̃I�u�W�F�N�g
	Model m_model;
	//! �A�j���[�V�����N���X�̃I�u�W�F�N�g
	Animation m_animation;
	//! �R���{�N���X
	Combo m_combo;
	//! �J�v�Z���R���W����
	//=================
	// �����蔻��
	//=================
	CapsuleCollision m_right_hand; //!< �E��̂����蔻��
	CapsuleCollision m_left_hand; //!< �E��̓����蔻��
	CapsuleCollision m_left_feet;  //!< �����̓����蔻��
	CapsuleCollision m_right_feet; //!< �E���̓����蔻��
	CapsuleCollision m_sword;     //!< �\�[�h�̓����蔻��
	CapsuleCollision m_body;       //!< �{�̂̂����蔻��
};
