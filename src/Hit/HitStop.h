#pragma once

class HitStop
{
public:
	// �q�b�g�X�g�b�v���Ăق����������Ăق�������Ԃ��֐�
	// �Ԃ��l
	//  true�F�q�b�g�X�g�b�v���Ăق���
	// false�F�q�b�g�X�g�b�v���Ăق����Ȃ�
	bool Hit_Stop();

	// stop_frame_count�����Z�b�g���邽�߂̊֐�
	void Stop_Count_Reset();
public:
	static const int m_hit_stop_count_max = 10; // �q�b�g�X�g�b�v�Ŏ~�܂�t���[����
	int m_stop_frame_count = 0; // �~�܂��Ă�t���[�����J�E���g��}��悤�ϐ�
};