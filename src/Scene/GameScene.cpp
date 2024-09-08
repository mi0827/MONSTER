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

#include "src/System/UIBar.h"

#include "src/System/Move.h"
#include "src/System/TargetMove.h"
#include "src/Character/CharacterBase.h"
#include "src/Character/MonsterBase.h"
#include "src/Character/SamplePlayer.h"
#include "src/Character/Hero.h"
#include "src/Character/Monster.h"
#include "src/Character/Mutant.h"

#include "src/Field/Field.h"
#include "src/Field/HitField.h" 

#include "src/System/DamageAction.h"
#include "src/Action/Attack.h"

#include "src/Camera.h"

#include "src/Scene/Base/Scene_Base.h"
#include "src/Scene/GameScene.h"

////! �J�����N���X�̃I�u�W�F�N�g
//Camera camera;
//
////! �T���v���v���C���[�N���X�̃I�u�W�F�N�g
//SamplePlayer player;
////! �q�[���[�N���X�̃I�u�W�F�N�g
////Hero hero;
////! �����X�^�[�N���X�̃I�u�W�F�N�g
////Monster monster;
//Mutant mutant;
//
////! �U���A�N�V�����̓����蔻��p�̃I�u�W�F�N�g
//// ���̃N���X�������̊֐��ł��悩�������ǒ���bool �^�̕ϐ��������̂ŃN���X�ɂ���
//Attack player_attack_hit;
//Attack monster_attack_hit;
//
//// ���̃{�b�N�X�̕`��
//BoxCollision box1;
//
//// ���̒n�ʃ��f���̓��ꕨ
//int ground = 0;
//
//// �t�B�[���h�I�u�W�F�N�g
//Field field;

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
	if (m_monster_num == MONSTER)
	{
		monster = new Monster;
	}

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

}

//---------------------------------------------------------------------------
// �X�V����
//---------------------------------------------------------------------------
void GameScene::Update(int bgm_volume, int se_volume)
{
	// �L�����N�^�[�̍X�V����
	CharacterUpdate(se_volume);
	
	// �t�B�[���h�Ƃ̓����蔻��
	HitField();

	// �J�����̍X�V����
	camera.Update(&player->m_transform.pos);
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

		//MV1SetPosition(ground, VGet(0.0f, 0.0f, 0.0f)); // �`�悷��v���C���[���f���̍��W�̐ݒ�
		//MV1SetRotationXYZ(ground, VGet(TO_RADIAN(0.0f), TO_RADIAN(0.0f), TO_RADIAN(0.0f))); // ���f���̉�]
		//MV1SetScale(ground, VGet(10, 10, 10)); // ���f���̑傫��(10���̂P�̃T�C�Y)
		//MV1DrawModel(ground); // ���f���̕`��
		field.Draw();
		// �����X�^�[�̕`��
		monster->Draw();
	}
	UseShadowMapSet();

	// �X�e�[�^�X�o�[�̕`��
	StatusDraw();
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
	player->Status_Bar_Draw();
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
void GameScene::CharacterUpdate(int se_volume)
{
	// �v���C���[�̍X�V����
	player->Update(&camera.m_rot);

	// �����X�^�[�̍X�V����
	monster->Update(&player->m_transform, player->m_hit_r);

	// �t�B�[���h�̒n�ʃ��f���ƃL�����N�^�[�̓����蔻��
	HitGroundCharacter(&player->m_transform.pos, &field.m_field_model);
	// ���̏�Ԃ��ƃW�����v�U�����ł��Ȃ�
	// �Ƃ̃f�X�N�g�b�v�����f�����g�ɓ����蔻���ݒ�̃\�[�X�ɃW�����v�̃q���g�������Ă���
	HitGroundCharacterJump(&monster->m_transform.pos, &monster->m_jump_mov,
		&monster->m_jump_flag, monster->m_up_speed, monster->m_down_speed,
		&field.m_field_model);





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
		// �����蔻�肪���܂����Ȃ��̂͂��̊֐��̒��g�̂���
		if (player_attack_hit.HitAttack(monster->m_body, player->m_attack_hit_damage[player->m_now_attack]->attack_hit, player->m_animation) == true)
		{
			// �_���[�W������͍̂U���A�j���[�V�����̊ԂɈ�񂾂�
			Damage_Count(player->m_attack_hit_damage[player->m_now_attack]->attack_damage, 5, &monster->m_hp_value);
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
			// �_���[�W������͍̂U���A�j���[�V�����̊ԂɈ�񂾂�
			// �����X�^�[�̓����蔻��ƃ_���[�W�̐ݒ�̓A�j���[�V�����������Ƃ����̂�����������
			Damage_Count(monster->m_attack_hit_damage[monster->m_now_attack]->attack_damage, 5, &player->m_hp_value);
		}
	}
}
