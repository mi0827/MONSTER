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
		m_menu_count++; // �J�E���g�𑝂₷
		// ���E�̃{�^���ŕύX����������I��
		// �O�FBGM
		// �P�FSE
		// ���{�^��
		if (IsPadOn(PAD_ID::PAD_D_DOWN, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_DOWN, PAD_NO::PAD_NO2))
		{
			m_select -= 1;
			if (m_select < 0)
			{
				m_select = 1;
			}
		}
		// �E�{�^��
		if (IsPadOn(PAD_ID::PAD_D_RIGHT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_RIGHT, PAD_NO::PAD_NO2))
		{
			m_select += 1;
			if (m_select >= 2)
			{
				m_select = 0;
			}
		}
		if (m_select == 0) {
			// BGM�̉��ʂ�������
			// ���{�^��
			if (IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO2))
			{
				m_bgm_Volume -= 10;
			}
			// BGM�̉��ʂ��グ��
			// ��{�^��
			if (IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO2))
			{
				m_bgm_Volume += 10;
			}
		}
		else {
			// SE�̉��ʂ�������
			// ���{�^��
			if (IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO2))
			{
				m_bgm_Volume -= 10;
			}
			// SE�̉��ʂ��グ��
			// ��{�^��
			if (IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO2))
			{
				m_se_Volume += 10;
			}
		}
	}
	//// BGM�̍Œ�̒l�Ŏ~�߂�
	//if (m_bgm_Volume <= Volume_LEAST) { m_bgm_Volume = Volume_LEAST; }
	//// BGM�̍ő�l�Ŏ~�߂�
	//if (m_bgm_Volume >= Volume_MAX) { m_bgm_Volume = Volume_MAX; }
	//// SE�̍Œ�̒l�Ŏ~�߂�
	//if (m_se_Volume <= Volume_LEAST) { m_se_Volume = Volume_LEAST; }
	//// SE�̍ő�l�Ŏ~�߂�
	//if (m_se_Volume >= Volume_MAX) { m_se_Volume = Volume_MAX; }

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

void Option::SetOptionMenu()
{
	// �e�o�[�̐ݒ�
	for (int i = 0; i < MENU_MAX; i++)
	{
		m_bra[i].Set(option_menu[i].m_pos, m_bra_size, &option_menu[i].m_value, true);

		// ���O�̐ݒ�
		m_bra[i].SetName(option_menu[i].m_name);

		// �F�̐ݒ�
		// �o�[�{�̂̐F
		m_bra[i].SetColor(255, 255, 0, &m_bra[i].m_color);
		// �o�[�̃o�b�N�̐F
		m_bra[i].SetColor(128, 128, 0, &m_bra[i].m_back_color);
		// �O�g�̐F
		m_bra[i].SetColor(255, 255, 255, &m_bra[i].m_line_color);
		// �����̐F
		m_bra[i].SetColor(0, 0, 0, &m_bra[i].m_character_color);
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
		//	// BGM�o�[�̕`�� 
		//	DrawBox(    (int)m_bgm_box_pos.x, (int)m_bgm_box_pos.y, (int)(m_bgm_box_pos.x + BAR_SIZE), (int)(m_bgm_box_pos.y - m_bgm_Volume), GetColor(0, 0, 0), true);
		//	DrawLineBox((int)m_bgm_box_pos.x, (int)m_bgm_box_pos.y, (int)(m_bgm_box_pos.x + BAR_SIZE), (int)(m_bgm_box_pos.y - m_bgm_Volume), GetColor(255, 255, 255));

		//	const char* bgm = "BGM";
		//	Vector2 bgm_pos; // ������̍��W
		//	bgm_pos.x = (float)GetDrawStringWidth(bgm, -1);
		//	bgm_pos.y = (float)GetFontSize();
		//	DrawFormatStringF((m_bgm_box_pos.x + BAR_SIZE / 2 - bgm_pos.x / 2), m_bgm_box_pos.y, GetColor(0, 0, 0), bgm);// ������̕`��

		//	// SE�o�[�̕`��
		//	DrawBox(    (int)m_se_box_pos.x, (int)m_se_box_pos.y, (int)(m_se_box_pos.x + BAR_SIZE), (int)(m_se_box_pos.y - m_se_Volume), GetColor(0, 0, 0), true);
		//	DrawLineBox((int)m_se_box_pos.x, (int)m_se_box_pos.y, (int)(m_se_box_pos.x + BAR_SIZE), (int)(m_se_box_pos.y - m_se_Volume), GetColor(255, 255, 255));
		//	const char* se = "SE";
		//	Vector2 se_pos; // ������̍��W
		//	se_pos.x = (float)GetDrawStringWidth(se, -1);
		//	se_pos.y = (float)GetFontSize();
		//	DrawFormatStringF((m_se_box_pos.x + BAR_SIZE / 2 - se_pos.x / 2), m_se_box_pos.y, GetColor(0, 0, 0), se); // ������̕`��
		//
		//
		//	// �ǂ���̃o�[��I��ł��邩�킩��₷�����邽�߂̂���
		//	if (m_select == 0) 
		//	{
		//		// BGM��
		//		DrawLineBox((int)m_bgm_box_pos.x, (int)m_bgm_box_pos.y, (int)(m_bgm_box_pos.x + BAR_SIZE), (int)(m_bgm_box_pos.y - m_bgm_Volume), GetColor(255, 255, 0));
		//		DrawFormatStringF(m_bgm_box_pos.x + BAR_SIZE / 2 - bgm_pos.x / 2 - 2, m_bgm_box_pos.y - 2, GetColor(255, 255, 0), bgm);
		//	}
		//	else
		//	{
		//		// SE��
		//		DrawLineBox((int)m_se_box_pos.x, (int)m_se_box_pos.y, (int)(m_se_box_pos.x + BAR_SIZE), (int)(m_se_box_pos.y - m_se_Volume), GetColor(225, 255, 0));
		//		DrawFormatStringF(m_se_box_pos.x + BAR_SIZE / 2 - se_pos.x / 2 -2, m_se_box_pos.y-2, GetColor(255, 255, 0), se);
		//	}

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
