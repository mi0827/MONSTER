#include "src/WinMain.h"
#include "HitStop.h"

// --------------------------------------------------
// �q�b�g�X�g�b�v���Ăق����������Ăق�������Ԃ��֐�
// --------------------------------------------------
bool HitStop::Hit_Stop()
{
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
void HitStop::Stop_Count_Reset()
{
	// �J�E���g�̃��Z�b�g
	m_stop_frame_count = m_hit_stop_count_max;
}
