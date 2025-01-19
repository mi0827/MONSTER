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
#include "src/Character/Receptionist.h"

#include "src/Field/FieldBase.h"
#include "src/Field/HitField.h" 
#include "src/Field/TitleField.h"
#include "src/Field/Field.h"

#include "src/Camera.h"
#include "src/System/Text.h"
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

	delete[] m_landmark_text;
}

//------------------------------------------
// ��������
//------------------------------------------
void QuestAreaScene::Init()
{
	// �x�[�X�N���X�ŏ��������Ă����������̂̏�����
	BaseInit();

	// �t�B�[���h�̏�����
	m_field_1.Init();

	// �J�����̏����ݒ�
	camera.PlayFieldInit();

	PlayerInit(hero);
	// �v���C���[�̏����ݒ� 
	m_player->Init();
	// �v���C���[�̍��W�̐ݒ�
	m_player->SetCharacterPos({ 0.0f, 0.0f,250.0f });
	// �v���C���[�̌����̐ݒ�
	m_player->SetCharacterRot({ 0.0f,-180.0f,0.0f });

	// �J�����̌����̐ݒ�
	camera.SetCameraRot(m_player->m_transform.rot);

	// ��t��̏����ݒ�
	receptionist.Init();
	// ��t��Ƙb����G���A�̐ݒ�
	InitArea();
	// �V���h�[�}�b�v�̐ݒ�
	ShadowMapInit();
	// ���݂̃V�[���̐ݒ�(�N�G�X�g�󒍃V�[��)
	m_now_scene = QuestArea;

	// �e�L�X�g�̓ǂݍ���
	m_quest_text.LoadText("Data/Text/Quest.txt", quest_max);
	m_quest_area_text.LoadText("Data/Text/QuestAreaStory.txt", story_max);
	m_reception_text.LoadText("Data/Text/QuestReception.txt", teception_max);
}


//------------------------------------------
// �X�V����
//------------------------------------------
void QuestAreaScene::Update()
{
	switch (m_turn)
	{
	case Main:
		// �J�����̍X�V����
		camera.MouseCamera(&m_player->m_transform.pos);
		// ���C���ōs�����������̃V�[���̏�Ԃɍ��킹�ď����𕪂����s����֐�
		QuestAreaUpdate();

		break;
	case FadeOut:
		// �t�F�[�h�A�E�g�̏���
		FadeOutSceneChange(Battle);
		break;
	}
}

