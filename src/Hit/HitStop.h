#pragma once
//! @file HitStop.h
//! @brief �q�b�g�X�g�b�v�p�̃N���X
class HitStop
{
public:
	// �q�b�g�X�g�b�v���Ăق����������Ăق�������Ԃ��֐�
	// �Ԃ��l
	//  true�F�q�b�g�X�g�b�v���Ăق���
	// false�F�q�b�g�X�g�b�v���Ăق����Ȃ�
	bool CheckHitStop();

	// stop_frame_count�����Z�b�g���邽�߂̊֐�
	void StopCountReset();
public:
	static const int HIT_STOP_COUNT_MAX = 10; // �q�b�g�X�g�b�v�Ŏ~�܂�t���[����
	int m_stop_frame_count = 0; // �~�܂��Ă�t���[�����J�E���g��}��悤�ϐ�
};