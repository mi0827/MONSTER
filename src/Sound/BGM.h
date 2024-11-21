#pragma once

// BGM�֌W�̃N���X
class BGM
{
public:
	// �f�X�g���N�^
	~BGM();

	// BGM���̔z������
	// ����
	// �P�FBGM�̐�
	void BGMContainerNew(int size);

	// BGM�̓ǂݍ���
	// ����
	// �P�F�Đ�����f�[�^�̏��
	void LoadBGM(const char name[256], int No);

	// BGM�̍Đ�
	// ����
	// �P�F�ǂ̃^�C�v�ōĐ������邩
	// �Đ��`��
	// DX_PLAYTYPE_NORMAL�@:�@�m�[�}���Đ�
	// DX_PLAYTYPE_BACK�@�@ : �o�b�N�O���E���h�Đ�
	// DX_PLAYTYPE_LOOP�@�@ : ���[�v�Đ�
	// �Q�F�Đ���Đ��ʒu���f�[�^�̐擪�Ɉړ����邩�ǂ���
	// �R�F���Ԗڂ�BGM���Đ����邩
	void PlayBGM( int type, bool loop, int No);

	// BGM�̃{�����[�������p�̊֐�
	// ����
	// �P�F�{�����[���̑傫��
	// �Q�FBGM�̐�
	void BGMChangeVolume(int bgm_volume/*, int size*/);

	// BGM���~�߂�
	// ����
	// �P�F�ǂ�BGM��
	void StopBGM(int No);

	// BGN���Đ�������Ԃ��֐�
	// �Đ��������ׂ�(�A���Ă��镨)
	// �Đ���          �F  �P�Ftrue
	// �Đ�����Ă��Ȃ��F  �O�Ffalse
	// �G���[          �F�|�P
	bool PlayingBGM(int No);

	// BGM�̃f���[�g�i�z��̉���j
	void BGMDelete();
public:
	//! BGM�̓��ꕨ�p�ϐ�
	int* m_bgm_container = 0; 

	//! BGM����ۑ�
	int m_bgm_size;
};