//------------------------------------------
// �`�揈��
//------------------------------------------
void QuestAreaScene::Draw()
{
	// �V���h�[�}�b�v�̃G���A�̃Z�b�g
	SetShadowMapArea(m_shadowMap_handle_1, m_player->m_transform.pos);
	SetShadowMapArea(m_shadowMap_handle_2, receptionist.m_transform.pos);
	//-------------------------------------------------------------
		// �V���h�E�}�b�v�̍쐬�i�����Ŋe�I�u�W�F�N�g�̃V���h�[�}�b�v�̐ݒ�j
		//-------------------------------------------------------------
		// �V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(m_shadowMap_handle_1);
	{
		// �v���C���[�̕`�揈��
		m_player->Draw();
	}
	ShadowMap_DrawSetup(m_shadowMap_handle_2);
	{
		receptionist.Draw();
	}
	ShadowMap_DrawSetup(m_shadowMap_handle);
	{
		// �t�B�[���h�̕`��
		m_field_1.Draw();
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
	// ��̕`��
	SkyDraw();

	// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
	SetUseShadowMap(1, m_shadowMap_handle_1);
	{
		m_player->Draw();
		// ��t��̕`��
		receptionist.Draw();
	}
	SetUseShadowMap(2, m_shadowMap_handle_2);
	{
		receptionist.Draw();
	}
	SetUseShadowMap(0, m_shadowMap_handle);
	{
		// �v���C���[�̕`�揈��
		m_player->Draw();

		// ��t��̕`��
		receptionist.Draw();
		// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
		m_field_1.Draw();

	}
	UseShadowMapSet();



	switch (secen_mode_num)
	{
	case normal:// ��b���Ă��Ȃ����
		ModeNormalDraw();
		break;
	case convo: // ��b��
		ConvoDraw();
		break;
	case accepting_quest: // �N�G�X�g���󂯂Ă�����
		AcceptingQuestDraw();
		break;
	}
	// �t�F�[�h�̕`�揈��
	FadeDraw();
}

//------------------------------------------
// �I������
//------------------------------------------
void QuestAreaScene::Exit()
{
	//�@�V���h�[�}�b�v�̍폜
	ExitShadowMap();

	// �v���C���[�̏I������
	m_player->Exit();
}

//------------------------------------------
// �t�B�[���h�ƃL�����N�^�[�̓����蔻��
//------------------------------------------
void QuestAreaScene::HitField()
{

	// �t�B�[���h�̒n�ʃ��f���ƃv���C���[�̓����蔻��
	HitGroundCharacter(&m_player->m_transform.pos, &m_field_1.m_field_model);
	// ��t��
	HitGroundCharacter(&receptionist.m_transform.pos, &m_field_1.m_field_model);


	// �؂̃I�u�W�F�N�g�ƃv���C���[�̓����蔻��
	// �Ȃ����Q�{���������蔻�肪�ǂ����Ȃ�
	for (int i = 0; i < m_field_1.TREE_MAX; i++)
	{
		// �����X�^�[�ƃv���C���[�̈ړ��̓����蔻��
		if (CheckCapsuleHit(m_field_1.m_hit_tree[i], m_player->m_body))
		{
			m_player->m_move.Move_Hit_Capsule(&m_player->m_transform.pos, m_player->m_body.m_capsule.radius, &m_field_1.m_hit_tree[i]);
		}
	}

	// �v���C���[�ƃt�B�[���h���͂��Ă�l�p�Ƃ̓����蔻��
	for (int i = 0; i < m_field_1.AROUND_MAX; i++)
	{
		if (CheckBoxHit3D(m_player->m_transform.pos, m_player->m_move_hit_size,
			m_field_1.m_hit_around[i].m_box.hit_pos, m_field_1.m_hit_around[i].m_box.half_size))
		{
			m_player->MoveHitUpdate(&m_field_1.m_hit_around[i]);
		}
	}

}

//------------------------------------------
// �I�v�V�������j���[�ł�����Ă����l�𔽉f����֐�
//------------------------------------------
void QuestAreaScene::OptionValuesReflect(int bgm, int se, int mouse)
{
	// �J�����̊��x�ݒ�
	camera.SetCameraSensi(mouse);
	// �L�����N�^�[�̃T�E���h�̒���
	m_player->m_se.SetSoundVolume(se);
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

//------------------------------------------
// �b����悤�ɂȂ�G���A�̐ݒ�
//------------------------------------------
void QuestAreaScene::LandMarkUpdate()
{
	// �J�����̌������擾����
	m_camera_rot = camera.GetCameraRot();

	// ������̕`��̂��߂̐ݒ�
	for (int i = 0; i < text_max; i++)
	{
		// ���W�ϊ�
		VECTOR pos = DrawStringWrold(receptionist.m_transform.pos, m_landmark_text[i].shift_pos);
		// �`����p�ɕϊ�
		m_landmark_text[i].draw_pos.VSet(pos);

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
					m_landmark_text[i].draw_flag = true;
				}
				else // ��ʂ���
				{
					// �`�悵�Ȃ�
					m_landmark_text[i].draw_flag = false;
				}
			}
			else // �͈͂����ł��`��ł��Ȃ�
			{
				m_landmark_text[i].draw_flag = false;
			}
		}
		else // �w��̃e�L�X�g�ȊO��
		{
			// �J�����̉�p���ғ����ɂ���ĕ`�悵�Ȃ�
			if (pos.z > 0.0f && pos.z < 1.0f)
			{
				// �`�悷��
				m_landmark_text[i].draw_flag = true;
			}
			else
			{
				// �`�悵�Ȃ�
				m_landmark_text[i].draw_flag = false;
			}
		}
	}
}

//------------------------------------------
// ���̃V�[���̏�Ԃɍ��킹�ēK�؂ȏ�����������֐�
//------------------------------------------
void QuestAreaScene::QuestAreaUpdate()
{
	switch (secen_mode_num)
	{
	case normal:// ��b���Ă��Ȃ����
		ModeNormalUpdate();
		break;
	case convo: // ��b��
		ConvoUpdate();

		break;
	case accepting_quest: // �N�G�X�g���󂯂Ă�����
		AcceptingQuestUpdate();
		break;
	}
}

//------------------------------------------
// ��b���Ă��Ȃ���Ԃ̍X�V����
//------------------------------------------
void QuestAreaScene::ModeNormalUpdate()
{
	// �J�����̌������擾����
	m_camera_rot = camera.GetCameraRot();

	// �v���C���[�̍X�V����
	m_player->Update(&m_camera_rot);

	// ��t��̂̍X�V����
	receptionist.Update();

	// ��t��ƃv���C���[�̈ړ��̓����蔻��
	if (CheckCapsuleHit(receptionist.m_hit_body, m_player->m_body))
	{
		m_player->m_move.Move_Hit_Capsule(&m_player->m_transform.pos, m_player->m_body.m_capsule.radius, &receptionist.m_hit_body);
	}
	// �t�B�[���h�ƃL�����N�^�[�̓����蔻��
	HitField();
	// �ڈ���ʂ����̏���
	LandMarkUpdate();
	// �v���C���[����t��Ƙb����͈͂ɓ��������̊m�F
	if (CheckCapsuleHit(m_area, m_player->m_body))
	{
		// X�L�[�������ꂽ���ɃV�[���̕ύX������i�������̉��j
		if (PushHitKey(KEY_INPUT_F))
		{
			// ���̃V�[���̏�Ԃ���b�p�[�g�Ɉړ�����
			secen_mode_num = convo;
			// �e�L�X�g�̍s�����Z�b�g����
			m_text_line_num = 0;
		}
		// �b����G���A�ɓ���������t���O���グ��
		m_area_hit = true;
	}
	else
	{
		// �͈͊O�ɂ���Ƃ��̓t���O��������
		m_area_hit = false;
	}
}

