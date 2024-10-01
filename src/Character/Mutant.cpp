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
#include "src/Character/MonsterBase.h"

#include "src/System/UIBar.h"
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
	m_transform.pos.set(50.0f, 0.0f, 50.0f);
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
	Anima_Load_Init();

	// �U���A�j���[�V�����̐����̂����蔻��񂨓��ꕨ���m�ۂ���
	NEW_Set_Attack_Hit_Damage(ATTACK_ACTION_MAX);

	// �X�e�[�^�X�o�[�̐ݒ�
	Status_Bar_Init();

	// �����蔻����Ƃ��Ăق����^�C�~���O�̂����Ă� 
	SetHitTimeInit();
	// �����X�^�[�̃X�e�[�^�X�̏����ݒ�
	BaseInit(HP_MAX, JUMP_UP_SPEED, JUMP_DOWN_SPEED);
}

//-----------------------------------------------
// �X�V����
//-----------------------------------------------
void Mutant::Update(Transform* target_pos, float target_r)
{
	//clsDx();
	// HP�̒l�����������ǂ���
	m_hp.Update(&m_hp_value);
	

	
	switch (m_life_and_death)
	{

	case alive: // ��������Ƃ�
		// �ړ���̃^�[�Q�b�g�̐ݒ�
		BaseSetTarget(target_pos, target_r);
		LiveUpdate(target_pos,target_r);
		// �����X�^�[��HP����葽������
		if (m_hp_value > 0)
		{
			// �����Ă�
			m_life_and_death = alive;
		}
		else // ����ȊO�̎�
		{

			// ����
			m_life_and_death = die;
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
			if (m_animation.Change_Flag(m_idle_flag))
			{
				// �A�j���[�V���������񂾂̂ɕύX����
				m_animation.Change_Animation(&m_model, die, true);
			}
		}

		break;

	case die: // ���񂾂Ƃ�
		DieUpdate();
		break;

	default:
		break;
	}
	

	// �A�j���[�V�����̍Đ�
	m_animation.Play_Animation(&m_model, m_combo_flag);
	// �����蔻��̍X�V����
	CDUpdate();


	// �v���C���[�ł͂��ꂪ�Ȃ��ƃo�O�邪
	// �����X�^�[�ł͂��ꂪ����ƃo�O��
	// �����X�^�[�̂ق����t���O�Ǘ��Ɏ��s����
	//MonsterMode(m_monster_mode);
}

//-----------------------------------------------
// �����Ă���Ƃ��̍X�V����
//-----------------------------------------------
void Mutant::LiveUpdate(Transform* target_pos, float target_r)
{
	// �ҋ@��Ԃ܂��͑���̎�������
	// �ړ�����
	if (m_idle_flag == true || m_run_flag == true /*&& m_monster_mode == IDLE*/)
	{
		// �����X�^�[�̉�]���Ă悢�悤�ɂ���
		move.Set_Can_Rotate(true);
		// �ړ�����
		Move_Update();
	}

	switch (m_monster_mode)
	{
	case IDLE: // ��~��� 
		if (m_idle_flag)
		{
			//Player_Mode(IDLE);
			// �A�j���[�V�����ύX���\�Ȏ���
			if (m_animation.Change_Flag(m_idle_flag))
			{
				// �A�j���[�V�������~�ɕύX����
				m_animation.Change_Animation(&m_model, idle, true);
			}

			// �ړ����~�܂��Ă�����
			if (!move.m_hit)
			{
				// �ŏ��̍U�����s��
				// �U���t���O���グ��
				m_attack_flag = true;
				Attack_First();
			}
		}
		break;
	case RUN:
		// �ҋ@�t���O�𖈉񃊃Z�b�g
		m_idle_flag = false;
		// run_flagf�t���O������������
		if (m_run_flag == false)
		{
			// �ҋ@�t���O���グ��
			m_idle_flag = true;
			// �A�j���[�V�����ύX���s����悤�ɂ���
			m_animation.m_anim_change_flag = true;
			m_monster_mode = IDLE;
		}

		// �����Ă���ԂɈ��ȏ�̋������󂢂���
		// �W�����v�U��������
		Attack_Jump();

		break;
	case ATTACK:

		// �����Ăق����Ȃ��̂Ńt���O��
		m_idle_flag = false;
		m_run_flag = false;


		// �W�����v�U�����̏���
		if (m_now_attack_anim == jump)
		{
			Jump_Update();
		}

		// ���[�����O�A�N�V�������̏���
		if (m_now_attack_anim == rolling)
		{
			Action_Rolling(ROLLING_SPEED);
		}
		// �U����(�A�j���[�V������)�͉�]���Ăق����Ȃ�
		move.Set_Can_Rotate(false);
		// �����Ă����͈͂����v���C���[�̌����Ƃ����Ă����邩�𒲂ׂ�
		move.m_hit = move.Target_Hit();

		// �A�j���[�V�����̍Đ����I������Ƃ�
		if (m_animation.m_contexts[0].play_time >= m_animation.m_contexts[0].animation_total_time)
		{
			// �ړ����Ă�����Ԃ�������
			if (move.m_hit)
			{
				// �ړ��t���O�𗧂Ă�
				m_run_flag = true;
				//m_monster_mode = RUN;
			}
		}
		// �U���p�̊֐�
		Attack_Update();

		break;
	}
}


