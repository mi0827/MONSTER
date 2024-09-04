#pragma once
// �����X�^�[��p�̃L�����x�[�X�N���X

//! 
//! @fule MonsterBase.h
//! @brief �����X�^�[�̃x�[�X�N���X


class MonsterBase
{
public:
	//! �R���X�g���N�^
	MonsterBase();

	//! �f�X�g���N�^
	~MonsterBase();




	//! �������z�֐�
	//! @brief ��������
	//! //! @param �ړ��̍ۂ̃^�[�Q�b�g���W
	virtual void Init() = 0;
	//! @brief �`�揈��
	virtual void Draw() = 0;
	//! @brief �X�V����
	virtual void Update(Transform* traget_pos, float traget_r) = 0;
	//! @brief �I������
	virtual void Exit() = 0;


	//! @brief �����蔻��̍X�V����
	virtual void CDUpdate() = 0;

	//! @brief �X�e�[�^�X�o�[�̐ݒ�p�֐�
	virtual void Status_Bar_Init() = 0;
	//! @brief �X�e�[�^�X�o�[�̕`��֐�
	virtual void Status_Bar_Draw() = 0;

	//! @brief ���[�����O�A�N�V�����p�̊֐��i����j
	//! @param ���[�����O�����Ƃ��̈ړ��X�s�[�h
	virtual void Action_Rolling(const int rolling_speed);

	//! @brief �x�[�X�N���X�ł̏�������
	//! @param �����X�^�[��HP�}�b�N�X
	//! @param �W�����v�̏㏸�X�s�[�h
	//! @param �W�����v�̉��~�X�s�[�h
	void BaseInit(int hp_num ,float up_speed, float down_speed);

	//! @brief �����X�^�[�̈ړ��Ɋւ���^�[�Q�b�g�̐ݒ�
	//! @param �^�[�Q�b�g�̍��W
	//! @param �^�[�Q�b�g�̃J�v�Z���̓����蔻��̔��a
	void BaseSetTarget(Transform* target_pos, const float m_target_hit_r);

	//! @brief �x�[�X�N���X�̍X�V����
	//! @param  �����Ă����Ԃ��̃t���O
	void BaseUpdate(bool* run_flag);




	// �U���̎��̓����蔻��ƃ_���[�W�̍\����
	// �e�q�N���X�Œ�`����
	struct Attack_Hit_Damage
	{
		//!  �U�����Ɏg�����������蔻��
		CapsuleCollision attack_hit;
		//! �U���ɂ������_���[�W
		int attack_damage = 0;
	};
	std::vector< Attack_Hit_Damage*> m_attack_hit_damage;

	//! @brief �U�����̓����蔻���ݒ肷��p�̊֐�
	//! @param �U���A�j���[�V�����̍ő吔
	void  NEW_Set_Attack_Hit_Damage(int attack_anim_max);


	//! @brief �L�����̕ǎC�蔻��p�̊֐�
	//! @param �L�����̍��W
	//! @param �L�����̓����O�̍��W
	//! @param �L�����̓����蔻��̃T�C�Y
	//! @param �����蔻�葊��̃{�b�N�X�̏��
	//void MoveHitUpdate(Vector3* monster_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box);
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
	int m_monster_mode = 0;
	//! ���̃A�j���[�V�����ԍ���ۑ�����p�̕ϐ�
	int m_now_attack_anim = 0;


	//! �ǎC�蔻��̂��߂ɂ���������W��ۑ����Ă����ϐ�
	Vector3 m_before_pos = { 0.0f,0.0f,0.0f };
	//! �ړ��̍ۂ̓����蔻��p�̃T�C�Y
	Vector3 move_hit_size = { 1.0f ,0.0f,1.0f };

	//! ���g�̔��a������p�̕ϐ�
	float m_hit_r = 10.0f;
	//! ���g�̈ړ��X�s�[�h
	static constexpr float M_MOV_SPEED = 1.0f;
	//! ���g��]���x
	static constexpr float M_ROT_SPEED = 5.0f;

	// HP�̎c��
	int m_hp_value;

	//------------------------------------------
	// �W�����v�֘A
	//------------------------------------------
	// �W�����v�̂��߂̈ړ��ʗp�̕ϐ�
	Vector3 m_jump_mov{ 0.0f,0.0f,0.0f };
	// �W�����v�t���O
	bool m_jump_flag = false;
	// �㏸�X�s�[�h
	float m_up_speed = 0;
	// ���~�X�s�[�h
	float m_down_speed = 0;

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


	//! �����X�^�[�̌��ݍs���Ă���U���A�j���[�V�����ԍ���ۑ�����
	int m_now_attack = -1;

	//-----------------------------------------------
	// �N���X�̃I�u�W�F�N�g�̐錾
	//-----------------------------------------------
	//! ���g�̏�������ϐ�
	Transform m_transform;
	//! �ړ��Ɏg���N���X
	TargetMove move;
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
	CapsuleCollision m_left_hand; //!< ����̂����蔻��
	CapsuleCollision m_right_hand; //!< �E��̓����蔻��
	CapsuleCollision m_body;       //!< �{�̂̂����蔻��

};
