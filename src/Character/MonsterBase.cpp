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
void MonsterBase::BaseInit(Transform* target_pos, const float m_target_hit_r)
{
	// �ړ��̍ۂ̃^�[�Q�b�g�̂̐ݒ�
	move.SetTargetInfo(target_pos, m_target_hit_r);
	// ���g�̏���ݒ�
	move.SetInfo(&m_transform, m_hit_r, M_MOV_SPEED, M_ROT_SPEED);

}

//---------------------------------------------------------------------------
// �x�[�X�N���X�̍X�V����
//---------------------------------------------------------------------------
void MonsterBase::BaseUpdate()
{
	// �ړ�����
	move.Update();
}

//---------------------------------------------------------------------------
// �ړ��p�̂����蔻��
//---------------------------------------------------------------------------
//void MonsterBase::MoveHitUpdate(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box)
//{
//	move.Move_Hit(player_pos, before_pos, hit_size, box);
//}
