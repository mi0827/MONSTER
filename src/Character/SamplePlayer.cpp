#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/System/Transform.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Collision/CapsuleCollision.h"
#include "src/Collision/BoxCollision.h"

#include "src/Action/Combo.h"
#include "src/System/Move.h"

#include "src/System/UIBar.h"

#include "src/Character/CharacterBase.h"
#include "SamplePlayer.h"



//-----------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------
SamplePlayer::SamplePlayer()
{
	// �ŏ��̓A�C�h����Ԃɂ��Ă���
	m_idle_flag = true;
	// �ŏ��̓A�C�h����Ԃɂ��Ă���
	m_player_mode = IDLE;


	// �ړ��̍ۂ̓����蔻��̃T�C�Y�̐ݒ�
	m_move_hit_size = { 3.0f,5.0f,3.0f };
}


//-----------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------
SamplePlayer::~SamplePlayer()
{
	// �I������������
	Exit();
}


//-----------------------------------------------
// ����������
//-----------------------------------------------
void SamplePlayer::Init()
{

	// �x�[�X�N���X�ōs���Ă��鏉�������Ă�
	CharacterBase::BaseInit(PLAYER_HIT_R, HP_MAX);

	// �v���C���[�̏������W
	SetCharacterPos({ 170,0,170 });
	// �����̐ݒ�
	SetCharacterRot({ 0,180.0f,0 });
	// ���f���̃X�P�[���̐ݒ�
	m_transform.scale.set(0.1f, 0.1, 0.1);


	// ���f���摜�̓ǂݍ���
	m_model.LoadModel("Data/Model/Player/Player.mv1");
	// �A�j���[�V�����̏����ݒ�
	Anima_Load_Init();

	// �U���A�j���[�V�����̐����̓����蔻��̓��ꕨ���m�ۂ���
	NEW_Set_Attack_Hit_Damage(ATTACK_ACTION);

	// �����蔻����Ƃ��Ăق����^�C�~���O�̂����Ă�
	SetHitTimeInit();

	// �X�e�[�^�X�o�[�̐ݒ�
	StatusBarInit();
}


//-----------------------------------------------
// �X�V����
//-----------------------------------------------
void SamplePlayer::Update(Vector3* camera_rot)
{

	// HP�̒l�����������ǂ���
	m_hp.Update(&m_hp_value);



	// �����Ă邩����ł邩�ŏ�����ς���
	switch (m_life_and_death)
	{
	case alive: // �����Ă鎞�̏���

		// �����Ă鎞�̍X�V����
		LiveUpdate(camera_rot);
		// �v���C���[��HP���O��葽������
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
			m_player_mode = DIE;
			// �A�j���[�V�����̐؂�ւ��t���O���グ��
			m_animation.m_anim_change_flag = true;

			// ���񂾃A�j���[�V����������
			if (m_animation.Change_Flag(true))
			{
				// �A�j���[�V�������~�ɕύX����
				m_animation.Change_Animation(&m_model, die, true);
			}
		}

		break;

	case die: // ���񂾂Ƃ��̏���
		DieUpdate();
		break;

	default:
		break;
	}


	// �A�j���[�V�����̍Đ�
	m_animation.Play_Animation(&m_model, m_combo_flag);

	// �����蔻��̍X�V����
	CDUpdate();

	// �t���O�Ǘ��p�֐�
	PlayerMode(m_player_mode);

	// �n�ʂɖ��܂��Ă��܂������̂��߂̏���
	if (m_transform.pos.y <= 0)
	{
		m_transform.pos.y = 0;
	}

}


