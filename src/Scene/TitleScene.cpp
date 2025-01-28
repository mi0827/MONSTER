#include "src/WinMain.h"
#include "src/System/Random.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/System/Transform.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"

#include "src/Collision/BoxCollision.h"
#include "src/Collision/CapsuleCollision.h"
#include "src/Hit/Hit.h"

#include "src/System/UIBar.h"
#include "src/Effect/Effect.h"
#include "src/Sound/Sound.h"

#include "src/Action/Combo.h"
#include "src/System/Move.h"
#include "src/Character/CharacterBase.h"
#include "src/Character/SamplePlayer.h"
#include "src/Character/Hero.h"

#include "src/Field/FieldBase.h"
#include "src/Field/HitField.h" 
#include "src/Field/TitleField.h"
#include "src/Field/Field.h"

#include "src/Camera.h"
#include "src/System/Text.h"
#include "Base/Scene_Base.h"
#include "TitleScene.h"



//------------------------------------------
// ��������
//------------------------------------------
void TitleScene::Init()
{
	// �x�[�X�N���X�ŏ��������Ă����������̂̏�����
	BaseInit();
	// �t�B�[���h�̏�����
	m_field_1.Init();

	// �J�����̏����ݒ�
	camera.PlayFieldInit();

	//PlayerInit(hero);
	//// �v���C���[�̏����ݒ� 
	//m_player->Init();
	//m_player->SetCharacterPos({ 0,0,750 });
	//m_player->SetCharacterRot({ 0.0f,180.0f,0.0f });

	// �J�����̌����̐ݒ�
	//camera.SetCameraRot(m_player->m_transform.rot);

	// �V���h�[�}�b�v�̐ݒ�
	//ShadowMapInit();

	m_background_image = LoadGraph("Data/Title/Title.jpg");
	// ���݂̃V�[���̐ݒ�(�^�C�g���V�[��)
	m_now_scene = Title;
}

//------------------------------------------
// �X�V����
//------------------------------------------
void TitleScene::Update()
{

	switch (m_turn)
	{
	case Main:
		// �J�����̌������擾����
		//m_camera_rot = camera.GetCameraRot();

		// �v���C���[�̍X�V����
		//m_player->Update(&m_camera_rot);

		// �t�B�[���h�Ƃ̓����蔻��
		//HitField();

		// �J�����̍X�V����
		//camera.MouseCamera(&m_player->m_transform.pos);

		// �^�C�g���V�[���̍X�V����
		TitleUpdate();



		break;
	case FadeOut:
		// �t�F�[�h�A�E�g�̏���
		FadeOutSceneChange(QuestArea);
		break;
	}

}

//------------------------------------------
// �`�揈��
//------------------------------------------
void TitleScene::Draw()
{

	//// �v���C���[�̃V���h�[�}�b�v�̃G���A�̃Z�b�g
	//SetShadowMapArea(m_shadowMap_handle_1, m_player->m_transform.pos);
	////-------------------------------------------------------------
 //   // �V���h�E�}�b�v�̍쐬�i�����Ŋe�I�u�W�F�N�g�̃V���h�[�}�b�v�̐ݒ�j
 //   //-------------------------------------------------------------
 //   // �V���h�E�}�b�v�ւ̕`��̏���
	//ShadowMap_DrawSetup(m_shadowMap_handle_1);
	//{
	//	// �v���C���[�̕`�揈��
	//	m_player->Draw();
	//}
	//ShadowMap_DrawSetup(m_shadowMap_handle);
	//{
	//	// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
	//	m_field_1.Draw();
	//}
	//// �V���h�E�}�b�v�ւ̕`����I��
	//ShadowMap_DrawEnd();
	////-------------------------------------------------------------
	//// �e���f���̕`��
	////-------------------------------------------------------------
	//// �o�b�N�o�b�t�@�ɕ`�悷��
	//SetDrawScreen(DX_SCREEN_BACK);
	//
	//// �J�����̕`�揈��
	//camera.Draw();
	//
	//// ��̕`��
	//SkyDraw();
	//
	//SetUseShadowMap(1, m_shadowMap_handle_1);
	//{
	//	// �v���C���[�̕`�揈��
	//	m_player->Draw();
	//}
	//// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	//SetUseShadowMap(0, m_shadowMap_handle);
	//{
	//	// �v���C���[�̕`�揈��
	//	m_player->Draw();
	//	// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
	//	m_field_1.Draw();
	//}
	//
	//
	//UseShadowMapSet();



	//=============================================
	// ���Ń^�C�g����`��
	//=============================================

	DrawExtendGraphF(0, 0, SCREEN_W, SCREEN_H, m_background_image, TRUE);

	// �t�H���g�T�C�Y�̐ݒ�
	//SetFontSize(80);
	//const char* name = "�����X�^�[�N���b�V��" /*:: RENTER*/;
	//// �`�敝�̎擾
	//float w = GetDrawStringWidth(name, -1);
	//// ������̍����̎擾
	//float h = GetFontSize();
	// �`����W
	/*Vector2 draw_pos = { SCREEN_W / 2 - w / 2, 0 };
	DrawString(draw_pos.x, draw_pos.y, name, GetColor(255, 128, 50));*/
	/*name = "Push : W";
	w = GetDrawStringWidth(name, -1);*/
	//h = GetFontSize();
	//draw_pos = { (SCREEN_W / 2 - m_text.TITLE_BACK_HALF_SIZE),(SCREEN_H - h - m_text.CREVICE_SIZE) };
	//// �e�L�X�g�t�@�C������̃X�g�[���[�̕`��
	//m_text.TextDraw(m_text_num, { draw_pos.x, draw_pos.y }, m_text.TITLE_BACK_SIZE);
	// �t�F�[�h�̕`�揈��
	FadeDraw();

}

