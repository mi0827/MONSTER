#pragma once



//	Field(�t�B�[���h)�N���X
class Field 
{

	// ���f���̕ۑ��ԍ�
	enum
	{
		// �؂̃��f���ԍ�
		tree1,
		/*tree2,
		tree3,*/
		// �t�F���X�̃��f���ԍ�
		fence1,

		// �΂̃��f���ԍ�
		stone1,


		MODEL_MAX
	};

	//---------------
	// �萔
	//---------------


private:

	const float MODEL_SIZE = 25.0f; // ���f���T�C�Y

public:
	//---------------
	// �֐��̒�`
	//---------------
	// �R���X�g���N�^
	Field();	//	����������
	void Init();             //�@��������
	int  Field_Init();       // �t�B�[���h��ɃI�u�W�F�N�g�̒u������Ԃ��֐�
	void Object_Init();      // �I�u�W�F�N�g�̍��W�A�T�C�Y�̏����ݒ�
	void Update();		     //	�X�V����
	void Draw();		     //	�`�揈��
	void Exit();		     //	�I������

	//---------------
	// �ϐ��̒�`
	//---------------

	//--------------- 
	// �e�N���X�̃I�u�W�F�N�g�̍쐬
	//---------------
	// �t�B�[���h�̃I�u�W�F�N�g
	struct field
	{
		Model model;
		Transform transform;
		// �����蔻��p�̃{�b�N�X
		BoxCollision box_hit;
	};
	// �u�����I�u�W�F�N�g�̐����p�ӂ���
	field m_field_object[MODEL_MAX];

	//�t�B�[���h���f���̓��ꕨ
	Model m_field_model;
	Transform m_field_transform;
};
