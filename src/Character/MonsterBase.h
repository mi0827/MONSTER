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
	virtual void Init(Vector3* traget_pos) = 0;
	//! @brief �`�揈��
	virtual void Draw() = 0;
	//! @brief �X�V����
	virtual void Update() = 0;
	//! @brief �I������
	virtual void Exit() = 0;

	//! @brief �����蔻��̍X�V����
	virtual void CDUpdate() = 0;

	//! @brief �x�[�X�N���X�ł̏�������
	void BaseInit();

	//! @brief �x�[�X�N���X�̍X�V����
	
	void BaseUpdate();

	//! @brief �L�����̕ǎC�蔻��p�̊֐�
	//! @param �L�����̍��W
	//! @param �L�����̓����O�̍��W
	//! @param �L�����̓����蔻��̃T�C�Y
	//! @param �����蔻�葊��̃{�b�N�X�̏��
	//void MoveHitUpdate(Vector3* monster_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box);
public:
	//-----------------------------------------------
	//! �N���X�̃I�u�W�F�N�g���`
	//-----------------------------------------------

	struct Information
	{
		//! ���g�̏�������ϐ�
		Transform m_transform;
		//! ���g�̔��a������p�̕ϐ�
		float m_hit_r;
		//! ���g�̈ړ��X�s�[�h
		float M_MOV_SPEED;
		//! ���g��]���x
		float M_ROT_SPEED;
	};
	Information* m_info;

	
	struct TargetInformation
	{
		//! �^�[�Q�b�g�̍��W������ϐ�
		Vector3* m_target;
		//! �^�[�Q�b�g�̔��a������ϐ�
		float m_target_hit_r;
	};
	TargetInformation targetinfo;


	TargetMove move;
	Spotlight spot_light;
};
