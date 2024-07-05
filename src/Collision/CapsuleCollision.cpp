#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"
#include "src/Model/Model.h"
#include "CapsuleCollision.h"

CapsuleCollision::CapsuleCollision()
{
}

CapsuleCollision::~CapsuleCollision()
{
}

//-----------------------------------------------
// �J�v�Z���̕`��
//-----------------------------------------------
void CapsuleCollision::Draw()
{
	DrawCapsule3D(m_capsule.pos1.VGet(), m_capsule.pos2.VGet(), m_capsule.radius, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
}

//-----------------------------------------------
// ���f���̎w��̈ʒu�ɃJ�v�Z��������
//-----------------------------------------------
void CapsuleCollision::CreateNodoCapsule(Model* model, int nodo_index)
{
	// ���f���̎w��̈ʒu�̍��W������Ă���
	m_capsule.pos1 = model->GetNodePos(nodo_index);
	// �T�C�Y�͓K���ȏ����l�����Ă���
	m_capsule.pos2 = m_capsule.pos1 + Vector3(1.0f, 1.0f, 1.0f);
	// ���a���K���Ȓl�����Ă���
	m_capsule.radius = 1.0f;
}

//-----------------------------------------------
// �J�v�Z��������
//-----------------------------------------------
void CapsuleCollision::CreateCapsule(Vector3 pos)
{
	// ���W�̕ۑ�
	m_capsule.pos1 = pos;
	// �T�C�Y�͓K���ȏ����l�����Ă���
	m_capsule.pos2 = m_capsule.pos1 + Vector3(1.0f, 1.0f, 1.0f);
	// ���a���K���Ȓl�����Ă���
	m_capsule.radius = 1.0f;
}

//-----------------------------------------------
// �J�v�Z���̂�����̍��W���m�[�h���������Ă���
//-----------------------------------------------
void CapsuleCollision::NodoSetSize(Model* model, int nodo_index, float radius)
{
	// �T�C�Y�̒���
	m_capsule.pos2 = model->GetNodePos(nodo_index);
	// �J�v�Z���̔��a�̐ݒ�
	m_capsule.radius = radius;
}

//-----------------------------------------------
// �J�v�Z���̃T�C�Y�̒���
//-----------------------------------------------
void CapsuleCollision::SetSize(Vector3 size,  float radius)
{
	// �T�C�Y�̒���
	m_capsule.pos2 = m_capsule.pos1 + size;
	// �J�v�Z���̔��a�̐ݒ�
	m_capsule.radius = radius;
}
