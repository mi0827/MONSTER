#include "src/WinMain.h"
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
#include "src/Character/Receptionist.h"

#include "src/Field/FieldBase.h"
#include "src/Field/HitField.h" 
#include "src/Field/TitleField.h"


#include "src/Sound/BGM.h"
#include "src/Sound/SE.h"

#include "src/Camera.h"

#include "Base/Scene_Base.h"
#include "QuestAreaScene.h"



//------------------------------------------
// ��������
//------------------------------------------
void QuestAreaScene::Init()
{
	// �t�B�[���h�̏�����
	field.Init();


	// �J�����̏����ݒ�
	camera.PlayField_Init();

	// �v���C���[�̐ݒ�
	player = new SamplePlayer;

	// �v���C���[�̏����ݒ� 
	player->Init();

	// ��t��̏����ݒ�
	receptionist.Init();

	// �V���h�[�}�b�v�̐ݒ�
	ShadowMapInit();
}


//------------------------------------------
// �X�V����
//------------------------------------------
void QuestAreaScene::Update()
{

	// �v���C���[�̍X�V����
	player->Update(&camera.m_rot);
	// ��t��̂̍X�V����
	receptionist.Update();

	// �t�B�[���h�̒n�ʃ��f���ƃv���C���[�̓����蔻��
	HitGroundCharacter(&player->m_transform.pos, &field.m_field_model);
	// ��t��
	HitGroundCharacter(&receptionist.m_transform.pos, &field.m_field_model);



	// �J�����̍X�V����
	camera.Update(&player->m_transform.pos);


	// X�L�[�������ꂽ���ɃV�[���̕ύX������i�������̉��j
	if (PushHitKey(KEY_INPUT_RETURN))
	{
		m_scene_change_judge = true;
	}
	else
	{
		m_scene_change_judge = false;
	}

}

//------------------------------------------
// �`�揈��
//------------------------------------------
void QuestAreaScene::Draw()
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

		// �q�[���[�̕`�揈��
		//hero.Draw();
	}
	ShadowMap_DrawSetup(m_shadowMap_handle);
	{
		// ��t��̕`��
		receptionist.Draw();

		// �t�B�[���h�̕`��
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

		// ��t��̕`��
		receptionist.Draw();
		// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
		field.Draw();

	}
	UseShadowMapSet();

	

	//// ���̃t�H���g�̕`��
	//// ��ŕύX�\��
	//// �t�H���g�̃f�t�H���g�T�C�Y�̕ۑ�
	//int default_font_size = GetFontSize();
	//// �t�H���g�T�C�Y�̐ݒ�
	//SetFontSize(80);
	//const char* name = "�G�X�g�G���A :: RENTER";
	//// �`�敝�̎擾
	//float w = GetDrawStringWidth(name, -1);
	//// ������̍����̎擾
	//float h = GetFontSize();
	//// �`����W
	//Vector2 draw_pos = { SCREEN_W / 2 - w / 2, 0 };
	//DrawString(draw_pos.x, draw_pos.y, name, GetColor(255, 128, 50));

	//// �t�H���g�̃T�C�Y���f�t�H���g�T�C�Y�ɖ߂�
	//SetFontSize(default_font_size);


	
}

//------------------------------------------
// �I������
//------------------------------------------
void QuestAreaScene::Exit()
{
	//�@�V���h�[�}�b�v�̍폜
	ExitShadowMap();

}
