#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Collision/BoxCollision.h"
#include "src/Collision/CapsuleCollision.h"

#include "src/System/TargetMove.h"
#include "src/Action/Combo.h"
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
// ���[�����O�A�N�V�����̒��̈ړ�����
//---------------------------------------------------------------------------
void MonsterBase::Action_Rolling(const int rolling_speed)
{
	// ���[�����O���̈ړ�����
// �����Ă�������� PLAYER_ROLLING_SPEED ���ړ�����
	m_transform.pos.z += rolling_speed * cosf(TO_RADIAN(m_transform.rot.y));
	m_transform.pos.x += rolling_speed * sinf(TO_RADIAN(m_transform.rot.y));
}

//---------------------------------------------------------------------------
// �x�[�X�N���X�̏�������
//---------------------------------------------------------------------------
void MonsterBase::BaseInit(Transform* target_pos, const float m_target_hit_r, int hp_num)
{
	// �ړ��̍ۂ̃^�[�Q�b�g�̂̐ݒ�
	move.SetTargetInfo(target_pos, m_target_hit_r);
	// ���g�̏���ݒ�
	move.SetInfo(&m_transform, m_hit_r, M_MOV_SPEED, M_ROT_SPEED);

	m_hp_value = hp_num;
}

//---------------------------------------------------------------------------
// �x�[�X�N���X�̍X�V����
//---------------------------------------------------------------------------
void MonsterBase::BaseUpdate(bool* run_flag)
{
	// �ړ�����
	move.Update(run_flag);
}

//---------------------------------------------------------------------------
// �U�����̓����蔻���ݒ肷��p�̊֐�
//---------------------------------------------------------------------------
void MonsterBase::NEW_Set_Attack_Hit_Damage(int attack_anim_max)
{

	// �U���A�j���[�V�����̐��m�ۂ���
	for (int i = 0; i < attack_anim_max; i++)
	{
		Attack_Hit_Damage* attack_hit_damage = new Attack_Hit_Damage;
		m_attack_hit_damage.push_back(attack_hit_damage);
		// �����l�͓K���Ȃ��̂����Ă���
		m_attack_hit_damage[i]->attack_hit = m_body;
		m_attack_hit_damage[i]->attack_damage = 0;
	}
}

//---------------------------------------------------------------------------
// �ړ��p�̂����蔻��
//---------------------------------------------------------------------------
//void MonsterBase::MoveHitUpdate(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box)
//{
//	move.Move_Hit(player_pos, before_pos, hit_size, box);
//}
