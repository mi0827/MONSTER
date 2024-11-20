#include "src/WinMain.h"

#include "src/Model/Model.h"

#include "src/Collision/CapsuleCollision.h"
#include "src/Collision/BoxCollision.h"
#include "src/Hit/Hit.h"
#include "src/Animation/Animation.h"
#include "src/Action/Attack.h"


bool HitAttack(CapsuleCollision capsule1, CapsuleCollision capsule2)
{
	// �w��̃J�v�Z�����m�̓����蔻�肪�������Ƃ�
	if (CheckCapsuleHit(capsule1, capsule2))
	{
		// �����蔻�肪�����ĂȂ������߂Ă���if���ɓ������Ƃ�����
		// true��Ԃ��ă_���[�W�v�Z��������
		return true;
	}
	return false;
}