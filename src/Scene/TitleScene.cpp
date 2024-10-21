#include "src/WinMain.h"
#include "src/System/Random.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/System/Transform.h"


#include "src/Model/Model.h"
#include "src/Animation/Animation.h"
#include "src/Effect/Effect.h"

#include "src/Collision/BoxCollision.h"
#include "src/Collision/CapsuleCollision.h"
#include "src/Hit/Hit.h"

#include "src/System/UIBar.h"

#include "src/Action/Combo.h"
#include "src/System/Move.h"
#include "src/Character/CharacterBase.h"
#include "src/Character/SamplePlayer.h"

#include "src/Field/FieldBase.h"
#include "src/Field/HitField.h" 
#include "src/Field/TitleField.h"


#include "src/Sound/BGM.h"
#include "src/Sound/SE.h"

#include "src/Camera.h"

#include "Base/Scene_Base.h"
#include "TitleScene.h"



//------------------------------------------
// ��������
//------------------------------------------
void TitleScene::Init()
{


	// �t�B�[���h�̏�����
	field.Init();


	// �J�����̏����ݒ�
	camera.PlayField_Init();

	// �v���C���[�̐ݒ�
	player = new SamplePlayer;

	// �v������[�̏����ݒ� 
	player->Init();
	player->SetCharacterPos({ 0,0,750 });
	player->SetCharacterRot({ 0.0f,180.0f,0.0f });

	// �J�����̌����̐ݒ�
	camera.SetCameraRot(player->m_transform.rot);

	// �V���h�[�}�b�v�̐ݒ�
	ShadowMapInit();

	// AreaBOX�̐ݒ�
	SetAeraBoxSet();

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
		m_camera_rot = camera.GetCameraRot();

		// �v���C���[�̍X�V����
		player->Update(&m_camera_rot);

		// �t�B�[���h�Ƃ̓����蔻��
		HitField();

		// �J�����̍X�V����
		camera.MouseCamera(&player->m_transform.pos);

		// X�L�[�������ꂽ���ɃV�[���̕ύX������i�������̉��j
		if (PushHitKey(KEY_INPUT_RETURN))
		{
			// ���ɍs���Ăق����V�[���Ɉړ�
			SetNextScene(QuestArea);
			// �V�[���ύX�t���O�𗧂Ă�
			m_scene_change_judge = true;
		}

		// ���̓����蔻��ɓ�������
		if (CheckBoxHit3D(player->m_transform.pos, player->m_move_hit_size,
			m_area_box[next_scene].m_box.hit_pos, m_area_box[next_scene].m_box.half_size))
		{
			// �t�F�[�h�q�f�̃^�[���ɕύX
			m_turn = FadeOut;
		}
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
	// �v���C���[�̃V���h�[�}�b�v�̃G���A�̃Z�b�g
	SetPlayerShadowMapArea(player->m_transform.pos);

	//-------------------------------------------------------------
		// �V���h�E�}�b�v�̍쐬�i�����Ŋe�I�u�W�F�N�g�̃V���h�[�}�b�v�̐ݒ�j
		//-------------------------------------------------------------
		// �V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(m_player_shadowMap_handle);
	{
		// �v���C���[�̕`�揈��
		player->Draw();

	}
	ShadowMap_DrawSetup(m_shadowMap_handle);
	{
		// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
		field.Draw();
	}

	// �V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	//-------------------------------------------------------------
	// �e���f���̕`��
	//-------------------------------------------------------------

	// �o�b�N�o�b�t�@�ɕ`�悷��
	SetDrawScreen(DX_SCREEN_BACK);

	// �J�����̕`�揈��
	camera.Draw();


	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(1, m_player_shadowMap_handle);
	{
		player->Draw();

		// �q�[���[�̕`�揈��
		//hero.Draw();
	}
	SetUseShadowMap(0, m_shadowMap_handle);
	{
		// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
		field.Draw();

	}
	UseShadowMapSet();

	
	// ����̕ǂ�`��
	//m_area_box[next_scene].Draw(255, 255);

	//=============================================
	// ���Ń^�C�g����`��
	//=============================================
	// �t�H���g�̃f�t�H���g�T�C�Y�̕ۑ�
	int default_font_size = GetFontSize();
	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(80);
	const char* name = "�����X�^�[�N���b�V��" /*:: RENTER*/;
	// �`�敝�̎擾
	float w = GetDrawStringWidth(name, -1);
	// ������̍����̎擾
	float h = GetFontSize();
	// �`����W
	Vector2 draw_pos = { SCREEN_W / 2 - w / 2, 0 };
	DrawString(draw_pos.x, draw_pos.y, name, GetColor(255, 128, 50));


	name = "Push : W";
	w = GetDrawStringWidth(name, -1);
	h = GetFontSize();
	draw_pos = { SCREEN_W / 2 - w / 2, SCREEN_H - h };
	DrawString(draw_pos.x, draw_pos.y, name, GetColor(255, 128, 50));


	// �t�H���g�̃T�C�Y���f�t�H���g�T�C�Y�ɖ߂�
	SetFontSize(default_font_size);
	
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
}

//------------------------------------------
// �t�B�[���h�Ƃ̓����蔻��
//------------------------------------------
void TitleScene::HitField()
{

	// �t�B�[���h�̒n�ʃ��f���ƃL�����N�^�[�̓����蔻��
	HitGroundCharacter(&player->m_transform.pos, &field.m_field_model);

	// �؂̃I�u�W�F�N�g�ƃv���C���[�̓����蔻��
	// �Ȃ����Q�{���������蔻�肪�ǂ����Ȃ�
	for (int i = 0; i < field.TREE_MAX; i++)
	{
		// �����X�^�[�ƃv���C���[�̈ړ��̓����蔻��
		if (CheckCapsuleHit(field.m_hit_tree[i], player->m_body))
		{
			player->m_move.Move_Hit_Capsule(&player->m_transform.pos, player->m_body.m_capsule.radius, &field.m_hit_tree[i]);
		}
	}

	// �v���C���[�ƃt�B�[���h���͂��Ă�l�p�Ƃ̓����蔻��
	for (int i = 0; i < field.AROUND_MAX; i++)
	{
		if (CheckBoxHit3D(player->m_transform.pos, player->m_move_hit_size,
			field.m_hit_around[i].m_box.hit_pos, field.m_hit_around[i].m_box.half_size))
		{
			player->MoveHitUpdate(&field.m_hit_around[i]);
		}
	}
}

//------------------------------------------
// �I�v�V�������j���[�ł�����Ă����l�𔽉f����֐�
//------------------------------------------
void TitleScene::OptionValuesReflect(int bgm, int se, int mouse)
{
	// �J�����̊��x�ݒ�
	camera.SetCameraSensi(mouse);

}

//------------------------------------------
// �G���ABOX�̏����ݒ�
//------------------------------------------
void TitleScene::SetAeraBoxSet()
{
	// �T�C�Y�̐ݒ�
	m_box_size.set(300.0f, 80.0f, 100.0f);


	// ���W�̐ݒ�
	m_box_pos[next_scene].set(0.0f, 0.0f, 150);


	// BOX�̍쐬
	m_area_box[next_scene].CreateBox(m_box_pos[next_scene], m_box_size);
}
