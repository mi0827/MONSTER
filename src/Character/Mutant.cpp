#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/System/Transform.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Collision/BoxCollision.h"
#include "src/Collision/CapsuleCollision.h"


#include "src/System/TargetMove.h"
#include "src/Action/Combo.h"
#include "src/System/UIBar.h"
#include "src/Character/MonsterBase.h"

#include "Mutant.h"

namespace
{
	// �v���C���[�̂Ƃ̂����蔻��Ŏg��box�̂����蔻��̃T�C�Y
	const Vector3 M_MOVE_SIZE{ 15.0f,0,15.0f };
	// ��L�ō쐬�����T�C�Y�̔����̃T�C�Y
	const Vector3 M_MOVE_SIZE_HALF{ M_MOVE_SIZE / 2 };
}


//-----------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------
Mutant::Mutant()
{
	// �ŏ��̓A�C�h����Ԃɂ��Ă���
	m_idle_flag = true;
	// �ŏ��̓A�C�h����Ԃɂ��Ă���
	m_monster_mode = IDLE;

	// �������W�̐ݒ�
	m_transform.pos.set(100.0f, 0.0f, 100.0f);
	// ���f���̃X�P�[���̐ݒ�
	m_transform.scale.set(0.2f, 0.2f, 0.2f);
}


//-----------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------
Mutant::~Mutant()
{
	Exit();
}

//-----------------------------------------------
// ����������
//-----------------------------------------------
void Mutant::Init()
{

	// aaaaa

	// ���f���摜�̓ǂݍ���
	m_model.LoadModel("Data/Model/Mutant/Mutant.mv1");

	// �A�j���[�V�����̏����ݒ�
	AnimLoadInit();
	// �U���A�j���[�V�����Ɋւ�����̐ݒ�
	SetAttackAnimInfo(ATTACK_ANIM_START, ATTACK_ANIM_MAX, attack_rolling);
	// �U���A�j���[�V�����̐����̂����蔻��p�̓��ꕨ���m�ۂ���
	NEW_Set_Attack_Hit_Damage(ATTACK_ACTION_MAX);

	// �X�e�[�^�X�o�[�̐ݒ�
	StatusBarInit();

	// �U���Ɋւ��邱�Ƃ̏����֐�
	SetAttackInfo();
	// �����X�^�[�̃X�e�[�^�X�̏����ݒ�
	BaseInit(HP_VALUE_MAX/* JUMP_UP_SPEED, JUMP_DOWN_SPEED*/);
	// �A�j���[�V��������̃t���O���グ�Ă���
	m_animation.m_anim_change_flag = true;
}

//-----------------------------------------------
// �X�V����
//-----------------------------------------------
void Mutant::Update(Transform* target_pos, float target_r)
{

	// �v���C���[�ł͂��ꂪ�Ȃ��ƃo�O�邪
	// �����X�^�[�ł͂��ꂪ����ƃo�O��
	// �����X�^�[�̂ق����t���O�Ǘ��Ɏ��s����
	MonsterMode(m_monster_mode);

	//clsDx();
	// HP�̒l�����������ǂ���
	m_hp_bra.Update(m_hp_value);
	m_stun_bra.Update(m_stun_value);


	switch (m_life_and_death)
	{

	case alive: // ��������Ƃ�
		// �ړ���̃^�[�Q�b�g�̐ݒ�
		BaseSetTarget(target_pos, target_r);
		LiveUpdate(target_pos, target_r);
		// �����X�^�[��HP����葽������
		if (m_hp_value > 0)
		{
			// �����Ă�
			m_life_and_death = alive;
		}
		else // ����ȊO�̎�
		{

			// ����
			m_life_and_death = die_anim;
			// �v���C���[�̏�Ԃ���DIE�ύX
			m_monster_mode = DIE;
			// ���ׂẴt���O��������
			m_idle_flag = false;
			m_run_flag = false;
			m_attack_flag = false;

			// �A�j���[�V�����̐؂�ւ��t���O���グ��
			m_animation.m_anim_change_flag = true;
			// �ҋ@�t���O�𖈉񃊃Z�b�g
			m_idle_flag = true;
			// ���񂾃A�j���[�V����������
			if (m_animation.ChangeFlag(m_idle_flag))
			{
				// �A�j���[�V���������񂾂̂ɕύX����
				m_animation.ChangeAnimation(&m_model, die_anim, true);
			}
		}

		break;

	case die_anim: // ���񂾂Ƃ�
		DieUpdate();
		break;

	default:
		break;
	}


	// �A�j���[�V�����̍Đ�
	m_animation.PlayAnimation(&m_model, m_combo_flag);
	// �����蔻��̍X�V����
	CDUpdate();


}

