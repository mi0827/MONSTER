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

	//! @brief �e�I�v�V�������j���[�̃o�[�̐ݒ�
	//! 
	void SetOptionMenu();
private:
	// �T�E���h�̉��͈̔�
	static constexpr int VOLUME_MAX = 10; // �ő�
	static constexpr int VOLUME_LEAST = 0; // �ŏ�
	static constexpr int VOLUME_CONSTANT_VALUE = 25; // VOLUME���P�ŕω�����l

	// ���j���[�{�^����������Ă������܂łɂ�����Œ᎞��
	static constexpr int MENU_COUNT = 10; 

	static constexpr int BOX_SIZE_X = SCREEN_W/ 2;               // �l�p�̔w�iX�����̃T�C�Y
	static constexpr int BOX_SIZE_Y = SCREEN_H / 2;               // �l�p�̔w�iY�����̃T�C�Y
	static constexpr int BOX_SIZE_HARF_X = BOX_SIZE_X / 2; // �w�iX�����̔����̃T�C�Y
	static constexpr int BOX_SIZE_HARF_Y = BOX_SIZE_Y / 2; // �w�iY�����̔����̃T�C�Y

	static constexpr int BAR_SIZE = 30;                // �o�[��X���W�̃T�C�Y
	static constexpr int BAR_SPACE_X = BOX_SIZE_HARF_X / 2;// ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(X���W)
	static constexpr int BAR_Y = VOLUME_MAX / 2;// ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(Y���W)


public:
	int m_bgm_Volume = 0; // BGM�̉���
	int m_se_Volume = 0;  // SE�̉���
	int m_mouse_sensi = 0; // �}�E�X���x
	bool m_option_flag = false;    // �I�v�V�������j���[���J�����߂̂���

private:
	// �I�v�V�������j���[���
	enum Menu
	{
		BGM,     // ����
		SE,        // ����
		MOUSE, //�}�E�X�̊��x
		OP,        // �������

		MAX
	};
	// ����������͂Ԃ������j���[�̍ő吔
	static constexpr int MENU_MAX = MOUSE + 1;

	// �e�X�e�[�^�X�Ŏg������
	struct Information
	{
		// �{�b�N�X(10���p��)
		Vector2 m_box_pos[VOLUME_MAX];
		// �O�g�̃{�b�N�X
		Vector2 m_back_line_box_pos;
		// �l
		int m_value = 0;
		// ������p�̓��ꕨ
		 const char* m_name;
	};
	// ��������ȊO�̂R����p��
	Information option_menu[MENU_MAX];



	Vector2 m_option_box_pos = { 0.0f,0.0f }; // �I�v�V�������j���[��ʂ̎l�p���W
	Vector2 m_bgm_box_pos = { 0.0f,0.0f };    // BGM�o�[�̍��W
	Vector2 m_se_box_pos = { 0.0f,0.0f };     // SE�o�[�̍��W

	int m_image_box = 0; // �w�i�摜�p�̓��ꕨ
	int m_menu_count = 0; // ���j���[�{�^����������Ă������܂łɂ�����Œ᎞�Ԃ��J�E���g���邽�߂̕�
	int m_select = 0; // SE��BGM����󂷂邽�߂̂���
};