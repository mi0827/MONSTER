#include "src/WinMain.h"
#include "Effect.h"

//---------------------------------------------------------------------------
//  �G�t�F�N�g�p�̔z��ϐ��̊l���p�֐�
//---------------------------------------------------------------------------
void Effect_New(int Effect_MAX, int* effect_container, int* effect_handle)
{
	effect_container = new int[Effect_MAX];
	effect_handle = new int[Effect_MAX];
	for (int i = 0; i < Effect_MAX; i++) 
	{
		effect_container[i] = 0;
		effect_handle[i] = 0;
	}
}

int* EffectContainerNew(int size)
{
	return new int[size];
}

//---------------------------------------------------------------------------
//  �G�t�F�N�g�p�ϐ���delete�p�֐�
//---------------------------------------------------------------------------
void Effect_Delete(int* effect_container, int* effect_handle)
{
	delete[] effect_container;
	delete[] effect_handle;
}


