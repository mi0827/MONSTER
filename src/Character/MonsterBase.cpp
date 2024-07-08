#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"
#include "src/System/Spotlight.h"
#include "src/Collision/BoxCollision.h"
#include "src/System/TargetMove.h"

#include "src/Character/MonsterBase.h"


// �����X�^�[��p�̃L�����x�[�X�N���X

//---------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------
MonsterBase::MonsterBase()
{

}

//---------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------
MonsterBase::~MonsterBase()
{

}

//---------------------------------------------------------------------------
// �x�[�X�N���X�̏�������
//---------------------------------------------------------------------------
void MonsterBase::BaseInit()
{
}

//---------------------------------------------------------------------------
// �x�[�X�N���X�̍X�V����
//---------------------------------------------------------------------------
void MonsterBase::BaseUpdate(const float mov_speed, const float rot_speed, Vector3* target_pos)
{
	// �ړ�����
	move.Update(&transform, mov_speed, rot_speed, target_pos);
}

//---------------------------------------------------------------------------
// �ړ��p�̂����蔻��
//---------------------------------------------------------------------------
//void MonsterBase::MoveHitUpdate(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box)
//{
//	move.Move_Hit(player_pos, before_pos, hit_size, box);
//}
