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
	virtual void Update(Transform* target_pos, float target_r) = 0;
	//! @brief �����Ă鎞�̍X�V����
	//! @param �^�[�Q�b�g�̍��W
	//! @param �^�[�Q�b�g�̔��a
	virtual void LiveUpdate(Transform* target_pos, float target_r) = 0;

	//! @brief �o�ꉉ�o�p�̍X�V����
	virtual void EntryUpdate() = 0;

	//! @brief HP�����܂Ō������Ƃ��̃��x���A�b�v����
	virtual void ReinforceUpdate() = 0;


	//! @brief ���񂾂Ƃ��̍X�V���� 
	virtual void DieUpdate() = 0;
	//! @brief �I������
	virtual void Exit() = 0;


	//! @brief �����蔻��̍X�V����
	virtual void CDUpdate() = 0;

	//! @brief �X�e�[�^�X�o�[�̐ݒ�p�֐�
	virtual void StatusBarInit() = 0;
	//! @brief �X�e�[�^�X�o�[�̕`��֐�
	virtual void StatusBarDraw() = 0;

	//! @brief ���[�����O�A�N�V�����p�̊֐��i����j
	//! @param ���[�����O�����Ƃ��̈ړ��X�s�[�h
	virtual void ActionRolling(const int rolling_speed);

	//! @brief �U���Ɋւ��邱�Ƃ̏����֐�
	//! �����蔻����s���Ăق����^�C�~���O��ۑ�����
	//! �R���{�p�^�[���̏�����
	//! �e�R���{�p�^�[���̐ݒ�
	virtual void SetAttackInfo() = 0;

	//! @brief �X�^���������p�̍X�V����
	//! @param �X�^�����̃_�E���A�j���[�V�����ԍ�
	//! @param �X�^�����̋N���オ��A�j���[�V�����ԍ�
	//! @param �X�^���l�̍ő��
	virtual void StunActionUpdate(int down_anim_num, int up_anim_num, int sutn_value_max);

	//! @brief �����X�^�[�̏��(�t���O)�Ǘ��֐�
	//! @param �����X�^�[�̏��
	virtual void MonsterMode(int mode) = 0;

	//! @brief �A�j���[�V�����ǂݍ��ݗp�֐�
	virtual void AnimLoadInit() = 0;

	//! @brief �U���A�j���[�V�����Ɋւ�����̐ݒ�
	//! @param �U���A�j���[�V�����̊J�n�ԍ�
	//! @param �U���A�j���[�V�����̍ő吔
	//! @param �����_���ōU����I�Ԏ��̂͂Ԃ��Ăق����U���ԍ�
	void SetAttackAnimInfo(int attack_anim_start, int attack_anim_max, int except_attack);

	//! @brief �A�C�h���A�N�V��������
	//! @param �A�C�h���A�j���[�V�����ԍ�
	void IdleActionUpdate(int idle_anim_num);

	//! @brief �ړ��A�N�V��������
	//! @param �ړ��p�A�j���[�V�����ԍ�
	void MoveAction(int ran_anim);

	//! @brief �R���{�p�^�[���̐���ݒ�
	//! @param �R���{�p�^�[���̍ő吔
	void ComboPatternNumberInit(int pattern_max);

	//! @brief �e�R���{�p�^�[���̐ݒ�
	//! @param ���p�^�[���ڂ̃R���{��
	//! @param �R���{�̐��̍ő吔
	//! @param �R���{���I�������̂��ƌ��̃t���[����
	//! @param �R���{�p�̍U���ԍ����ۑ�����Ă���z������炤
	void ComboPatternInfoInit(int pattern_num, int combo_num_max, int rear_crevice_frame, int* anim_num);

	//! @brief �ŏ��̍U�����s���p�֐�
	void FirstAttackAction();

	//! @brief �U���֘A�̍X�V����
	void AttackActionComboUpdate();

	//! @brief �W�����v�U���J�n�̏���
	//! @param �W�����v�p�̃A�j���[�V�����ԍ�
	//! @param ����Ƃ̋���
	void JumpAction(int jump_anim, int target_distance);

	//! @brief �W�����v�U���̍X�V����
	//! @param �����X�s�[�h
	void JumpActionUpdate(float down_speed);

	void SetJumpPos(Vector3 pos);

	//! @brief �R���{�U���X�V����
	void ComboUpdate();

	//! @brief �s�������U���A�j���[�V�����������_���őI�Ԃ��߂̊֐�
	int SetRandAttack();

	//! @brief �x�[�X�N���X�ł̏�������
	//! @param �����X�^�[��HP�}�b�N�X
	//! @param �W�����v�̏㏸�X�s�[�h
	//! @param �W�����v�̉��~�X�s�[�h
	void BaseInit(int hp_num, float up_speed, float down_speed);

	//! @brief �����X�^�[�̈ړ��Ɋւ���^�[�Q�b�g�̐ݒ�
	//! @param �^�[�Q�b�g�̍��W
	//! @param �^�[�Q�b�g�̃J�v�Z���̓����蔻��̔��a
	void BaseSetTarget(Transform* target_pos, const float m_target_hit_r);

	//! @brief �ړ��̍X�V����
	//! @param  �����Ă����Ԃ��̃t���O
	void MoveUpdate(bool* run_flag);

	//! @brief �����蔻����s���Ăق����^�C�~���O���Z�b�g����֐�
	//! @param �����蔻����Ƃ��Ăق����t���[���̃X�^�[�g
	//! @param �����蔻����I����Ăق����t���[���̏I���
	//! @param �ۑ��������U���ԍ�
	void SetHitTime(int attack_frame_start, int attack_frame_end, int attack_num);

	// �����蔻����Ƃ��Ă悢�^�C�~���O���𔻒f����֐�
	//! @brief �U���ԍ�
	bool AttackHitGoodTiming(int anim_num);

	//! @brief �����蔻��ƃ_���[�W��ۑ�����֐�
	//! @param �����蔻��p�̃J�v�Z��
	//! @param �^����_���[�W
	//! @param �U���ԍ�
	void SetHitDamage(CapsuleCollision attack_hit, int attack_damage, int attack_num);

	

	// �U���̎��̓����蔻��ƃ_���[�W�̍\����
	// �e�q�N���X�Œ�`����
	struct Attack_Hit_Damage
	{
		//!  �U�����Ɏg�����������蔻��
		CapsuleCollision attack_hit;
		//! �U���ɂ������_���[�W
		int attack_damage = 0;

		//! �����蔻����Ƃ��Ăق����^�C�~���O
		//! �X�^�[�g
		int start_time = 0;
		//! �I���
		int end_time = 0;

	};
	std::vector< Attack_Hit_Damage*> m_attack_hit_damage;

	//! @brief �U�����̓����蔻���ݒ肷��p�̊֐�
	//! @param �U���A�j���[�V�����̍ő吔
	void  NEW_Set_Attack_Hit_Damage(int attack_anim_max);

