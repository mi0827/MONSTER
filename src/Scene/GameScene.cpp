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
// ��������
//---------------------------------------------------------------------------
void GameScene::GameSceneInit(int player_num, int monster_num)
{
}

//---------------------------------------------------------------------------
// ��������
//---------------------------------------------------------------------------
void GameScene::Init()
{
	// �J�����̏����ݒ�
	camera.PlayField_Init();

	// �t�B�[���h�̏����� 
	field.Init();
}

//---------------------------------------------------------------------------
// �X�V����
//---------------------------------------------------------------------------
void GameScene::Update(int bgm_volume, int se_volume)
{
	// �L�����N�^�[�̍X�V����
	Character_Update(se_volume);
	// �J�����̍X�V����
	camera.Update(&player->m_transform.pos);
}

//---------------------------------------------------------------------------
// �`�揈��
//---------------------------------------------------------------------------
void GameScene::Draw()
{
	
}

//---------------------------------------------------------------------------
// �I������
//---------------------------------------------------------------------------
void GameScene::Exit()
{
}

//---------------------------------------------------------------------------
// ���C�g�̏����ݒ�
//---------------------------------------------------------------------------
void GameScene::Light_Init()
{
}

//---------------------------------------------------------------------------
// �L�����N�^�[�̏�������
//---------------------------------------------------------------------------
void GameScene::Character_Init()
{
	// �v���C���[�̏�������
	player->Init();
}

//---------------------------------------------------------------------------
// �L�����N�^�\�̍X�V����
//---------------------------------------------------------------------------
void GameScene::Character_Update(int se_volume)
{
	// �v���C���[�̍X�V����
	player->Update(&camera.m_rot);

	// �����X�^�[�̍X�V����
	monster->Update(&player->m_transform,player->m_hit_r);

	// �t�B�[���h�̃I�u�W�F�N�g�ƃv���C���[�̈ړ��̍ۂ̕ǎC�蔻��
	if (CheckBoxHit3D(player->m_transform.pos, player->m_move_hit_size,
		field.m_field_object[0].box_hit.m_box.hit_pos, field.m_field_object[0].box_hit.m_box.half_size))
	{
		player->MoveHitUpdate(&field.m_field_object->box_hit);
	}

	// �����X�^�[�ƃv���C���[�̈ړ��̓����蔻��
	if (CheckCapsuleHit(monster->m_body, player->m_body))
	{
		player->m_move.Move_Hit_Capsule(&player->m_transform.pos, player->m_body.m_capsule.radius, &monster->m_body);
	}
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
		if (player_attack_hit.HitAttack(monster->m_body, player->m_attack_hit_damage[player->m_now_attack].attack_hit, player->m_animation) == true)
		{
			// �_���[�W������͍̂U���A�j���[�V�����̊ԂɈ�񂾂�
			Damage_Count(player->m_attack_hit_damage[player->m_now_attack].attack_damage, 5, &monster->m_hp_value);
		}
	}
	//�����X�^�[�̍U��
	if (monster->m_attack_flag)
	{
		// �����X�^�[�̍U�����Ɏg�����������蔻���player�̑̂Ƃ̓����蔻��
		if (monster_attack_hit.HitAttack(player->m_body,  monster->m_attack_hit_damage[monster->m_now_attack].attack_hit,  monster->m_animation) == true)
		{
			// �_���[�W������͍̂U���A�j���[�V�����̊ԂɈ�񂾂�
			// �����X�^�[�̓����蔻��ƃ_���[�W�̐ݒ�̓A�j���[�V�����������Ƃ����̂�����������
			Damage_Count(monster->m_attack_hit_damage[monster->m_now_attack].attack_damage, 5, &player->m_hp_value);
		}
	}
}
