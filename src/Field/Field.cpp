#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/System/Transform.h"
#include "src/Model/Model.h"
#include "src/Collision/BoxCollision.h"
#include "src/Collision/CapsuleCollision.h"
#include "src/Field/HitField.h"
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
	// �n�ʃ��f���̓����蔻��̐ݒ�
	SetHitGround(&m_field_model);
	// �t�B�[���h�ݒ�
	m_field_transform.pos.set(0, -10, 0);
	m_field_transform.scale.set(1, 1, 1);

	// �t�B�[���h�̃I�u�W�F�N�g�̏�����
	Object_Init();
}

void Field::Object_Init()
{
	//---------------------------------
	// �؂̃��f��
	//--------------------------------
	// ���f���f�[�^�̓ǂݍ���
	m_field_object[tree1].model.LoadModel("Data/Field/object/tree/Stage_Obj001.mv1");
	// ���W�ݒ�
	m_field_object[tree1].transform.pos.set(50.0f, 50.0f, 0.0f);

	// �����̐ݒ�
	m_field_object[tree1].transform.rot.set(0.0f, 0.0f, 0.0f);

	// �T�C�Y�̐ݒ�
	m_field_object[tree1].transform.scale.set(0.5f, 0.5f, 0.5f);

	// �����蔻��̐ݒ�
	m_field_object[tree1].box_hit.CreateBox(m_field_object[tree1].transform.pos, { 50.0f,20.0f,50.f });

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

	/*for (int i = 0; i < MODEL_MAX; i++)
	{
		m_field_object[i].model.DrawModel(&m_field_object[i].transform);
	}*/
	m_field_object[tree1].model.DrawModel(&m_field_object[tree1].transform);
	m_field_object[tree1].box_hit.Draw(255,255);
}

//---------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------
void Field::Exit()
{

}
