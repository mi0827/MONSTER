#include "src/WinMain.h"
#include "src/System/Vector2.h"
#include "src/Sound/BGM.h"
#include "src/Sound/SE.h"
#include "Base/Scene_Base.h"
#include "TitleScene.h"

const int Title_Time_MAX = 5;  // �^�C�g���`�掞��(������3�b)
BGM title_bgm; // BGM�N���X�̃I�u�W�F�N�g
SE title_se; // SE�N���X�̃I�u�W�F�N�g

//------------------------------------------
// ��������
//------------------------------------------
void TiteleScene::Init()
{
	m_background_image = LoadGraph("Data/Background/Title.jpg"); // �摜�̗p������
	m_image_pos.set(0.0f, 0.0f); // �`����W�̐ݒ�

	// �J�E���g�ނ͍ŏ��̓}�b�N�X�X�^�[�g
	m_count_flame = FLAME_MAX;
	m_count_time = Title_Time_MAX;

	m_scene_change_judge = false; // �ŏ��̓V�[���̐؂�ւ������Ă͂����Ȃ�

	// �t�H���g�f�[�^�̓ǂݍ���
	//GTA_font_data = LoadFontDataToHandle("Data/Font/Gta/GTA.dft", 1.0f);
	m_GTA_font_path = "Data/Font/Gta/pricedown bl.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(m_GTA_font_path, FR_PRIVATE, NULL) > 0)
	{

	}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	ChangeFont("Pricedown Bl", DX_CHARSET_DEFAULT);

	// BGM�̔z��̊m��
	title_bgm.BGM_ContainerNew(BGM_MAX);
	// BGM�̓ǂݍ���
	title_bgm.Load_BGM("Data/BGM/Title/Title.mp3", TITLE_BGM);
	// BGM�̍Đ�
	title_bgm.Play_BGM(DX_PLAYTYPE_BACK, true, TITLE_BGM);
	// SE�p�̔z��̗p��
	title_se.SE_ContainerNew(SE_MAX);
	// SE�̓ǂݍ���
	title_se.Load_SE("Data/SE/Title/Title_start.mp3", DECISION);

}

//------------------------------------------
// �X�V����
//------------------------------------------
void TiteleScene::Update(int bgm_volume, int se_volume)
{

	title_bgm.BGM_ChangeVolume(bgm_volume, BGM_MAX); // BGM�̃{�����[���ύX����
	title_se.SE_ChangeVolume(se_volume, SE_MAX);     // SE�̃{�����[���ύX����
	switch (m_title_scene)
	{
	case TITLE:

		// BGM���I�������
		if (!title_bgm.Playing_BGM(TITLE_BGM))
		{
			// BGM�̍Đ�
			title_bgm.Play_BGM(DX_PLAYTYPE_LOOP, true, TITLE_BGM);
		}

		// �Q�[���p�b�h�̏����ۂ��Ǝ擾
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)
		{
			// A�{�^���������ꂽ�玟�̃V�[���Ɉړ�
			m_start_flag = true;

		}
		else if (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_A)
		{
			// A�{�^���������ꂽ�玟�̃V�[���Ɉړ�
			m_start_flag = true;
		}
		else
		{
			// �{�^����������Ă��Ȃ��Ƃ��̓t���O��������
			m_start_flag = false;
		}


		// �X�^�[�g�t���O�������Ă�����SE�̍Đ�
		if (m_start_flag) {
			title_se.Play_SE(DECISION, DX_PLAYTYPE_BACK, TRUE);
		}
		// �X�^�[�g�t���O�������Ă����玟�̃V�[���ɐi��
		if (m_start_flag && title_se.Playing_SE(DECISION))
		{
			m_scene_change_judge = true; // �V�[���̐؂�ւ���������
			title_bgm.Stop_BGM(TITLE_BGM); // BGM���~�߂�
		}
		else {
			// �t���O���������Ă�����
			m_count_flame--; // �t���[���̃J�E���g�����炷
			if (m_count_flame <= 0)
			{ // �t���[�����ݒ肳�ꂽ�l�ȏ�ɂȂ�����
				m_count_flame = FLAME_MAX; // �t���[���J�E���g�����Z�b�g
				m_count_time--;    // �^�C���J�E���g��i�߂�
			}
			if (m_count_time <= 0) // �^�C�g����ʂň�莞�Ԏ~�܂��Ă�����
			{
				m_title_scene = MOVIE; // ����̃V�[���̐؂�ւ���
			}
		}

		break;

	case MOVIE:

		title_bgm.Stop_BGM(TITLE_BGM); // BGM���~�߂�

		// �v���C����̍Đ�
		m_movie = PlayMovie("Data/Movie/02.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		GetMovieStateToGraph(m_movie);
		// �Q�[���p�b�h�̏����ۂ��Ǝ擾
		if (GetMovieStateToGraph(m_movie))
		{
			// A�{�^���������ꂽ��^�C�g���`��ɖ߂�
			m_title_scene = TITLE;
			m_count_time = Title_Time_MAX;
			PauseMovieToGraph(m_movie);
		}
		// �Q�[���p�b�h�̏����ۂ��Ǝ擾
		//if (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_A) {
		//	// A�{�^���������ꂽ��^�C�g���`��ɖ߂�
		//	title_scene = TITLE;
		//}

		break;
	}
}

//------------------------------------------
// �`�揈��
//------------------------------------------
void TiteleScene::Draw()
{

	// �w�i�摜�̕`��
	DrawExtendGraphF(m_image_pos.x, m_image_pos.y, SCREEN_W, SCREEN_H, m_background_image, TRUE);
	// �����łƂ��Ă����������Z�b�g���Ă���
	// �����̍ŏ��̑傫�����Ƃ��Ă���
	int original_font_size = GetFontSize();


	switch (m_title_scene)
	{
	    case TITLE:
	    {
		    SetFontSize(200); // �t�H���g�T�C�Y�̕ύX
		    const char* name = "GLADIATOR";
		    // �`�敝�̎擾
		    int w = GetDrawStringWidth(name, -1);
		    // ������̍����擾
		    int h = GetFontSize();
		    // �`��
		    int taile_h = -50;
		    DrawString(SCREEN_W / 2 - w / 2 + 7, SCREEN_H / 2 + taile_h + 7, name, GetColor(128, 0, 0)); // ��
		    DrawString(SCREEN_W / 2 - w / 2, SCREEN_H / 2 + taile_h, name, GetColor(255, 0, 0));         // ��
	    }
	break;

	   case MOVIE:
	   {

	   }
	   break;
	}

	SetFontSize(100); // �t�H���g�T�C�Y�̕ύX
	DrawString(16 + 5, 16 + 5, "START: A ", GetColor(0, 128, 128)); // ��
	DrawString(16, 16, "START: A ", GetColor(0, 255, 255));         // ��
	SetFontSize(original_font_size); // �t�H���g�T�C�Y��

}

//------------------------------------------
// �I������
//------------------------------------------
void TiteleScene::Exit()
{
	DeleteGraph(m_background_image); // �摜�f�[�^�̉��

	// ********** �t�H���g�̃A�����[�h **********
	if (RemoveFontResourceEx(m_GTA_font_path, FR_PRIVATE, NULL)) 
	{

	}
	else 
	{
		MessageBox(NULL, "remove failure", "", MB_OK);
	}
	ChangeFont("�l�r ����", DX_CHARSET_DEFAULT);

}