//-----------------------------------------------
// �����Ă���Ƃ��̍X�V����
//-----------------------------------------------
void SamplePlayer::LiveUpdate(Vector3* camera_rot)
{
	// ���[�����O�͖��G�Ȃ̂Ń��[�����O�̊ԂɍU�����󂯂Ȃ�
	// �v���C���[�̃��[�h���J�E���^�[�łȂ��Ƃ�
	// �v���C���[���U�����󂯂����̃`�F�b�N
	if (!m_rolling_flag || m_player_mode != COUNTER)
	{
		CheckHitDamage();
	}


	// �ҋ@��Ԃ܂��͑���̎�����
	if (m_idle_flag == true || m_run_flag == true)
	{
		// ���[�����O�������ȊO ���� �G����̃_���[�W��H������t���O�������ĂȂ�������
		if (m_rolling_flag == false && m_damage_flag == false && m_counter_flag== false)
		{
			// �ړ�����
			Move_Update(camera_rot);
		}
	}

	// �_���[�W��H������t���O�������Ă��Ȃ�������
	if (m_damage_flag == false && !m_counter_flag )
	{
		// ���[�����O�̐؂�ւ�
		SetRolling();
	}


	// �L�����N�^�[�̏�Ԃɂ���čs����ς���
	switch (m_player_mode)
	{
	case IDLE: // �A�C�h���̎�
		if (m_idle_flag)
		{
			//Player_Mode(IDLE);
			// �A�C�h����ԂȂ̂ŃA�C�h���t���O�𗧂Ă�
			m_idle_flag = true;

			// �A�j���[�V�����ύX���\�Ȏ���
			if (m_animation.Change_Flag(m_idle_flag))
			{
				// �A�j���[�V�������~�ɕύX����
				m_animation.Change_Animation(&m_model, idle, true);
			}
		}
		// �ŏ��̍U���𔻒f����
		AttackFirst();
		break;
	case RUN: // �ړ��� 
		// �ҋ@�t���O�𖈉񃊃Z�b�g
		m_idle_flag = false;
		// run_flagf�t���O������������
		if (m_run_flag == false)
		{
			// �ҋ@�t���O���グ��
			m_idle_flag = true;
			// �A�j���[�V�����ύX���s����悤�ɂ���
			m_animation.m_anim_change_flag = true;
			// �v���C���[�̏�Ԃ�IDLE�ɕύX
			m_player_mode = IDLE;
		}

		// �ŏ��̍U���𔻒f����
		AttackFirst();

		break;
	case ROLLING: // ���[�����O�A�N�V���������Ă��鎞
		ActionRolling();

		break;
	case COUNTER:
		CounterAction();

		break;

	case ATTACK: // �U�����J��o���Ă��鎞

		// �R���{�t���O�������Ă��Ȃ���
		// �U���A�j���[�V�����̍Đ����I����Ă�����
		if (m_combo_flag == false && m_animation.m_contexts[0].is_playing == false)
		{
			// �ҋ@���[�h�ɂ��Ă���
			m_player_mode = IDLE;
		}
		// �J�E���^�[�U�����s���Ă���ꍇ
		// �������邱�Ƃɂ���ăJ�E���^�[�U������ɉ�����ł��Ȃ��Ȃ�
		if (m_counter_flag && m_animation.m_contexts[0].is_playing == false)
		{
			// �J�E���^�[�t���O������
			m_counter_flag = false;
			// �ҋ@���[�h�ɂ��Ă���
			m_player_mode = IDLE;
		}

		// �U���p�̊֐�
		AttackUpdate();
		break;

	case HIT_DAMAGE: // �_���[�W���󂯂���
		HitDamageUpdate();
		break;
	}
}

//-----------------------------------------------
// ���񂾁i�������j���̍X�V����
//-----------------------------------------------
void SamplePlayer::DieUpdate()
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
void SamplePlayer::Draw()
{

	//===================
	// �J�v�Z���̕`��i���j�i��ŏ����j
	//===================
	// �U���t���O���������Ă�����
	if (m_attack_flag)
	{
		// �U���̓����蔻��s���Ă����Ƃ�����
		if (AttackHitGoodTiming(m_now_attack))
		{
			// �����蔻���`��
			m_attack_hit_damage[m_now_attack]->attack_hit.Draw();
		}
	}
	/*m_body.Draw();
	m_right_hand.Draw();
	m_left_hand.Draw();
	m_right_feet.Draw();
	m_left_feet.Draw();*/
	m_hit.Draw();
	// ���f���̕`�� (�`�����ɂ��Ȃ��Ɠ����蔻�肪������������)

	m_model.DrawModel(&m_transform);



	//m_move_hit_box.Draw(255, 255);
}


