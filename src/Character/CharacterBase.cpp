#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"
#include "src/System/Spotlight.h"

#include "src/Model/Model.h"

#include "src/Collision/BoxCollision.h"
#include "src/Collision/CapsuleCollision.h"
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

//---------------------------------------------------------------------------
// �ړ��p�̂����蔻��
//---------------------------------------------------------------------------
void CharacterBase::MoveHitUpdate(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box)
{
	m_move_hit_box.CreateBox(*player_pos, *hit_size);
	m_move.Move_Hit(player_pos, before_pos, hit_size, box);
}

//---------------------------------------------------------------------------
// �x�[�X�N���X�ł̏�������
//---------------------------------------------------------------------------
void CharacterBase::BaseInit(float r)
{
	// ���W�A�����A��]�̏�����
	m_transform.pos.clear();
	// �����蔻��̔��a�̐ݒ�
	m_hit_r = r;
}

//---------------------------------------------------------------------------
//  �x�[�X�N���X�ł̍X�V����
//---------------------------------------------------------------------------
void CharacterBase::BaseUpdate(bool* m_check_move, Vector3* camera_rot, const float* mov_speed)
{
	// �ړ��̏���
	m_move.Update(m_check_move, camera_rot, &m_transform.rot, mov_speed, &m_transform.pos, m_pad_no, m_mov);
}