//------------------------------------------
// �I������
//------------------------------------------
void TitleScene::Exit()
{

	//�@�V���h�[�}�b�v�̍폜
	ExitShadowMap();

	//m_player->Exit();
}

//------------------------------------------
// �t�B�[���h�Ƃ̓����蔻��
//------------------------------------------
void TitleScene::HitField()
{

}

//------------------------------------------
// �I�v�V�������j���[�ł�����Ă����l�𔽉f����֐�
//------------------------------------------
void TitleScene::OptionValuesReflect(int bgm, int se, int mouse)
{
	// �J�����̊��x�ݒ�
	camera.SetCameraSensi(mouse);

	// �L�����N�^�[�̃T�E���h�̒���
	//m_player->m_se.SetSoundVolume(se);

	// BGM�̃T�E���h�̒���
}

//------------------------------------------
// �^�C�g���̍X�V����
//------------------------------------------
void TitleScene::TitleUpdate()
{
	switch (m_title_mode_num)
	{
	case TITLE:

		// �^�C�g����ʂł̃J�E���g�����炷
		m_count_flame++;
		// �t���[�������ȉ��ɂȂ�����
		if ((m_count_flame % FLAME_MAX == 0) && m_count_flame != 0)
		{
			// ���Ԃ𑝂₷
			m_count_time++;
		}
		// ���Ԃ����ȏ�o�߂�����
		if (m_count_time >= TITLE_TIME_MAX)
		{
			// �J�E���g�����Z�b�g
			m_count_time = 0;
			m_count_flame = 0;
			// ���惂�[�h�Ɉڍs����
			m_title_mode_num = MOVIE;
		}
		// BGM���I�������
		//if (!title_bgm.Playing_BGM(TITLE_BGM))
		//{
		//	// BGM�̍Đ�
		//	title_bgm.Play_BGM(DX_PLAYTYPE_LOOP, true, TITLE_BGM);
		//}
		// X�L�[�������ꂽ���ɃV�[���̕ύX������i�������̉��j
		if (PushHitKey(KEY_INPUT_RETURN))
		{
			// ���ɍs���Ăق����V�[���Ɉړ�
			SetNextScene(Story);
			// �V�[���ύX�t���O�𗧂Ă�
			m_scene_change_judge = true;
		}
		break;

	case MOVIE:

		// �v���C����̍Đ�
		m_movie = PlayMovie("Data/Movie/02.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		//GetMovieStateToGraph(m_movie);
		// �w��̓���̍Đ���Ԃ��擾
		if (GetMovieStateToGraph(m_movie))
		{
			// ��ʂ̏�Ԃ��^�C�g����Ԃɂ���
			m_title_mode_num = TITLE;
			// �Đ����̓�����~����
			PauseMovieToGraph(m_movie);
		}
	

	
		break;
	}
}

