#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"
#include "src/System/Spotlight.h"
#include "src/Collision/BoxCollision.h"
#include "src/System/Move.h"
#include "CharacterBase.h"

//---------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------
CharacterBase::CharacterBase()
{

}

//---------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------
CharacterBase::~CharacterBase()
{

}

void CharacterBase::MoveHitUpdate(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box)
{
	move.Move_Hit(player_pos, before_pos, hit_size, box);
}

//---------------------------------------------------------------------------
// �x�[�X�N���X�ł̏�������
//---------------------------------------------------------------------------
void CharacterBase::BaseInit()
{
	// ���W�A�����A��]�̏�����
	transform.pos.clear();
}

//---------------------------------------------------------------------------
//  �x�[�X�N���X�ł̍X�V����
//---------------------------------------------------------------------------
void CharacterBase::BaseUpdate(bool* m_check_move, Vector3* camera_rot, const float* mov_speed)
{
	// �ړ��̏���
	move.Update(m_check_move, camera_rot, &transform.rot, mov_speed, &transform.pos, m_pad_no, m_mov);
}
