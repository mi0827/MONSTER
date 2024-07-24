#include "WinMain.h"
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

#include "src/System/Move.h"
#include "src/System/TargetMove.h"
#include "src/Character/CharacterBase.h"
#include "src/Character/MonsterBase.h"
#include "src/Character/SamplePlayer.h"
#include "src/Character/Hero.h"
#include "src/Character/Monster.h"

#include "src/Camera.h"
#include "GameMain.h"

// aisdjla
//aaaaaa

// �v���ł��邩�̎���


//! �J�����N���X�̃I�u�W�F�N�g
Camera camera;

//! �T���v���v���C���[�N���X�̃I�u�W�F�N�g
//SamplePlayer player;
//! �q�[���[�N���X�̃I�u�W�F�N�g
Hero hero;
//! �����X�^�[�N���X�̃I�u�W�F�N�g
Monster monster;

// �V�F�[�_�[�̊�̍��W�ƂȂ�p�̕ϐ�
FLOAT4 shader_base_pos_;
//	���_�V�F�[�_�[�p�̕ϐ�
int vertex_shader = 0;
//	�s�N�Z���V�F�[�_�[�p�̕ϐ�
int pixel_shader = 0;

BoxCollision box1;

// ���̒n�ʃ��f���̓��ꕨ
int ground = 0;


// �e�Ɏg�����

//! �v���C���[�p�̃V���h�E�}�b�v
int player_shadowmap_hanndle;
//! �V���h�[�}�b�v�p�̕ϐ�
int ShadowMapHandle;
float Angle;
VECTOR LightDirection;

int light_handle;
int light_handle_2;
//! ���C�g�̍��W�p�ϐ�



// ��������
void GameInit()
{
	//// �V�F�[�_�[�t�@�C���̓ǂݍ��݁i�c�w���C�u�����p�ɕϊ����ꂽ�t�@�C���j
	//vertex_shader = LoadVertexShader( "shader/SampleVS.vso");	//	���_�V�F�[�_�[

	//pixel_shader = LoadPixelShader( "shader/SamplePS.pso" );    //	�s�N�Z���V�F�[�_�[

	// �J�����̏����ݒ�
	camera.PlayField_Init();

	// �v���C���[�̏�������
	//player.Init();
	
	// �q�[���[�̏�������
	hero.Init();
	// �����X�^�[�̏�������
	monster.Init();

	// �n�ʃ��f���̂�������
	ground = MV1LoadModel("Data/ground.mqoz");
	// ���̃{�b�N�X
	Vector3 pos = { 10.0f,0.0f,10.0f };
	Vector3 size = { 10.0f,10.0f,10.0f };
	box1.CreateBox(pos, size);

	// �V���h�[�}�b�v�̍쐬
	player_shadowmap_hanndle = MakeShadowMap(4096, 4096);
	ShadowMapHandle = MakeShadowMap(4096, 4096);
	//	ShadowMapHandle = MakeShadowMap(16384, 16384);

		// ���C�g�̊p�x��������
	Angle = 10.0f;

	// ���C�g�̕����x�N�g���̎Z�o
	LightDirection.x = sin(Angle);
	LightDirection.z = cos(Angle);
	LightDirection.y = -1.0f;
	VectorNormalize(&LightDirection, &LightDirection);

	// ���C�g�̕�����ݒ�
	SetLightDirection(LightDirection);

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(player_shadowmap_hanndle, LightDirection);
	SetShadowMapLightDirection(ShadowMapHandle, LightDirection);
	// �V���h�[�}�b�v�ɕ`�悷��͈͂̐ݒ�
	SetShadowMapDrawArea(ShadowMapHandle, VGet(-2000.0f, -0.1f, -2000.0f), VGet(+2000.0f, 3000.0f, +2000.0f));


	// �f�t�H���g�̃��C�g�͕��s�����̂܂܏����Â߂ɂ��܂�
	//SetLightDifColor(GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
	//SetLightEnable(FALSE);

	// �f�t�H���g�J���[��������Ă���
	COLOR_F color = GetLightDifColor();

	// ������̃��C�g�̍쐬
	// ���g���Ƃ܂Ԃ�������
	// �L�����N�^�[�ɂ����w�ォ��̃��C�g����̉e�����󂯂Ȃ�
	Vector3 light_pos = { 1000.0f, 100.0f, 0.0f };
	light_handle = CreateDirLightHandle(VGet(0.0f, 0.0f, 1.0f));
	// ���C�g�̃|�W�V�����̐ݒ�
	SetLightPositionHandle(light_handle, light_pos.VGet());
	// �F�̐ݒ�
	SetLightDifColorHandle(light_handle, color);
	
}

