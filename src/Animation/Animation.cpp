#include "src/WinMain.h"
#include "src/Model/Model.h"
#include "Animation.h"
using namespace std;

//-----------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------
Animation::Animation()
{
	m_contexts[0].is_playing = false;
}

//-----------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------
Animation::~Animation()
{
	anim_handle.clear();

	// ���̓��delete�̓G���[���o��
	//delete[] (m_contexts);
	//delete m_contexts;
}

//-----------------------------------------------
// �A�j���[�V�����̏��̏������֐�
//-----------------------------------------------
void Animation::Information_Init(int num)
{
	//�A�j���[�V�����̏������ׂď��������Ă���
	m_contexts[num].is_playing = false;
	m_contexts[num].is_loop = false;
	m_contexts[num].animation_index = -1;
	m_contexts[num].animation_attach_index = -1;
	m_contexts[num].m_blend_ratio = 0.0f;
	m_contexts[num].animation_total_time = 0.0;
	m_contexts[num].play_time = 0.0f;
}

//-----------------------------------------------
// �A�j���[�V�����̏����ݒ�
//-----------------------------------------------
void Animation::Init_Animation(int anim_max, int default_anim)
{
	// �f�t�H���g�A�j���[�V�����̐ݒ�
	m_default_anim = default_anim;
	// �A�j���[�V�����̓��ꕨ��z��Ŋm�ۂ���
	for (int i = 0; i < anim_max; i++)
	{
		AnimData* anim = new AnimData;
		anim_handle.push_back(anim);
	}
}

//-----------------------------------------------
// �ǂݍ���
//-----------------------------------------------
void Animation::Load_Animation(const char file_path[256], int anim_no, int anim_index, float anim_play_speed)
{
	// �ǂݍ���
	anim_handle[anim_no]->handle = MV1LoadModel(file_path);
	// �A�j���V�����C���f�b�N�X�ԍ��̕ۑ�
	anim_handle[anim_no]->index = anim_index;
	// �A�j���[�V�����̍Đ����x�̐ݒ�
	anim_handle[anim_no]->play_speed = anim_play_speed;
}

//-----------------------------------------------
// �ŏ��̏������̎����������A�j���[�V�������Z�b�g����
//-----------------------------------------------
void Animation::Init_Attach_Animation(Model* model, int anim_num, bool loop)
{
	for (int i = 0; i < 2; i++) {
		// ���ꕨ�����������Ă���
		Information_Init(i);

		// �A�j���V�����̃Z�b�g
		m_contexts[i].animation_attach_index = MV1AttachAnim
		(
			model->m_model,
			anim_handle[anim_num]->index,
			anim_handle[anim_num]->handle
		);

		// �A�j���[�V�������Đ��t���[���̎擾
		m_contexts[i].animation_total_time = MV1GetAttachAnimTotalTime
		(
			model->m_model,
			m_contexts[i].animation_attach_index
		);

		// �u�����h���̎擾
		m_contexts[i].m_blend_ratio = MV1GetAttachAnimBlendRate
		(
			model->m_model,
			m_contexts[i].animation_attach_index
		);

		if (i == 0) {
			m_contexts[0].m_blend_ratio = 1.0f;
		}
		else
		{
			m_contexts[1].m_blend_ratio = 1.0f;
		}

		// ���[�v���邩�ǂ���
		m_contexts[i].is_loop = loop;
	}
	m_detach_flag = true;
	// �ǂ̃A�j���[�V��������ۑ�
	m_anim_num = anim_num;
}

//-----------------------------------------------
// �A�j���[�V�����̃Z�b�g
//-----------------------------------------------
void Animation::Attach_Animation(Model* model, int anim_num, bool loop)
{
	// ���ꕨ�����������Ă���
	Information_Init(0);

	// �A�j���V�����̃Z�b�g
	m_contexts[0].animation_attach_index = MV1AttachAnim
	(
		model->m_model,
		anim_handle[anim_num]->index,
		anim_handle[anim_num]->handle
	);

	// �A�j���[�V�������Đ��t���[���̎擾
	m_contexts[0].animation_total_time = MV1GetAttachAnimTotalTime
	(
		model->m_model,
		m_contexts[0].animation_attach_index
	);

	// �u�����h���̎擾
	m_contexts[0].m_blend_ratio = MV1GetAttachAnimBlendRate
	(
		model->m_model,
		m_contexts[0].animation_attach_index
	);

	// ���[�v���邩�ǂ���
	m_contexts[0].is_loop = loop;

	// �A�j���[�V�������Đ����ɂ���
	//m_contexts[0].is_playering = true;

	// �ǂ̃A�j���[�V��������ۑ�
	m_anim_num = anim_num;
}

// �A�j���[�V�����̎��O��
void Animation::Detach_Animation(Model* model)
{
	// �A�j���[�V�������̎��O��
	m_contexts[1].animation_attach_index = MV1DetachAnim
	(model->m_model,
		m_contexts[1].animation_attach_index);
	// ���O�����A�j���[�V�����̏������ׂď��������Ă���
	Information_Init(1);
	// �f�^�b�`���ꂽ����t���O��������
	m_detach_flag = false;
}

//-----------------------------------------------
// �u�����h���̕ύX������֐�
//-----------------------------------------------
void Animation::Change_Blend()
{
	// ���̃A�j���[�V�����̃u�����h�����グ��
	m_contexts[0].m_blend_ratio += 0.1f;
	// ����̐ݒ�
	if (m_contexts[0].m_blend_ratio >= 1.0f)
	{
		m_contexts[0].m_blend_ratio = 1.0f;
	}
	// ���Ƃ��Ƃ̃A�j���[�V�����̃u�����h����������
	m_contexts[1].m_blend_ratio -= 0.1f;
	// �����̐ݒ�
	if (m_contexts[1].m_blend_ratio <= 0)
	{
		m_contexts[1].m_blend_ratio = 0.0f;
		// �u�����h�������������̂Ńt���O��������
		m_attached = false;
	}
}