//-----------------------------------------------
// �I������
//-----------------------------------------------
void SamplePlayer::Exit()
{

}


//-----------------------------------------------
// �����蔻��
//-----------------------------------------------
void SamplePlayer::CDUpdate()
{
	// �L�����{�̂̓����蔻��̃J�v�Z���i��ŏ����j
	m_body.CreateNodoCapsule(&m_model, 6, 65, 3.5f);
	// �E��̂����蔻��
	m_right_hand.CreateNodoCapsule(&m_model, 32, 46, 2.5f);
	// ����̓����蔻��
	m_left_hand.CreateNodoCapsule(&m_model, 8, 22, 2.5f);
	// �E���̓����蔻��
	m_right_feet.CreateNodoCapsule(&m_model, 60, 64, 2.5f);
	// �����̓����蔻��
	m_left_feet.CreateNodoCapsule(&m_model, 55, 59, 2.5f);

	// ���̓����蔻��𒲂ׂ邽�߂ɍ��������
	{
		// �J�v�Z���̍��W�P
		Vector3 top_pos;
		top_pos.set(m_transform.pos.x + sinf(TO_RADIAN(m_transform.rot.y)) * 10,
			m_transform.pos.y + 5,
			m_transform.pos.z + cosf(TO_RADIAN(m_transform.rot.y)) * 10);

		// �J�v�Z���̍��W�Q
		Vector3 under_pos;
		under_pos.set(m_transform.pos.x + sinf(TO_RADIAN(m_transform.rot.y)) * 5,
			m_transform.pos.y + 5,
			m_transform.pos.z + cosf(TO_RADIAN(m_transform.rot.y)) * 5);

		m_hit.CreateCapsuleCoordinatePos(top_pos, under_pos, 5);
	}
	// �U�����̓����蓖������̕ۑ��ƃ_���[�W�̐ݒ�
	SetHitDamage(m_left_hand, m_attack_damage[attack_punch_1], (attack_punch_1));
	SetHitDamage(m_right_hand, m_attack_damage[attack_punch_2], (attack_punch_2));
	SetHitDamage(m_right_hand, m_attack_damage[attack_punch_3], (attack_punch_3));
	SetHitDamage(m_right_feet, m_attack_damage[attack_kick_1], (attack_kick_1));
	SetHitDamage(m_left_feet, m_attack_damage[attack_kick_2], (attack_kick_2));
	SetHitDamage(m_right_feet, m_attack_damage[attack_kick_3], (attack_kick_3));
}


//-----------------------------------------------
// �X�e�[�^�X�o�[�̐ݒ�p�֐�
//-----------------------------------------------
void SamplePlayer::StatusBarInit()
{
	// HP�̐ݒ�
	m_hp.Set({ 50, SCREEN_H - 50 }, { 500,25 }, &m_hp_value, true);
	m_hp.SetColor(50, 255, 50, &m_hp.m_color);
	m_hp.SetColor(128, 128, 128, &m_hp.m_back_color);
	m_hp.SetColor(0, 0, 0, &m_hp.m_line_color);
	m_hp.SetColor(255, 0, 0, &m_hp.m_character_color);
	m_hp.SetName("HP");
}


//-----------------------------------------------
// �X�e�[�^�X�o�[�`��p�֐�
//-----------------------------------------------
void SamplePlayer::StatusBarDraw()
{

	m_hp.Update(&m_hp_value);
	//===================
	// UI�̕`��
	//===================
	m_hp.Draw();
}


