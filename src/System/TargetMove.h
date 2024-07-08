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

	//! 
	//! @brief �ړ��S�̂̍X�V����
	//! @param ���̃N���X���g���Ĉړ�����{�̂�transform
	//! @param �ړ��X�s�[�h
	//! @param �U��������x
	//! @param �^�[�Q�b�g�ɂ��������̂̍��W
	void Update(Transform* transform, const float mov_speed, const float rot_speed, Vector3* target_pos);

	//!
	//! @fn
	//! @brief �ړ��Ɋւ��铖���蔻��p�̊֐�
	//! @param ���� (�L����) �̍��W(���̍��W)
	//! @param �����i�L�����j�̍��W(�����蔻��O��)
	//! @param �����i�L�����j�̓����蔻��̃T�C�Y�i���S���猩���T�C�Y�j
	//! @param �����蔻����Ƃ肽���{�b�N�X�̏��
	//! @detail �ړ��̕ǎC��p�֐�
	void Move_Hit(Vector3* pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box);
};
