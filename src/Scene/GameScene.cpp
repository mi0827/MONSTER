#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"

#include "src/Action/Combo.h"
#include "src/System/Transform.h"
#include "src/System/InputPad.h"

#include "src/System/Spotlight.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"
#include "src/Effect/Effect.h"

#include "src/Collision/BoxCollision.h"
#include "src/Collision/CapsuleCollision.h"
#include "src/Hit/Hit.h"
#include "src/Hit/HitStop.h"

#include "src/System/UIBar.h"

#include "src/System/Move.h"
#include "src/System/TargetMove.h"
#include "src/Character/CharacterBase.h"
#include "src/Character/MonsterBase.h"
#include "src/Character/SamplePlayer.h"
#include "src/Character/Hero.h"
#include "src/Character/Monster.h"
#include "src/Character/Mutant.h"

#include "src/Field/FieldBase.h"
#include "src/Field/Field.h"
#include "src/Field/HitField.h" 

#include "src/System/DamageAction.h"
#include "src/Action/Attack.h"

#include "src/Camera.h"



#include "src/Scene/Base/Scene_Base.h"
#include "src/Scene/GameScene.h"


//---------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------
GameScene::GameScene()
{
}

//---------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------
GameScene::~GameScene()
{
}

//---------------------------------------------------------------------------
// �L�����N�^�[�̐ݒ�
//---------------------------------------------------------------------------
void GameScene::GameSceneInit()
{
	// �L�����N�^�[�̐ݒ�
	if (m_player_num == SAMPLEPLAYER)
	{
		player = new SamplePlayer;
	}
	if (m_monster_num == MUTANT)
	{
		monster = new Mutant;
	}
	/*if (m_monster_num == MONSTER)
	{
		monster = new Monster;
	}*/

}


//---------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------
void GameScene::Init()
{

	GameSceneInit();

	// �J�����̏����ݒ�
	camera.PlayField_Init();

	// �L�����N�^�[�̏�������
	Character_Init();

	// �t�B�[���h�̏����� 
	field.Init();

	// �V���h�[�}�b�v�̐ݒ�
	ShadowMapInit();
	// ���݂̃V�[���̐ݒ�(�o�g���V�[��)
	m_now_scene = Battle;

	// �J�����̐ݒ�
	camera.SetCamera(camera.CAMERA_HEIGHT_MONSTER, camera.CAMERA_LENGTH);
}

//---------------------------------------------------------------------------
// �X�V����
//---------------------------------------------------------------------------
void GameScene::Update()
{

	// �t�B�[���h�Ƃ̓����蔻��
	// ��U�����蔻���؂��Ă���
	HitField();

	// �Q�[���V�[���̒��łǂ̏�ʂ��ɂ���ď�����ς���
	switch (m_what_scene)
	{
	case entry:
		EntryUpdate();
		break;
	case battle: // �o�g���V�[��
		GameUpdate();
		break;
	case power_up: // �����X�^�[�̃p���[�A�b�v���o
		break;
	case result: // �o�g���V�[���̌�
		EndUpdate();
		break;

	}


	// X�L�[�������ꂽ���ɃV�[���̕ύX������i�������̉��j
	if (PushHitKey(KEY_INPUT_RETURN))
	{
		// ���ɍs���Ăق����V�[���̐ݒ������
		SetNextScene(End);

		m_scene_change_judge = true;
	}

}

//---------------------------------------------------------------------------
// �����X�^�[�̓o�ꉉ�o
//---------------------------------------------------------------------------
void GameScene::EntryUpdate()
{
	// �J�����̍X�V����
	camera.MoveCamera(&monster->m_transform.pos, CAMERA_DIRECTIN_FLET, CAMERA_ROT_SPEED);
	monster->EntryUpdate();

	// �t���[���̃J�E���g�𑝂₷
	m_count_flame++;
	// �t���[�����w��̒l�܂ő�������
	if (m_count_flame >= ONE_SECOND_FLAME)
	{
		// �^�C�}�[��i�߂�
		m_count_time++;
		// �J�E���g�����Z�b�g
		m_count_flame = 0;
	}
	// �^�C�}�[����莞�Ԃ�������(�T�b)
	if (m_count_time > CHANGE_TIME)
	{
		// �o�g�����X�^�[�Ƃ���
		m_what_scene = battle;
	}


}