//-----------------------------------------------
// �����蔻����s���ė~�����^�C�~���O��ۑ�����֐�
// �S���̍U���ɓ����蔻��ɐݒ肷��(���Ƃł���)
//-----------------------------------------------
void SamplePlayer::SetHitTimeInit()
{
	SetHitTime(attack_frame[attack_punch_1].start_frame, attack_frame[attack_punch_1].end_frame, attack_punch_1);
	SetHitTime(attack_frame[attack_punch_2].start_frame, attack_frame[attack_punch_2].end_frame, attack_punch_2);
	SetHitTime(attack_frame[attack_punch_3].start_frame, attack_frame[attack_punch_3].end_frame, attack_punch_3);
	SetHitTime(attack_frame[attack_kick_1].start_frame, attack_frame[attack_kick_1].end_frame, attack_kick_1);
	SetHitTime(attack_frame[attack_kick_2].start_frame, attack_frame[attack_kick_2].end_frame, attack_kick_2);
	SetHitTime(attack_frame[attack_kick_3].start_frame, attack_frame[attack_kick_3].end_frame, attack_kick_3);
}


//-----------------------------------------------
// �A�j���[�V�����̏�������
//-----------------------------------------------
void SamplePlayer::Anima_Load_Init()
{
	// �A�j���[�V�����̏����ݒ�
	m_animation.Init_Animation(anim_max, idle);
	// �A�j���[�V�����̓ǂݍ���
	m_animation.Load_Animation("Data/Model/Player/Animation/Player_Idle.mv1", idle, 1, 1.0f); //!< �A�C�h��
	m_animation.Load_Animation("Data/Model/Player/Animation/Player_Run.mv1", run, 1, 1.0f);   //!< ����
	m_animation.Load_Animation("Data/Model/Player/Animation/rolling.mv1", rolling, 1, 2.0f);     //!< ���[�����O
	m_animation.Load_Animation("Data/Model/player/Animation/hit_damage.mv1", hit_damage, 1, 1.0f); //!< �_���[�W��H�������
	m_animation.Load_Animation("Data/Model/Player/Animation/die.mv1", die, 1, 1.0f);            //!< ���񂾂Ƃ�
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Punch.mv1", attack_anim_1, 1, 1.0f);  //!< �U���P
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Punch2.mv1", attack_anim_2, 1, 2.0f); //!< �U���Q
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Punch3.mv1", attack_anim_3, 1, 2.0f); //!< �U���R
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Kick2.mv1", attack_kick_anim_1, 1, 1.5f); //<! �L�b�N�U��
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Kick3.mv1", attack_kick_anim_2, 1, 1.5f); //<! �L�b�N�U��
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Kick4.mv1", attack_kick_anim_3, 1, 1.5f); //<! �L�b�N�U��
	// �ŏ��̓f�t�H���g�A�j���[�V���������Ă���
	m_animation.Init_Attach_Animation(&m_model, idle, true);
}

//-----------------------------------------------
// �v���C���[�̈ړ��p�֐�
//-----------------------------------------------
void SamplePlayer::Move_Update(Vector3* camera_rot)
{
	// ���񃊃Z�b�g
	m_run_flag = false;

	// �ړ��O�̍��W��U�ۑ����Ă���
	m_before_pos = m_transform.pos;

	// �x�[�X�N���X�̍X�V����
	// �ړ��̏��������ɓ����Ă���
	BaseUpdate(&m_run_flag, camera_rot, &PLAYER_MOVE_SPEED);

	// run_flag ���オ���Ă�Ƃ�����
	// �v���C���[���[�h��RUN�ȊO�̎�
	if (m_run_flag && m_player_mode != RUN)
	{
		// �A�j���[�V�����̐؂�ւ��t���O���グ��
		m_animation.m_anim_change_flag = true;
	}

	// �A�j���[�V�����ύX���\�Ȏ���
	if (m_animation.Change_Flag(m_run_flag))
	{
		// ����A�j���[�V�����ɕύX
		m_animation.Change_Animation(&m_model, run, true);
		// �A�j���[�V�������ς��������
		// �v���C���[���[�h�̐؂�ւ�������
		m_player_mode = RUN;
	}


}