// �X�V����
void GameUpdate()
{
	
	// �v���C���[�̍X�V����
	//player.Update(&camera.m_rot);

	// �q�[���[�̍X�V����
	hero.Update(&camera.m_rot);

	// �����X�^�[�̍X�V����
	// ���̓v���C���[�Ɠ����X�V�������������X�^�[�Ǝ��̍X�V�������ǉ�����
	monster.Update(&hero.m_transform, hero.m_hit_r);

	// �J�����̍X�V����
	camera.Update(&hero.m_transform.pos);

	// �v���C���[�ƃ{�b�N�X�̓����蔻�肪�������Ƃ������ǂ�������Ăق���
	if (CheckBoxHit3D(hero.m_transform.pos, hero.move_hit_size, box1.m_box.hit_pos, box1.m_box.half_size))
	{
		hero.MoveHitUpdate(&hero.m_transform.pos, &hero.m_before_pos, &hero.move_hit_size, &box1);
	}
	// �����X�^�[�ƃv���C���[�̈ړ��̓����蔻��
	if (CheckCapsuleHit(monster.m_body, hero.m_body))
	{
		// �������Ă�����
		hero.m_move.Move_Hit_Capsule(&hero.m_transform.pos, hero.m_body.m_capsule.radius,
			&monster.m_body);
	}
	


	// �R�F�q�̕ϐ��̒l���V�F�[�_�[�ɓn���܂�
	//SetPSConstF(25, shader_base_pos);
}

// �`�揈��
void GameDraw()
{
	

	////	�V�F�[�_�[���g���ĕ`�悵�܂�
	//MV1SetUseOrigShader(TRUE);
	////	���_�V�F�[�_�[�̃Z�b�g
	//SetUseVertexShader(vertex_shader);
	////	�s�N�Z���V�F�[�_�[�̃Z�b�g
	//SetUsePixelShader(pixel_shader);


	// �V���h�[�}�b�v�ɕ`�悷��͈͂̐ݒ�
	// ���͂��́@�͈͂Ńv���C���[�̃V���h�E�}�b�v��ݒ肵�Ă��邪
	// �w��̉e���C�ɓ���Ȃ���Γ�ڂ�Y���W�̒l���グ�邩�S�̓I�ɕ`��͈͂��L����
	SetShadowMapDrawArea(player_shadowmap_hanndle,
		VGet(hero.m_transform.pos.x - 200.0f, -0.1f, hero.m_transform.pos.z - 200.0f),
		VGet(hero.m_transform.pos.x + 200.0f, +1000.0f, hero.m_transform.pos.z + 200.0f));


	// ���{�b�N�X�̕`��
	box1.Draw(255, 100);


	//-------------------------------------------------------------
	// �V���h�E�}�b�v�̍쐬�i�����Ŋe�I�u�W�F�N�g�̃V���h�[�}�b�v�̐ݒ�j
	//-------------------------------------------------------------
	// �V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(player_shadowmap_hanndle);
	{
		// �v���C���[�̕`�揈��
		//player.Draw();

		// �q�[���[�̕`�揈��
		hero.Draw();
	}
	ShadowMap_DrawSetup(ShadowMapHandle);
	{
		// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
		MV1SetPosition(ground, VGet(0.0f, 0.0f, 0.0f)); // �`�悷��v���C���[���f���̍��W�̐ݒ�
		MV1SetRotationXYZ(ground, VGet(TO_RADIAN(0.0f), TO_RADIAN(0.0f), TO_RADIAN(0.0f))); // ���f���̉�]
		MV1SetScale(ground, VGet(10, 10, 10)); // ���f���̑傫��(10���̂P�̃T�C�Y)
		MV1DrawModel(ground); // ���f���̕`��

		// �����X�^�[�̕`��
		monster.Draw();
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
	SetUseShadowMap(1, player_shadowmap_hanndle);
	{
		//player.Draw();

		// �q�[���[�̕`�揈��
		hero.Draw();
	}
	SetUseShadowMap(0, ShadowMapHandle);
	{
		// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��

		MV1SetPosition(ground, VGet(0.0f, 0.0f, 0.0f)); // �`�悷��v���C���[���f���̍��W�̐ݒ�
		MV1SetRotationXYZ(ground, VGet(TO_RADIAN(0.0f), TO_RADIAN(0.0f), TO_RADIAN(0.0f))); // ���f���̉�]
		MV1SetScale(ground, VGet(10, 10, 10)); // ���f���̑傫��(10���̂P�̃T�C�Y)
		MV1DrawModel(ground); // ���f���̕`��

		// �����X�^�[�̕`��
		monster.Draw();
	}

	printfDx("run:%d ", monster.m_run_flag);
	printfDx("idle:%d ", monster.m_idle_flag);
	printfDx("attack:%d ", monster.m_attack_flag);
	printfDx("combo_flag:%d ", monster.m_combo_flag);
	
	// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
	SetUseShadowMap(1, -1);
	SetUseShadowMap(0, -1);
}

// �I������
void GameExit()
{
	////	�V�F�[�_�[�t�@�C���̏I������
	//DeleteShader(vertex_shader);
	//DeleteShader(pixel_shader);

	// �V���h�[�}�b�v�̍폜
	DeleteShadowMap(player_shadowmap_hanndle);
	DeleteShadowMap(ShadowMapHandle);
	// ���C�g�̍폜
	//DeleteLightHandle(light_handle);
	//DeleteLightHandle(light_handle_2);
}