//-----------------------------------------------
// �����Ă���Ƃ��̍X�V����
//-----------------------------------------------
void Mutant::LiveUpdate(Transform* target_pos, float target_r)
{

	// �X�^����ԂɂȂ邩�Ȃ�Ȃ���
	if (m_stun_value <= 0 && m_stun_flag == false)
	{
		// �X�^����ԂɈړ�
		m_monster_mode = STUN;
		// �X�^���t���O���グ��
		m_stun_flag = true;
		m_attack_flag = false;
		// �A�j���[�V�����ύX�t���O�𗧂Ă�
		m_animation.m_anim_change_flag = true;
	}



	switch (m_monster_mode)
	{
	case IDLE: // ��~��� 
		IdleActionUpdate(idle_anim);

		break;
	case RUN:
		// �ҋ@�t���O�𖈉񃊃Z�b�g
		m_idle_flag = false;
		// �ҋ@��Ԃ܂��͑���̎�������
		// �ړ�����
		//if (m_idle_flag == true || m_run_flag == true /*&& m_monster_mode == IDLE*/)
		{
			// �����X�^�[�̉�]���Ă悢�悤�ɂ���
			move.SetCanRotate(true);
			// �ړ�����
			MoveAction(run_anim);
		}

		// �����Ă���Ԃ̃t���[�������Z����
		m_running_frame_count++;

		// �����Ă��鎞�Ԃ����ȏ�ɂȂ�����
		if (m_running_frame_count >= CHANGE_JUMP_RUNNIG_FRAME)
		{
			// ���[�����O�A�N�V�������Z�b�g����
			SetRollingAction(rolling_anim, ROLLING_TARGET_DISTANCE);
			// �J�E���g�����Z�b�g����
			m_running_frame_count = 0;
		}

		// �����Ă��鎞�Ԃ����ȏ�ɂȂ�����
		if (m_running_frame_count >= CHANGE_JUMP_RUNNIG_FRAME)
		{
			// �W�����v�A�N�V�������Z�b�g����
			JumpAction(jump_anim, JUMP_TARGET_DISTANCE);
			// �J�E���g�����Z�b�g����
			m_running_frame_count = 0;
		}

		

		break;
	case ATTACK:
		// �X�^�����͂ق��̍U�����������Ăق����Ȃ�
		if (m_stun_flag == true)
		{
			break;
		}

		// �W�����v�t���O�������Ă���Ƃ�
		if (m_jump_flag)
		{
			// �W�����v�̍X�V����
			JumpActionUpdate(JUMP_MOV_SPEED, JUMP_STRAT_FRAME, JUMP_END_FRAME);
			// �W�����v�A�j���[�V�������I������Ƃ��ɃA�j���[�V�����ł������W�̂����͂����Œ���
			if (m_animation.m_contexts[0].is_playing == false)
			{
				m_transform.pos.x += JUMP_DEVIATION_POS * sinf(TO_RADIAN(m_transform.rot.y));
				m_transform.pos.z += JUMP_DEVIATION_POS * cosf(TO_RADIAN(m_transform.rot.y));
			}
		}

		// ���[�����O�A�N�V�������̏���
		if (m_now_attack_anim == rolling_anim)
		{
			ActionRolling(ROLLING_SPEED, ROLLING_STRAT_FRAME, ROLLING_END_FRAME);
		}


		
		// �����Ă����͈͂����v���C���[�̌����Ƃ����Ă����邩�𒲂ׂ�
		move.m_hit = move.TargetHit();

		// �U���p�̊֐�
		// �W�����v�ƃ��[�����O�̂��s���Ă��Ȃ��Ƃ�
		if (m_jump_flag == false && m_rolling_flag == false)
		{
			// �����X�^�[�̈ړ����ł��Ȃ������ɓG��������
			if (!move.m_hit)
			{
				// �U�����n�߂�
				AttackActionComboUpdate();
			}
		
		}

		// �U����(�A�j���[�V������)�͉�]���Ăق����Ȃ�
		move.SetCanRotate(false);

		break;
	case STUN:
		// �W�����v���ɃX�^������Ă��܂����Ƃ�
		if (m_jump_flag == true)
		{
			m_transform.pos.x += JUMP_DEVIATION_POS * sinf(TO_RADIAN(m_transform.rot.y));
			m_transform.pos.z += JUMP_DEVIATION_POS * cosf(TO_RADIAN(m_transform.rot.y));
			// �W�����v�t���O��������
			m_jump_flag = false;
		}

		StunActionUpdate(stun_down_anim, stun_up_anim, STUN_VALUE_MAX);
		//if (m_anim_ && m_animation.m_contexts[0].is_playing == false)
		//{
		//	// �X�^���A�j���[�V�����ł��ꂽ���W������
		//	m_transform.pos.z += 23 * cosf(TO_RADIAN(m_transform.rot.y));
		//	m_transform.pos.x += 23 * sinf(TO_RADIAN(m_transform.rot.y));

		//}
		break;
	}
}


