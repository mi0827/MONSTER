#pragma once



//! �L�����̍��W�A��]�A�X�P�[�����܂Ƃ߂�����
class Transform
{
public:
	Vector3 pos{ 0.0f,0.0f,0.0f };
	Vector3 rot{ 0.0f,0.0f,0.0f };
	Vector3 scale{ 0.1f,0.1f,0.1f };
	//! �R���X�g���N�^
	Transform();
	//! �f�X�g���N�^
	~Transform();
};