//-----------------------------------------------
// ���񂾂Ƃ��̍X�V����
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
	//attack_hit_damage[m_now_attack].attack_hit.Draw();
	// �J�v�Z���̕`��(�����蔻��)
	m_body.Draw();
	m_left_hand.Draw();
	m_right_hand.Draw();
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
void Mutant::Status_Bar_Init()
{
	// HP��
	m_hp_value = HP_MAX;
	// HP�̐ݒ�
	m_hp.Set({ 25,25 }, { SCREEN_W - 50, 25 }, &m_hp_value, true);
	m_hp.SetColor(255, 100, 50, &m_hp.m_color);
	m_hp.SetColor(128, 128, 128, &m_hp.m_back_color);
	m_hp.SetColor(0, 0, 0, &m_hp.m_line_color);
	m_hp.SetColor(255, 255, 255, &m_hp.m_character_color);
	m_hp.SetName("HP");

}

//-----------------------------------------------
// �X�e�[�^�X�o�[�`��p�֐�
//-----------------------------------------------
void Mutant::Status_Bar_Draw()
{
	
	//===================
	// UI�̕`��
	//===================
	m_hp.Draw();
}


//-----------------------------------------------
// �����蔻����s���ė~�����^�C�~���O��ۑ�����֐�
// �S���̍U�������蔻��ɐݒ肷��(��ł��)
//-----------------------------------------------
void Mutant::SetHitTimeInit()
{
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
	}
}

//-----------------------------------------------
// �A�j���[�V�����̏�������
//-----------------------------------------------
void Mutant::Anima_Load_Init()
{
	// �A�j���[�V�����̏����ݒ�
	m_animation.Init_Animation(anim_max, idle);
	// �A�j���[�V�����̓ǂݍ���
	m_animation.Load_Animation("Data/Model/Mutant/Animation/idle.mv1", idle, 0, 1.0f); //!< �A�C�h��
	m_animation.Load_Animation("Data/Model/Mutant/Animation/Run.mv1", run, 0, 1.0f); //!< ����
	m_animation.Load_Animation("Data/Model/Mutant/Animation/die.mv1", die, 0, 1.0f); //!< ���S

	// �����ƃ����X�^�[���ۂ��U����T���Ă���
	m_animation.Load_Animation("Data/Model/Mutant/Animation/Attack/Punch1.mv1", attack_1, 0, 1.0f); //!< �U���P
	m_animation.Load_Animation("Data/Model/Mutant/Animation/Attack/Punch2.mv1", attack_2, 0, 1.0f); //!< �U���Q
	m_animation.Load_Animation("Data/Model/Mutant/Animation/Attack/Punch3.mv1", attack_3, 0, 1.0f); //!< �U���R
	m_animation.Load_Animation("Data/Model/Mutant/Animation/Attack/Punch4.mv1", attack_4, 0, 1.0f); //!< �U���S
	m_animation.Load_Animation("Data/Model/Mutant/Animation/Attack/Rolling.mv1", rolling, 0, 1.0f); //!< ���[�����O
	m_animation.Load_Animation("Data/Model/Mutant/Animation/Attack/jump.mv1", jump, 0, 1.0f); //!< �W�����v
	// �ŏ��̓f�t�H���g�A�j���[�V���������Ă���
	m_animation.Init_Attach_Animation(&m_model, idle, true);
}

//-----------------------------------------------
// �v���C���[�̈ړ��p�֐�
//-----------------------------------------------
void Mutant::Move_Update()
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
	if (m_animation.Change_Flag(m_run_flag)) {
		// ����A�j���[�V�����ɕύX
		m_animation.Change_Animation(&m_model, run, true);
		// �A�j���[�V�������ς��������
		// �v���C���[���[�h�̐؂�ւ�������
		m_monster_mode = RUN;
	}
}

//-----------------------------------------------
// �ŏ��̍U���𔻒f����
//-----------------------------------------------
void Mutant::Attack_First()
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
	int attack = GetRand(attack_rolling) + ATTACK_ANIM_START;
	m_animation.Change_Animation(&m_model, attack, false);
	// �U���A�j���[�V�����ԍ��̕ۑ�
	m_now_attack_anim = attack_1;

	// ���݂̍U���ԍ���ۑ�����
	m_now_attack = m_now_attack_anim - ATTACK_ANIM_START;

	m_stop_combo_flag = true;
}

//-----------------------------------------------
// �U���Ɋւ���X�V����
//-----------------------------------------------
void Mutant::Attack_Update()
{
	// �R���{�����Ă����t���O�������Ă��鎞����
	if (m_stop_combo_flag)
	{
		// �R���{�֐����Ă�
		Combo_Update();
	}
}

