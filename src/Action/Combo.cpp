#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "Combo.h"

Combo::Combo()
{
}

Combo::~Combo()
{
}

// �R���{���Ă悢���𔻒f����֐�
void Combo::Combo_Judgment(bool* combo_flag, int* mouse_flag, int key, float play_anim_time, float anim_total,int*combo_count)
{
	// �U���A�j���[�V�������I���O��
	if (play_anim_time <= anim_total)
	{
		if (*combo_flag == false)
		{
			// �w��̃}�E�X�{�^���������Ă�����
			if (PushMouseInput(key))
			{
				// �R���{�J�E���g�𑝂₷
				*combo_count += 1;
				// �ǂ̃{�^��������������ۑ�
				*mouse_flag = key;
				// �R���{�t���O���グ��
				*combo_flag = true;
				// �R���{�J�E���g�𑝂₷
			}
		}
	}
}
