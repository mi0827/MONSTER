#pragma once

// ���ʉ��p�̃N���X
class SE
{
public:
	// �f�X�g���N�^
	~SE();

	// SE���̔z������
	// ����
	// �P�FSE�̐�
	void SE_ContainerNew(int size); 

	// SE�̓ǂݍ���
	// ����
	// �P�F�Đ�����f�[�^�̏��
	// �Q�F�z��̉��Ԗڂɓǂݍ��ނ�
	void Load_SE(const char name[256], int No);
	
	// SE�̍Đ�
	// ����
	// �P�F�z��̉��Ԗڂ�SE���g����
	// �Q�F�ǂ̃^�C�v�̍Đ������邩
	// �Đ��`��
    // DX_PLAYTYPE_NORMAL�@:�@�m�[�}���Đ�
    // DX_PLAYTYPE_BACK�@�@ : �o�b�N�O���E���h�Đ�
    // DX_PLAYTYPE_LOOP�@�@ : ���[�v�Đ�
	// �R�F�Đ���Đ��ʒu���f�[�^�̐擪�Ɉړ����邩�ǂ���
	void Play_SE(int No, int type, bool loop);

	// SE�̃{�����[�������p�̊֐�
	// ����
	// �P�F�{�����[���̑傫��
	// �Q�FSE�̐�
	void SE_ChangeVolume(int se_volume,int size);

	// SE���Đ�������Ԃ��֐�
	// ����
	// �P�F�z��̉��Ԗڂ�SE�𒲂ׂ邩
	// �Đ��������ׂ�(�A���Ă��镨)
	// �Đ���          �F  �P�Ftrue
	// �Đ�����Ă��Ȃ��F  �O�Ffalse
	// �G���[          �F�|�P
	bool Playing_SE(int No);

	// SE�̃f���[�g�i�z��̉���j
	void SE_Delete();
	
public:

	int* m_se_container; // SE�̓��ꕨ�p�̔z��
};