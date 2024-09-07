#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "Scene_Base.h"

// -------------------------------------------------------------------------- -
// �ǂ̃L�����N�^�[���g�����̐ݒ�
//---------------------------------------------------------------------------
void Scene_Base::SetCharacter(int player_num, int monster_num)
{
	// �L�����N�^�[�ԍ��̕ۑ�
	m_player_num = player_num;
	m_monster_num = monster_num;
}

//-----------------------------------------------
// �V���h�[�}�b�v�̏�������
//-----------------------------------------------
void Scene_Base::ShadowMapInit()
{
	// �v���C���[�p�̃V���h�[�}�b�v�̍쐬
	m_player_shadowMap_handle = MakeShadowMap(4096, 4096);
	// �V���h�[�}�b�v�̍쐬
	m_shadowMap_handle = MakeShadowMap(4096, 4096);
	// ���C�g�̊p�x�̏�����
	m_light_angle = 10.0f;

	// ���C�g�̕����x�N�g���̎Z�o
	m_light_direction.x = sin(m_light_angle);
	m_light_direction.z = cos(m_light_angle);
	m_light_direction.y = -1.0f;
	VectorNormalize(&m_light_direction, &m_light_direction);

	// ���C�g������ݒ�
	SetLightDirection(m_light_direction);

	// �V���h�[�}�b�v���z�肷�郉�C�g�̕����̃Z�b�g
	SetShadowMapLightDirection(m_player_shadowMap_handle, m_light_direction);
	SetShadowMapLightDirection(m_shadowMap_handle, m_light_direction);
	// �V���h�[�}�b�v�ɕ`�悷��͈͂̐ݒ�
	SetShadowMapDrawArea(m_shadowMap_handle, VGet(-8192.0f, -0.1f, -8192.0f), VGet(+8192.0f, 3000.0f, +8192.0f));

}

//-----------------------------------------------
// �v���C���[�̃V���h�[�}�b�v�͈̔͐ݒ�
//-----------------------------------------------
void Scene_Base::SetPlayerShadowMapArea(Vector3 player_pos)
{
	// �V���h�[�}�b�v�ɕ`�悷��͈͂̐ݒ�
// ���͂��́@�͈͂Ńv���C���[�̃V���h�E�}�b�v��ݒ肵�Ă��邪
// �w��̉e���C�ɓ���Ȃ���Γ�ڂ�Y���W�̒l���グ�邩�S�̓I�ɕ`��͈͂��L����
	SetShadowMapDrawArea(m_player_shadowMap_handle,
		VGet(player_pos.x - 200.0f, -0.1f, player_pos.z - 200.0f),
		VGet(player_pos.x + 200.0f, +1500.0f, player_pos.z + 200.0f));
}

//-----------------------------------------------
// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
//-----------------------------------------------
void Scene_Base::UseShadowMapSet()
{
	
	SetUseShadowMap(1, -1);
	SetUseShadowMap(0, -1);
}

//-----------------------------------------------
// �V���h�[�}�b�v�̍폜
//-----------------------------------------------
void Scene_Base::ExitShadowMap()
{
	DeleteShadowMap(m_player_shadowMap_handle);
	DeleteShadowMap(m_shadowMap_handle);
}
