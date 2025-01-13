#pragma once
// �w�肳�ꂽ�^�[�Q�b�g�̕����Ɉړ����邽�߂̃N���X

//! @file TargetMove.h
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
	//! @param �ړ��X�s�[�h
	//! @param ��]�X�s�[�h
	void SetInfo(Transform* transform, const float hit_r, const float MOV_SPEED, const float ROT_SPEED);

	//! @�^�[�Q�b�g�̏���ݒ�
	//! @param �^�[�Q�b�g�̍��W
	//! @param �~�̔��a
	void SetTargetInfo(Transform* taregt_pos, const float target_hit_r);

	//! @brief �ړ��S�̂̍X�V����
	//! @param �ړ����������łȂ����̃t���O
	void Update(bool* run_flag);

	//! @brief �{�̂̌�����
	void SetDirection();

	//! @brief �L�����̌����Ă�������Ƀ^�[�Q�b�g�����邩���Ȃ�����Ԃ��֐�
	//! @param �����Ă��Ăق����͈�
	//! @return true : �͈͓�, false : �͈͊O
	bool WithinRange(int range);

	//! @brief �^�[�Q�b�g�ƈ��̋����ɓ���������Ԃ��֐�
	bool TargetHit();

	//! @brief �^�[�Q�b�g�Ƃ̋�����Ԃ��֐�
	float GetTargetDistance();

	// @brief �����̕ύX�����Ă悢���̃t���O���󂯎��
	void SetCanRotate(bool can = true);

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
public:
	//! �^�[�Q�b�g�̏������Ă�������
	TargetInformation m_target_info;

	//! �{�l�̌����Ă���������킩��₷�����邽�߂̍��W
	Vector3 m_line_start;
	Vector3 m_line_goal;

	//=========================================================================
	// �萔�̐錾
	//=========================================================================
	//! �U��������s���Ăق����l
	static constexpr int RANGE = 500;

public:
	//! �^�[�Q�b�g�Ƃ̋����������߂Â�������m�邽�߂̕ϐ�
	// �����Ă��Ă������:true
	// �����Ă͂Ȃ�Ȃ��Ƃ�:false
	bool m_hit = false;
private:
	// �O�ς��g�������f���������̂ŏ�ō�����Q�̃x�N�g���̊O�ς����߂܂�
	Vector3 m_cross;
	// ��]���Ă������̃t���O�悤�̕ϐ�
	bool m_can_rot = true;
};
