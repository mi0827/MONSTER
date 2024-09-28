#pragma once
// #include "Character_Base.h"


class GameScene :public Scene_Base
{
public:



	//! @brief �R���X�g���N�^
	GameScene();
	//! @brief �f�X�g���N�^
	~GameScene();

	//! �Q�[���V�[���ɂ����g����������
	void GameSceneInit();

	//! @brief ��������
	void Init()override;

	//! @brief �X�V����
	//! @param BGM�̉���
	//! @param SE�̉���
	void Update()override;

	// �o�g���̍X�V����
	void GameUpdate();
	// �o�g����ʂ��I������Ƃ��̏���
	void EndUpdate();

	//! @brief  �`�揈��
	void Draw()override;

	//! @brief �I������
	void Exit()override;

	//! @brief �X�e�[�^�X�o�[�̕`��
	void StatusDraw();

	// �����_�ŕK�v���킩��Ȃ�
	//// SE�̏�����
	//void SE_Init();
	//// BGM�̏�����
	//void BGM_Init();

	// ���C�g�̏�����
	void LightInit();

	//! @brief �t�B�[���h�ƃL�����N�^�[�Ƃ̓����蔻��
	void HitField()override;

	//! @brief �L�����N�^�[�̏�������
	void Character_Init();

	//! @brief �L�����N�^�[�̍X�V����
	void CharacterUpdate();

	//! @brief �L�����N�^�[�̍U���Ɋւ��Ă̍X�V����
	void AttackUpdate();

	//! @brief ���s���t�����炻���m�点�郁�b�Z�[�W��`�悷�邽�߂̊֐�
	void VDMessage();

	// �^�C�}�[�̍X�V����
	// @param ���Ԃ��J�E���g���邽�߂̂���
	//void Time_Update(int& time_count);
	// �^�C�}�[�̕`��
	//void Time_Draw();
	// �`���[�g���A���ł̕`�揈��
	// void Tutorial_Draw();
	// ����������`�悳���邾���̊֐�
	//void Ready_Draw();
	// �G���h�ł̕`�揈��
	//void End_Draw();
	// �U���̂����蔻����s���֐�
	//void Attack_Hit(int player1, int player2);
	// �K�[�h�̓����蔻��
	// void Block_Hit(int player1, int player2);
	// �L�����N�^�[�̃X�e�[�^�X�`�揈��
	// void Draw_Status();
	// �Q�[���V�[��
	//enum play_scene
	//{
	//	Play_Tutorial, // �`���[�g���A���V�[��
	//	Play_Main,     // �Q�[�����C���V�[��
	//	Play_End,      // �v���CEND�V�[��
	//	Play_Max       // �v���C�V�[���̍ő�
	//};
	// SE
	//enum play_se
	//{
	//	READY, // �`���[�g���A���̏�������
	//	SE_MAX // SE�̍ő吔
	//};
	// BGM
	//enum BGM
	//{
	//	TUTORIAL_BGM,  // �`���[�g���A����BGM
	//	BATTLE_1_BGM,  // �v���C���C����BGM�P
	//	BATTLE_2_BGM,  // �v���C���C����BGM�Q
	//	BATTLE_3_BGM,  // �v���C���C����BGM�R
	//	BGM_MAX        // BGM�̍ő吔
	//};
public:

	//! �J�����N���X�̃I�u�W�F�N�g
	Camera camera;

	//! �v���C���[�L�����p�̃I�u�W�F�N�g
	CharacterBase* player;

	//! �����X�^�[�p�̃I�u�W�F�N�g
	MonsterBase* monster;

	//! �U���A�N�V�����̓����蔻��p�̃I�u�W�F�N�g
	Attack player_attack_hit;
	Attack monster_attack_hit;

	// �t�B�[���h�I�u�W�F�N�g
	Field field;

	// �q�b�g�X�g�b�v�p�̃I�u�W�F�N�g
	HitStop hit_stop;
	
	//=================
	// �J�����̉�]�Ɋւ��Ă̕ϐ�
	//! �J�����̈ړ��X�s�[�h
	static constexpr float CAMERA_ROT_SPEED = 2.0f;
	//! �J�����̉�]�������
	static constexpr int CAMERA_DIRECTIN_RIGHT = 0; // �E��]
	static constexpr int CAMERA_DIRECTIN_FLET = 1;   // ����]
	// �ǂ��炪���񂾂����킩��₷���Ǘ�
	enum Ditection
	{
		player_die,     // �v���C���[�����񂾂Ƃ� , ����
		monster_die,  // �����X�^�[�����񂾂Ƃ� , ����

		max,
	};
	// �N�����񂾂���ۑ����邽�߂̂���
	int m_who_died;


	//==========================
	// �o�g���V�[���������łȂ����Ɋւ��Ă̕ϐ�
	// �ǂ̃V�[�������킩��₷���ۑ�
	enum WhatScene
	{
		battle, // �o�g�����
		result, // �o�g�����I�������̏��
	};
	//! �ǂ̃o�g���V�[������ۑ����邽�߂̂���
	int m_what_scene = battle; //!< �ŏ��̓o�g���V�[������n�߂�(����ύX�\��)
	//! ��b������̃t���[���̐�
	static constexpr int ONE_SECOND_FLAME = 60;
	int m_count_flame = 0; // �t���[���J�E���g�p�̕ϐ� 
	int m_count_time = 0;  // �t���[��������ۂ̎��Ԃ�����o���ē����p�̎���


	// �o�g�����I����Ă���ǂꂭ�炢�̎��ԂŎ��̃V�[���Ɉړ����邩�̎���
	static constexpr int CHANGE_TIME = 5;

	//================================
	//  �o�g�����I�������ɕ`�悷�郁�b�Z�[�W�Ɋւ���ϐ�
	struct Message
	{
		//! ���b�Z�[�W������ϐ�
		const char* message;
	};
	Message m_massage[max]
	{
		{ "QUEST : FAILED"}, // ���s
		{ "QUEST : CLEAR" } // �N���A
		
	};
	//! ���b�Z�[�W�̕`����W
	Vector2 m_massage_pos{ 0.0f,0.0f };


};