#pragma once
//! @file Transform.h
//! @brief �L�����̍��W�A��]�A�X�P�[�����܂Ƃ߂�����
class Transform
{
public:
	//! ���W
	Vector3 pos{ 0.0f,0.0f,0.0f };
	//! ����
	Vector3 rot{ 0.0f,0.0f,0.0f };
	//! �傫��
	Vector3 scale{ 0.1f,0.1f,0.1f };

	/*MATRIX mat_player;
	mat_player.m[0][0];*/

	//! �R���X�g���N�^
	Transform();
	//! �f�X�g���N�^
	~Transform();
};
