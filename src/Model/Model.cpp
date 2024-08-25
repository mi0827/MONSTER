#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"
#include "Model.h"

//-----------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------
Model::Model()
{
	m_model = 0;
}

//-----------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------
Model::~Model()
{
	// ���f���f�[�^�̍폜
	MV1DeleteModel(m_model);
}

//-----------------------------------------------
// ���f���ǂݍ��݊֐�
//-----------------------------------------------
void Model::LoadModel(const char data[256])
{
	// ���f���̓ǂݍ���
	m_model = MV1LoadModel(data);

}

//-----------------------------------------------
// �`��p�֐�
//-----------------------------------------------
void Model::DrawModel(Transform *transform)
{
	// ���f���̃T�C�Y�̒���
	m_transform = *transform;
	//m_transform.scale.set(0.1f, 0.1f, 0.1f);
	//m_transform.scale.set(1.0f, 1.0f, 1.0f);

	MV1SetPosition(m_model, VGet(m_transform.pos.x, m_transform.pos.y, m_transform.pos.z)); // �`�悷��v���C���[���f���̍��W�̐ݒ�
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_transform.rot.x), TO_RADIAN(m_transform.rot.y + 180), TO_RADIAN(m_transform.rot.z))); // ���f���̉�]
	MV1SetScale(m_model, m_transform.scale.VGet()); // ���f���̑傫��(10���̂P�̃T�C�Y)
	MV1DrawModel(m_model); // ���f���̕`��

}

//-----------------------------------------------
// ���f���̍��W��������Ă���p�֐�
//-----------------------------------------------
Vector3 Model::GetModelPos()
{
	return m_transform.pos;
}

//-----------------------------------------------
// ���f���̍��W���Z�b�g����p�֐�
//-----------------------------------------------
void Model::SetModelPos(Vector3 pos)
{
	m_transform.pos.set(pos);
}

//-----------------------------------------------
// ���f���̌��������炤�p�֐�
//-----------------------------------------------
Vector3 Model::GetModelRot(Vector3 rot)
{
	return m_transform.rot;
}

//-----------------------------------------------
// ���f���Ɍ������Z�b�g���邽�ߗp�֐�
//-----------------------------------------------
void Model::SetModelRot(Vector3 rot)
{
	m_transform.rot.set(rot);
}

//-----------------------------------------------
// ���f���̃X�P�[����ύX���邽�߂̊֐�
//-----------------------------------------------
void Model::SetModelScale(Vector3 scale)
{
	m_transform.scale.set(scale);
}

// ---------------------------------------------- -
//-----------------------------------------------
Vector3 Model::GetNodePos(int node_index)
{
	Vector3 pos;
	// �w�肵���m�[�h�̍��W������Ă���
	pos = MV1GetFramePosition(m_model, node_index);

	return pos;
}