//---------------------------------------------------------------------------
// �o�g���V�[���ł̏���
//---------------------------------------------------------------------------
void GameScene::GameUpdate()
{
	// �q�b�g�X�g�b�v���N�����Ăق����Ƃ�������
	if (hit_stop.Hit_Stop() == false)
	{
		// �L�����N�^�[�̍X�V����
		CharacterUpdate();
	}

	// �J�����̍X�V����
	camera.TargetCamera(&player->m_transform, &monster->m_transform.pos);
	// �v���C���[��HP���O�ɂȂ�����
	if (player->m_hp_value <= 0)
	{
		// �v���C���[�̎��S��m�点��
		m_who_died = player_die;
		// �o�g�����I����������m�点��
		m_what_scene = result;
	}
	// �����X�^�[��HP���[���ɂȂ�����
	if (monster->m_hp_value <= 0)
	{
		// �����X�^�[�̎��S��m�点��
		m_who_died = monster_die;
		// �o�g�����I����������m�点��
		m_what_scene = result;
	}
}

//---------------------------------------------------------------------------
// �o�g�����I������Ƃ��̏���
//---------------------------------------------------------------------------
void GameScene::EndUpdate()
{
	// �t���[���̃J�E���g�𑝂₷
	m_count_flame++;
	// �t���[�����w��̒l�܂ő�������
	if (m_count_flame >= ONE_SECOND_FLAME)
	{
		// �^�C�}�[��i�߂�
		m_count_time++;
		// �J�E���g�����Z�b�g
		m_count_flame = 0;
	}
	// �^�C�}�[����莞�Ԃ�������(�T�b)
	if (m_count_time > CHANGE_TIME)
	{
		// ���ɍs���Ăق����V�[���̐ݒ������
		SetNextScene(End);
		// ���̃V�[���Ɉړ����邽�߂̃t���O�𗧂Ă�
		m_scene_change_judge = true;
	}
	// �ǂ���̃����X�^�[�����񂾂��ɂ���ď�����ς���
	switch (m_who_died)
	{

	case player_die: // �v���C���[�����񂾂Ƃ�
		// �v���C���[�𒆐S��
		// �E��]
		camera.MoveCamera(&player->m_transform.pos, CAMERA_DIRECTIN_RIGHT, CAMERA_ROT_SPEED);
		break;

	case monster_die: // �����X�^�[�����񂾂Ƃ�
	    // �����X�^�[�𒆐S��
		// ����]
		camera.MoveCamera(&monster->m_transform.pos, CAMERA_DIRECTIN_FLET, CAMERA_ROT_SPEED);
		break;

	}

}

//---------------------------------------------------------------------------
// �`�揈��
//---------------------------------------------------------------------------
void GameScene::Draw()
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
		// �����X�^�[�̕`��
		monster->Draw();
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
		// �����X�^�[�̕`��
		monster->Draw();
	}
	UseShadowMapSet();

	// �X�e�[�^�X�o�[�̕`��
	StatusDraw();

	// ���U���g�̎������`�悷��
	if (m_what_scene == result)
	{
		// �o�g����̃��b�Z�[�W�̕`��
		VDMessage();
	}
	

}

//---------------------------------------------------------------------------
// �I������
//---------------------------------------------------------------------------
void GameScene::Exit()
{
	//�@�V���h�[�}�b�v�̍폜
	ExitShadowMap();
}

//---------------------------------------------------------------------------
// �X�e�[�^�X�o�[�̕`��
//---------------------------------------------------------------------------
void GameScene::StatusDraw()
{
	player->StatusBarDraw();
	monster->Status_Bar_Draw();

}

//---------------------------------------------------------------------------
// ���C�g�̏����ݒ�
//---------------------------------------------------------------------------
void GameScene::LightInit()
{
}