public:

	//-----------------------------------------------
	// �ϐ��̐錾
	//-----------------------------------------------

	//===============
	// ��ԊǗ��p�t���O
	//=============== 
	//-----------------------------------------------
	// �񋓑̂ŊǗ�
	//-----------------------------------------------
	//! �����X�^�[�̏��
	enum Situation
	{
		alive, // �����Ă�Ƃ�
		die,   // ����ł�
	};
	//! �����Ă邩��ۑ����邽�߂̕ϐ�
	// �ŏ��͐����Ă��Ԃ���n�߂�
	int m_life_and_death = alive;

	//! �����X�^�[�̂Ɏg�p����t���O
	//! �A�C�h����Ԃ��̃t���O
	bool m_idle_flag = false;
	//! �����Ă����ȉ��̃t���O
	bool m_run_flag = false;
	//! �U����Ԃ��ǂ����̃t���O
	bool m_attack_flag = false;
	//! 1�t���[���O�̍U���t���O�̏�Ԃ�ۑ����Ă���
	bool m_past_attack_flag = m_attack_flag;
	//! �U�����󂯂����̃A�j���[�V������ݒ肷�邽�߂̕ϐ�
	//! �Ȃ񂩂����_���[�W���󂯂����̃A�j���[�V�����Z�b�g�ɓ����Ăق����Ȃ��̂ō����
	//! �{���͂����Ƃ������@������Ǝv���������炻����ɕύX
	bool m_damage_anim_flag = false;
	//! �����蔻����Ƃ��Ă������̃t���O
	bool m_can_hit_damage_flag;
	//! �X�^����Ԃ��̃t���O
	bool m_stun_flag;



private:
	//! �U���A�j���[�V�����̃X�^�[�g�ԍ�
	int m_ATTACK_ANIM_START = 0;
	//! �U���A�j���[�V�����̍ő吔
	int m_ATTACK_ANIM_MAX = 0;
	//! �����_���ōU����I�ԍۂɂ͂Ԃ��Ăق����A�j���[�V�����ԍ�
	int m_ATTACK_ANIM_EXCEPT = 0;

public:
	//! �ǎC�蔻��̂��߂ɂ���������W��ۑ����Ă����ϐ�
	Vector3 m_before_pos = { 0.0f,0.0f,0.0f };
	//! �ړ��̍ۂ̓����蔻��p�̃T�C�Y
	Vector3 move_hit_size = { 1.0f ,0.0f,1.0f };

	//! ���g�̔��a������p�̕ϐ�
	float m_hit_r = 15.0f;
	//! ���g�̈ړ��X�s�[�h
	static constexpr float M_MOV_SPEED = 1.0f;
	//! ���g��]���x
	static constexpr float M_ROT_SPEED = 5.0f;

	//------------------------------------------
	// �X�e�[�^�X�֘A
	//------------------------------------------
	// HP�̎c��
	int m_hp_value;
	// HP�p�̃o�[
	UIBra m_hp_bra;
	// �X�^���l�̎c��
	int m_stun_value;
	// �X�^���p�̃o�[
	UIBra m_stun_bra;

