#pragma once
//! @file Effect.h
//! @brief �G�t�F�N�g�p�̃N���X
class Effect
{
public:
	//! @brief �R���X�g���N�^
	Effect();
	//! @brief �f�X�g���N�^
	~Effect();

	//! @brief �G�t�F�N�g�p�̔z��ϐ��̊m�ۊ֐�
	//! @param �G�t�F�N�g�̍ő��
	//! @param �G�t�F�N�g�����Ă����p�̕ϐ�
	//! @param �G�t�F�N�g���g�����Ɏg���n���h���p�̕ϐ�
	void EffectNew(int Effect_MAX, int* effect_container, int* m_effect_handle);


	//! @brief �G�t�F�N�g�p�̕ϐ�delete�p�̊֐�
	//! @param �G�t�F�N�g�����Ă����p�̕ϐ�
	//! @param �G�t�F�N�g���g�����Ɏg���n���h���p�̕ϐ�
	void EffectDelete(int* effect_container, int* effect_handle);

	//! @brief �G�t�F�N�g���Đ�
	//! @param �Đ��������G�t�F�N�g�ԍ�
	//! @param �G�t�F�N�g�̍��W
	//! @param �G�t�F�N�g�̌���

	//! @brief �G�t�F�N�g�̍��W��ݒ�
	//! @param �ݒ肵�������W

	//! @brief �G�t�F�N�g�̍��W(���炵������)��ݒ�
	//! @param ���炵�������̍��W
	
	//! @brief �G�t�F�N�g�̌����̐ݒ�
	
	//! @brief �m�ۂ����G�t�F�N�g���J������֐�

private:
	//! �G�t�F�N�g��ۑ�����p�̕ϐ�
	std::vector<int>m_effect_handle;
};