//---------------------------------------------------------------------------
// �t�B�[���h�̓����蔻���
//---------------------------------------------------------------------------
void GameScene::HitField()
{

	// �t�B�[���h�̒n�ʃ��f���ƃL�����N�^�[�̓����蔻��
	HitGroundCharacter(&player->m_transform.pos, &field.m_field_model);

	// �����X�^�[�ƒn�ʂ̓����蔻��i�W�����v�����Ȃł���j
	HitGroundCharacterJump(&monster->m_transform.pos, &monster->m_jump_mov,
		&monster->m_jump_flag, monster->m_up_speed, monster->m_down_speed,
		&field.m_field_model);

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

//---------------------------------------------------------------------------
// �L�����N�^�[�̏�������
//---------------------------------------------------------------------------
void GameScene::Character_Init()
{
	// �v���C���[�̏�������
	player->Init();
	// �����X�^�[�̏�������
	monster->Init();
}

//---------------------------------------------------------------------------
// �L�����N�^�\�̍X�V����
//---------------------------------------------------------------------------
void GameScene::CharacterUpdate()
{
	// �v���C���[�̍X�V����
	player->Update(&camera.m_rot);

	// �����X�^�[�̍X�V����
	monster->Update(&player->m_transform, player->m_hit_r);



	// �����X�^�[�ƃv���C���[�̈ړ��̓����蔻��
	if (CheckCapsuleHit(monster->m_body, player->m_body))
	{
		player->m_move.Move_Hit_Capsule(&player->m_transform.pos, player->m_body.m_capsule.radius, &monster->m_body);
	}

	// �U���֌W�̃A�b�v�f�[�g
	AttackUpdate();
}

//---------------------------------------------------------------------------
// �L�����N�^�\�̍U���Ɋւ���X�V����
//---------------------------------------------------------------------------
void GameScene::AttackUpdate()
{
	// �v���C���[�̍U��
	if (player->m_attack_flag)
	{
		// ��̃A�j���[�V�����̊ԂɈ�񂾂�����������true��Ԃ��悤�ɂ���悤�ɂ����������܂������Ȃ�
		// �ڂ����͊֐��̒��ɏ���

		// player�̍U���̎��Ɏ�肽�������蔻��ƃ����X�^�[�̑̂Ƃ̓����蔻����Ƃ�
		int num = player->m_now_attack;
		CharacterBase::Attack_Hit_Damage* ptr = player->m_attack_hit_damage[num];
		if (player_attack_hit.HitAttack(monster->m_body, ptr->attack_hit, player->m_animation) == true)
		{
			// �U���̓����蔻��s���Ă����Ƃ�����(�U���A�j���[�V�����̎w��̃t���[���Ԃ���)
			if (player->AttackHitGoodTiming(player->m_now_attack))
			{
			
				// �_���[�W������͍̂U���A�j���[�V�����̊ԂɈ�񂾂�
				Damage_Count(player->m_attack_hit_damage[player->m_now_attack]->attack_damage, 5, &monster->m_hp_value);
			}

		}
	}



	//�����X�^�[�̍U��
	if (monster->m_attack_flag)
	{
		// �����X�^�[�̍U�����Ɏg�����������蔻���player�̑̂Ƃ̓����蔻��
		int num = monster->m_now_attack;
		MonsterBase::Attack_Hit_Damage* ptr = monster->m_attack_hit_damage[num];
		if (monster_attack_hit.HitAttack(player->m_body, ptr->attack_hit, monster->m_animation) == true)
		{
			// �v���C���[�̍U���󂯂��t���O���������Ă���Ƃ�
			if (player->m_damage_flag == false)
			{
				// �v���C���[�̍U���󂯂��t���O���グ��
				player->m_damage_flag = true;
			}
			// �_���[�W������͍̂U���A�j���[�V�����̊ԂɈ�񂾂�
			// �����X�^�[�̓����蔻��ƃ_���[�W�̐ݒ�̓A�j���[�V�����������Ƃ����̂�����������
			Damage_Count(monster->m_attack_hit_damage[monster->m_now_attack]->attack_damage, 5, &player->m_hp_value);
		
			// �_���[�W���������^�C�~���O�Ńq�b�g�X�g�b�v�̃J�E���g�����Z�b�g����
			hit_stop.Stop_Count_Reset();
		}
	}
}


//---------------------------------------------------------------------------
// �L�����N�^�\�̍U���Ɋւ���X�V����
// Victory(����)
// Defeat(�s�k)
//---------------------------------------------------------------------------
void GameScene::VDMessage()
{

	// �t�H���g�T�C�Y�̐ݒ�
	// �t�H���g�̃f�t�H���g�T�C�Y�̕ۑ�
	int default_font_size = GetFontSize();
	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(80);
	// �`�敝�̎擾
	float w = GetDrawStringWidth(m_massage[m_who_died].message, -1);
	// ������̍����̎擾
	float h = GetFontSize();
	// �`����W
	m_massage_pos = { SCREEN_W / 2 - w / 2, SCREEN_H / 2 - h };
	DrawString(m_massage_pos.x, m_massage_pos.y, m_massage[m_who_died].message, GetColor(255, 128, 50));

	// �t�H���g�̃T�C�Y���f�t�H���g�T�C�Y�ɖ߂�
	SetFontSize(default_font_size);
}
