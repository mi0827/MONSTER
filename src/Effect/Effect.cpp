#include "src/WinMain.h"
#include "Effect.h"

//---------------------------------------------------------------
// �G�t�F�N�g�p�̔z��m�ۊ֐�
//---------------------------------------------------------------
void Effect::EffectNew(int Effect_MAX, int* effect_container, int* m_effect_handle)
{
	// ��蒼��
	effect_container = new int[Effect_MAX];
	effect_handle = new int[Effect_MAX];
	for (int i = 0; i < Effect_MAX; i++)
	{
		effect_container[i] = 0;
		effect_handle[i] = 0;
	}
}


//---------------------------------------------------------------------------
//  �G�t�F�N�g�p�ϐ���delete�p�֐�
//---------------------------------------------------------------------------
void Effect::EffectDelete(int* effect_container, int* effect_handle)
{
	delete[] effect_container;
	delete[] effect_handle;
}