//-----------------------------------------------
// �A�j���[�V�����̕ύX�����Ă������𔻒f����֐�
//-----------------------------------------------
bool Animation::Change_Flag(bool flag1)
{
	// �L�����N�^�[�̊e�t���O��
	// �A�j���[�V�����ύX�t���O�������オ���Ă�����
	if (flag1 == true && m_anim_change_flag == true)
	{
		// �ύX�̋����o��
		return true;
	}
	else // �ǂ��炩����ł��t���O�������Ă��Ȃ�������
	{
		// �A�j���[�V�����̕ύX�͂����Ȃ�
		return false;
	}

}

//-----------------------------------------------
// �A�j���[�V�����؂�ւ��p�֐�
//-----------------------------------------------
void Animation::Change_Animation(Model* model, int anim_num, bool loop)
{
	// �A�j���[�V�����ύX�t���O��������
	m_anim_change_flag = false;
	// �A�j���[�V���������ւ���O�ɂ��Ƃ��Ƃ��Ă��A�j���[�V���������O��
	Detach_Animation(model);
	// ���ɂ͂��Ă���������ւ���
	m_contexts[1] = m_contexts[0];
	// ��t����Ă��邩��t���O���グ��
	m_attached = true;
	// ��ڂ̃A�j���[�V�������t���Ă��邩��
	m_detach_flag = true;
	// ���ɍs�������A�j���[�V����������
	Attach_Animation(model, anim_num, loop);
}

//-----------------------------------------------
// �A�j���[�V�����؂�ւ��p�֐��i�A�j���[�V�������I���^�C�~���O�Ő؂�ւ���j
//-----------------------------------------------
void Animation::Action_Change_Animation(Model* model, int anim_num, bool loop, bool* combo_flag)
{
	// �A�j���[�V�������Ō�̃t���[���ɍ����|��������
	if (m_contexts[0].animation_total_time <= m_contexts[0].play_time)
	{
		Change_Animation(model, anim_num, loop);
		// ���̃A�j���[�V��������������R���{�t���O������
		*combo_flag = false;
	}
}

//-----------------------------------------------
// �A�j���[�V�������Đ������邽�߂̊֐�
//-----------------------------------------------
void Animation::Play_Animation(Model* model, bool combo_flag)
{
	m_playing_anim = true;
	// �A�j���[�V�������Đ����ɂ��Ă���
	if (m_contexts[0].play_time <= m_contexts[0].animation_total_time)
	{
		m_contexts[0].is_playing = true;
	}
	// �A�j���[�V�����̍Đ��t���[����i�߂�
	m_contexts[0].play_time += anim_handle[m_anim_num]->play_speed;
	// ���[�v���邩�ǂ����ɂ���ď����̕ύX

	if (m_contexts[0].is_loop)
	{
		Loop_Animation();
	}
	else // ���[�v���Ȃ��ꍇ
	{
		if (combo_flag == false)
		{
			Not_Loop(model);
		}
	}

	
	// �u�����h���̕ύX
	Change_Blend();

	// ��t���Ă���Ƃ��Ƃ����łȂ��Ƃ��ŏ�����ς���
	if (m_attached)
	{
		for (int i = 0; i < 2; i++)
		{
			// ���ꂼ��ɃA�j���[�V�����̊������Đ����܂�
			// �u�����h���̐ݒ�
			MV1SetAttachAnimBlendRate(
				model->m_model,
				m_contexts[i].animation_attach_index,
				m_contexts[i].m_blend_ratio);
			// �A�j���[�V�����̍Đ�
			MV1SetAttachAnimTime
			(
				model->m_model,
				m_contexts[i].animation_attach_index,
				m_contexts[i].play_time
			);
		}
	}
	else
	{
		if (m_detach_flag)
		{
			// �f�^�b�`����ĂȂ�������
			// �f�^�b�`����
			Detach_Animation(model);
		}
		// �A�j���[�V�����̍Đ�
		MV1SetAttachAnimTime
		(
			model->m_model,
			m_contexts[0].animation_attach_index,
			m_contexts[0].play_time
		);
	}
}

//-----------------------------------------------
// �A�j���[�V���������[�v������
//-----------------------------------------------
void Animation::Loop_Animation()
{
	// �A�j���[�V�����t���[�����Ō�܂ŉ������
	if (m_contexts[0].play_time >= m_contexts[0].animation_total_time)
	{
		// �ŏ��Ƀ��Z�b�g����
		m_contexts[0].play_time = 0.0f;
		// �A�j���[�V�����Đ��O�ɂ���
		m_contexts[0].is_playing = false;
	}
}


//-----------------------------------------------
// �A�j���[�V���������[�v���������ꍇ
//-----------------------------------------------
void Animation::Not_Loop(Model* model)
{
	// �A�j���[�V�����t���[�����Ō�܂ŉ������
	if (m_contexts[0].play_time >= m_contexts[0].animation_total_time)
	{
		//m_playing_anim = false;
		// �A�j���[�V�����Đ��O�ɂ���
		m_contexts[0].is_playing = false;
		// �ŏ��Ƀ��Z�b�g����
		m_contexts[0].play_time = 0.0f;

		// �f�t�H���g�̃A�j���[�V�����ɐݒ�
		Change_Animation(model, m_default_anim, true);
	}

}


