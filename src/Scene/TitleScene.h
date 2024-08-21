#pragma once
#include "src/Scene/Base/Scene_Base.h"
#include "src/System/Vector2.h"
// �^�C�g���V�[���̃N���X
class TiteleScene : public Scene_Base
{
	//int effeckt_h;
public:
	// ��������
	void Init()override;

	// �X�V����
	void Update(int bgm_volume, int se_volume)override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

public:
	int m_background_image = 0; // �w�i�摜�p�̕ϐ�
	Vector2 m_image_pos = {0.0f,0.0f};    // �摜�p�̕`����W
	int m_count_flame = 0; // �t���[���J�E���g�p�̕ϐ� 
	int m_count_time = 0;  // �t���[��������ۂ̊���o���ē����p�̎���
	int m_movie = 0;       // ����p�̕ϐ�

	// �t�H���g�f�[�^�p
	int m_GTA_font_data = 0; // GTA�̃t�H���g�f�[�^�p�̕ϐ�
	LPCSTR m_GTA_font_path = 0;

	enum Title_se
	{
		DECISION, // �^�C�g����ʂŎw��̃{�^���������ꂽ��

		SE_MAX,   // SE�̍ő吔
	};

	enum BGM
	{
		TITLE_BGM,  // �^�C�g����ʂŗ���BGM

		BGM_MAX // BGM�̍ő吔
	};

private:

	// �^�C�g����ʂł̐؂�ւ��p
	enum Title_SCENES
	{
		TITLE, // �^�C�g�����
		MOVIE, // ������
	};

	// ��ʐ؂�ւ��p�̕ϐ�
	int m_title_scene = 0;

	bool m_start_flag = false; // �^�C�g����ʂŃ{�^���������ꂽ���ǂ����̃t���O

};
