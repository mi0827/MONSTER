#pragma once

class Option
{
public:
	// �R���X�g���N�^
	Option();
	// �f�X�g���N�^
	~Option();
	// ��������
	void Init();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

public:
	int m_BGM_Volume = 0; // BGM�̉���
	int m_SE_Volume = 0;  // SE�̉���
	bool m_option_flag = false;    // �I�v�V�������j���[���J�����߂̂���

private:
	Vector2 m_option_box_pos = { 0.0f,0.0f }; // �I�v�V�������j���[��ʂ̎l�p���W
	Vector2 m_BGM_box_pos = { 0.0f,0.0f };    // BGM�o�[�̍��W
	Vector2 m_SE_box_pos = { 0.0f,0.0f };     // SE�o�[�̍��W

	int m_image_box = 0; // �w�i�摜�p�̓��ꕨ
	int m_menu_count = 0; // ���j���[�{�^����������Ă������܂łɂ�����Œ᎞�Ԃ��J�E���g���邽�߂̕�
	int m_select = 0; // SE��BGM����󂷂邽�߂̂���
};