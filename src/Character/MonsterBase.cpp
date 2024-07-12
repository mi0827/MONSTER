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
void MonsterBase::BaseInit(Vector3 target_pos,float m_target_hit_r)
{

	//�����̌^������Ȃ�����������œn����setInfo�̒��ō\���̂̒��ɓ����
	// �������󂯎��Ƃ���͍l����
	//

	move.SetInfo(m_info, &targetinfo);
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