//-----------------------------------------------
// ���񂾂Ƃ��̍X�V����(�Q�[���V�[���Œ��ڌĂ�)
//-----------------------------------------------
void Mutant::DieUpdate()
{
	// ���񂾃A�j���[�V�������ǂ�Ȃ��悤��
	// ���̂Ƃ���܂Ői�񂾂�
	if (m_animation.m_contexts[0].play_time >= 260)
	{
		// �����O�ɖ߂�
		m_animation.m_contexts[0].play_time = 200;
	}


}

//-----------------------------------------------
// �`�揈��
//-----------------------------------------------
void Mutant::Draw()
{
	if (m_attack_flag)
	{
		if (AttackHitGoodTiming(m_now_attack))
		{
			//m_right_hand.Draw();
			m_attack_hit_damage[m_now_attack]->attack_hit.Draw();
		}

	}

	if (m_jump_flag)
	{
		DrawCapsule3D(m_jump_pos.VGet(), m_jump_pos.VGet(), 10.0f, 8.0f, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
	}


	// �J�v�Z���̕`��(�����蔻��)
	m_body.Draw();
	/*m_body.Draw();
	m_left_hand.Draw();
	m_right_hand.Draw();*/
	// ���f���̕`�� (�`�����ɂ��Ȃ��Ɠ����蔻�肪������������)
	m_model.DrawModel(&m_transform);
}

//-----------------------------------------------
// �I������
//-----------------------------------------------
void Mutant::Exit()
{
}

//-----------------------------------------------
// �o�ꉉ�o�p�̍X�V����
//-----------------------------------------------
void Mutant::EntryUpdate()
{
	// �����ł��邱��
	// �o��V�[���ɂ��������т̃A�j���[�V����������

	// �o��A�j���[�V�����̃Z�b�g(���[�v�����Ȃ�)
	if (m_animation.ChangeFlag(true))
	{
		m_animation.ChangeAnimation(&m_model, shout_anim, true);
	}

	// �A�j���[�V�����̍Đ�
	m_animation.PlayAnimation(&m_model, m_combo_flag);
}

//-----------------------------------------------
// HP�����܂Ō������Ƃ��̃��x���A�b�v����
//-----------------------------------------------
void Mutant::ReinforceUpdate()
{
	// HP�������ɂȂ�����
	// �_���\�W��H������A�j���[���[�V����������
	// ���̂��Ƃɋ��ԃA�j���[�V����������
	// ���̌�ōU���𑝂₵����_���[�W�ʂ𑝂₵������G�t�F�N�g��h��ɂ�����ω���������

}

//-----------------------------------------------
// �����蔻��
//-----------------------------------------------
void Mutant::CDUpdate()
{
	// �L�����{�̂̓����蔻��̃J�v�Z���i��ŏ����j
	// ���̍��W�����f���̃m�[�h���łƂ��Ă���Ƃ�������
	m_body.CreateNodoCapsule(&m_model, 0, 7, 8.0f);

	// ����̂����蔻��
	m_left_hand.CreateNodoCapsule(&m_model, 13, 19, 3.0f);

	// �E��̓����蔻��
	// �܂̕����������蔻�肪�Ȃ�
	m_right_hand.CreateNodoCapsule(&m_model, 9, 11, 5.0f);

	// �U�����̓����蓖���蔻��̕ۑ�
	SetHitDamage(m_left_hand, m_attack_damage[attack_punch_1], (attack_punch_1));
	SetHitDamage(m_right_hand, m_attack_damage[attack_punch_2], (attack_punch_2));
	SetHitDamage(m_right_hand, m_attack_damage[attack_punch_3], (attack_punch_3));
	SetHitDamage(m_right_hand, m_attack_damage[attack_punch_4], (attack_punch_4));
	SetHitDamage(m_body, m_attack_damage[attack_rolling], (attack_rolling));
	SetHitDamage(m_body, m_attack_damage[attack_jump], (attack_jump));

}

//-----------------------------------------------
// �X�e�[�^�X�o�[�̐ݒ�p�֐�
//-----------------------------------------------
void Mutant::StatusBarInit()
{
	// HP�̎c�ʂ�ݒ�
	m_hp_value = HP_VALUE_MAX;
	// HP�o�[�̐ݒ�
	m_hp_bra.Set({ 25,25 }, { SCREEN_W - 50, 25 }, &m_hp_value, true);
	m_hp_bra.SetColor(255, 100, 50, &m_hp_bra.m_color);
	m_hp_bra.SetColor(128, 128, 128, &m_hp_bra.m_back_color);
	m_hp_bra.SetColor(0, 0, 0, &m_hp_bra.m_line_color);
	m_hp_bra.SetColor(255, 255, 255, &m_hp_bra.m_character_color);
	m_hp_bra.SetName("HP");

	// �X�^���l�̎c�ʂ�ݒ�
	m_stun_value = STUN_VALUE_MAX;
	// �X�^���o�[�̐ݒ�
	m_stun_bra.Set({ 25,70 }, { SCREEN_W - 50, 20 }, &m_stun_value, true);
	m_stun_bra.SetColor(255, 255, 0, &m_stun_bra.m_color);
	m_stun_bra.SetColor(128, 128, 128, &m_stun_bra.m_back_color);
	m_stun_bra.SetColor(0, 0, 0, &m_stun_bra.m_line_color);
	m_stun_bra.SetColor(255, 255, 255, &m_stun_bra.m_character_color);
	//m_stun_bra.SetName("STUN");
}

//-----------------------------------------------
// �X�e�[�^�X�o�[�`��p�֐�
//-----------------------------------------------
void Mutant::StatusBarDraw()
{

	//===================
	// UI�̕`��
	//===================
	m_hp_bra.Draw();
	m_stun_bra.Draw();

}


//-----------------------------------------------
// �����蔻����s���ė~�����^�C�~���O��ۑ�����֐�
// �S���̍U�������蔻��ɐݒ肷��(��ł��)
//-----------------------------------------------
void Mutant::SetAttackInfo()
{

	//------------------------------------------
	// �R���|�p�^�[�������p�^�[�����邩�̐ݒ�
	//------------------------------------------
	ComboPatternNumberInit(M_COMBO_PATTERN_MAX);

	//------------------------------------------
	// �e�R���{�p�^�[���̃R���{�̐ݒ�
	//------------------------------------------
	for (int i = 0; i < M_COMBO_PATTERN_MAX; i++)
	{
		// �e�R���{�̌㌄��ۑ�
		int frame = m_combo_rear_crevice_frame[i];
		// �e�R���{�p�^�[���̐ݒ�
		ComboPatternInfoInit(i, M_COMBO_NUM_MAX, frame, m_combo_pattern[i]);
	}


	//------------------------------------------
	// �����蔻��̃^�C�~���O�̐ݒ�
	//------------------------------------------
	SetHitTime(attack_frame[attack_punch_1].start_frame, attack_frame[attack_punch_1].end_frame, attack_punch_1);
	SetHitTime(attack_frame[attack_punch_2].start_frame, attack_frame[attack_punch_2].end_frame, attack_punch_2);
	SetHitTime(attack_frame[attack_punch_3].start_frame, attack_frame[attack_punch_3].end_frame, attack_punch_3);
	SetHitTime(attack_frame[attack_punch_4].start_frame, attack_frame[attack_punch_4].end_frame, attack_punch_4);
	SetHitTime(attack_frame[attack_rolling].start_frame, attack_frame[attack_rolling].end_frame, attack_rolling);
	SetHitTime(attack_frame[attack_jump].start_frame, attack_frame[attack_jump].end_frame, attack_jump);
}


//-----------------------------------------------
// �t���O�Ǘ��p�֐�
// ���̊֐����Ȃ��ƐF�X�ȃo�O���o��
//-----------------------------------------------
void Mutant::MonsterMode(int mode)
{
	switch (mode)
	{
	case IDLE:
		m_idle_flag = true;
		m_run_flag = false;
		m_attack_flag = false;
		break;
	case RUN:
		m_idle_flag = false;
		m_run_flag = true;
		m_attack_flag = false;

		break;
	case ATTACK:

		m_idle_flag = false;
		m_run_flag = false;
		m_attack_flag = true;
		break;
	case DIE:
		m_idle_flag = false;
		m_run_flag = false;
		m_attack_flag = false;

		break;
	case STUN:

		m_idle_flag = false;
		m_run_flag = false;
		m_attack_flag = false;

		break;
	}
}

//-----------------------------------------------
// �A�j���[�V�����̏�������
//-----------------------------------------------

void Mutant::AnimLoadInit()
{
	// �A�j���[�V�����̏����ݒ�
	m_animation.InitAnimation(anim_max, idle_anim);
	// �A�j���[�V�����̓ǂݍ���
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/idle2.mv1", idle_anim, 0, 1.0f); //!< �A�C�h��
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/Run.mv1", run_anim, 0, 1.0f); //!< ����
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/die.mv1", die_anim, 0, 1.0f); //!< ���S
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/shout.mv1", shout_anim, 0, 0.5f); //!< ����
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/hit_damage.mv1", hit_damage_anim, 0, 1.0f); //!< �_���[�W���󂯂���
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/stun_down2.mv1", stun_down_anim, 0, 1.5f);  //!< �X�^����H��������̃_�E��
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/stun_up.mv1", stun_up_anim, 0, 2.0f);          //!< �X�^����H��������̋N���オ��


	// �����ƃ����X�^�[���ۂ��U����T���Ă���
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/Attack/Punch1.mv1", attack_1_anim, 0, 1.0f); //!< �U���P
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/Attack/Punch2.mv1", attack_2_anim, 0, 1.0f); //!< �U���Q
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/Attack/Punch3.mv1", attack_3_anim, 0, 1.0f); //!< �U���R
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/Attack/Punch4.mv1", attack_4_anim, 0, 1.0f); //!< �U���S
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/Attack/Rolling.mv1", rolling_anim, 0, 1.0f); //!< ���[�����O
	m_animation.LoadAnimation("Data/Model/Mutant/Animation/Attack/JumpAttack.mv1", jump_anim, 0, 1.0f); //!< �W�����v
	// �ŏ��̓f�t�H���g�A�j���[�V���������Ă���
	m_animation.InitAttachAnimation(&m_model, idle_anim, true);


}

