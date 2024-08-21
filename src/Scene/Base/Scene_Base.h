#pragma once

// �V�[���N���X�����̃x�[�X�N���X
class Scene_Base
{
public:


	// ��������
	virtual void Init() = 0;
	// �X�V����
	// ����
	// �P�FBGM�̃{�����[��
	// �Q�FSE�̃{�����[��
	virtual void Update(int bgm_volume, int se_volume) = 0;
	// �`�揈��
	virtual void Draw() = 0;
	// �I������
	virtual void Exit() = 0;

	
public:
	const int FLAME_MAX = 60; // ��b���t���[����

	bool m_scene_change_judge = false;  // �V�[���̐؂�ւ����s���Ă����� (true�ɂȂ�����V�[���̐؂�ւ��\)

};