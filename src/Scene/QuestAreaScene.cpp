#include "src/WinMain.h"
#include "src/System/Vector2.h"
#include "src/Sound/BGM.h"
#include "src/Sound/SE.h"
#include "Base/Scene_Base.h"
#include "QuestAreaScene.h"



//------------------------------------------
// ��������
//------------------------------------------
void QuestAreaScene::Init()
{

}

//------------------------------------------
// �X�V����
//------------------------------------------
void QuestAreaScene::Update()
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
void QuestAreaScene::Draw()
{

	DrawString(100, 100, "�N�G�X�g�G���A", GetColor(255, 255, 255));

}

//------------------------------------------
// �I������
//------------------------------------------
void QuestAreaScene::Exit()
{


}
