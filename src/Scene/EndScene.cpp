#include "src/WinMain.h"
#include "src/System/Vector2.h"
#include "src/Sound/BGM.h"
#include "src/Sound/SE.h"
#include "Base/Scene_Base.h"
#include "EndScene.h"

BGM end_bgm;

const int End_Time_MAX = 3;  // �G���h�`�掞��(������3�b)
//------------------------------------------
// ��������
//------------------------------------------
void EndScene::Init()
{


}

//------------------------------------------
// �X�V����
//------------------------------------------
void EndScene::Update()
{
	
	// X�L�[�������ꂽ���ɃV�[���̕ύX������i�������̉��j
	if (PushHitKey(KEY_INPUT_X))
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
void EndScene::Draw()
{
	DrawString(100, 100, "�I���", GetColor(255, 255, 255));
}

//------------------------------------------
// �I������
//------------------------------------------
void EndScene::Exit()
{

}
//------------------------------------------
// BGM�̏�������
//------------------------------------------
void EndScene::BGM_Init()
{
	
}