//-----------------------------------------------
// �t���O�Ǘ��p�֐�
// ���̊֐����Ȃ��ƐF�X�ȃo�O���o��
//-----------------------------------------------
void SamplePlayer::PlayerMode(int mode)
{
	switch (mode)
	{
	case IDLE:
		m_idle_flag = true;
		m_run_flag = false;
		m_attack_flag = false;
		m_rolling_flag = false;
		break;
	case RUN:
		m_idle_flag = false;
		m_run_flag = true;
		m_attack_flag = false;
		m_rolling_flag = false;
		break;
	case ATTACK:

		m_idle_flag = false;
		m_run_flag = false;
		m_rolling_flag = false;
		m_attack_flag = true;
		break;
	case ROLLING:
		m_idle_flag = false;
		break;
	case HIT_DAMAGE:
		m_idle_flag = false;
		m_run_flag = false;
		m_attack_flag = false;
		m_rolling_flag = false;
		m_damage_flag = true;

		break;
	case DIE:
		m_idle_flag = false;
		m_run_flag = false;
		m_attack_flag = false;
		m_damage_flag = false;
		m_rolling_flag = false;
		break;
	}
}

//-----------------------------------------------
// �ŏ��̍U���𔻒f����
//-----------------------------------------------
void SamplePlayer::AttackFirst()
{
	// �w��̃}�E�X�{�^���������ꂽ��
	if (PushMouseInput(MOUSE_INPUT_LEFT) /*& MOUSE_INPUT_LEFT*/)
	{
		// attack_flag ���オ���Ă�Ƃ�����
		// �v���C���[���[�h��ATTACK�ȊO�̎�
		if (m_attack_flag && m_player_mode != ATTACK)
		{
			// �A�j���[�V�����̐؂�ւ��t���O���グ��
			m_animation.m_anim_change_flag = true;

		}
		// �U�����[�h�ɂ��Ă���
		m_player_mode = ATTACK;
		// �U���A�j���[�V�����ԍ��̕ۑ�
		m_now_attack_anim = attack_anim_1;
		m_animation.Change_Animation(&m_model, m_now_attack_anim, false);
		

		// ���݂̍U���ԍ���ۑ�����
		m_now_attack = m_now_attack_anim - ATTACK_ANIM_STAR;

		// �R���{�̉񐔂����Z�b�g
		m_combo_count = 0;

		m_stop_combo_flag = true;
	}
	// �w��̃}�E�X�{�^���������ꂽ��
	if (PushMouseInput(MOUSE_INPUT_RIGHT) /*& MOUSE_INPUT_LEFT*/)
	{
		// attack_flag ���オ���Ă�Ƃ�����
		// �v���C���[���[�h��ATTACK�ȊO�̎�
		if (m_attack_flag && m_player_mode != ATTACK)
		{
			// �A�j���[�V�����̐؂�ւ��t���O���グ��
			m_animation.m_anim_change_flag = true;

		}
		// �U�����[�h�ɂ��Ă���
		m_player_mode = ATTACK;
		// �U���A�j���[�V�����ԍ��̕ۑ�
		m_now_attack_anim = attack_kick_anim_1;

		m_animation.Change_Animation(&m_model, m_now_attack_anim, false);
		

		// ���݂̍U���ԍ���ۑ�����
		m_now_attack = m_now_attack_anim - ATTACK_ANIM_STAR;

		// �R���{�̉񐔂����Z�b�g
		m_combo_count = 0;

		// �R���{�����Ă����悤�ɂ���
		m_stop_combo_flag = true;
	}
}

