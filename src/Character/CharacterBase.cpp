#include "src/WinMain.h"
#include "src/System/Vector2.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Collision/CapsuleCollision.h"
#include "src/Collision/BoxCollision.h"

#include "src/Action/Combo.h"

#include "src/Model/Model.h"
#include "src/System/Move.h"

#include "src/System/UIBar.h"

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
	m_attack_hit_damage.clear();
}

//---------------------------------------------------------------------------
// �ړ��p�̂����蔻��
//---------------------------------------------------------------------------
void CharacterBase::MoveHitUpdate(BoxCollision* box)
{
	// �����蔻���
	m_move_hit_box.CreateBox(m_transform.pos, m_move_hit_size);
	m_move.Move_Hit(&m_transform.pos, &m_before_pos, &m_move_hit_size, box);
}

//---------------------------------------------------------------------------
// �x�[�X�N���X�ł̏�������
//---------------------------------------------------------------------------
void CharacterBase::BaseInit(float r, int HP)
{
	// ���W�A�����A��]�̏�����
	m_transform.pos.clear();
	// �����蔻��̔��a�̐ݒ�
	m_hit_r = r;
	// HP�̐ݒ�
	m_hp_value = HP;
}

//---------------------------------------------------------------------------
// �U�����̓����蔻���ݒ肷��p�̊֐�
//---------------------------------------------------------------------------
void CharacterBase::NEW_Set_Attack_Hit_Damage(int attack_anim_max)
{
	// �U���A�j���[�V�����̐��m�ۂ���
	for (int i = 0; i < attack_anim_max; i++)
	{
		Attack_Hit_Damage* attack_hit_damage = new Attack_Hit_Damage;
		m_attack_hit_damage.push_back(attack_hit_damage);
		// �����l�͓K���Ȃ��̂����Ă���
		m_attack_hit_damage[i]->attack_hit =  m_body;
		m_attack_hit_damage[i]->attack_damage = 0;
	}
}

//---------------------------------------------------------------------------
//  �x�[�X�N���X�ł̍X�V����
//---------------------------------------------------------------------------
void CharacterBase::BaseUpdate(bool* m_check_move, Vector3* camera_rot, const float* mov_speed)
{
	// �ړ��̏���
	m_move.Update(m_check_move, camera_rot, &m_transform.rot, mov_speed, &m_transform.pos, m_pad_no, m_mov);
}
