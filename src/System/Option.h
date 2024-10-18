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
	void SetOptionMenu();

private:
	// �͈�
	static constexpr int VOLUME_MAX = 10;  // �ő�
	static constexpr int VOLUME_LEAST = 0; // �ŏ�
	static constexpr int VOLUME_CONSTANT_VALUE = 25; // VOLUME���P�ŕω�����l
	// ���j���[�{�^����������Ă������܂łɂ�����Œ᎞��
	static constexpr int MENU_COUNT = 10; 

	static constexpr int BOX_SIZE_X = SCREEN_W/ 2;         // �l�p�̔w�iX�����̃T�C�Y
	static constexpr int BOX_SIZE_Y = SCREEN_H / 2;        // �l�p�̔w�iY�����̃T�C�Y
	static constexpr int BOX_SIZE_HARF_X = BOX_SIZE_X / 2; // �w�iX�����̔����̃T�C�Y
	static constexpr int BOX_SIZE_HARF_Y = BOX_SIZE_Y / 2; // �w�iY�����̔����̃T�C�Y
	// �e�o�[�̐ݒ�Ŏg��
	static constexpr int BRA_X_DIVISION =  BOX_SIZE_X / 5;  // �w�i�摜�pX���W�w��̕����ŕ��������̑傫��
	static constexpr int BRA_Y_DIVISION =  BOX_SIZE_Y / 5;  // �w�i�摜�pY���W�w��̕����ŕ��������̑傫��


	static constexpr int BAR_X_SIZE = 550;                 // �o�[��X���W�̃T�C�Y
	static constexpr int BAR_Y_SIZE = 50;                  // �o�[�̍��W�̃T�C�Y
	static constexpr int BAR_SPACE_X = BOX_SIZE_HARF_X / 2; // ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(X���W)
	static constexpr int BAR_Y = VOLUME_MAX / 2;            // ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(Y���W)


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

	//! �I�v�V�������j���[��ʂ̔w�i�̒��S���W
	Vector2 m_option_box_pos = { SCREEN_W / 2 - BOX_SIZE_HARF_X, SCREEN_H / 2 - BOX_SIZE_HARF_Y }; 
	// �e�o�[��X���W
	static constexpr float BRA_X_STRAT = SCREEN_W / 2 - BOX_SIZE_HARF_X + BRA_X_DIVISION;
	
	// �e�X�e�[�^�X�Ŏg������
	struct Information
	{
		Vector2 m_pos;
		// �l
		int m_value = 0;
		// ������p�̓��ꕨ
		const char* m_name;
		// �o�[�̐F
		int m_color; 
	};
	// ��������ȊO�̂R����p��
	Information option_menu[MENU_MAX]
	{
		//! BGM�p
		{{ BRA_X_STRAT ,  m_option_box_pos.y + BRA_Y_DIVISION},  VOLUME_MAX, "BGM"},
		//! SE�p
		{{ BRA_X_STRAT , m_option_box_pos.y + BRA_Y_DIVISION * 2}, VOLUME_MAX, "SE"},
		//! �}�E�X���x�p
		{{ BRA_X_STRAT ,m_option_box_pos.y + BRA_Y_DIVISION * 3},  VOLUME_MAX, "�}�E�X���x"}

	};

	// ���ꂼ��ŕ`�悷��o�[
	UIBra m_bra[MENU_MAX];
	UIBra m_op;

	// �e�o�[�̃T�C�Y�̐ݒ�
	Vector2 m_bra_size = { BAR_X_SIZE, BAR_Y_SIZE };

	
	

	int m_image_box = 0; // �w�i�摜�p�̓��ꕨ
	int m_menu_count = 0; // ���j���[�{�^����������Ă������܂łɂ�����Œ᎞�Ԃ��J�E���g���邽�߂̕�
	int m_select = 0; // SE��BGM����󂷂邽�߂̂���
};