//-----------------------------------------------
// �W�����v�U���Ɋւ��鏈��
//-----------------------------------------------
void Mutant::Attack_Jump()
{
	// �^�[�Q�b�g�Ƃ̋���
	float distance = move.Get_Target_Distance();
	// �^�[�Q�b�g�Ƃ̋��������ȏ�ɂȂ�����
	if (TARGET_DISTANCE <= distance)
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

		m_animation.Change_Animation(&m_model, jump, false);
		// �U���A�j���[�V�����ԍ��̕ۑ�
		m_now_attack_anim = jump;
		// ���݂̍U���ԍ���ۑ�����
		m_now_attack = m_now_attack_anim - ATTACK_ANIM_START;

		m_stop_combo_flag = true;
		// �W�����v������
		jump_num = STANDBY;
	}
	else
	{
		// �W�����v�t���O��������
		m_jump_flag = false;
	}
}

//-----------------------------------------------
// �W�����v�U�����̏���
//-----------------------------------------------
void Mutant::Jump_Update()
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
		m_down_speed = JUMP_DOWN_SPEED;

		// �t���O�������Ă��鎞���n�ʂɂ��A�j���[�V�����̎�
		if (m_jump_flag&& m_animation.m_contexts[0].play_time >= 140.0f)
		{
			// �ړ���̍��W�̐ݒ�^�[�Q�b�g�̍��W���烂���X�^�[��body�̔��a��
			m_transform.pos.x = move.m_target_info.m_target->pos.x - m_body.m_capsule.radius;
			m_transform.pos.z = move.m_target_info.m_target->pos.z - m_body.m_capsule.radius;
			// �W�����v�t���O��������
			m_jump_flag = false; // �����鏈����
		}
	}
	//switch (jump_num)
	//{
	//case STANDBY: // �ҋ@
	//	// �w��̃A�j���[�V�����t���[���ɂȂ�����w��̏����̂Ƃ���ɍs���悤�ɂ�����

		//	
		//	break;
		//case GOUP:        // �オ��
		//	m_transform.pos.y += 5;
		//	// ���̍����܂ŏオ������
		//	if (m_transform.pos.y >= JUMP_HEIGHT)
		//	{
		//		// �オ��̂��~�߂Ĉړ��̏�����
		//		m_transform.pos.y = JUMP_HEIGHT;
		//		jump_num = MOVE;
		//	}
		//	break;

		//case MOVE:        // ���W�ړ�
		//	// �ړ���̍��W�̐ݒ�^�[�Q�b�g�̍��W���烂���X�^�[��body�̔��a��菭�����������炢���炵���Ƃ�
		//	m_transform.pos.x = move.m_target_info.m_target->pos.x - m_body.m_capsule.radius + 5;
		//	m_transform.pos.z = move.m_target_info.m_target->pos.z - m_body.m_capsule.radius + 5;

		//	jump_num = STANDBY; // ������^�C�~���O�����킹�邽�߂ɂ�������ҋ@��
		//	break;

		//case DROPDOWN:   // ������
		//	m_transform.pos.y -= 5;
		//	// �}�ʂɂ����痎����̂���߂�
		//	if (m_transform.pos.y <= 0)
		//	{
		//		m_transform.pos.y = 0;
		//	}
		//	break;
		//}

}

//-----------------------------------------------
// �R���{�̔��f������֐�
//-----------------------------------------------
void Mutant::Combo_Update()
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
	m_combo.Combo_Judgment_Condition
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
		m_next_anim = Set_Rand_Attack();

		// �R���{�p�̃A�j���[�V����������
		m_animation.Action_Change_Animation(&m_model, m_next_anim, false, &m_combo_flag);

		if (!m_combo_flag)
		{
			// ���݂̍U���A�j���[�V������ۑ�
			m_now_attack_anim = m_next_anim;
			// ���݂̍U���ԍ���ۑ�����
			m_now_attack = m_now_attack_anim - ATTACK_ANIM_START;
		}
	}
}


//-----------------------------------------------
// �s�������A�j���[�V�����������_���őI�Ԃ��߂̊֐�
//-----------------------------------------------
int Mutant::Set_Rand_Attack()
{
	// ���ɍs���Ăق����A�j���[�V����������ϐ�
	int next_anim = 0;

	// �A�j���[�V���������܂閼�Ŗ������[�v
	while (true)
	{
		// ���̃A�j���[�V�����������_���œ����
		// �U���A�j���[�V�����X�^�[�g����U���A�j���[�V�����̍ő�܂ł�
		next_anim = GetRand(ATTACK_ANIM_MAX) + ATTACK_ANIM_START;
		// ���ɍs�������A�j���[�V�����ƍ��̃A�j���[�V���������Ԃ�����
		if (next_anim == m_now_attack_anim || next_anim == 0)
		{
			// �܂������_���œ���Ȃ���
			next_anim = GetRand(ATTACK_ANIM_MAX) + ATTACK_ANIM_START;
		}
		break;
	}

	// ���ɍs���Ăق����U���A�j���[�V������Ԃ�
	return next_anim;
}
