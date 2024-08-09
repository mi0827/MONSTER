#pragma once

//! 
//! @fule CharacterBase.h
//! @brief �L�����N�^�[�̃x�[�X�N���X

class CharacterBase
{
public:

	//-----------------------------------------------
	//! �֐��̐錾
	//-----------------------------------------------
	//! @brief �R���X�g���N�^
	CharacterBase();

	//! @brief �f�X�g���N�^
	~CharacterBase();

	//! �������z�֐�
	//! @brief ��������
	virtual void Init() = 0;

	//! @brief �X�V����
	//! @param �J�����̌���
	virtual void Update(Vector3* camera_rot) = 0;

	//! @brief �L�����̕ǎC�蔻��p�̊֐�
	//! @param �L�����̍��W
	//! @param �L�����̓����O�̍��W
	//! @param �L�����̓����蔻��̃T�C�Y
	//! @param �����蔻�葊��̃{�b�N�X�̏��
	void MoveHitUpdate(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box);

	//! @brief �`�揈��
	virtual void Draw() = 0;

	//! @brief �I������
	virtual void Exit() = 0;

	//! @brief �����蔻��̍X�V����
	virtual void CDUpdate() = 0;

	//! @brief �X�e�[�^�X�o�[�̐ݒ�p�֐�
	virtual void Suatus_Bar_Init() = 0;
	//! @brief �X�e�[�^�X�o�[�̕`��֐�
	virtual void Status_Bar_Draw() = 0;

	//! @brief �x�[�X�N���X�ł̏�������
	//! @param �G�̈ړ��̍ۂɎg�����a�̐ݒ�
	void BaseInit(float r);



	//! @brief �x�[�X�N���X�ł̍X�V����
	//! @param �P�F�ړ����������łȂ����̃t���O
	//! @param �Q�F�J�����̌���
	//! @param �S�F�ړ��X�s�[�h
	//! @detail �ړ��Ɋւ�����̂̍X�V����
	void BaseUpdate(bool* m_check_move, Vector3* camera_rot, const float* mov_speed);


	//-----------------------------------------------
	//! �Q�[���p�b�h�̏���
	//-----------------------------------------------
	// �Q�[���p�b�h�p�̕ϐ�
	int m_pad_input = 0;

	PAD_NO m_pad_no = PAD_NO::PAD_NO1;				// ���Ԃ̃p�b�h���g���Ă���̂�
	// �Q�[���p�b�h�̔ԍ����Z�b�g����
	// DX���C�u�����[���ł̃p�b�h�̔ԍ����擾
	void SetPadNo(PAD_NO no, int dx_no)
	{
		m_pad_no = no;
		m_pad_input = dx_no;
	}
	// �Q�[���p�b�h�̔ԍ����Ƃ��Ă���
	PAD_NO GetPadNo() const
	{
		return m_pad_no;
	}

public:
	//-----------------------------------------------
	//! �N���X�̃I�u�W�F�N�g���`
	//-----------------------------------------------
	//! ���W�A�����A�T�C�Y
	Transform m_transform;
	//! �ړ�
	Move m_move;
	//! �ړ��̍ۂ̓����蔻��Ɏg��
	BoxCollision m_move_hit_box;
	//-----------------------------------------------
	//! �ϐ��̒�`
	//-----------------------------------------------
	//!  �Q�[���p�b�h�p�ړ��p�x�N�g���p�ϐ�
	Vector3 m_mov = { 0.0f,0.0f,0.0f };

	//! �G�Ƃ̈ړ������蔻��Ɏg��
	float m_hit_r = 0.0f;

};