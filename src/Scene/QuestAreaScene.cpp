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
// �R���X�g���N�^
//------------------------------------------
QuestAreaScene::QuestAreaScene()
{
}

//------------------------------------------
// �f�X�g���N�^
//------------------------------------------
QuestAreaScene::~QuestAreaScene()
{

	delete[] m_text;
}

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
	// �v���C���[�̍��W�̐ݒ�
	player->SetCharacterPos({ 0.0f, 0.0f,250.0f });
	// �v���C���[�̌����̐ݒ�
	player->SetCharacterRot({ 0.0f,-180.0f,0.0f });

	// ��t��̏����ݒ�
	receptionist.Init();
	// ��t��Ƙb����G���A�̐ݒ�
	InitArea();
	// �V���h�[�}�b�v�̐ݒ�
	ShadowMapInit();
	// ���݂̃V�[���̐ݒ�(�N�G�X�g�󒍃V�[��)
	m_now_scene = QuestArea;

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

	// ��t��ƃv���C���[�̈ړ��̓����蔻��
	if (CheckCapsuleHit(receptionist.m_hit_body, player->m_body))
	{
		player->m_move.Move_Hit_Capsule(&player->m_transform.pos, player->m_body.m_capsule.radius, &receptionist.m_hit_body);
	}
	// �t�B�[���h�ƃL�����N�^�[�̓����蔻��
	HitField();


	// �v���C���[����t��Ƙb����͈͂ɓ��������̊m�F
	if (CheckCapsuleHit(m_area, player->m_body))
	{
		// X�L�[�������ꂽ���ɃV�[���̕ύX������i�������̉��j
		if (PushHitKey(KEY_INPUT_F))
		{
			// ���ɍs���Ăق����V�[���Ɉړ�(�o�g���V�[��)
			SetNextScene(Battle);
			m_scene_change_judge = true;
		}
		// �b����G���A�ɓ���������t���O���グ��
		m_area_hit = true;
	}
	else
	{
		// �͈͊O�ɂ���Ƃ��̓t���O��������
		m_area_hit = false;
	}

	// �J�����̍X�V����
	camera.Update(&player->m_transform.pos);

	// ������̕`��̂��߂̐ݒ�
	for (int i = 0; i < text_max; i++)
	{
		// ���W�ϊ�
		VECTOR pos = DrawStringWrold(receptionist.m_transform.pos, m_text[i].shift_pos);
		// �`����p�ɕϊ�
		m_text[i].draw_pos.VSet(pos);

		// �ϊ������X�N���[�����W��Z�̒l��0.0 ~ 1.0 �Ȃ�`�悵�Ă���
		if (i == f_text)
		{
			// �`�悵����������F : �b���̏ꍇ
			// �b���Ă����G���A�ɓ����Ă��Ȃ��ƕ`��ł��Ȃ��悤�ɂ���
			if (m_area_hit)
			{
				// �J�����̉�p���ғ����ɂ���ĕ`�悵�Ȃ�
				// ��p��
				if (pos.z > 0.0f && pos.z < 1.0f)
				{
					// �`�悷��
					m_text[i].draw_flag = true;
				}
				else // ��ʂ���
				{
					// �`�悵�Ȃ�
					m_text[i].draw_flag = false;
				}
			}
			else // �͈͂����ł��`��ł��Ȃ�
			{
				m_text[i].draw_flag = false;
			}
		
		}
		else // �w��̃e�L�X�g�ȊO��
		{
			// �J�����̉�p���ғ����ɂ���ĕ`�悵�Ȃ�
			if (pos.z > 0.0f && pos.z < 1.0f)
			{
				// �`�悷��
				m_text[i].draw_flag = true;
			}
			else
			{
				// �`�悵�Ȃ�
				m_text[i].draw_flag = false;
			}

		}

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


	// �G���A��`��i����ŏ����j
	// m_area.Draw();


	// ���̃t�H���g�̕`��
	// ��ŕύX�\��
	// �t�H���g�̃f�t�H���g�T�C�Y�̕ۑ�
	int default_font_size = GetFontSize();

	for (int i = 0; i < text_max; i++)
	{
		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(m_text[i].font_size);
		if (m_text[i].draw_flag)
		{
			// �`�敝�̎擾
			float w = GetDrawStringWidth(m_text[i].text, -1);
			// ������̍����̎擾
			float h = GetFontSize();
			// �`����W
			Vector2 draw_pos = { m_text[i].draw_pos.x - w / 2,  m_text[i].draw_pos.y - h };
			// ������̕`��
			DrawString(draw_pos.x, draw_pos.y, m_text[i].text, GetColor(255, 128, 50));

		}

	}


	// �t�H���g�̃T�C�Y���f�t�H���g�T�C�Y�ɖ߂�
	SetFontSize(default_font_size);



}

//------------------------------------------
// �I������
//------------------------------------------
void QuestAreaScene::Exit()
{
	//�@�V���h�[�}�b�v�̍폜
	ExitShadowMap();

}

//------------------------------------------
// �t�B�[���h�ƃL�����N�^�[�̓����蔻��
//------------------------------------------
void QuestAreaScene::HitField()
{

	// �t�B�[���h�̒n�ʃ��f���ƃv���C���[�̓����蔻��
	HitGroundCharacter(&player->m_transform.pos, &field.m_field_model);
	// ��t��
	HitGroundCharacter(&receptionist.m_transform.pos, &field.m_field_model);


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
// �b����悤�ɂȂ�G���A�̐ݒ�
//------------------------------------------
void QuestAreaScene::InitArea()
{
	// �J�v�Z�����W�͎�t��Ɠ������W�ɂ���
	Vector3 pos = receptionist.m_transform.pos;
	Vector3 pos2 = { 0.0f, 60.0f, 0.0f };
	// ���a�̐ݒ�
	float r = AREA_FIELD_R;
	// �J�v�Z���̍쐬
	m_area.CreateCapsule(pos, pos2, r);
}
