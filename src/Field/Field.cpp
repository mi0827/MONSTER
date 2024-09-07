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

Field::~Field()
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
	ObjectInit();
}

void Field::ObjectInit()
{
	// �؂̏�������
	TreeInit();
	// �t�F���X�̏�������
	FenceInit();
	// �΂̏�������
	StoneInit();
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

	for (int i = 0; i < MODEL_MAX; i++)
	{
		m_field_object[i].model.DrawModel(&m_field_object[i].transform);
		m_field_object[i].box_hit.Draw(255, 255);
	}

}

//---------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------
void Field::Exit()
{

}

//---------------------------------------------------------------------------
//	�؂̃I�u�W�F�N�g�̏����ݒ�
//---------------------------------------------------------------------------
void Field::TreeInit()
{
	// ���f���f�[�^�̓ǂݍ���
	m_field_object[tree1].model.LoadModel("Data/Field/object/tree/Stage_Obj001.mv1");
	m_field_object[tree2].model.LoadModel("Data/Field/object/tree/Stage_Obj001.mv1");
	m_field_object[tree3].model.LoadModel("Data/Field/object/tree/Stage_Obj001.mv1");

	// ���W�ݒ�
	m_field_object[tree1].transform.pos.set(0.0f, 30.0f, 0.0f);
	m_field_object[tree2].transform.pos.set(0.0f, 30.0f, 240.0f);
	m_field_object[tree3].transform.pos.set(240.0f, 30.0f, 0.0f);


	// �����̐ݒ�
	m_field_object[tree1].transform.rot.set(0.0f, 45.0f, 0.0f);
	m_field_object[tree2].transform.rot.set(0.0f, 45.0f, 0.0f);
	m_field_object[tree3].transform.rot.set(0.0f, 45.0f, 0.0f);

	// �T�C�Y�̐ݒ�
	m_field_object[tree1].transform.scale.set(0.5f, 0.5f, 0.5f);
	m_field_object[tree2].transform.scale.set(0.5f, 0.5f, 0.5f);
	m_field_object[tree3].transform.scale.set(0.5f, 0.5f, 0.5f);

	// �����蔻��̐ݒ�
	m_field_object[tree1].box_hit.CreateBox(m_field_object[tree1].transform.pos, { 50.0f,20.0f,50.f });
	m_field_object[tree2].box_hit.CreateBox(m_field_object[tree2].transform.pos, { 50.0f,20.0f,50.f });
	m_field_object[tree3].box_hit.CreateBox(m_field_object[tree3].transform.pos, { 50.0f,20.0f,50.f });
}