//-----------------------------------------------
// �U���Ɋւ���X�V����
//-----------------------------------------------
void SamplePlayer::AttackUpdate()
{
	// �R���{�����Ă����t���O�������Ă��鎞����
	if (m_stop_combo_flag)
	{
		// �R���{�֐����Ă�
		ComboUpdate();
	}
}

//-----------------------------------------------
// ���[�����O�A�N�V�����p�̃L�[�������ꂽ���̔��f�p�֐�
//-----------------------------------------------
void SamplePlayer::SetRolling()
{
	// if (m_player_mode != ROLLING) {}
	// �w��̃L�[�������ꂽ��
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		// �A�N�V�������[�h�����[�����O�ɂ���
		m_player_mode = ROLLING;
	}
}

//-----------------------------------------------
// ���[�����O�A�N�V�����ւ���X�V����
//-----------------------------------------------
void SamplePlayer::ActionRolling()
{
	// ���[�����O�A�j���[�V�����̃Z�b�g
	// ���[�����O�t���O���オ���Ă��Ȃ��Ƃ�
	if (!m_rolling_flag)
	{
		// ���[�����O�A�j���[�V�������Z�b�g����
		m_animation.Change_Animation(&m_model, rolling, false);
		// ���[�����O�t���O��������
		m_rolling_flag = true;
	}

	// ���[�����O���ɍU���{�^������������J�E���^�[�U���ɔh������
	if (PushMouseInput(MOUSE_INPUT_LEFT) || PushMouseInput(MOUSE_INPUT_RIGHT))
	{
		m_counter_flag = true;
	}

	// ���[�����O���̈ړ�����
	// �����Ă�������� PLAYER_ROLLING_SPEED ���ړ�����
	m_transform.pos.z += PLAYER_ROLLING_SPEED * cosf(TO_RADIAN(m_transform.rot.y));
	m_transform.pos.x += PLAYER_ROLLING_SPEED * sinf(TO_RADIAN(m_transform.rot.y));

	// ���[�����O�A�j���[�V�������I�������(�I��肾�Ƃ��܂�����Ȃ���������I��鏭���O�ɂ���)
	// �܂��̓_���[�W��H������t���O���オ����������
	if (m_animation.m_contexts[0].play_time >= m_animation.m_contexts[0].animation_total_time - 10 )
	{
		// �A�j���[�V�����̃`�F���W�t���O���グ��
		m_animation.m_anim_change_flag = true;
		// ���[�����O�t���O��������
		m_rolling_flag = false;
  		if (m_counter_flag)
		{
			m_player_mode = COUNTER;
		}
		else
		{
			// ��U�A�N�V�������[�h��IDLE�ɂ��Ă���
			m_player_mode = IDLE;
		}
		
		
	}
}

//-----------------------------------------------
// �J�E���^�[�A�N�V����
//-----------------------------------------------
void SamplePlayer::CounterAction()
{
	
	// �U�����[�h�ɂ��Ă���
	m_player_mode = ATTACK;
	// �U���A�j���[�V�����ԍ��̕ۑ�
	m_now_attack_anim = attack_kick_anim_3;
	m_animation.Change_Animation(&m_model, m_now_attack_anim, false);
	

	// ���݂̍U���ԍ���ۑ�����
	m_now_attack = m_now_attack_anim - ATTACK_ANIM_STAR;
}

