#include "src/WinMain.h"
#include "Vector2.h"
#include "Option.h"

// �T�E���h�̉��͈̔�
constexpr int Volume_MAX = 255; // �ő�
constexpr int Volume_LEAST = 0; // �ŏ�

constexpr int MENU_COUNT = 10; // ���j���[�{�^����������Ă������܂łɂ�����Œ᎞��

constexpr int BOX_SIZE_X = 280;               // �l�p�̔w�iX�����̃T�C�Y
constexpr int BOX_SIZE_Y = 350;               // �l�p�̔w�iY�����̃T�C�Y
constexpr int BOX_SIZE_HARF_X = BOX_SIZE_X / 2; // �w�iX�����̔����̃T�C�Y
constexpr int BOX_SIZE_HARF_Y = BOX_SIZE_Y / 2; // �w�iY�����̔����̃T�C�Y

constexpr int BAR_SIZE = 30;                // �o�[��X���W�̃T�C�Y
constexpr int BAR_SPACE_X = BOX_SIZE_HARF_X / 2;// ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(X���W)
constexpr int BAR_Y = Volume_MAX / 2;// ���S����ǂꂭ�炢���Ԃ��J���邩�̒l(Y���W)



Option::Option()
{
	m_menu_count = 0; // �O����X�^�[�g

	// ���W�ݒ�
	m_option_box_pos.set(SCREEN_W / 2 - BOX_SIZE_HARF_X, SCREEN_H / 2 - BOX_SIZE_HARF_Y); // �w�i
	m_BGM_box_pos.set(SCREEN_W / 2 - BAR_SPACE_X, SCREEN_H / 2 + BAR_Y);
	m_SE_box_pos.set(SCREEN_W / 2 + BAR_SPACE_X - BAR_SIZE, SCREEN_H / 2 + BAR_Y);
	m_option_flag = false; // �ŏ��̓I�v�V�������j���[�͕��Ă���
	m_BGM_Volume = 100;
	m_SE_Volume = 100;
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
}

//----------------------------------------------
// �I�v�V�����̍X�V����
//----------------------------------------------
void Option::Update()
{

	// �I�v�V�������j���[���J���Ƃ�
	// �{�^���������ꂽ��
	if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO1))
	{
		// �I�v�V�������j���[���J��
		m_option_flag = true;
	}
	if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO2))
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
				m_BGM_Volume -= 10;
			}
			// BGM�̉��ʂ��グ��
			// ��{�^��
			if (IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO2)) 
			{
				m_BGM_Volume += 10;
			}
		}
		else {
			// SE�̉��ʂ�������
			// ���{�^��
			if (IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_LEFT, PAD_NO::PAD_NO2)) 
			{
				m_SE_Volume -= 10;
			}
			// SE�̉��ʂ��グ��
			// ��{�^��
			if (IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_D_UP, PAD_NO::PAD_NO2))
			{
				m_SE_Volume += 10;
			}
		}
	}
	// BGM�̍Œ�̒l�Ŏ~�߂�
	if (m_BGM_Volume <= Volume_LEAST) { m_BGM_Volume = Volume_LEAST; }
	// BGM�̍ő�l�Ŏ~�߂�
	if (m_BGM_Volume >= Volume_MAX) { m_BGM_Volume = Volume_MAX; }
	// SE�̍Œ�̒l�Ŏ~�߂�
	if (m_SE_Volume <= Volume_LEAST) { m_SE_Volume = Volume_LEAST; }
	// SE�̍ő�l�Ŏ~�߂�
	if (m_SE_Volume >= Volume_MAX) { m_SE_Volume = Volume_MAX; }

	// �J�E���g�����ȏ�ɂȂ�����
	if (m_menu_count >= MENU_COUNT) 
	{
		// �I�v�V�������j���[���J���Ă���
		// �Ȃ��{�^���������ꂽ��
		if (IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO1) || IsPadOn(PAD_ID::PAD_START, PAD_NO::PAD_NO2))
		{
			// �I�v�V�������j���[�����
			m_option_flag = false;
			// �J�E���g�����Z�b�g
			m_menu_count = 0;
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
		// BGM�o�[�̕`�� 
		DrawBox(    (int)m_BGM_box_pos.x, (int)m_BGM_box_pos.y, (int)(m_BGM_box_pos.x + BAR_SIZE), (int)(m_BGM_box_pos.y - m_BGM_Volume), GetColor(0, 0, 0), true);
		DrawLineBox((int)m_BGM_box_pos.x, (int)m_BGM_box_pos.y, (int)(m_BGM_box_pos.x + BAR_SIZE), (int)(m_BGM_box_pos.y - m_BGM_Volume), GetColor(255, 255, 255));
		int original_font_size = GetFontSize();
		SetFontSize(28); // �t�H���g�T�C�Y�̕ύX
		const char* bgm = "BGM";
		Vector2 bgm_pos; // ������̍��W
		bgm_pos.x = (float)GetDrawStringWidth(bgm, -1);
		bgm_pos.y = (float)GetFontSize();
		DrawFormatStringF((m_BGM_box_pos.x + BAR_SIZE / 2 - bgm_pos.x / 2), m_BGM_box_pos.y, GetColor(0, 0, 0), bgm);// ������̕`��

		// SE�o�[�̕`��
		DrawBox(    (int)m_SE_box_pos.x, (int)m_SE_box_pos.y, (int)(m_SE_box_pos.x + BAR_SIZE), (int)(m_SE_box_pos.y - m_SE_Volume), GetColor(0, 0, 0), true);
		DrawLineBox((int)m_SE_box_pos.x, (int)m_SE_box_pos.y, (int)(m_SE_box_pos.x + BAR_SIZE), (int)(m_SE_box_pos.y - m_SE_Volume), GetColor(255, 255, 255));
		const char* se = "SE";
		Vector2 se_pos; // ������̍��W
		se_pos.x = (float)GetDrawStringWidth(se, -1);
		se_pos.y = (float)GetFontSize();
		DrawFormatStringF((m_SE_box_pos.x + BAR_SIZE / 2 - se_pos.x / 2), m_SE_box_pos.y, GetColor(0, 0, 0), se); // ������̕`��
	
	
		// �ǂ���̃o�[��I��ł��邩�킩��₷�����邽�߂̂���
		if (m_select == 0) 
		{
			// BGM��
			DrawLineBox((int)m_BGM_box_pos.x, (int)m_BGM_box_pos.y, (int)(m_BGM_box_pos.x + BAR_SIZE), (int)(m_BGM_box_pos.y - m_BGM_Volume), GetColor(255, 255, 0));
			DrawFormatStringF(m_BGM_box_pos.x + BAR_SIZE / 2 - bgm_pos.x / 2 - 2, m_BGM_box_pos.y - 2, GetColor(255, 255, 0), bgm);
		}
		else
		{
			// SE��
			DrawLineBox((int)m_SE_box_pos.x, (int)m_SE_box_pos.y, (int)(m_SE_box_pos.x + BAR_SIZE), (int)(m_SE_box_pos.y - m_SE_Volume), GetColor(225, 255, 0));
			DrawFormatStringF(m_SE_box_pos.x + BAR_SIZE / 2 - se_pos.x / 2 -2, m_SE_box_pos.y-2, GetColor(255, 255, 0), se);
		}
		SetFontSize(original_font_size); // �t�H���g�T�C�Y��߂�
	}

}
