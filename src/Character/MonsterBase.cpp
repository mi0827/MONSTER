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
void MonsterBase::ActionRolling(const int rolling_speed)
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
	if (start_time <= play_anim_time   && play_anim_time <= end_time)
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
// �U���A�j���[�V�����Ɋւ�����̐ݒ�
//---------------------------------------------------------------------------
void MonsterBase::SetAttackAnimInfo(int attack_anim_start, int attack_anim_max, int except_attack)
{
	// �U���A�j���[�V�����̃X�^�[�g�̕ۑ�
	m_ATTACK_ANIM_START = attack_anim_start;
	// �U���A�j���[�V�����̍ő吔�̕ۑ�
	m_ATTACK_ANIM_MAX = attack_anim_max;
	// �����_���ōU����I�ԍۂɂ͂Ԃ��Ăق����U���ԍ��̕ۑ�
	m_ATTACK_ANIM_EXCEPT = except_attack;
}

//---------------------------------------------------------------------------
// �ړ������֐�
//---------------------------------------------------------------------------
void MonsterBase::MoveActionUpdate(int ran_anim)
{
	// ���񃊃Z�b�g
	m_run_flag = false;

	// �ړ��O�̍��W��U�ۑ����Ă���
	m_before_pos = m_transform.pos;

	// �x�[�X�N���X�̍X�V����
	// �ړ��̏��������ɓ����Ă���
	BaseUpdate(&m_run_flag);

	// run_flag ���オ���Ă�Ƃ�����
	// �v���C���[���[�h��RUN�ȊO�̎�
	if (m_run_flag && m_monster_mode != RUN)
	{
		// �A�j���[�V�����̐؂�ւ��t���O���グ��
		m_animation.m_anim_change_flag = true;
	}

	// �A�j���[�V�����ύX���\�Ȏ���
	if (m_animation.ChangeFlag(m_run_flag)) {
		// ����A�j���[�V�����ɕύX
		m_animation.ChangeAnimation(&m_model, ran_anim, true);
		// �A�j���[�V�������ς��������
		// �v���C���[���[�h�̐؂�ւ�������
		m_monster_mode = RUN;
	}
}


//---------------------------------------------------------------------------
// �ŏ��̍U�����s���p�֐�
//---------------------------------------------------------------------------
void MonsterBase::FirstAttackAction()
{
	// attack_flag ���オ���Ă�Ƃ�����
	// �v���C���[���[�h��ATTACK�ȊO�̎�
	if (m_attack_flag && m_monster_mode != ATTACK)
	{
		// �A�j���[�V�����̐؂�ւ��t���O���グ��
		m_animation.m_anim_change_flag = true;
	}
	// �U�����[�h�ɂ��Ă���
	m_monster_mode = ATTACK;
	// �ŏ��̍U���������_���ɐݒ肷��
	// �U���A�j���[�V�����ȊO��r�����Ă���
	int attack = GetRand(m_ATTACK_ANIM_EXCEPT) + m_ATTACK_ANIM_START;
	m_animation.ChangeAnimation(&m_model, attack, false);
	// �U���A�j���[�V�����ԍ��̕ۑ�
	m_now_attack_anim = attack;

	// ���݂̍U���ԍ���ۑ�����
	m_now_attack = m_now_attack_anim - m_ATTACK_ANIM_START;

	m_stop_combo_flag = true;
}

//---------------------------------------------------------------------------
// �U���֘A�̍X�V����
//---------------------------------------------------------------------------
void MonsterBase::AttackActionUpdate()
{
	// �R���{�����Ă����t���O�������Ă��鎞����
	if (m_stop_combo_flag)
	{
		// �R���{�֐����Ă�
		ComboUpdate();
	}
}

//---------------------------------------------------------------------------
// �U���֘A�̍X�V����
//---------------------------------------------------------------------------
void MonsterBase::JumpAction(int jump_anim, int target_distance)
{
	// �^�[�Q�b�g�Ƃ̋���
	float distance = move.Get_Target_Distance();
	// �^�[�Q�b�g�Ƃ̋��������ȏ�ɂȂ�����
	if (target_distance <= distance)
	{
		// �W�����v�U�������Ăق����̂Ń����t���O������
		m_run_flag = false;

		// attack_flag ���オ���Ă�Ƃ�����
	   // �v���C���[���[�h��ATTACK�ȊO�̎�
		if (m_attack_flag && m_monster_mode != ATTACK)
		{
			// �A�j���[�V�����̐؂�ւ��t���O���グ��
			m_animation.m_anim_change_flag = true;
		}
		// �U�����[�h�ɂ��Ă���
		m_monster_mode = ATTACK;

		m_animation.ChangeAnimation(&m_model, jump_anim, false);
		// �U���A�j���[�V�����ԍ��̕ۑ�
		m_now_attack_anim = jump_anim;
		// ���݂̍U���ԍ���ۑ�����
		m_now_attack = m_now_attack_anim - m_ATTACK_ANIM_START;

		m_stop_combo_flag = true;
		// �W�����v������
		//jump_num = STANDBY;
	}
	else
	{
		// �W�����v�t���O��������
		m_jump_flag = false;
	}
}