//-----------------------------------------------
// �R���{�̔��f������֐�
//-----------------------------------------------
void SamplePlayer::ComboUpdate()
{
	// �R���{�\�����f�p�֐�
	// �w��̃L�[���삪���ꂽ�ꍇ
	m_combo.Combo_Judgment_Key
	(
		&m_combo_flag,
		&m_mouse_flag,
		MOUSE_INPUT_LEFT,
		m_animation.m_contexts[0].play_time,
		m_animation.m_contexts[0].animation_total_time,
		&m_combo_count
	);
	m_combo.Combo_Judgment_Key
	(
		&m_combo_flag,
		&m_mouse_flag,
		MOUSE_INPUT_RIGHT,
		m_animation.m_contexts[0].play_time,
		m_animation.m_contexts[0].animation_total_time,
		&m_combo_count
	);
	// �R���{�t���O���オ���Ă���Ƃ�
	if (m_combo_flag)
	{
		// ���̃A�j���[�V�����ԍ��������̃A�j���[�V����
		if (m_mouse_flag == MOUSE_INPUT_RIGHT)
		{
			m_next_anim = attack_kick_anim_1 + m_combo_count;
		}
		if (m_mouse_flag == MOUSE_INPUT_LEFT)
		{
			m_next_anim = attack_anim_1 + m_combo_count;
		}
		// �R���{���A�j���[�V�����̍ő�Ɠ����ɂȂ�����
		if (m_combo_count >= COMBO_MAX)
		{
			// �R���{���X�g�b�v����悤�ɂ���
			m_stop_combo_flag = false;
			// �R���{�t���O��������
			m_combo_flag = false;
			// �R���{�̉񐔂����Z�b�g
			m_combo_count = 0;
			// �����蔻��̐ݒ肪�o�b�N���Ă���̂ňꉺ����
			m_next_anim--;
		}

		// �R���{�p�̃A�j���[�V����������
		m_animation.Action_Change_Animation(&m_model, m_next_anim, false, &m_combo_flag);

		if (!m_combo_flag)
		{
			// ���݂̍U���A�j���[�V������ۑ�
			m_now_attack_anim = m_next_anim;
			// ���݂̍U���ԍ���ۑ�����
			m_now_attack = m_now_attack_anim - ATTACK_ANIM_STAR;
		}

	}

}

//-----------------------------------------------
// �U�����󂯂������`�F�b�N���邽�߂̊֐�
//-----------------------------------------------
void SamplePlayer::CheckHitDamage()
{
	// �_���[�W��H������t���O�������Ă�����
	if (m_damage_flag)
	{
		// �v���C���[�̏�Ԃ��_���[�W���󂯂���Ԃɂ���
		m_player_mode = HIT_DAMAGE;
		// �A�j���[�V�����̐؂�ւ��t���O���グ��
		m_animation.m_anim_change_flag = true;
	}
}

//-----------------------------------------------
// �U�����󂯂����̏���
//-----------------------------------------------
void SamplePlayer::HitDamageUpdate()
{
	// �U�����󂯂������U�����󂯂����̃A�j���[�V�������t���ĂȂ��Ƃ�(�t���O���������Ă�Ƃ�)
	if (m_damage_flag && m_damage_anim_flag == false)
	{
		// �U�����󂯂����̃A�j���[�V�������t�����̂Ńt���O���グ��
		m_damage_anim_flag = true;
		// �_���[�W�A�j���[�V����������
		if (m_animation.Change_Flag(m_damage_anim_flag))
		{
			// �A�j���[�V�������~�ɕύX����
			m_animation.Change_Animation(&m_model, hit_damage, true);

		}
	}

	// �_���[�W��H������A�j���[�V�������I���ɂ���������
	if (m_animation.m_contexts[0].play_time >= m_animation.m_contexts[0].animation_total_time - 10)
	{
		// ��U�����Ń_���[�W�󂯂��t���O�������Ă���
		m_damage_flag = false;
		// �U�����󂯂����̃A�j���[�V�������I���̂Ńt���O��������
		m_damage_anim_flag = false;
		// �v���C���[�̃��[�h��IDLE��Ԃɂ���
		m_player_mode = IDLE;
		// �A�C�h����Ԃɂ������̂ŃA�C�h���t���O�𗧂Ă�
		m_idle_flag = true;
		// �A�j���[�V�����ύX�t���O�����ĂĂ���
		m_animation.m_anim_change_flag = true;
	}
}
