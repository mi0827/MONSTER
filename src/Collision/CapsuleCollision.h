#pragma once

//! @fule CapsuleCollision.h
//! @brief �J�v�Z���R���|�[�l���g�̃N���X


class CapsuleCollision
{
public:
	//! @brief �R���X�g���N�^
	CapsuleCollision();
	//! @brief �f�X�g���N�^
	~CapsuleCollision();

	//! @brief �J�v�Z����`�悷��֐�
	void Draw();

	//! @brief ���f���̃m�[�h�̈ʒu�ɃJ�v�Z��������֐�
	//! @param ���f���N���X
	//! @param ���f���̂��������W�ԍ�
	//! @param ���f���̂��������W�ԍ�2
	//! @param ���a�̑傫��
	void CreateNodoCapsule(Model* model, int node_index , int node_index2, float radius = 1);

	//! @brief �J�v�Z�������֐�
	//! @param �Z�b�g���������W(Vector3)
	//! @param �Z�b�g���������W�Q(Vector3)
	//! @param �Z�b�g���������a
	void CreateCapsule(Vector3 pos, Vector3 pos2, float radius=1);

	//! @brief �J�v�Z���̂�����̍��W�����f���̃m�[�h����������Ă���
	//! @param ���f���̏��
	//! @param �m�[�h�̃C���f�b�N�X
	//! @param ���a
	void NodoSetSize(Model* model, int node_index, float radius);

	//! @brief �J�v�Z���̃T�C�Y��ݒ肷��֐�
	//! @param �ݒ肵�����T�C�Y(Vector3)
	//! @param ���a(float)
	void SetSize(Vector3 pos, float radius);


public:
	// �J�v�Z���̊�{�I���
	struct Capsule
	{
		Vector3 pos1 = { 0.0f, 0.0f, 0.0f }; //!< �J�v�Z���̍��W�P
		Vector3 pos2 = { 0.0f, 0.0f, 0.0f }; //!< �J�v�Z���̍��W�Q
		float radius = 0.0f;             //!< �J�v�Z���̔��a
	};
	Capsule m_capsule;
};
