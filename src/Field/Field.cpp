#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/System/Transform.h"
#include "src/Model/Model.h"
#include "src/Collision/BoxCollision.h"
#include "src/Collision/CapsuleCollision.h"
#include "src/Field/Field.h"


// �t�B�[���h�̃I�u�W�F�N�g��u�����W 
constexpr int MAP_W = 10;  // �c
constexpr int MAP_H = 10;  // ��

// 1���ǂO�������Ȃ�
// �t�B�[���h�̃I�u�W�F�N�g��u�����W�p�̓񎟌��z��
//	����������
Field::Field()
{
	
}

//---------------------------------------------------------------------------
//��������
//---------------------------------------------------------------------------
void Field::Init()
{
	// �t�B�[���h���f���̓ǂݍ���
	m_field_model.LoadModel("Data/Field/ground/Stage00.mv1");
	// �t�B�[���h�ݒ�
	m_field_transform.pos.set(0, 0, 0);
	m_field_transform.scale.set(0.1, 0.1, 0.1);
	//m_field_object[0].model.LoadModel();
}

//---------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------
void Field::Update()
{

}

//---------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------
void Field::Draw()
{
	
	m_field_model.DrawModel(&m_field_transform);
}

//---------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------
void Field::Exit()
{

}
