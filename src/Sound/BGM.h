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
	void BGM_ContainerNew(int size);

	// BGM�̓ǂݍ���
	// ����
	// �P�F�Đ�����f�[�^�̏��
	void Load_BGM(const char name[256], int No);

	// BGM�̍Đ�
	// ����
	// �P�F�ǂ̃^�C�v�ōĐ������邩
	// �Đ��`��
	// DX_PLAYTYPE_NORMAL�@:�@�m�[�}���Đ�
	// DX_PLAYTYPE_BACK�@�@ : �o�b�N�O���E���h�Đ�
	// DX_PLAYTYPE_LOOP�@�@ : ���[�v�Đ�
	// �Q�F�Đ���Đ��ʒu���f�[�^�̐擪�Ɉړ����邩�ǂ���
	// �R�F���Ԗڂ�BGM���Đ����邩
	void Play_BGM( int type, bool loop, int No);

	// BGM�̃{�����[�������p�̊֐�
	// ����
	// �P�F�{�����[���̑傫��
	// �Q�FBGM�̐�
	void BGM_ChangeVolume(int bgm_volume, int size);

	// BGM���~�߂�
	// ����
	// �P�F�ǂ�BGM��
	void Stop_BGM(int No);

	// BGN���Đ�������Ԃ��֐�
	// �Đ��������ׂ�(�A���Ă��镨)
	// �Đ���          �F  �P�Ftrue
	// �Đ�����Ă��Ȃ��F  �O�Ffalse
	// �G���[          �F�|�P
	bool Playing_BGM(int No);

	// BGM�̃f���[�g�i�z��̉���j
	void BGM_Delete();
public:
	int* m_bgm_container = 0; // BGM�̓��ꕨ�p�ϐ�
};