//---------------------------------------------------------------------------
// �W�����v�U���̍X�V����
//---------------------------------------------------------------------------
void MonsterBase::JumpActionUpdate(float down_speed)
{
	// �����X�^�[�̃A�j���[�V�������W�����v�������ɏu�Ԃ��璅�n�A�j���[�V�������n�܂�܂ł̊�
	if (m_animation.m_contexts[0].play_time >= 80.0f && m_animation.m_contexts[0].play_time < 110.0f)
	{
		// �W�����v���Ă��牺�ɉ�����X�s�[�h���[���ɂ���
		m_down_speed = 0.0f;
		m_jump_flag = true;
	}

	if (m_animation.m_contexts[0].play_time >= 110.0f)
	{
		// �~���X�s�[�h�����Z�b�g
		m_down_speed = down_speed;

		// �t���O�������Ă��鎞���n�ʂɂ��A�j���[�V�����̎�
		if (m_jump_flag && m_animation.m_contexts[0].play_time >= 140.0f)
		{
			// �ړ���̍��W�̐ݒ�^�[�Q�b�g�̍��W���烂���X�^�[��body�̔��a��
			m_transform.pos.x = move.m_target_info.m_target->pos.x - m_body.m_capsule.radius;
			m_transform.pos.z = move.m_target_info.m_target->pos.z - m_body.m_capsule.radius;
			// �W�����v�t���O��������
			//m_jump_flag = false; // �����鏈����
		}
	}


}

void MonsterBase::SetJumpPos(Vector3 pos)
{
	m_jump_pos = pos;
}


//---------------------------------------------------------------------------
// �R���{�U���X�V����
//---------------------------------------------------------------------------
void MonsterBase::ComboUpdate()
{
	// �R���{���s���Ă�����ԂȂ̂͂���ۑ�����ϐ�
	bool combo_jug;
	// TargetMove���^�[�Q�b�g�Ɛڂ��Ă��邻���łȂ����ŕς��
	// �ڂ��Ă����ړ��\��ԂɂȂ��
	if (move.m_hit)
	{
		// �R���{���ł����ԂłȂ�
		combo_jug = true;
	}
	// �ڂ��Ă��Ď~�܂��Ă���ꍇ
	if (!move.m_hit)
	{
		// �R���{�ł�����
		combo_jug = true;
	}

	// �R���{�\�����f�p�֐�
	m_combo.ComboJudgmentCondition
	(
		&m_combo_flag,
		combo_jug,
		m_animation.m_contexts[0].play_time,
		m_animation.m_contexts[0].animation_total_time
	);

	// �R���{�t���O���オ���Ă���Ƃ�
	if (m_combo_flag)
	{
		// ���̍U���A�j���[�V�����������_���ŃZ�b�g
		m_next_anim = SetRandAttack();

		// �R���{�p�̃A�j���[�V����������
		m_animation.ActionComboChangeAnimation(&m_model, m_next_anim, false, &m_combo_flag);

		if (!m_combo_flag)
		{
			// ���݂̍U���A�j���[�V������ۑ�
			m_now_attack_anim = m_next_anim;
			// ���݂̍U���ԍ���ۑ�����
			m_now_attack = m_now_attack_anim - m_ATTACK_ANIM_START;
		}
	}
}


//---------------------------------------------------------------------------
// �s�������U���A�j���[�V�����������_���őI�Ԃ��߂̊֐�
//---------------------------------------------------------------------------
int MonsterBase::SetRandAttack()
{
	// ���ɍs���Ăق����A�j���[�V����������ϐ�
	int next_anim = 0;

	// �A�j���[�V���������܂閼�Ŗ������[�v
	while (true)
	{
		// ���̃A�j���[�V�����������_���œ����
		// �U���A�j���[�V�����X�^�[�g����U���A�j���[�V�����̍ő�܂ł�
		next_anim = GetRand(m_ATTACK_ANIM_MAX) + m_ATTACK_ANIM_START;
		// ���ɍs�������A�j���[�V�����ƍ��̃A�j���[�V���������Ԃ�����
		if (next_anim == m_now_attack_anim || next_anim == 0)
		{
			// �܂������_���œ���Ȃ���
			next_anim = GetRand(m_ATTACK_ANIM_MAX) + m_ATTACK_ANIM_START;
		}
		break;
	}

	// ���ɍs���Ăق����U���A�j���[�V������Ԃ�
	// ���̓v���C���[�̃J�E���^�[�����܂������Ă��邩�����邽�߂ɌŒ�ɂ��Ă���
	return next_anim;
}
