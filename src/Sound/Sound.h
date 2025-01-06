#pragma once
//! @file Sound.h
//! @brief �T�E���h�֘A�̃N���X
class Sound
{
public:
	//! @brief �R���X�g���N�^
	Sound();
	//! @brief �f�X�g���N�^
	~Sound();

	//! @brief �T�E���h���̔z������֐�
	//! @param �T�E���h�̐��̍ő吔
	void NewArraySecureSound(int sound_max);

	//! @brief �T�E���h�̓ǂݍ���
	//! @param �T�E���h�f�[�^�̃p�X
	//! @param �T�E���h�̔ԍ�
	void LoadSound(const char path[256], int no);

	//! @brief �T�E���h�̍Đ�
	//! @param �T�E���h�̔ԍ�
	//! @param �Đ�����^�C�v
	//! DX_PLAYTYPE_NORMAL�@:�@�m�[�}���Đ�
    //! DX_PLAYTYPE_BACK�@�@ : �o�b�N�O���E���h�Đ�
    //! DX_PLAYTYPE_LOOP�@�@ : ���[�v�Đ�
	//! @param �Đ������[�v���邩�ǂ���
	void PlaySound_(int no, int type, bool loop);

	//! @brief �T�E���h���Đ������ǂ�����Ԃ�
	//! @return true�F�Đ����Afalse�F��~��
    bool PlayingSound();

	//! �w��̃T�E���h���Đ������ǂ�����Ԃ�
	//! @param �Đ��������ׂ���SE�ԍ�
	//! @return true�F�Đ����Afalse�F��~��
	bool PickPlayingSound(int num);

	//! @brief �T�E���h�̃{�����[�������p�̊֐�
	//! @param �ݒ肵�����{�����[��
	void SetSoundVolume(int volume);

	//! @brief �Đ����̃T�E���h���~�߂�
	void StopSound();

private:
	//! �T�E���h�̓��ꕨ
	std::vector<int>m_sound_handle;
	//! �T�E���h�̍ő吔��ۑ�����
	int m_sound_max;
	//! ���ݍĐ����̃T�E���h�ԍ�
	int m_now_playing_se_num;

public:
	//! ���ݍĐ��\��ԉ��𔻒f���邽�߂̃t���O
	bool m_playing_flag = true;
};