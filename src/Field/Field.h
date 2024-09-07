#pragma once



//	Field(�t�B�[���h)�N���X
class Field 
{

	

	


private:
	//---------------
	// �萔
	//---------------
	const float MODEL_SIZE = 25.0f; // ���f���T�C�Y

public:
	// ���f���̕ۑ��ԍ�
	enum
	{
		// �؂̃��f���ԍ�
		tree1,
		tree2,
		tree3,

		// �t�F���X�̃��f���ԍ�
		fence1,
		fence2,
		fence3,
		fence4,
		fence5,
		fence6,
		fence7,
		fence8,
		fence9,
		fence10,
		fence11,
		fence12,
		fence13,
		fence14,
		fence15,
		fence16,
		fence17,
		fence18,
		fence19,
		fence20,

		// �΂̃��f���ԍ�
		stone1,


		MODEL_MAX
	};
	//---------------
	// �֐��̒�`
	//---------------
	// �R���X�g���N�^
	Field();	
	// �f�X�g���N�^
	~Field();

	
	
	
	
	//! @brief ��������
	void Init();             

	
	//! @brief �X�V����
	void Update();		     
	//! @brief �`�揈��
	void Draw();		     
	//! @brief �I������
	void Exit();		

	//! @brinf �I�u�W�F�N�g�̍��W�A�T�C�Y�̏����ݒ�
	void ObjectInit();    
	//! @brinf �؂̃I�u�W�F�N�g�̏����ݒ�֐�
	void TreeInit();
	//! @brinf �t�F���X�̃I�u�W�F�N�g�̏����ݒ�
	void FenceInit();
	//! @brinf �΂̃I�u�W�F�N�g�̏����ݒ�
	void StoneInit();

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
