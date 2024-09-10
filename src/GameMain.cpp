#include "WinMain.h"
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

#include "src/System/Move.h"
#include "src/System/TargetMove.h"

#include "src/System/UIBar.h"
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
#include "src/Scene/TitleScene.h"
#include "src/Scene/GameScene.h"
#include "src/Scene/EndScene.h"

#include "GameMain.h"

// �e�V�[���̃I�u�W�F�N�g
Scene_Base* scene;


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

int scene_num = 0; // ���ǂ̃V�[�����̂�����p�̕ϐ�
// �e�V�[���ł̎g�����������邽�߂̃V�[���̗񋓑�
enum Scene
{
	Titele, // �^�C�g��
	Play,  // ���C���̃v���C�V�[��
	End,   // �G���h

	Scene_Max // �V�[���̍ő吔
};


//-------------------------------------------------------------
// ��������
//-------------------------------------------------------------
void GameInit()
{
	// �Ƃ肠�������̓^�C�g���V�[�������Ă���
	scene = new TitleScene;

	// �L�����N�^�[�̂����Ă�
	//scene->SetCharacter(scene->SAMPLEPLAYER,scene->MUTANT);

	scene->Init();

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

//-------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------
void GameUpdate()
{
	switch (scene_num)
	{
	case Titele: // �^�C�g���V�[��

		scene->Update();
		if (scene->m_scene_change_judge) {                             // �V�[���̐؂�ւ��̋���������
			scene->Exit();                                           // dekete�O�ɏI����������
			Scene_Change_Judge(scene_num, Play);                     // �V�[���̐؂�ւ�
			delete scene;                                            // �V�[���̐؂�ւ��̑O�Ƀ^�C�g���V�[����������
			scene = new GameScene;                                   // ���̃V�[����new���Ă���
			scene->Init();                                           // ���̃V�[���̏��������������ōς܂�
		}
		break;

	case Play:  // �v���C�V�[��
		scene->Update();
		if (scene->m_scene_change_judge) {                              // �V�[���̐؂�ւ��̋���������
			scene->Exit();                                            // dekete�O�ɏI����������
			Scene_Change_Judge(scene_num, End);  // �V�[���̐؂�ւ�	                                                        
			delete scene;                                            // �V�[���̐؂�ւ��̑O�Ƀ^�C�g���V�[����������
			scene = new EndScene;                                    // ���̃V�[����new���Ă���
			scene->Init();                                           // ���̃V�[���̏��������������ōς܂�
		}
		break;
	case End:  // �G���h�V�[��
		scene->Update();
		if (scene->m_scene_change_judge) {                             // �V�[���̐؂�ւ��̋���������
			scene->Exit();                                           // dekete�O�ɏI����������
			Scene_Change_Judge(scene_num, Titele);                   // �V�[���̐؂�ւ�
			delete scene;                                            // �V�[���̐؂�ւ��̑O�Ƀ^�C�g���V�[����������
			scene = new TitleScene;                                 // ���̃V�[����new���Ă���
			scene->Init();                                           // ���̃V�[���̏��������������ōς܂�
		}
		break;
	}

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




