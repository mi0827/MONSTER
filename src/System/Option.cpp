#include "src/WinMain.h"
#include "Vector2.h"
#include "UIBar.h"
#include "Option.h"

// �I�v�V�������j���[�ł�邱��
// BGM,SE,�̃{�����[������
// �}�E�X�̊��x����
// �������
// 

// 
// �I�v�V�����w�i�͔�������
// ���ʂ͂P�O�����̃^�C�v�ɂ���
// �}�E�X���x�̂P�O����
// ��������͌��

Option::Option()
{
	m_menu_count = 0; // �O����X�^�[�g

	// ���W�ݒ�
	//m_option_box_pos.set(SCREEN_W / 2 - BOX_SIZE_HARF_X, SCREEN_H / 2 - BOX_SIZE_HARF_Y); // �w�i
	//m_bgm_box_pos.set(SCREEN_W / 2 - BAR_SPACE_X, SCREEN_H / 2 + BAR_Y);
	//m_se_box_pos.set(SCREEN_W / 2 + BAR_SPACE_X - BAR_SIZE, SCREEN_H / 2 + BAR_Y);
	m_option_flag = false; // �ŏ��̓I�v�V�������j���[�͕��Ă���
	m_bgm_Volume = 10;
	m_se_Volume = 10;
	m_select = 0; // BGM����X�^�[�g
}

Option::~Option()
{
}

//----------------------------------------------
// ��������
//----------------------------------------------
void Option::Init()
{
	m_image_box = LoadGraph("Data/Option/OptionMenu.png");
	// �e�o�[�̐ݒ�
	SetOptionMenu();
	// ������������������ŏ���
	//m_op.Set({ BRA_X_STRAT ,m_option_box_pos.y + BRA_Y_DIVISION * 4 }, { 200,30 }, 0, true);
}



//----------------------------------------------
// �I�v�V�����̍X�V����
//----------------------------------------------
void Option::Update()
{

	// �I�v�V�������j���[���J���Ƃ�
	// �{�^���������ꂽ��
	if (PushHitKey(KEY_INPUT_TAB))
	{
		// �I�v�V�������j���[���J��
		m_option_flag = true;
	}

	// �I�v�V�������j���[���J���Ă���Ƃ�
	if (m_option_flag)
	{
		// �ǂ̃��j���[�𑀍삷�邩�̑I��
		MenuSelect();
		m_menu_count++; // �J�E���g�𑝂₷
		// �I�����ꂽ���j���[�o�[�̒l�𑝂₷
		if (PushHitKey(KEY_INPUT_RIGHT))
		{
			// �\�����ł���p�ɒl��ݒ肵�Ēl�ɑ���
			option_menu[m_selection_menu].m_value += VOLUME_CONSTANT_VALUE;
			if (option_menu[m_selection_menu].m_value >= VOLUME_MAX)
			{
				// �ő�̒l�𒴂��Ȃ��悤�ɂ���
				option_menu[m_selection_menu].m_value = VOLUME_MAX;
			}
		}
		// �I�����ꂽ���j���[�o�[�̒l�����炷
		if (PushHitKey(KEY_INPUT_LEFT))
		{
			// �\�����ł���p�ɒl��ݒ肵�Ēl�ɑ���
			option_menu[m_selection_menu].m_value -= VOLUME_CONSTANT_VALUE;
			if (option_menu[m_selection_menu].m_value <= VOLUME_LEAST)
			{
				// �ŏ��̒l�𒴂��Ȃ��悤�ɂ���
				option_menu[m_selection_menu].m_value = VOLUME_LEAST;
			}
		}
	}

	// �J�E���g�����ȏ�ɂȂ�����
	if (m_menu_count >= MENU_COUNT)
	{
		// �I�v�V�������j���[���J���Ă���
		// �Ȃ��{�^���������ꂽ��
		if (PushHitKey(KEY_INPUT_TAB))
		{
			// �I�v�V�������j���[�����
			m_option_flag = false;
			// �J�E���g�����Z�b�g
			m_menu_count = 0;
		}
	}
	// �o�[�̍X�V����
	for (int i = 0; i < MENU_MAX; i++)
	{
		m_bra[i].Update(&option_menu[i].m_value);
	}
}

//----------------------------------------------
// �I�v�V�����̐ݒ�
//----------------------------------------------
void Option::SetOptionMenu()
{
	// �e�o�[�̐ݒ�
	for (int i = 0; i < MENU_MAX; i++)
	{
		// �e�o�[�̍쐬
		m_bra[i].Set(option_menu[i].m_pos, m_bra_size, &option_menu[i].m_value, true);

		// ���O�̐ݒ�
		m_bra[i].SetName(option_menu[i].m_name);

		// �F�̐ݒ�
		// �o�[�{�̂̐F
		m_bra[i].SetColor(255, 255, 0, &m_bra[i].m_color);
		// �o�[�̃o�b�N�̐F
		m_bra[i].SetColor(128, 128, 0, &m_bra[i].m_back_color);
		// �O�g�̐F
		m_bra[i].SetColor(0, 0, 0, &m_bra[i].m_line_color);
		// �����̐F
		m_bra[i].SetColor(0, 0, 0, &m_bra[i].m_character_color);
	}
}

//----------------------------------------------
// �ǂ̃��j���[�𑀍삷�邩�̑I������
//----------------------------------------------
void Option::MenuSelect()
{
	// ��L�[�������ꂽ��
	if (PushHitKey(KEY_INPUT_UP))
	{
		m_selection_menu--;
		// ���ȏ��ɍs���Ɖ��Ɉړ�����
		if (m_selection_menu < BGM)
		{
			m_selection_menu = MOUSE;
		}
	}
	if (PushHitKey(KEY_INPUT_DOWN))
	{
		m_selection_menu++;
		// ���ȏ㉺�ɍs���Ə�Ɉړ�����
		if (m_selection_menu > MOUSE)
		{
			m_selection_menu = BGM;
		}
	}
	// �I�����Ă��郁�j���[�����O�g�̐F��ς���
	for (int i = 0; i < MENU_MAX; i++)
	{
		if (i == m_selection_menu)
		{
			// �O�g�̐F
			m_bra[m_selection_menu].SetColor(255, 255, 255, &m_bra[m_selection_menu].m_line_color);
		}
		else
		{
			// �O�g�̐F
			m_bra[i].SetColor(0, 0, 0, &m_bra[i].m_line_color);
		}
	}

}

//----------------------------------------------
// �I�v�V�����̕`�揈��
//----------------------------------------------
void Option::Draw()
{
	// ChangeFont("�l�r ����");
	// �I�v�V�������j���[���J���Ă��鎞����
	// �`�悷��
	if (m_option_flag)
	{
		DrawExtendGraphF(m_option_box_pos.x, m_option_box_pos.y, m_option_box_pos.x + BOX_SIZE_X, m_option_box_pos.y + BOX_SIZE_Y, m_image_box, TRUE);  // �I�v�V�������j���[�̔w�i
		

		// �f�t�H���g�̕����̑傫����ۑ����Ă���
		int original_font_size = GetFontSize();
		SetFontSize(28); // �t�H���g�T�C�Y�̕ύX
		// �e�o�[�̕`�揈��
		for (int i = 0; i < MENU_MAX; i++)
		{
			m_bra[i].Draw();
		}
		SetFontSize(original_font_size); // �t�H���g�T�C�Y��߂�
	}

}
