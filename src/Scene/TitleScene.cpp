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

	// �V���h�[�}�b�v�̐ݒ�
	ShadowMapInit();

}

//------------------------------------------
// �X�V����
//------------------------------------------
void TitleScene::Update()
{

	if(CheckHitKey(KEY_INPUT_W))
		{ }
	// �v���C���[�̍X�V����
	player->Update(&camera.m_rot);
	// �t�B�[���h�̒n�ʃ��f���ƃL�����N�^�[�̓����蔻��
	HitGroundCharacter(&player->m_transform.pos, &field.m_field_model);

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

		// �q�[���[�̕`�揈��
		//hero.Draw();
	}
	ShadowMap_DrawSetup(m_shadowMap_handle);
	{
		// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
		//MV1SetPosition(ground, VGet(0.0f, 0.0f, 0.0f)); // �`�悷��v���C���[���f���̍��W�̐ݒ�
		//MV1SetRotationXYZ(ground, VGet(TO_RADIAN(0.0f), TO_RADIAN(0.0f), TO_RADIAN(0.0f))); // ���f���̉�]
		//MV1SetScale(ground, VGet(10, 10, 10)); // ���f���̑傫��(10���̂P�̃T�C�Y)
		//MV1DrawModel(ground); // ���f���̕`��
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

	DrawString(100, 100, "�^�C�g�� :: RENTER", GetColor(255, 255, 255));

}

//------------------------------------------
// �I������
//------------------------------------------
void TitleScene::Exit()
{
	
	//�@�V���h�[�}�b�v�̍폜
	ExitShadowMap();
}
