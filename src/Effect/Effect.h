#pragma once

//---------------------------------------------------------------------------
//  �G�t�F�N�g�p
//---------------------------------------------#include "src/System/Vector3.h"------------------------------


// �G�t�F�N�g�p�̔z��ϐ��̊l���֐�
// ����
// �P�F�G�t�F�N�g�̍ő��
// �Q�F�G�t�F�N�g�����Ă����p�̕ϐ�
// �R�F�G�t�F�N�g���g�����Ɏg���n���h���p�̕ϐ�
void Effect_New(int Effect_MAX, int* effect_container, int* m_effect_handle);


// �G�t�F�N�g�p�̕ϐ���delete�p�̊֐�
// ����
// �P�F�G�t�F�N�g�����Ă����p�̕ϐ�
// �Q�F�G�t�F�N�g���g�����Ɏg���n���h���p�̕ϐ�
void Effect_Delete(int* effect_container, int* effect_handle);

int* EffectContainerNew(int size);