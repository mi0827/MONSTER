#pragma once
// �w�肳�ꂽ�^�[�Q�b�g�̕����Ɉړ����邽�߂̃N���X

//! @fule TargetMove.h
//! @brief �w�肳�ꂽ�^�[�Q�b�g�����Ɉړ����邽�߂̃N���X

class TargetMove
{
public:
	//! �R���X�g���N�^
	TargetMove();
	//! �f�X�g���N�^
	~TargetMove();

	//=========================================================================
	// �\���̂̒�`
	//=========================================================================

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


	struct TargetInformation
	{
		//! �^�[�Q�b�g�̍��W������ϐ�
		Vector3 m_target;
		//! �^�[�Q�b�g�̔��a������ϐ�
		float m_target_hit_r;
	};



	//=========================================================================
	// �֐��̒�`
	//=========================================================================

	//! @�^�[�Q�b�g�̐ݒ�
	//! @param ���g�̏��
	//! @param �~�̔��a
	void SetInfo(Transform* transform, const float hit_r);

	//! @�^�[�Q�b�g�̏���ݒ�
	//! @param �^�[�Q�b�g�̍��W
	//! @param �~�̔��a
	void SetTargetInfo(Vector3* taregt_pos, const float target_hit_r);

	//! @brief �ړ��S�̂̍X�V����
	//! @param ���̃N���X���g���Ĉړ�����{�̂�transform
	//! @param �ړ��X�s�[�h
	//! @param �U��������x
	void Update();

	//!
	//! @fn
	//! @brief �ړ��Ɋւ��铖���蔻��p�̊֐�
	//! @param ���� (�L����) �̍��W(���̍��W)
	//! @param �����i�L�����j�̍��W(�����蔻��O��)
	//! @param �����i�L�����j�̓����蔻��̃T�C�Y�i���S���猩���T�C�Y�j
	//! @param �����蔻����Ƃ肽���{�b�N�X�̏��
	//! @detail �ړ��̕ǎC��p�֐�
	void Move_Hit(Vector3* pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box);


	//! @brief �^�[�Q�b�g�Ƃ̋����ɂ���Ĉړ�����߂邽�߂̊֐�
	void Target_Hit();

private:

	//=========================================================================
	// �ϐ��̒�`
	//=========================================================================
	//! ���g�̏������Ă�������
	Information m_info;
	//! �^�[�Q�b�g�̏������Ă�������
	TargetInformation m_target_info;



};
