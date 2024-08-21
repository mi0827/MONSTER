#include "src/WinMain.h"

#include "src/Model/Model.h"

#include "src/Collision/CapsuleCollision.h"
#include "src/Collision/BoxCollision.h"
#include "src/Hit/Hit.h"
#include "src/Animation/Animation.h"
#include "src/Action/Attack.h"


bool Attack::HitAttack(CapsuleCollision capsule1, CapsuleCollision capsule2, Animation anim)
{

	// �U���A�j���[�V�������I��鐡�O��hit �t���O��������
// �{���͐��O�łȂ��I�������̂ق����ǂ���animation�N���X�̏�����������
// �A�j���[�V�����̏I���u�Ԃ����Ȃ��̂ł��̂悤�Ȍ`�ɂȂ��Ă���
// -5�Ȃ͕̂��ɂ���Ă̓A�j���[�V�����̐i�ރX�s�[�h���Ⴄ�̂ō��̂Ƃ��낱��ɂȂ��Ă���
// ��L�̏������ł����܂������Ă��Ȃ�����if���ɓ���Ƃ��Ɠ���Ȃ��Ƃ�������
// �R���{���Ȃ��Ɠ���
// �{����anim.m_contexts[0].is_playing�Ŕ�����Ƃ肽�������܂������Ȃ�
// �v���O���~���O�̏��ԓI�ɂ͂��܂������͂��Ȃ̂ɂ��܂������Ȃ�
	if (anim.m_contexts[0].play_time >= anim.m_contexts[0].animation_total_time -1 /*!anim.m_contexts[0].is_playing*/)
	{
		// �����蔻�肪�Ȃ��Ƃ���false�ɂ��Ă���
		hit = false;
	}
	// �w��̃A�j���[�V�����̍Đ�����
	if (anim.m_contexts[0].play_time < anim.m_contexts[0].animation_total_time)
	{
		// �w��̃J�v�Z�����m�̓����蔻�肪�������Ƃ�
		if (CheckCapsuleHit(capsule1, capsule2))
		{
			if (!hit)
			{
				hit = true;
				// �����蔻�肪�����ĂȂ������߂Ă���if���ɓ������Ƃ�����
				// true��Ԃ��ă_���[�W�v�Z��������
				return true;
			}
			return false;
		}
	}
}
