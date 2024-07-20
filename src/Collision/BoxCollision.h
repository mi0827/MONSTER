#pragma once
//! @fule BoxCollision.h
//! @brief �{�b�N�X�R���|�l���g�̃N���X 


class BoxCollision
{
public:
	//! @brief �R���X�g���N�^
	BoxCollision();
	//! @brief �f�X�g���N�^
	~BoxCollision();

	//! @brief �{�b�N�X��`�悷��֐�
	void Draw(int color, int line_color);

	//! @biref �{�b�N�X�����֐�
	//! 
	void CreateBox(Vector3 pos, Vector3 size);

	void SetPos(Vector3 pos);

	void SetSize(Vector3 size);

public:
	// �{�b�N�X�̊�{�I�ȏ��
	struct Box
	{
		Vector3 pos1 = { 0.0f,0.0f,0.0f };          //!< ���W�P
		Vector3 pos2 = { 0.0f,0.0f,0.0f };		   //!< ���W�Q
		Vector3 size = { 0.0f ,0.0f,0.0f };		   //!< �{�b�N�X�̃T�C�Y

		// �����蔻��̓{�b�N�X�̐^�񒆂��甼���̃T�C�Y�����炵�Ĕ�����Ƃ�
		Vector3 half_size = { 0.0f ,0.0f,0.0f };   //!< �����蔻��Ŏg�����߂ɔ����̃T�C�Y
		Vector3 hit_pos= { 0.0f ,0.0f,0.0f };	   //!< �����蔻��p�̍��W
	
		int   color = 0;         // �����̂̐F
		int   line_color = 0;         // ���C���̐F
	};
	Box m_box;
};