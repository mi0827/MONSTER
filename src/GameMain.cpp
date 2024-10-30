#include "WinMain.h"
#include "src/System/Random.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"

#include "src/Action/Combo.h"
#include "src/System/Transform.h"
#include "src/System/InputPad.h"

#include "src/Model/Model.h"
#include "src/Animation/Animation.h"
#include "src/Effect/Effect.h"

#include "src/Collision/BoxCollision.h"
#include "src/Collision/CapsuleCollision.h"
#include "src/Hit/Hit.h"
#include "src/Hit/HitStop.h"

#include "src/System/Move.h"
#include "src/System/TargetMove.h"

#include "src/System/UIBar.h"
#include "src/Character/CharacterBase.h"
#include "src/Character/MonsterBase.h"
#include "src/Character/SamplePlayer.h"
#include "src/Character/Hero.h"
#include "src/Character/Monster.h"
#include "src/Character/Mutant.h"
#include "src/Character/Receptionist.h"


#include "src/Field/FieldBase.h"
#include "src/Field/Field.h"
#include "src/Field/TitleField.h"

#include "src/System/DamageAction.h"
#include "src/Action/Attack.h"

#include "src/Camera.h"

#include <fstream>
#include <string>
#include "src/System/Text.h"

#include "src/Scene/Base/Scene_Base.h"
#include "src/Scene/TitleScene.h"
#include "src/Scene/QuestAreaScene.h"
#include "src/Scene/GameScene.h"
#include "src/Scene/EndScene.h"

#include "src/Sound/BGM.h"
#include "src/Sound/BGM.h"
#include "src/System/Option.h"

#include "GameMain.h"
using namespace std;
// �e�V�[���̃I�u�W�F�N�g
Scene_Base* scene;

Option option;


// ���C�g�ƃV���h�[�}�b�v�̐ݒ�̓Q�[�����C���ōs��


// �e�Ɏg�����
//! �v���C���[�p�̃V���h�E�}�b�v
//int player_shadowmap_hanndle;
////! �V���h�[�}�b�v�p�̕ϐ�
//int ShadowMapHandle;
//float Angle;
//VECTOR LightDirection;


int light_handle;

//! ���C�g�̍��W�p�ϐ�

//int scene_num = 0; // ���ǂ̃V�[�����̂�����p�̕ϐ�
//// �e�V�[���ł̎g�����������邽�߂̃V�[���̗񋓑�
//enum Scene
//{
//	Titele, // �^�C�g��
//	QuestArea, // �N�G�X�g�󒍃V�[��
//	Play,  // ���C���̃v���C�V�[��
//	End,   // �G���h
//
//	Scene_Max // �V�[���̍ő吔
//};

int gazou;

