#pragma once

class EndScene : public Scene_Base
{
public:
	// ��������
	void Init()override;

	// �X�V����
	void Update(int bgm_volume, int se_volume)override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

	// BGM�̏�������
	void BGM_Init();

public:
	int m_background_image = 0; // �w�i�摜�p��
	Vector2 m_image_pos = {0.0f,0.0f};    // �摜�p�̕`����W

	int m_count_flame = 0; // �t���[���J�E���g�p�̕ϐ� 
	int m_count_time = 0;  // �t���[��������ۂ̊���o���ē����p�̎���

	// �t�H���g�f�[�^�p
	int m_GTA_font_data = 0; // GTA�̃t�H���g�f�[�^�p�̕ϐ�
	LPCSTR m_GTA_font_path = 0;


	enum BGM
	{

		BGM_1, // ��ڂ�bgm

		BGM_MAX // bgm�̍ő吔
	};
};