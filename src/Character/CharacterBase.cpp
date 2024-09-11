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
// �����蔻����Ƃ��Ăق����^�C�~���O��ۑ����邽�߂̊֐�
//---------------------------------------------------------------------------
void CharacterBase::SetHitTime(int attack_frame_start, int attack_frame_end, int attack_num)
{
	// �����蔻����Ƃ��Ăق����ŏ��̃t���[���̕ۑ�
	m_attack_hit_damage[attack_num]->start_time = attack_frame_start;
	// �I����Ăق����t���[���̕ۑ�
	m_attack_hit_damage[attack_num]->end_time = attack_frame_end;
}

bool CharacterBase::AttackHitGoodTiming(int attack_num)
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
// �����蔻��ƃ_���[�W��ۑ�����֐�
//---------------------------------------------------------------------------
void CharacterBase::SetHitDamage(CapsuleCollision attack_hit, int attack_damage, int attack_num)
{
	// �{���͓�܂Ƃ߂ĕۑ��ł������ł��Ȃ��Ȃ��Ă��邽�߂ЂƂÂ��Ă���
	// �����蔻��̕ۑ�
	m_attack_hit_damage[attack_num]->attack_hit = attack_hit;

	// �_���[�W�̕ۑ�
	m_attack_hit_damage[attack_num]->attack_damage = attack_damage;
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
