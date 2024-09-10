#include "src/WinMain.h"
#include "src/System/Vector2.h"
#include "src/Sound/BGM.h"
#include "src/Sound/SE.h"
#include "Base/Scene_Base.h"
#include "TitleScene.h"



//------------------------------------------
// ��������
//------------------------------------------
void TitleScene::Init()
{
	
}

//------------------------------------------
// �X�V����
//------------------------------------------
void TitleScene::Update()
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
void TitleScene::Draw()
{

	DrawString(100, 100, "�^�C�g��", GetColor(255, 255, 255));

}

//------------------------------------------
// �I������
//------------------------------------------
void TitleScene::Exit()
{
	

}
