#pragma once

/**
* @file Move.h
* @ brief �L�����̈ړ��p�̃N���X
*/
class Move
{
public:

	Move();
	~Move();

	//!
	//! @fn
	//! @brief �X�V����
	//! @param �������Ă������̕ϐ�
	//! @param �J�����̌���
	//! @param �v���C���[�̌����Ă������
	//! @param �ړ��X�s�[�h
	//! @param �v���C���[�̍��W
	//! @param �p�b�h�̔ԍ�
	//! @param �X�e�B�b�N�̒l
	//! @detail �ړ��Ɋւ�����̂̍X�V����
	//! 
	void Update(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed, Vector3* player_pos, PAD_NO m_pad_no, Vector3 m_mov);

	//!
	//! @fn
	//! @brief �ړ��Ɋւ��铖���蔻��p�̊֐�
	//! @param ���� (�L����) �̍��W(���̍��W)
	//! @param �����i�L�����j�̍��W(�����蔻��O��)
	//! @param �����i�L�����j�̓����蔻��̃T�C�Y�i���S���猩���T�C�Y�j
	//! @param �����蔻����Ƃ肽���{�b�N�X�̏��
	//! @detail �ړ��̕ǎC��p�֐�
	void Move_Hit(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box);

	//! 
	//! @brief �ړ��Ɋւ��铖�Ă蔻��p�̊֐�
	// !@param ���� (�L����) �̍��W(���̍��W)
	//! @param �����i�L�����j�̍��W(�����蔻��O��)
	//! @param �����i�L�����j�̓����蔻��̃T�C�Y�i���S���猩���T�C�Y�j
	//! @param �����蔻����Ƃ肽���{�b�N�X�̏��
	//! @detail �ړ��̕ǎC��p�֐�
	void Move_Hit_Capsule(Vector3* player_pos, float r, CapsuleCollision* capsule);
	
	//! @fn
	//! @brief �Q�[���p�b�h�ł̈ړ��p�֐�
	//! @param �����Ă����̂��̕ϐ�
	//! @param �X�e�B�b�N�̒l
	//! @param �L�����̌����Ă������
	//! @param �L�����̍��W
	//! @param �ړ��X�s�[�h
	//! @detail �Q�[���p�b�h�ł̈ړ��p�֐�
	//! 
	void Move_GamePad(bool* m_check_move, Vector3* mov, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);

	//!
	//! @fn
	//! @brief �J�����̕����ɑ΂��Đ^�������ւ̈ړ��p�֐�
	//! @param �����Ă����̂��̕ϐ�
	//! @param �J�����̌���
	//! @param �L�����̌����Ă������
	//! @param �L�����̍��W
	//! @param �ړ��X�s�[�h
	//! @detail �J�����̕����ɑ΂��Đ^�������̈ړ��p�֐�
	//! 
	void Move_Front(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);

	//!
	//! @fn
	//! @brief �J�����̕����ɑ΂��Ĕ��΂ւ̈ړ��p�֐�
	//! @param �����Ă����̂��̕ϐ�
	//! @param �J�����̌���
	//! @param �L�����̌����Ă������
	//! @param �ړ��X�s�[�h
	//! @detail �J�����̕����ɑ΂��Ĕ��΂̈ړ��p�֐�
	//! 
	void Move_Dhindo(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


	//! 
	//! @fn
	//! @brief �J�����̕����ɑ΂��č��ւ̈ړ��p�֐�
	//! @param �����Ă����̂��̕ϐ�
	//! @param �J�����̌���
	//! @param �L�����̌����Ă������
	//! @param �ړ��X�s�[�h
	//! @detail �J�����̕����ɑ΂��č��ւ̈ړ��p�֐�
	//! 
	void Move_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


	//!
	//! @fn
	//! @brief �J�����̕����ɑ΂��ĉE�ւ̈ړ��p�֐�
	//! @param �����Ă����̂��̕ϐ�
	//! @param �J�����̌���
	//! @param �L�����̌����Ă������
	//! @param �ړ��X�s�[�h
	//! @detail �J�����̕����ɑ΂��ĉE�ւ̈ړ��p�֐�
	//! 
	void Move_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


	//! @fn
	//! @brief �J�����̕����ɑ΂��ĉE�΂ߏ�ւ̈ړ��p�֐�
	//! @param �����Ă����̂��̕ϐ�
	//! @param �J�����̌���
	//! @param �L�����̌����Ă������
	//! @param �ړ��X�s�[�h
	//! @detail �J�����̕����ɑ΂��ĉE�΂ߏ�ւ̈ړ��p�֐�
	void Move_Diagonally_Up_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);

	//! @fn
	//! @brief �J�����̕����ɑ΂��č��΂ߏ�ւ̈ړ��p�֐�
	//! @param �P�F�����Ă����̂��̕ϐ�
	//! @param �Q�F�J�����̌���
	//! @param �R�F�L�����̌����Ă������
	//! @param �S�F�ړ��X�s�[�h
	//! @detail �J�����̕����ɑ΂��č��΂ߏ�ւ̈ړ��p�֐�
	void Move_Diagonally_Up_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);

	//! @brief �J�����̕����ɑ΂��ĉE�΂߉��ւ̈ړ��p�֐�
	//! @param �����Ă����̂��̕ϐ�
	//! @param �J�����̌���
	//! @param �L�����̌����Ă������
	//! @param �ړ��X�s�[�h
	//! @detail �J�����̕����ɑ΂��ĉE�΂߉��ւ̈ړ��p�֐�
	void Move_Oblique_Lower_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);


	//! @brief �J�����̕����ɑ΂��č��΂߉��ւ̈ړ��p�֐�
	//! @param �����Ă����̂��̕ϐ�
	//! @param �J�����̌���
	//! @param �L�����̌����Ă������
	//! @param �ړ��X�s�[�h
	//! @detail �J�����̕����ɑ΂��č��΂߉��ւ̈ړ��p�֐�
	void Move_Oblique_Lower_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed);

public:
	////! �v���C���[�̍��W�����Ă�������
	//Vector3 m_player_pos = { 0.0f,0.0f,0.0f };

	////! �v���C���[�̈ړ��X�s�[�h�����Ă�������
	//// static const float player_mov_speed;

	////! �v���C���[�̌��������Ă�������
	//Vector3 m_player_rot = { 0.0f,0.0f,0.0f };

	////! �J�����̌��������Ă�������
	//Vector3 m_camera_rot = { 0.0f,0.0f,0.0f };
};