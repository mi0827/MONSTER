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

	//! @brief �x�[�X�N���X�ł̏�������
	void BaseInit(Transform* target_pos, const  float m_target_hit_r);

	//! @brief �x�[�X�N���X�̍X�V����

	void BaseUpdate(bool* run_flag);

	//! @brief �L�����̕ǎC�蔻��p�̊֐�
	//! @param �L�����̍��W
	//! @param �L�����̓����O�̍��W
	//! @param �L�����̓����蔻��̃T�C�Y
	//! @param �����蔻�葊��̃{�b�N�X�̏��
	//void MoveHitUpdate(Vector3* monster_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box);
public:
	//-----------------------------------------------
	//! �N���X�̃I�u�W�F�N�g��錾
	//-----------------------------------------------


    //! ���g�̏�������ϐ�
	Transform m_transform;
	// �ړ��Ɏg���N���X
	TargetMove move;

	
	//-----------------------------------------------
	//! �ϐ���錾
	//-----------------------------------------------

	//! ���g�̔��a������p�̕ϐ�
	float m_hit_r = 10.0f;
	//! ���g�̈ړ��X�s�[�h
	static constexpr float M_MOV_SPEED = 1.0f;
	//! ���g��]���x
	static constexpr float M_ROT_SPEED = 5.0f;

	
};
