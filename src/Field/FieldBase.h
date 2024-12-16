#pragma once

//! @file FieldBase.h
//! @brief �t�B�[���h�̃x�[�X�N���X
class FieldBase
{
public:
	//! @brief ��������
	virtual void Init() = 0;

	//! @brief �X�V����
	virtual void Update() = 0;

	//! @brief �`�揈��
	virtual void Draw() = 0;

	//! @brief �I������
	virtual void Exit() = 0;


	//! @brinf �I�u�W�F�N�g�̍��W�A�T�C�Y�̏����ݒ�
	virtual void ObjectInit() = 0;


	//�t�B�[���h���f���̓��ꕨ
	Model m_field_model;
	Transform m_field_transform;

};