//---------------------------------------------------------------------------
//	�t�F���X�̃I�u�W�F�N�g�̏����ݒ�
//---------------------------------------------------------------------------
void Field::FenceInit()
{
	// ���f���f�[�^�̓ǂݍ���
	m_field_object[fence1 ].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence2 ].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence3 ].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence4 ].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence5 ].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence6 ].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence7 ].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence8 ].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence9 ].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence10].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence11].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence12].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence13].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence14].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence15].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence16].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence17].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence18].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence19].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	m_field_object[fence20].model.LoadModel("Data/Field/object/fence/Stage_Obj009.mv1");
	
	// ���W�ݒ�
	m_field_object[fence1  ].transform.pos.set(0.0f, 30.0f, 240.0f);
	m_field_object[fence2  ].transform.pos.set(60.0f, 30.0f, 240.0f);
	m_field_object[fence3  ].transform.pos.set(120.0f, 30.0f, 240.0f);
	m_field_object[fence4  ].transform.pos.set(180.0f, 30.0f, 240.0f);
	m_field_object[fence5  ].transform.pos.set(240.0f, 30.0f, 240.0f);

	m_field_object[fence6  ].transform.pos.set(0.0f, 30.0f, 0.0f);
	m_field_object[fence7  ].transform.pos.set(60.0f, 30.0f, 0.0f);
	m_field_object[fence8  ].transform.pos.set(120.0f, 30.0f,0.0f);
	m_field_object[fence9  ].transform.pos.set(180.0f, 30.0f, 0.0f);
	m_field_object[fence10].transform.pos.set(240.0f, 30.0f, 0.0f);

	m_field_object[fence11].transform.pos.set(0.0f, 30.0f, 20.0f);
	m_field_object[fence12].transform.pos.set(0.0f, 30.0f, 60.0f);
	m_field_object[fence13].transform.pos.set(0.0f, 30.0f, 120.0f);
	m_field_object[fence14].transform.pos.set(0.0f, 30.0f, 180.0f);
	m_field_object[fence15].transform.pos.set(0.0f, 30.0f, 240.0f);

	m_field_object[fence16].transform.pos.set(240.0f, 30.0f, 0.0f);
	m_field_object[fence17].transform.pos.set(240.0f, 30.0f, 60.0f);
	m_field_object[fence18].transform.pos.set(240.0f, 30.0f, 120.0f);
	m_field_object[fence19].transform.pos.set(240.0f, 30.0f, 180.0f);
	m_field_object[fence20].transform.pos.set(240.0f, 30.0f, 240.0f);

	// �����̐ݒ�
	m_field_object[fence1 ].transform.rot.set(0.0f, 0.0f, 0.0f);
	m_field_object[fence2 ].transform.rot.set(0.0f, 0.0f, 0.0f);
	m_field_object[fence3 ].transform.rot.set(0.0f, 0.0f, 0.0f);
	m_field_object[fence4 ].transform.rot.set(0.0f, 0.0f, 0.0f);
	m_field_object[fence5 ].transform.rot.set(0.0f, 0.0f, 0.0f);

	m_field_object[fence6 ].transform.rot.set(0.0f, 0.0f, 0.0f);
	m_field_object[fence7 ].transform.rot.set(0.0f, 0.0f, 0.0f);
	m_field_object[fence8 ].transform.rot.set(0.0f, 0.0f, 0.0f);
	m_field_object[fence9 ].transform.rot.set(0.0f, 0.0f, 0.0f);
	m_field_object[fence10].transform.rot.set(0.0f, 0.0f, 0.0f);

	m_field_object[fence11].transform.rot.set(0.0f, 90.0f, 0.0f);
	m_field_object[fence12].transform.rot.set(0.0f, 90.0f, 0.0f);
	m_field_object[fence13].transform.rot.set(0.0f, 90.0f, 0.0f);
	m_field_object[fence14].transform.rot.set(0.0f, 90.0f, 0.0f);
	m_field_object[fence15].transform.rot.set(0.0f, 90.0f, 0.0f);

	m_field_object[fence16].transform.rot.set(0.0f, 90.0f, 0.0f);
	m_field_object[fence17].transform.rot.set(0.0f, 90.0f, 0.0f);
	m_field_object[fence18].transform.rot.set(0.0f, 90.0f, 0.0f);
	m_field_object[fence19].transform.rot.set(0.0f, 90.0f, 0.0f);
	m_field_object[fence20].transform.rot.set(0.0f, 90.0f, 0.0f);
	
	// �T�C�Y�̐ݒ�
	m_field_object[fence1].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence2].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence3].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence4].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence5].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence6].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence7].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence8].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence9].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence10].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence11].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence12].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence13].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence14].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence15].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence16].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence17].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence18].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence19].transform.scale.set(0.1f, 0.1f, 0.1f);
	m_field_object[fence20].transform.scale.set(0.1f, 0.1f, 0.1f);

	// �����蔻��̐ݒ�
	m_field_object[fence1].box_hit.CreateBox(m_field_object[fence1].transform.pos, { 60.0f,20.0f,5.0f });
	m_field_object[fence2].box_hit.CreateBox(m_field_object[fence2].transform.pos, { 60.0f,20.0f,5.0f });
	m_field_object[fence3].box_hit.CreateBox(m_field_object[fence3].transform.pos, { 60.0f,20.0f,5.0f });
	m_field_object[fence4].box_hit.CreateBox(m_field_object[fence4].transform.pos, { 60.0f,20.0f,5.0f });
	m_field_object[fence5].box_hit.CreateBox(m_field_object[fence5].transform.pos, { 60.0f,20.0f,5.0f });

	m_field_object[fence6].box_hit.CreateBox(m_field_object[fence6].transform.pos, { 60.0f,20.0f,5.0f });
	m_field_object[fence7].box_hit.CreateBox(m_field_object[fence7].transform.pos, { 60.0f,20.0f,5.0f });
	m_field_object[fence8].box_hit.CreateBox(m_field_object[fence8].transform.pos, { 60.0f,20.0f,5.0f });
	m_field_object[fence9].box_hit.CreateBox(m_field_object[fence9].transform.pos, { 60.0f,20.0f,5.0f });
	m_field_object[fence10].box_hit.CreateBox(m_field_object[fence10].transform.pos, { 60.0f,20.0f,5.0f });

	m_field_object[fence11].box_hit.CreateBox(m_field_object[fence11].transform.pos, { 5.0f,20.0f,60.0f });
	m_field_object[fence12].box_hit.CreateBox(m_field_object[fence12].transform.pos, { 5.0f,20.0f,60.0f });
	m_field_object[fence13].box_hit.CreateBox(m_field_object[fence13].transform.pos, { 5.0f,20.0f,60.0f });
	m_field_object[fence14].box_hit.CreateBox(m_field_object[fence14].transform.pos, { 5.0f,20.0f,60.0f });
	m_field_object[fence15].box_hit.CreateBox(m_field_object[fence15].transform.pos, { 5.0f,20.0f,60.0f });

	m_field_object[fence16].box_hit.CreateBox(m_field_object[fence16].transform.pos, { 5.0f,20.0f,60.0f });
	m_field_object[fence17].box_hit.CreateBox(m_field_object[fence17].transform.pos, { 5.0f,20.0f,60.0f });
	m_field_object[fence18].box_hit.CreateBox(m_field_object[fence18].transform.pos, { 5.0f,20.0f,60.0f });
	m_field_object[fence19].box_hit.CreateBox(m_field_object[fence19].transform.pos, { 5.0f,20.0f,60.0f });
	m_field_object[fence20].box_hit.CreateBox(m_field_object[fence20].transform.pos, { 5.0f,20.0f,60.0f });

}

//---------------------------------------------------------------------------
//	�΂̃I�u�W�F�N�g�̏����ݒ�
//---------------------------------------------------------------------------
void Field::StoneInit()
{
	// ���f���f�[�^�̓ǂݍ���
	m_field_object[stone1].model.LoadModel("Data/Field/object/stone/Stage_Obj002.mv1");
	// ���W�ݒ�
	m_field_object[stone1].transform.pos.set(-50.0f, 30.0f, 0.0f);

	// �����̐ݒ�
	m_field_object[stone1].transform.rot.set(0.0f, 0.0f, 0.0f);

	// �T�C�Y�̐ݒ�
	m_field_object[stone1].transform.scale.set(0.05f, 0.05f, 0.05f);

	// �����蔻��̐ݒ�
	m_field_object[stone1].box_hit.CreateBox(m_field_object[stone1].transform.pos, { 50.0f,20.0f,110.f });
}
