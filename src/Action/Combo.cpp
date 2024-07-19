#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "Combo.h"

//---------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------
Combo::Combo()
{
}

//---------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------
Combo::~Combo()
{
}

//---------------------------------------------------------------------------
// �R���{���Ă悢���𔻒f����֐�
// �w��̃L�[�i�{�^���������ꂽ�Ƃ��j
//---------------------------------------------------------------------------

void Combo::Combo_Judgment_Key(bool* combo_flag, int* mouse_flag, int key, float play_anim_time, float anim_total,int*combo_count)
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

//---------------------------------------------------------------------------
// �R���{���Ă悢���𔻒f����֐�
// �w��̏����𖞂����Ă���Ƃ�
//---------------------------------------------------------------------------
void Combo::Combo_Judgment_Condition(bool* combo_flag, bool condition, float play_anim_time, float anim_total)
{
	// �U���A�j���[�V�������I��鎞��
	if (play_anim_time == anim_total - 5.0f)
	{
		if (*combo_flag == false)
		{
			// �w��̏�����treu�̎�
			if (condition)
			{			
				// �R���{�t���O���グ��
				*combo_flag = true;
				// �R���{�J�E���g�𑝂₷
			}
		}
	}
}
