#pragma once

//---------------------------------------------------------------------------------
//	�J�����N���X
// Base�N���X���p��
class Camera
{
public:
	//---------------
	// �֐��̒�`
	//---------------
	// �R���X�g���N�^
	Camera();

	void Init();        //�@��������

	void PlayField_Init(); // �v���C��ʂ̏����ݒ�

	// �v���C���[�̏����󂯎��`�ɂ��܂�
	// ����̓v���C���[�̂����ɃJ�������������̏o
	// �v���C���[�̍��W�ƌ������󂯎���悤�ɂ��܂�
	void Update(Vector3* player_pos); // �X�V����
	void Hit_Object(Vector3* obj_pos, Vector3* obj_size); // �J�������ǂɖ��܂�Ȃ��悤�ɂ���
	void Draw_Set();                  // �`�揈���̑O�ɃJ�����A��ʂ̃Z�b�g
	void Draw();		              // �揈��
	void Exit();		              // �I������

	//---------------
	// �ϐ��̒�`
	//---------------
public:
	// �J������������W
	Vector3 m_look;
	// �J�����̍��W
	Vector3 m_pos;
	// �J�����̌���
	Vector3 m_rot;
public:
	//--------------------
	// ��ʕ����p�̕ϐ�
	int m_screen_field = 0;   // �`�悷���ʂ�����摜�p�ϐ�
	Vector2 m_field_pos = { 0.0f, 0.0f };  // �`�悷����W
	Vector2 m_field_size = { 0.0f, 0.0f, }; // �`�悷��T�C�Y

private:
	// �}�E�X�̈ړ��ʗp�̕ϐ�
	float m_mouse_move_x = 0.0f; // X���W�̈ړ���
	float m_mouse_move_y = 0.0f; // Y���W�̈ړ���
	Vector3 m_before_pos = { 0.0f,0.0f,0.0f };   // ���t���[���ړ��O�̍��W�������p�̕ϐ�
	Vector3 m_hit_box_size = { 0.0f,0.0f,0.0f }; // �ǂƂ̓����蔻��p�̕ϐ�
public:
	int pad_no = 0;				// ���Ԃ̃p�b�h���g���Ă���̂�
	void SetPadNo(int no)
	{
		pad_no = no;
	}


	
};
