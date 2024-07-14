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
	// �֐��̒�`
	//=========================================================================

	//! @�^�[�Q�b�g�̐ݒ�
	//! @param ���g�̏��
	//! @param �~�̔��a
	void SetInfo(Transform* transform, const float hit_r ,const float MOV_SPEED,const float ROT_SPEED);

	//! @�^�[�Q�b�g�̏���ݒ�
	//! @param �^�[�Q�b�g�̍��W
	//! @param �~�̔��a
	void SetTargetInfo(Transform* taregt_pos, const float target_hit_r);

	//! @brief �ړ��S�̂̍X�V����
	//! @param ���̃N���X���g���Ĉړ�����{�̂�transform
	//! @param �ړ��X�s�[�h
	//! @param �U��������x
	void Update();

	//! @brief �^�[�Q�b�g�ƈ��̋����ɓ���������Ԃ��֐�
	bool Target_Hit();

private:

	//=========================================================================
	// �\���̂̒�`
	//=========================================================================

	struct Information
	{
		//! ���g�̏�������ϐ�
		Transform* m_transform;
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
		Transform* m_target;
		//! �^�[�Q�b�g�̔��a������ϐ�
		float m_target_hit_r;
	};


	//=========================================================================
	// �ϐ��̐錾
	//=========================================================================
	//! ���g�̏������Ă�������
	Information m_info;
	//! �^�[�Q�b�g�̏������Ă�������
	TargetInformation m_target_info;

	//! �{�l�̌����Ă���������킩��₷�����邽�߂̍��W
	Vector3 m_line_start;
	Vector3 m_line_goal;

	//=========================================================================
	// �萔�̐錾
	//=========================================================================
	static constexpr int RANGE = 200;

};
