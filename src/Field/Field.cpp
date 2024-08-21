#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/Base.h"
#include "src/Object/Object.h"
#include "src/Field/Field.h"


// �t�B�[���h�̃I�u�W�F�N�g��u�����W 
constexpr int MAP_W = 10;  // �c
constexpr int MAP_H = 10;  // ��

// 1���ǂO�������Ȃ�
// �t�B�[���h�̃I�u�W�F�N�g��u�����W�p�̓񎟌��z��
int MapData[MAP_H][MAP_W]
{
	{ 2,2,2,2,2,2,2,2,2,2},
	{ 2,0,0,0,0,0,0,0,0,2},
	{ 2,0,0,1,0,0,1,0,0,2},
	{ 2,0,0,0,0,0,0,0,0,2},
	{ 2,0,0,1,0,0,1,0,0,2},
	{ 2,0,0,0,0,0,0,0,0,2},
	{ 2,0,0,1,0,0,1,0,0,2},
	{ 2,0,0,0,0,0,0,0,0,2},
	{ 2,0,0,1,0,0,1,0,0,2},
	{ 2,2,2,2,2,2,2,2,2,2},
};
//	����������
Field::Field()
{
	//// �����Ńt�B�[���h���f���̓ǂݍ��݂�����
	//m_model = MV1LoadModel("Data/Model/Field/z.mv1");
	m_pos.set(0 + MODEL_SIZE* 15,0.0f, 0 + MODEL_SIZE * 15); // �`����W�̐ݒ�
	m_rot.clear(); // ��]�ʂ� 

	m_wall_obj_max = 0;
	m_model = 0;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void Field::Init()
{
	// �����Ńt�B�[���h���f���̓ǂݍ��݂�����
	m_model = MV1LoadModel("Data/Model/Field/Ground_2.mv1");
	m_obj_max = Field_Init();
	//wall_obj_max = Wall_Field_Init();
	// �I�u�W�F�N�g�̏����ݒ�
	for (int i = 0; i < m_obj_max; ++i)
	{
		// ������NEW����
		Object* object = new Object;
		// �ǉ��o�^(����ŃI�u�W�F�N�g�N���X�̔z�񂪑����Ă���)
		objects.push_back(object);
	}

	
	Field_Init();  // �t�B�[���h��ɃI�u�W�F�N�g�̒u������Ԃ�
	Object_Init(); // �I�u�W�F�N�g�̍��W�A�T�C�Y�̏����ݒ�
}

//---------------------------------------------------------------------------
// �t�B�[���h��ɃI�u�W�F�N�g�̒u������Ԃ�
//---------------------------------------------------------------------------
int Field::Field_Init()
{
	// ���̃I�u�W�F�N�g���K�v��������
	int object_count = 0;
	for (int h = 0; h < MAP_H; h++) 
	{
		for (int w = 0; w < MAP_W; w++) 
		{
			if (MapData[h][w] != 0) 
			{
				object_count++;
			}
		}
	}
	return object_count; // ���̃I�u�W�F�N�g���K�v���Ԃ�
}

//---------------------------------------------------------------------------
// �I�u�W�F�N�g�̍��W�A�T�C�Y�̏����ݒ�
//---------------------------------------------------------------------------
void Field::Object_Init()
{
	// ���߃I�u�W�F�N�g��������
	int object_count = 0;
	for (int h = 0; h < MAP_H; h++) 
	{
		for (int w = 0; w < MAP_W; w++)
		{
			if (MapData[h][w] == 1)
			{   // �t�B�[���h�̏�̒u��
				// �ŏ��̂O�ڂ�G�邽�߂ɏ�ɒu��
				objects[object_count]->Field_Object_Init(m_field_size, h, w);
				object_count++; // ���̕��̃J�E���g��i�߂Ă���
			}
			if (MapData[h][w] == 2)
			{   // ��
				// �ŏ���2�ڂ�G�邽�߂ɏ�ɒu��
				objects[object_count]->Field_Wall_Object_Init(m_wall_size, h, w);
				object_count++; // ���̕��̃J�E���g��i�߂Ă�
			}
		}
	}

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
	// �t�B�[���h���f���̕`����W
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
	// �t�B�[���h�̉�]
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y), TO_RADIAN(m_rot.z)));
	// ���f���̑傫��
	MV1SetScale(m_model, VGet(MODEL_SIZE, MODEL_SIZE, MODEL_SIZE));
	// ���f���̕`��
	MV1DrawModel(m_model);

	for (int i = 0; i < m_obj_max; i++) 
	{
		objects[i]->Draw();
	}
}

//---------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------
void Field::Exit()
{
	// ���f���f�[�^�̍폜
	MV1DeleteModel(m_model);

	// �I�u�W�F�N�g�̔z��̉��
	objects.clear();
	m_wall_objects.clear();
}
