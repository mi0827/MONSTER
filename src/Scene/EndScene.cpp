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
//#include "src/Field/TitleField.h"
#include "src/Field/Field.h"


#include "src/Sound/BGM.h"
#include "src/Sound/SE.h"

#include "src/Camera.h"

#include "Base/Scene_Base.h"
#include "EndScene.h"


//------------------------------------------
// �R���X�g���N�^
//------------------------------------------
EndScene::EndScene()
{
}

//------------------------------------------
// �f�X�g���N�^
//------------------------------------------
EndScene::~EndScene()
{
}

//------------------------------------------
// ��������
//------------------------------------------
void EndScene::Init()
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

	// ���݂̃V�[���̐ݒ�(�G���h�V�[��)
	m_now_scene = End;
}


//------------------------------------------
// �X�V����
//------------------------------------------
void EndScene::Update()
{

	// �v���C���[�̍X�V����
	player->Update(&camera.m_rot);
	

	// �J�����̍X�V����
	camera.Update(&player->m_transform.pos);


	// �G���^�[�������ꂽ���ɃV�[���̕ύX������i�������̉��j
	if (PushHitKey(KEY_INPUT_RETURN))
	{
		// ���ɍs���Ăق����V�[���̐ݒ������
		SetNextScene(Title);
		// ���̃V�[���Ɉړ����邽�߂̃t���O�𗧂Ă�
		m_scene_change_judge = true;
	}
	else
	{
		m_scene_change_judge = false;
	}

	// �G���^�[�������ꂽ���ɃV�[���̕ύX������i�������̉��j
	if (PushHitKey(KEY_INPUT_RETURN)&& CheckHitKey(KEY_INPUT_LSHIFT))
	{
		// ���ɍs���Ăق����V�[���̐ݒ������
		SetNextScene(QuestArea);
		// ���̃V�[���Ɉړ����邽�߂̃t���O�𗧂Ă�
		m_scene_change_judge = true;
	}
	else
	{
		m_scene_change_judge = false;
	}


	// �t�B�[���h�ƃL�����N�^�[�̂���������
	HitField();

}

//------------------------------------------
// �`�揈��
//------------------------------------------
void EndScene::Draw()
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

	
	// �t�H���g�̃f�t�H���g�T�C�Y�̕ۑ�
	int default_font_size = GetFontSize();
	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(80);
	const char* name = "END :: RETURN";
	// �`�敝�̎擾
	float w = GetDrawStringWidth(name, -1);
	// ������̍����̎擾
	float h = GetFontSize();
	// �`����W
	Vector2 draw_pos = { SCREEN_W / 2 - w / 2, 0 };
	DrawString(draw_pos.x, draw_pos.y, name, GetColor(255, 128, 50));


	// �t�H���g�̃T�C�Y���f�t�H���g�T�C�Y�ɖ߂�
	SetFontSize(default_font_size);
	
	

}

//------------------------------------------
// �I������
//------------------------------------------
void EndScene::Exit()
{
	//�@�V���h�[�}�b�v�̍폜
	ExitShadowMap();
	// �v���C���[�N���X�̓|�C���^�Ȃ̂ōŌ�ɊJ������
	delete player;
}

//------------------------------------------
// �t�B�[���h�ƃL�����N�^�[�̓����蔻��
//------------------------------------------
void EndScene::HitField()
{
	// �t�B�[���h�̒n�ʃ��f���ƃL�����N�^�[�̓����蔻��
	HitGroundCharacter(&player->m_transform.pos, &field.m_field_model);

	// �؂̃I�u�W�F�N�g�ƃv���C���[�̓����蔻��
	for (int i = 0; i < field.TREE_MAX; i++)
	{
		// �����X�^�[�ƃv���C���[�̈ړ��̓����蔻��
		if (CheckCapsuleHit(field.m_hit_tree[i], player->m_body))
		{
			player->m_move.Move_Hit_Capsule(&player->m_transform.pos, player->m_body.m_capsule.radius, &field.m_hit_tree[i]);
		}
	}

	// �t�F���X�ƃL�����N�^�[�̓����蔻��
	for (int i = 0; i < field.FENCE_MAX; i++)
	{
		if (CheckBoxHit3D(player->m_transform.pos, player->m_move_hit_size,
			field.m_hit_fence[i].m_box.hit_pos, field.m_hit_fence[i].m_box.half_size))
		{
			player->MoveHitUpdate(&field.m_hit_fence[i]);
		}
	}


	// �΂ƃL�����N�^�[�̓����蔻��
	for (int i = 0; i < field.STONE_MAX; i++)
	{
		if (CheckBoxHit3D(player->m_transform.pos, player->m_move_hit_size,
			field.m_hit_stone[i].m_box.hit_pos, field.m_hit_stone[i].m_box.half_size))
		{
			player->MoveHitUpdate(&field.m_hit_stone[i]);
		}
	}
}

