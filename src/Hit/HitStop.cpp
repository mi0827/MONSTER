#include "src/WinMain.h"
#include "HitStop.h"

// --------------------------------------------------
// �q�b�g�X�g�b�v���Ăق����������Ăق�������Ԃ��֐�
// --------------------------------------------------
bool HitStop::CheckHitStop()
{
	// �J�E���g�̃��Z�b�g�̓q�b�g�X�g�b�v���N�����Ăق����������s��ꂽ���ɂ����Ȃ��悤�ɂ���
	m_stop_frame_count--; // �J�E���g�����炷

	// �X�g�b�v�J�E���g�����̒l�ȏ゠���
	if (m_stop_frame_count > 0)
	{
		return  true; // �q�b�g�X�g�b�v���Ăق���
	}
	else
	{
		m_stop_frame_count = 0;
	    return false; // ���Ăق����Ȃ�
	}

}

// --------------------------------------------------
// stop_frame_count�����Z�b�g���邽�߂̊֐�
// --------------------------------------------------
void HitStop::StopCountReset()
{
	// �J�E���g�̃��Z�b�g
	// ���Z�b�g���邱�ƂŃq�b�g�X�g�b�v�̔��肪�ł���
	m_stop_frame_count = HIT_STOP_COUNT_MAX;
}
