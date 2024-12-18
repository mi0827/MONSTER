#include "src/WinMain.h"

#include "src/System/Vector3.h"
#include "Effect.h"

Effect::Effect()
{

}
Effect::~Effect()
{

}
//---------------------------------------------------------------
// �G�t�F�N�g�p�̔z��m�ۊ֐�
//---------------------------------------------------------------
void Effect::NewArraySecure(int effect_max)
{
	// �G�t�F�N�g�̔z����m��
	m_effect_info.resize(effect_max);
}


//---------------------------------------------------------------------------
//  �G�t�F�N�g�p�ϐ���delete�p�֐�
//---------------------------------------------------------------------------
void Effect::EffectDelete()
{
	// �m�ۂ����z����J������
	m_effect_info.clear();
}

//---------------------------------------------------------------------------
//  �G�t�F�N�g�̓ǂݍ���
//---------------------------------------------------------------------------
void Effect::LoadEffect(const char file_path[256], int effect_no, float  effect_play_speed)
{
	// �G�t�F�N�g�̓ǂݍ���
	m_effect_info[effect_no].effect_handle = LoadEffekseerEffect(file_path);
	// �G�t�F�N�g�̍Đ����x�̐ݒ�
	m_effect_info[effect_no].effect_play_speed = effect_play_speed;

}

//---------------------------------------------------------------------------
//  �G�t�F�N�g�̍Đ�
//---------------------------------------------------------------------------
void Effect::PlayEffect(int effect_num, Vector3 pos)
{
	// �G�t�F�N�g�̃n���h��
	int effect_handle = m_effect_info[effect_num].effect_handle;

	// �G�t�F�N�g�̍Đ�
	// ���ݍĐ����̃G�t�F�N�g�ɐݒ肵�Ă���
	int b = PlayEffekseer3DEffect(effect_handle);
	// �G�t�F�N�g�̍Đ��X�s�[�h�̐ݒ�
	int a =SetSpeedPlayingEffekseer3DEffect(effect_handle, m_effect_info[effect_num].effect_play_speed);

	// �G�t�F�N�g�̐������W�̐ݒ�
	SetPosPlayingEffekseer3DEffect(effect_handle, pos.x, pos.y, pos.z);
}

//---------------------------------------------------------------------------
// �G�t�F�N�g�̍��W��ݒ�
//---------------------------------------------------------------------------
void Effect::SetEffectPos(int effect_num, Vector3 pos, Vector3 pos2)
{
	// �ݒ肵�������W
	Vector3 pos_ = pos + pos2;
	// �G�t�F�N�g�̐ݒ�
	SetPosPlayingEffekseer3DEffect(m_effect_info[effect_num].effect_handle, pos_.x, pos_.y, pos_.z);
}

//---------------------------------------------------------------------------
//  �G�t�F�N�g�̍��W�����f���̌����ɍ��킹�Ă��炷�֐�
//---------------------------------------------------------------------------
void Effect::SetEffectRotPos(int effect_num, Vector3 pos, Vector3 pos2, Vector3 rot)
{
	// �ݒ肵�������f���̌����ɍ��킹�č��W���Z�b�g����
	Vector3 pos_ = pos;
	pos_.x += pos2.x + sinf(TO_RADIAN(rot.y));
	pos_.y += pos2.y;
	pos_.z += pos2.z + cosf(TO_RADIAN(rot.y));
	// �G�t�F�N�g�̍��W��ݒ�
	SetPosPlayingEffekseer3DEffect(m_effect_info[effect_num].effect_handle, pos_.x, pos_.y, pos_.z);
}


//---------------------------------------------------------------------------
//  �G�t�F�N�g�̍Đ�
//---------------------------------------------------------------------------
void Effect::SetEffectRot(int effect_num, Vector3 rot)
{
	// �ݒ肵���������̂��o��
	Vector3 rot_;
	rot_.x = TO_RADIAN(rot.x);
	rot_.y = TO_RADIAN(rot.y);
	rot_.z = TO_RADIAN(rot.z);
	// �G�t�F�N�g�̌�����ݒ�
	SetRotationPlayingEffekseer3DEffect(m_effect_info[effect_num].effect_handle, rot_.x, rot_.y, rot_.z);
}

//---------------------------------------------------------------------------
//  �G�t�F�N�g�ׂ̍����T�C�Y�̐ݒ�
//---------------------------------------------------------------------------
void Effect::SetEffectSize(int effect_num, Vector3 size)
{
	// �G�t�F�N�g�̃T�C�Y��ݒ�
	SetScalePlayingEffekseer3DEffect(m_effect_info[effect_num].effect_handle, size.x, size.y, size.z);
}

//---------------------------------------------------------------------------
//  �G�t�F�N�g�̍Đ����x�̐ݒ�
//---------------------------------------------------------------------------
void Effect::SetEffectPlaySpeed(int effect_num, float speed)
{
	SetSpeedPlayingEffekseer3DEffect(m_effect_info[effect_num].effect_handle, speed);
}

//---------------------------------------------------------------------------
//  �G�t�F�N�g�̐F�̐ݒ�
//---------------------------------------------------------------------------
void Effect::SetEffectColor(int effect_num, COLOR_F color)
{
	// �G�t�F�N�g�̐F�̐ݒ�
	SetColorPlayingEffekseer3DEffect(m_effect_info[effect_num].effect_handle, color.r, color.g, color.b, color.a);
}