//-------------------------------------------------------------
// ��������
//-------------------------------------------------------------
void GameInit()
{

	option.Init();

	gazou = LoadGraph("Data/Monsuta 2024_10_12 16_49_23.png");


	// �Ƃ肠�������̓^�C�g���V�[�������Ă���
	scene = new TitleScene;

	// �L�����N�^�[�̂����Ă�
	//scene->SetCharacter(scene->SAMPLEPLAYER,scene->MUTANT);

	scene->Init();
	


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

//-------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------
void GameUpdate()
{
	// �I�v�V�������j���[���J���Ă��Ȃ��Ƃ�����
	if (!option.m_option_flag)
	{
		switch (scene->m_now_scene)
		{
		case scene->Title: // �^�C�g���V�[��

			scene->Update();
			// �V�[���̕ύX�t���O�������Ă����
			if (scene->m_scene_change_judge) {
				// ���ɍs���Ăق����V�[�����N�G�X�g�󒍃G���A�Ȃ�                     	                                                
				if (scene->m_next_scene == scene->QuestArea)
				{
					scene->Exit();              // delete�O�ɏI����������
					delete scene;               // ���݂̃V�[���̍폜
					scene = new QuestAreaScene; // ���̃V�[����new���Ă���
					scene->Init();              // ���̃V�[���̏��������������ōς܂�
				}

			}
			break;

		case scene->QuestArea: // �N�G�X�g�󒍃G���A
			scene->Update();
			// �V�[���̕ύX�t���O�������Ă����
			if (scene->m_scene_change_judge)
			{
				// ���ɍs���Ăق����V�[�����o�g���V�[����������
				if (scene->m_next_scene == scene->Battle)
				{
					scene->Exit();         // delete�O�ɏI����������
					delete scene;          // ���݂̃V�[���̍폜
					scene = new GameScene; // ���̃V�[����new���Ă���
					scene->Init();         // ���̃V�[���̏��������������ōς܂�
				}
			}
			break;

		case scene->Battle:  // �v���C�V�[��(�o�g���V�[��)
			scene->Update();
			// �V�[���̕ύX�t���O�������Ă����
			if (scene->m_scene_change_judge)
			{
				// ���ɍs���Ăق����V�[�����G���h�V�[����������
				if (scene->m_next_scene == scene->End)
				{
					scene->Exit();        // delete�O�ɏI����������
					delete scene;         // ���݂̃V�[���̍폜
					scene = new EndScene; // ���̃V�[����new���Ă���
					scene->Init();        // ���̃V�[���̏��������������ōς܂�
				}
			}
			break;

		case scene->End:  // �G���h�V�[��
			scene->Update();
			// �V�[���̕ύX�t���O�������Ă����
			if (scene->m_scene_change_judge)
			{
				// ���ɍs���Ăق����V�[�����^�C�g���V�[����������
				if (scene->m_next_scene == scene->Title)
				{
					scene->Exit();             // delete�O�ɏI����������
					delete scene;              // ���݂̃V�[���̍폜
					scene = new TitleScene;    // ���̃V�[����new���Ă���
					scene->Init();             // ���̃V�[���̏��������������ōς܂�
				}
				// ���ɍs���Ăق����V�[�����N�G�X�g�󒍃V�[����������@
				if (scene->m_next_scene == scene->QuestArea)
				{
					scene->Exit();              // delete�O�ɏI����������
					delete scene;               // ���݂̃V�[���̍폜
					scene = new QuestAreaScene; // ���̃V�[����new���Ă���
					scene->Init();              // ���̃V�[���̏��������������ōς܂�
				}
			}
			break;
		}

	}

	// �I�v�V�������j���[�̍X�V����
	option.Update();
	// �I�v�V�����ŕύX���ꂽ�l�𔽉f�@�@
	scene->OptionValuesReflect(option.option_menu[option.BGM].m_value,
		option.option_menu[option.SE].m_value,
		option.option_menu[option.MOUSE].m_value);
	// �R�F�q�̕ϐ��̒l���V�F�[�_�[�ɓn���܂�
	//SetPSConstF(25, shader_base_pos);
}


//-------------------------------------------------------------
// �`�揈��
//-------------------------------------------------------------
void GameDraw()
{

	// �V�[���̕`�揈��
	scene->Draw();


	option.Draw();


	scene->BaseDraw(scene->m_now_scene, { 0,100 });
	////	�V�F�[�_�[���g���ĕ`�悵�܂�
	//MV1SetUseOrigShader(TRUE);
	////	���_�V�F�[�_�[�̃Z�b�g
	//SetUseVertexShader(vertex_shader);
	////	�s�N�Z���V�F�[�_�[�̃Z�b�g
	//SetUsePixelShader(pixel_shader);


}

// �I������
void GameExit()
{
	////	�V�F�[�_�[�t�@�C���̏I������
	//DeleteShader(vertex_shader);
	//DeleteShader(pixel_shader);

	// �V�[���̏I������
	scene->Exit();

	// �V�[���x�[�X�N���X�̍폜
	delete scene;
	// ���C�g�̍폜
	//DeleteLightHandle(light_handle);

}

//----------------------------------------------
// ���̃V�[�����玟�̃V�[���ɐ؂�ւ���֐�
//----------------------------------------------
void Scene_Change_Judge(int& now_scene, const int& next_scene)
{
	// ���̃V�[���ԍ��Ɏ��s�������V�[���ԍ�������
	now_scene = next_scene;
}




