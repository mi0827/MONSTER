#pragma once



//	Field(�t�B�[���h)�N���X
// Base�N���X���p��
class Field : public Base
{
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
public:
	//---------------
	// �}�b�v���̐ݒ�
	//---------------
	
	// ��̃}�X�̑傫��
	const int m_field_size = 70;   // �T�C�Y
	const int m_wall_size = 70 ;
	// �u���p�̃I�u�W�F�N�g
	std::vector<Object*> objects;  // �I�u�W�F�N�g�N���X�^�̃|�C���^���͂��Ă�@
	int m_obj_max = 0;               // �I�u�W�F�N�g�̐�

	// ����̕�
	std::vector<Object*> m_wall_objects;  // �I�u�W�F�N�g�N���X�^�̃|�C���^���͂��Ă�
	int m_wall_obj_max = 0;                   // �I�u�W�F�N�g�̐�
private:
	int m_model = 0; // ���f���p�̕ϐ�

};