private:
	//------------------------------------------
	// �A�C�h���֘A
	//------------------------------------------
	//! �ǂꂾ���̃t���[���~�܂��ė~�������Z�b�g���������ۂ̃t���O
	bool m_set_stop_frame_flag = false;
	//! �A�C�h����ԂŎ~�܂��Ă��Ăق����t���[��
	int m_stop_frame = 0;
	//! ���t���[���~�܂��Ă���̂��̃J�E���g
	int m_stop_frame_count = 0;
public:
	//------------------------------------------
	// �W�����v�֘A
	//------------------------------------------
	// �W�����v�̂��߂̈ړ��ʗp�̕ϐ�
	Vector3 m_jump_mov{ 0.0f,0.0f,0.0f };
	// �W�����v�̒��n�n�_�̍��W
	Vector3 m_jump_pos{ 0.0f,0.0f,0.0f };
	// �W�����v�̎��ɐi�ދ���
	float m_jump_move;
	// �W�����v�t���O
	bool m_jump_flag = false;
	// �㏸�X�s�[�h
	float m_up_speed = 0;
	// ���~�X�s�[�h
	float m_down_speed = 0;

	//------------------------------------------
	// �R���{�֘A
	//------------------------------------------
	// �R���{�����p�^�[�����p�ӂ��Ă���������_���Ń����X�^�[�ɑI�΂���
	struct ComboPattern
	{
		// �R���{�����q���邩�̐�
		int m_combo_num_max;
		// �R���{�Ŏg���A�j���[�V�����ԍ���ۑ����邽�߂ɕϐ�
		// 
		std::vector<int> m_combo_parts;
		// �R���{�̌�̂��ƌ����t���[����
		int m_rear_crevice_frame;
	};
	std::vector<ComboPattern> m_combo_pattern;
	//! �R���{�̃p�^�[���̍ő吔��ۑ�����
	int m_combo_pattern_max = 0;
	//! ���p�^�[���ڂ̃R���{���g�p���邩
	int m_combo_pattern_num = 0;

	// ��L�ō���Ă���R���{�̃p�^�[�������ł���΂��̉��̃t���O�֘A�͂���Ȃ��Ȃ�
	// �R���{�̍ő吔
	static constexpr int COMBO_MAX = 3;
	//! �R���{�p�t���O
	bool m_combo_flag = false;

	//! �����Ăق������̃t���O

	//! ���̃A�j���[�V�����ԍ���ۑ�
	int m_next_anim = -1;
	//! �R���{����߂Ăق������̃t���O
	bool m_stop_combo_flag = false;


	//! �����X�^�[�̏��
	enum MonsterMode
	{
		IDLE,        //!< �ҋ@���
		RUN,         //!< ������
		ATTACK,    //!< �U�����
		STUN,       //!< �X�^�����
		DIE,          //!< ����
	};
	//! �����X�^�[�̏�Ԃ��Ǘ�����ϐ�
	int m_monster_mode = 0;

	// �W�����v�̏�Ԃ��Ǘ�
	//enum Jump
	//{
	//	STANDBY,     //! �X�^���o�C
	//	GOUP,           //! �オ��^�C�~���O
	//	MOVE,           //! �W�����v���̈ړ��̃^�C�~���O
	//	DROPDOWN,  //! �����Ă���^�C�~���O

	//	max
	//};
	////! �W�����v�̏�Ԃ�ۑ�����ϐ�
	//int jump_info_num = 0;

	// �U����Ԃ̊Ǘ�
	enum Attack
	{
		ATTACKSET,
		UNDERATTACK,
	};
	//! �U����Ԃ�ۑ�����ϐ�
	int m_attack_info_num = ATTACKSET;
	//! ���̃A�j���[�V�����ԍ���ۑ�����p�̕ϐ�
	int m_now_attack_anim = 0;
	//! �����X�^�[�̌��ݍs���Ă���U���A�j���[�V�����ԍ���ۑ�����
	int m_now_attack = -1;
	//! �R���{�����ڂ�
	int m_combo_num = 0;

	// �X�^���̏�Ԃ��Ǘ�
	enum Stun
	{
		DOWN,          //! �|��Ă���Ƃ�
		UPSTANDBY,  //! �|��Ă���N���オ��܂ł̊�
		UP,                //! �N���オ��Ƃ�
	};
	//! �X�^���̏�Ԃ�ۑ�����ϐ�
	int m_stun_info_num = DOWN;

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
