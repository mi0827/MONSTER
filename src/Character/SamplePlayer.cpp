#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"

#include "src/System/Spotlight.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Collision/CapsuleCollision.h"
#include "src/Collision/BoxCollision.h"

#include "src/Action/Combo.h"
#include "src/System/Move.h"

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
	// ���f���̃X�P�[���̐ݒ�
	m_transform.scale.set(0.1f,0.1,0.1);
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
	CharacterBase::BaseInit(PLAYER_R);
	// ���f���摜�̓ǂݍ���
	m_model.LoadModel("Data/Model/Player/Player.mv1");
	// �A�j���[�V�����̏����ݒ�
	Anima_Load_Init();


}

//-----------------------------------------------
// �X�V����
//-----------------------------------------------
void SamplePlayer::Update(Vector3* camera_rot)
{
	clsDx();

	// �ҋ@��Ԃ܂��͑���̎�������
	// �ړ�����
	if (m_idle_flag == true || m_run_flag == true)
	{
		Move_Update(camera_rot);
	}
	
	switch (m_player_mode)
	{
	case IDLE:
		if (m_idle_flag)
		{
			//Player_Mode(IDLE);
			// �A�j���[�V�����ύX���\�Ȏ���
			if (m_animation.Change_Flag(m_idle_flag))
			{
				// �A�j���[�V�������~�ɕύX����
				m_animation.Change_Animation(&m_model, idle, true);

			}
		}
		// �ŏ��̍U���𔻒f����
		Attack_First();
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
			m_player_mode = IDLE;
		}

		// �ŏ��̍U���𔻒f����
		Attack_First();

		break;
	case ATTACK:


		// �R���{�t���O�������Ă��Ȃ���
		// �U���A�j���[�V�����̍Đ����I����Ă�����
		// �ҋ@���[�h�ɂ��Ă���
		if (m_combo_flag == false && m_animation.m_contexts[0].is_playering == false)
		{
			m_player_mode = IDLE;
		}
		// �U���p�̊֐�
		Attack_Update();
		break;
	}


	// �A�j���[�V�����̍Đ�
	m_animation.Play_Animation(&m_model, m_combo_flag);
	// �����蔻��̍X�V����
	CDUpdate();

	// �t���O�Ǘ��p�֐�
	Player_Mode(m_player_mode);
}

//-----------------------------------------------
// �`�揈��
//-----------------------------------------------
void SamplePlayer::Draw()
{
	// �J�v�Z���̕`��i���j�i��ŏ����j
	//m_body.Draw();
	//m_right_hand.Draw();

	// ���f���̕`�� (�`�����ɂ��Ȃ��Ɠ����蔻�肪������������)
	m_model.DrawModel(&m_transform);
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
	m_body.CreateCapsule({ m_transform.pos.x, m_transform.pos.y, m_transform.pos.z });
	m_body.SetSize({ 0.0f,15.0f, 0.0f }, 2.5);

	// �E��̂����蔻��
	m_right_hand.CreateNodoCapsule(&m_model, 10);
	m_right_hand.NodoSetSize(&m_model, 9, 1.0f);

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
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Punch.mv1", attack_1, 1, 1.0f);  //!< �U���P
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Punch2.mv1", attack_2, 1, 2.0f); //!< �U���Q
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Punch3.mv1", attack_3, 1, 2.0f); //!< �U���R
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Kick2.mv1", attack_kick_1, 1, 1.5f); //<! �L�b�N�U��
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Kick3.mv1", attack_kick_2, 1, 1.5f); //<! �L�b�N�U��
	m_animation.Load_Animation("Data/Model/Player/Animation/Attack/Kick4.mv1", attack_kick_3, 1, 1.5f); //<! �L�b�N�U��
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
	if (m_animation.Change_Flag(m_run_flag)) {
		// ����A�j���[�V�����ɕύX
		m_animation.Change_Animation(&m_model, run, true);
		// �A�j���[�V�������ς��������
		// �v���C���[���[�h�̐؂�ւ�������
		m_player_mode = RUN;
	}
}

//-----------------------------------------------
// �I������
//----------------------------------------------- 
void SamplePlayer::Player_Mode(int mode)
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

	}
}

//-----------------------------------------------
// �ŏ��̍U���𔻒f����
//-----------------------------------------------
void SamplePlayer::Attack_First()
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
		m_animation.Change_Animation(&m_model, attack_1, false);
		// �U���A�j���[�V�����ԍ��̕ۑ�
		m_now_attack_anim = attack_1;

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
		m_animation.Change_Animation(&m_model, attack_kick_1, false);
		// �U���A�j���[�V�����ԍ��̕ۑ�
		m_now_attack_anim = attack_1;
		// �R���{�̉񐔂����Z�b�g
		m_combo_count = 0;

		// �R���{�����Ă����悤�ɂ���
		m_stop_combo_flag = true;
	}
}

//-----------------------------------------------
// �U���Ɋւ���X�V����
//-----------------------------------------------
void SamplePlayer::Attack_Update()
{
	// �R���{�����Ă����t���O�������Ă��鎞����
	if (m_stop_combo_flag)
	{
		// �R���{�֐����Ă�
		Combo_Update();
	}
}

//-----------------------------------------------
// �R���{�̔��f������֐�
//-----------------------------------------------
void SamplePlayer::Combo_Update()
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
			m_next_anim = attack_kick_1 + m_combo_count;
		}
		if (m_mouse_flag == MOUSE_INPUT_LEFT)
		{
			m_next_anim = attack_1 + m_combo_count;
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
		}

		// �R���{�p�̃A�j���[�V����������
		m_animation.Action_Change_Animation(&m_model, m_next_anim, false, &m_combo_flag);

		if (!m_combo_flag)
		{
			// ���݂̍U���A�j���[�V������ۑ�
			m_now_attack_anim = m_next_anim;
		}
	}
}
