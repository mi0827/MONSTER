#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"

#include "src/System/Spotlight.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Collision/CapsuleCollision.h"
#include "src/Collision/BoxCollision.h"

#include "src/Action/Combo.h"
#include "src/System/TargetMove.h"

#include "src/Character/MonsterBase.h"
#include "Monster.h"

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
Monster::Monster()
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
Monster::~Monster()
{
	Exit();
}

//-----------------------------------------------
// ����������
//-----------------------------------------------
void Monster::Init()
{
	// ���f���摜�̓ǂݍ���
	m_model.LoadModel("Data/Model/Monster/Monster.mv1");
	// �A�j���[�V�����̏����ݒ�
	Anima_Load_Init();

	// �����Ƀ{�b�N�X�̓����蔻��̍쐬
	m_move_hit.CreateBox(m_transform.pos, M_MOVE_SIZE);
}

//-----------------------------------------------
// �X�V����
//-----------------------------------------------
void Monster::Update(Transform* traget_pos, float target_r)
{
	clsDx();

	MonsterBase::BaseInit(traget_pos, target_r);

	// �ҋ@��Ԃ܂��͑���̎�������
	// �ړ�����
	if (m_idle_flag == true || m_run_flag == true)
	{
		Move_Update();
	}
	
	// �����̓����蔻��̍X�V����
	// �����蔻��̍��W�������X�^�[�𒆐S�ɂ������̂�
	// M_MOVE_SIZE�̔��������炷(�����X�^�[�̍��W����n�[�t�����炷)
	m_move_hit.SetPos(m_transform.pos-M_MOVE_SIZE_HALF);

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



		break;
	case ATTACK:


		// �R���{�t���O�������Ă��Ȃ���
		// �U���A�j���[�V�����̍Đ����I����Ă�����
		// �ҋ@���[�h�ɂ��Ă���
		if (m_combo_flag == false && m_animation.m_contexts[0].is_playering == false)
		{
			m_monster_mode = IDLE;
		}
		// �U���p�̊֐�
		Attack_Update();
		break;
	}


	// �A�j���[�V�����̍Đ�
	m_animation.Play_Animation(&m_model, m_combo_flag);
	// �����蔻��̍X�V����
	CDUpdate();
}

//-----------------------------------------------
// �`�揈��
//-----------------------------------------------
void Monster::Draw()
{
	// �J�v�Z���̕`��i���j�i��ŏ����j
	m_body.Draw();
	m_right_hand.Draw();
	
	m_move_hit.Draw(255, 100);
	// ���f���̕`�� (�`�����ɂ��Ȃ��Ɠ����蔻�肪������������)
	m_model.DrawModel(&m_transform);
}

//-----------------------------------------------
// �I������
//-----------------------------------------------
void Monster::Exit()
{
}

//-----------------------------------------------
// �����蔻��
//-----------------------------------------------
void Monster::CDUpdate()
{
	// �L�����{�̂̓����蔻��̃J�v�Z���i��ŏ����j
	m_body.CreateCapsule(m_transform.pos);
	m_body.SetSize({ 0.0f,15.0f, 0.0f }, 2.5);

	// �E��̂����蔻��
	m_right_hand.CreateNodoCapsule(&m_model, 10);
	m_right_hand.NodoSetSize(&m_model, 9, 1.0f);

}

//-----------------------------------------------
// �A�j���[�V�����̏�������
//-----------------------------------------------
void Monster::Anima_Load_Init()
{
	// �A�j���[�V�����̏����ݒ�
	m_animation.Init_Animation(anim_max, idle);
	// �A�j���[�V�����̓ǂݍ���
	m_animation.Load_Animation("Data/Model/Monster/Animation/idle.mv1", idle, 0, 1.0f); //!< �A�C�h��
	m_animation.Load_Animation("Data/Model/Monster/Animation/Run.mv1", run, 0, 1.0f); //!< ����

	// �����ƃ����X�^�[���ۂ��U����T���Ă���

	m_animation.Load_Animation("Data/Model/Monster/Animation/Punch_1.mv1", attack_1, 0, 1.0f); //!< �U���P
	m_animation.Load_Animation("Data/Model/Monster/Animation/rolling.mv1", rolling, 0, 1.0f); //!< ���[�����O
	m_animation.Load_Animation("Data/Model/Monster/Animation/jump.mv1", jump, 0, 1.0f); //!< �W�����v
	// �ŏ��̓f�t�H���g�A�j���[�V���������Ă���
	m_animation.Init_Attach_Animation(&m_model, idle, true);
}

//-----------------------------------------------
// �v���C���[�̈ړ��p�֐�
//-----------------------------------------------
void Monster::Move_Update()
{
	// ���񃊃Z�b�g
	m_run_flag = false;

	// �ړ��O�̍��W��U�ۑ����Ă���
	m_before_pos = m_transform.pos;

	//// �x�[�X�N���X�̍X�V����
	//// �ړ��̏��������ɓ����Ă���
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
void Monster::Attack_First()
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
	m_animation.Change_Animation(&m_model, attack_1, false);
	// �U���A�j���[�V�����ԍ��̕ۑ�
	m_now_attack_anim = attack_1;


	m_stop_combo_flag = true;
}

//-----------------------------------------------
// �U���Ɋւ���X�V����
//-----------------------------------------------
void Monster::Attack_Update()
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
void Monster::Combo_Update()
{
	// �R���{���s���Ă�����ԂȂ̂͂���ۑ�����ϐ�
	bool combo_jug;
	// TargetMove���^�[�Q�b�g�Ɛڂ��Ă��邻���łȂ����ŕς��
	// �ڂ��Ă����ړ��\��ԂɂȂ��
	if (move.m_hit)
	{
		// �R���{���ł����ԂłȂ�
		combo_jug = false;
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
		m_next_anim = Set_Rand_Attack();

		// �R���{�p�̃A�j���[�V����������
		m_animation.Action_Change_Animation(&m_model, m_next_anim, false, &m_combo_flag);

		if (!m_combo_flag)
		{
			// ���݂̍U���A�j���[�V������ۑ�
			m_now_attack_anim = m_next_anim;
		}
	}
}


//-----------------------------------------------
// �s�������A�j���[�V�����������_���őI�Ԃ��߂̊֐�
//-----------------------------------------------
int Monster::Set_Rand_Attack()
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
		if (next_anim == m_now_attack_anim)
		{
			// �܂������_���œ���Ȃ���
			next_anim = GetRand(ATTACK_ANIM_MAX) + ATTACK_ANIM_START;
		}
		break;
	}

	// ���ɍs���Ăق����U���A�j���[�V������Ԃ�
	return next_anim;
}
