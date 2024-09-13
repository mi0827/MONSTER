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
void MonsterBase::BaseInit(int hp_num,float up_speed, float down_speed)
{
	// HP�ݒ�
	m_hp_value = hp_num;
	// �W�����v�֘A�̐ݒ�
	m_up_speed = up_speed;
	m_down_speed = down_speed;
}


//---------------------------------------------------------------------------
// �����X�^�[�̈ړ��Ɋւ���^�[�Q�b�g�̐ݒ�
//---------------------------------------------------------------------------
void MonsterBase::BaseSetTarget(Transform* target_pos, const float m_target_hit_r)
{
	// �ړ��̍ۂ̃^�[�Q�b�g�̂̐ݒ�
	move.SetTargetInfo(target_pos, m_target_hit_r);
	// ���g�̏���ݒ�
	move.SetInfo(&m_transform, m_hit_r, M_MOV_SPEED, M_ROT_SPEED);

	
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
// �����蔻����Ƃ��Ăق����^�C�~���O��ۑ����邽�߂̊֐�
//---------------------------------------------------------------------------
void MonsterBase::SetHitTime(int attack_frame_start, int attack_frame_end, int attack_num)
{
	// �����蔻����Ƃ��Ăق����ŏ��̃t���[���̕ۑ�
	m_attack_hit_damage[attack_num]->start_time = attack_frame_start;
	// �I����Ăق����t���[���̕ۑ�
	m_attack_hit_damage[attack_num]->end_time = attack_frame_end;
}


//---------------------------------------------------------------------------
//  �����蔻����s���Ă����^�C�~���O��Ԃ��邽�߂̊֐�
//---------------------------------------------------------------------------
bool MonsterBase::AttackHitGoodTiming(int attack_num)
{
	// �X�^�[�g�̃t���[��
	int start_time = m_attack_hit_damage[attack_num]->start_time;
	// �I����Ăق����t���[��
	int end_time = m_attack_hit_damage[attack_num]->end_time;
	// �A�j���[�V�����̌��݂̃t���[��
	int play_anim_time = m_animation.m_contexts[0].play_time;
	if (play_anim_time >= start_time && end_time <= play_anim_time)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//---------------------------------------------------------------------------
// �����蔻����Ƃ��Ăق����^�C�~���O��ۑ����邽�߂̊֐�
//---------------------------------------------------------------------------
void MonsterBase::SetHitDamage(CapsuleCollision attack_hit, int attack_damage, int attack_num)
{
	// �{���͓�܂Ƃ߂ĕۑ��ł������ł��Ȃ��Ȃ��Ă��邽�߂ЂƂÂ��Ă���
	// �����蔻��̕ۑ�
	m_attack_hit_damage[attack_num]->attack_hit = attack_hit;

	// �_���[�W�̕ۑ�
	m_attack_hit_damage[attack_num]->attack_damage = attack_damage;
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
