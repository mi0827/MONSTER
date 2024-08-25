#pragma once

//! @fule SamplePlayer.h
//! @brief �T���v���L�����̃N���X
//! @brief �L�����N�^�[�x�[�X�N���X���p��

class SamplePlayer :public CharacterBase
{
public:
	//-----------------------------------------------
	// �萔�̐錾
	//-----------------------------------------------
	static constexpr float PLAYER_MOVE_SPEED = 2.0f;       //! �v���C���[�̈ړ��X�s�[�h
	static constexpr float PLAYER_R = 5.0f;                         //! �v���C���[�̉�]�X�s�[�h
	static constexpr float PLAYER_ROLLING_SPEED = 1.1f;   //! �v���C���[�̃��[�����O�X�s�[�h 
	static constexpr int HP_MAX = 100;                               //! HP�̍ő�l

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
		rolling, //!< ���[�����O
		attack_1,      //< �U���P
		attack_2,      //< �U���Q
		attack_3,      //< �U���R
		attack_kick_1, //< �L�b�N�U���P
		attack_kick_2, //< �L�b�N�U���Q
		attack_kick_3, //< �L�b�N�U���R

		anim_max //!< �A�j���[�V�����̍ő吔
	};

	static constexpr int NORMAL_ACTION = 3;                     //! �A�j���[�V�����̍U���n�ȊO�̃A�j���[�V�����̐�
	static constexpr int ATTACK_ACTION = anim_max - NORMAL_ACTION; //! �U���A�j���[�V�����̍ő吔

	//! �v���C���[�̏��
	enum PlayerMode
	{
		IDLE,      // �ҋ@
		RUN,       // ������
		ROLLING, // ���
		ATTACK,    // �U��
	};


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
	void Move_Update(Vector3* camera_rot);

	//! @brief �v���C���[�̏�ԊǗ��֐�
	//! @param �v���C���[�̏��
	void Player_Mode(int mode);

	//! @brief �U���J�n�������łȂ����𔻒f����֐�
	void Attack_First();

	//! @brief �U���p�̊֐�
	void Attack_Update();

	//! @brief ���[�����O�Z�b�g�p�̊֐�
	void Set_Rolling();

	//! @brief ���[�����O�A�N�V�����p�̊֐��i����j
	void Action_Rolling();

	//! @brief �R���{�֐�
	void Combo_Update();

public:
	////-----------------------------------------------
	//// �ϐ��̐錾
	////-----------------------------------------------
	////! �A�C�h����Ԃ��̃t���O
	//bool m_idle_flag = false;
	////! �����Ă����ȉ��̃t���O
	//bool m_run_flag = false;
	////! ���[�����O�t���O
	//bool m_rolling_flag = false;
	////! �U����Ԃ��ǂ����̃t���O
	//bool m_attack_flag = false;
	////! �v���C���[�̃��[�h���Ǘ�����ϐ�
	//int m_player_mode = -1;
	////! ���̃A�j���[�V�����ԍ���ۑ�����p�̕ϐ�
	//int m_now_attack_anim = -1;





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
	//CapsuleCollision m_right_hand; //!< �E��̓����蔻��
	//CapsuleCollision m_left_hand;   //!< �E��̓����蔻��
	//CapsuleCollision m_body;         //!< �{�̂̓����蔻��
	//CapsuleCollision m_left_feet;    //!< �����̓����蔻��
	//CapsuleCollision m_right_feet;  //!< �E���̓����蔻��

	//==================================
	// �U�����̓����蔻��ƃ_���[�W�̐ݒ蓖���蔻��
	//==================================
	// ���̃J�v�Z���̓����蔻���ۑ����邱�Ƃ����܂��ł��Ȃ�
	//Attack_Hit_Damage attack_hit_damage[ATTACK_ACTION];
	//


	////=================
	//// �o�[�^��UI
	////=================
	UIBra m_hp;

	//=================
	// �X�e�[�^�X
	//=================
	
	// �h���(�Ƃ肠����20)
	static constexpr int M_DEFENSE = 20;

};
