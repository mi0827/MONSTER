#pragma once

// �V�[���N���X�����̃x�[�X�N���X
class Scene_Base
{
public:


	//! @brief ��������
	virtual void Init() = 0;
	//! @brief
	//! @param BGM�̃{�����[��
	//! @param SE�̃{�����[��
	virtual void Update(int bgm_volume, int se_volume) = 0;
	//! @brief �`�揈��
	virtual void Draw() = 0;
	//! @brief �I������
	virtual void Exit() = 0;

	//! @brief �V���h�[�}�b�v�p�̏������֐�
	void ShadowMapInit();

	//! @brief �v���C���[�̃V���h�[�}�b�v�͈̔͂̐ݒ�
	void SetPlayerShadowMapArea(Vector3 player_pos);

public:
	const int FLAME_MAX = 60; // ��b���t���[����

	bool m_scene_change_judge = false;  // �V�[���̐؂�ւ����s���Ă����� (true�ɂȂ�����V�[���̐؂�ւ��\)

	//! �v���C���[�p�̃V���h�[�}�b�v�p�ϐ�
	int m_player_shadowMap_handle = 0;
	//! �V���h�[�}�b�v�p�̕ϐ�
	int m_shadowMap_handle = 0;

	// �V���h�[�}�b�v�̃��C�g�̊p�x
	float m_light_angle = 0;
	// ���C�g�̃x�N�g��
	VECTOR m_light_direction;
};