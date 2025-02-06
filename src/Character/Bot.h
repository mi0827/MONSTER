#pragma once

//! @file Bot.h
//! @brief bot�N���X
class Bot
{
public:
	//! @brief �R���X�g���N�^
	Bot();
	//! @brief �f�X�g���N�^
	~Bot();
	
	//! @brief ����������
	void Init();

	//! @brief �X�V����
	void Update();

	//! @brief �`�揈��
	void Draw();

	//! @brief �I������
	void Exit();


public:
	//! �{�b�g�̓����蔻��
	CapsuleCollision m_body;

private:
	/*���̃V�[���ŕʂŖ؂̃��f����ǂݍ��ނ�
	���̃��f���Ƀ����X�^�[�Ƃ���Ȃ��悤�ȓ����蔻����Ƃ�
	�U�������������瓖�������G�t�F�N�g���o��*/

	//! Transform
	Transform m_transform;
	//! �{�b�g���f��
	Model m_bot_model;
	//! �{�b�g�̃G�t�F�N�g
	Effect m_bot_effect;
	//! �G�t�F�N�g�̐�
	static constexpr int EFFECT_MAX = 1;
	
	//! SE
	Sound m_se;
	//! SE�̐�
	static constexpr int SE_MAX = 1;

};

