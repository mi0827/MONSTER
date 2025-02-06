#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/System/Transform.h"

#include "src/Model/Model.h"

#include "src/Collision/CapsuleCollision.h"
#include "src/Collision/BoxCollision.h"


#include "src/Effect/Effect.h"
#include "src/Sound/Sound.h"

#include "src/Model/Model.h"

#include "Bot.h"


//------------------------------------------
// �R���X�g���N�^
//------------------------------------------
Bot::Bot()
{
}

//------------------------------------------
// �f�X�g���N�^
//------------------------------------------
Bot::~Bot()
{
}

//------------------------------------------
// ����������
//------------------------------------------
void Bot::Init()
{
	// ���W�̐ݒ�
	m_transform.pos.set(0.0f, 80.0f, 500.0f);
	// �����̐ݒ�
	m_transform.rot.set(0.0f, 0.0f, 0.0f);
	// �傫���̐ݒ�
	m_transform.scale.set(0.3f, 0.2f, 0.3f);
	// ���f���̓ǂݍ���
	m_bot_model.LoadModel("Data/Model/Bot/bot.mv1");
	// ���W�̐ݒ�
	m_bot_model.SetModelPos(m_transform.pos);
	// �G�t�F�N�g�̏�����
	m_bot_effect.NewArraySecure(EFFECT_MAX);
	// �G�t�F�N�g�̓ǂݍ���
	m_bot_effect.LoadEffect("Data/Model/Bot/Effect/HitDamage.efkefc", 0, 1.0f);
	

	// �����蔻��̏�����
	Vector3 pos2 = { m_transform.pos.x,m_transform.pos.y + 10,m_transform.pos.z };
	m_body.CreateCapsuleCoordinatePos(m_transform.pos, pos2, 15.0f);

	// SE�̏�����
	m_se.NewArraySecureSound(SE_MAX);
	m_se.LoadSound("Data/Model/Bot/SE/Damage.mp3",0);
}

//------------------------------------------
// �X�V����
//------------------------------------------
void Bot::Update()
{
	// �U�����󂯂���
	// �G�t�F�N�g���Đ����Ȃ�
	if (m_bot_effect.IsPlayingEffect())
	{
		// �Đ����̃G�t�F�N�g���~�߂�
		m_bot_effect.StopEffect();
	}
	// �G�t�F�N�g�̍Đ�
	Vector3 effect_pos = { m_transform.pos.x,m_transform.pos.y + 10.0f ,m_transform.pos.z };
	m_bot_effect.PlayEffect(0, effect_pos);
	// �G�t�F�N�g�T�C�Y�̕ύX
	m_bot_effect.SetEffectSize({ 4.0f,4.0f,4.0f });
	// SE���Đ����Ȃ�~�߂�
    m_se.StopSound();
	// SE�̍Đ�
	if (m_se.PlayingSound() == false )
	{
		// SE�̍Đ�
		m_se.PlaySound_(0, DX_PLAYTYPE_BACK, true);
		// SE���Đ����ꂽ�̂ōĐ��\��Ԃ�ύX����
		m_se.m_playing_flag = false;
	}
}

//------------------------------------------
// �`�揈��
//------------------------------------------
void Bot::Draw()
{
	// �{�b�g���f���̕`��
	m_bot_model.DrawModel(&m_transform);
	// �����蔻��̕`��
	// m_body.Draw();
}

//------------------------------------------
// �I������
//------------------------------------------
void Bot::Exit()
{
}