//------------------------------------------
// ��b�p�[�g�̍X�V����
//------------------------------------------
void QuestAreaScene::ConvoUpdate()
{
	// �}�E�X�̉E�N���b�N���X�y�[�X�L�[�ŉ�b��i�߂�
	if (PushMouseInput(MOUSE_INPUT_LEFT)|| PushHitKey(KEY_INPUT_SPACE))
	{
		m_text_line_num++;
	}
	// �e�L�X�g����s�i�񂾂�
	if (m_text_line_num == 1)
	{
		// �N�G�X�g���[�h�Ɉڍs����
		secen_mode_num = accepting_quest;
		m_text_line_num = 0;
	}

	//if (? ? ? )
	{
		// ���̃V�[���̏�Ԃ��N�G�X�g�󒍂Ɉړ�����
		//secen_mode_num = accepting_quest;
	}
}

//------------------------------------------
// �N�G�X�g���󂯂Ă���Ƃ��̍X�V����
//------------------------------------------
void QuestAreaScene::AcceptingQuestUpdate()
{

	if (PushMouseInput(MOUSE_INPUT_LEFT) || PushHitKey(KEY_INPUT_SPACE))
	{
		m_text_line_num++;
	}

	//if (? ? ? )
	{
		// ���̃V�[���̏�Ԃ��ŏ��̏�Ԃ��Ă���
		//secen_mode_num = normal;
	}
}

//------------------------------------------
// ��b���Ă��Ȃ���Ԃ̕`�揈��
//------------------------------------------
void QuestAreaScene::ModeNormalDraw()
{
	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(FONT_SIZE);

	// ������̍����̎擾
	float h = GetFontSize();
	// �ڈ�̕`��
	for (int i = 0; i < landmark_text_max; i++)
	{
		if (m_landmark_text[i].draw_flag)
		{
			// �`�敝�̎擾
			float w = GetDrawStringWidth(m_landmark_text[i].text, -1);
			// �`����W
			m_landmark_draw_pos = { m_landmark_text[i].draw_pos.x - w / 2,  m_landmark_text[i].draw_pos.y - h };
			// ������̕`��
			DrawString(m_landmark_draw_pos.x, m_landmark_draw_pos.y, m_landmark_text[i].text, GetColor(255, 128, 50));
		}
	}
	// �v���C���[�̃e�L�X�g�̕`��
	SetFontSize(TEXT_FONT_SIZE);
	h = GetFontSize();
	m_text_draw_pos.set((SCREEN_W / 2 - m_quest_area_text.TITLE_BACK_HALF_SIZE), (SCREEN_H - (h * 2 + m_quest_area_text.CREVICE_SIZE)));
	m_quest_area_text.TextDraw(m_text_line_num, { m_text_draw_pos.x, (m_text_draw_pos.y + h) }, m_quest_area_text.TITLE_BACK_SIZE);
	DrawString(m_text_draw_pos.x, m_text_draw_pos.y, "Player", GetColor(255, 128, 50));
}

//------------------------------------------
// ��b�p�[�g�̕`�揈��
//------------------------------------------
void QuestAreaScene::ConvoDraw()
{
	// ������̍����̎擾
	float h = GetFontSize();

	h = GetFontSize();
	m_text_draw_pos.set((SCREEN_W / 2 - m_reception_text.QUEST_BACK_HALF_SIZE), (SCREEN_H - (h * 2 + m_reception_text.CREVICE_SIZE)));
	m_reception_text.TextDraw(m_text_line_num, { m_text_draw_pos.x, (m_text_draw_pos.y + h) }, m_reception_text.QUEST_BACK_SIZE);


}

//------------------------------------------
// �N�G�X�g���󂯂Ă���Ƃ��̕`�揈��
//------------------------------------------
void QuestAreaScene::AcceptingQuestDraw()
{
	// ������̍����̎擾
	float h = GetFontSize();

	h = GetFontSize();
	m_text_draw_pos.set((SCREEN_W / 2 - m_quest_text.QUEST_BACK_HALF_SIZE), (SCREEN_H - (h * 2 + m_quest_text.CREVICE_SIZE)));
	m_quest_text.TextDraw(m_text_line_num, { m_text_draw_pos.x, (m_text_draw_pos.y + h) }, m_quest_text.QUEST_BACK_SIZE);

}


