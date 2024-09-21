#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/System/Transform.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Collision/CapsuleCollision.h"
#include "src/Collision/BoxCollision.h"

#include "src/Character/Receptionist.h"


//---------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------
Receptionist::Receptionist()
{
}

//---------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------
Receptionist::~Receptionist()
{
}

//---------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------
void Receptionist::Init()
{
	// ���W�̏������W
	m_transform.pos.set(-20, 0,120);
	// �X�P�[���̐ݒ�
	m_transform.scale.set(0.1f, 0.1f, 0.1f);
	// �����̐ݒ�
	m_transform.rot.set(0.0f, 0.0f, 0.0f);



	// ���f���̓ǂݍ���
	m_model.LoadModel("Data/Model/Receptionist/receptionist.mv1");


	// �A�j���[�V�����̏����ݒ�
	// �A�j���[�V�����̐���ݒ肵�Ă���
	m_animation.Init_Animation(anim_max, idle);

	// �A�j���[�V�����̓ǂݍ���
	// �Ƃ肠�����̏�Ԃ�ݒ肵�Ă���
	// ��ŕύX�\��
	m_animation.Load_Animation("Data/Model/Receptionist/Animation/idle.mv1", idle,0,1.0f);
	// �ŏ��̓A�C�h���A�j���[�V���������Ă���
	m_animation.Init_Attach_Animation(&m_model, 0, true);

}

//---------------------------------------------------------------------------
// �X�V����
//---------------------------------------------------------------------------
void Receptionist::Update()
{
	// �A�j���[�V�����̍Đ�
	m_animation.Play_Animation(&m_model, true);


	// Body�̓����蔻��̐ݒ�
	m_hit_body.CreateNodoCapsule(&m_model, 69, 5, BDOY_R);
}

//---------------------------------------------------------------------------
// �`�揈��
//---------------------------------------------------------------------------
void Receptionist::Draw()
{
	// ���f���̕`��
	m_model.DrawModel(&m_transform);
	m_hit_body.Draw();
}

//---------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------
void Receptionist::Exit()
{
}
