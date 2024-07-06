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
	virtual void Init() = 0;
	//! @brief �`�揈��
	virtual void Draw() = 0;
	//! @brief �X�V����
	//! @param �J�����̌���
	virtual void Update() = 0;
	//! @brief �I������
	virtual void Exit() = 0;

	//! @brief �����蔻��̍X�V����
	virtual void CDUpdate() = 0;

	//! @brief �x�[�X�N���X�ł̏�������
	void BaseInit();


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
	Transform transform;
	//TargetMove move;
	Spotlight spot_light;
};
