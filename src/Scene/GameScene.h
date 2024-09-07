#pragma once
// #include "Character_Base.h"


class GameScene :public Scene_Base
{
public:

	


	GameScene();
	 ~GameScene();

	 //! �Q�[���V�[���ɂ����g����������
	 void GameSceneInit();

	

	 //! @brief ��������
	void Init()override;

	//! @brief �X�V����
	//! @param BGM�̉���
	//! @param SE�̉���
	void Update(int bgm_volume, int se_volume)override;

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
	void HitField();
	
	//! @brief �L�����N�^�[�̏�������
	void Character_Init();

	//! @brief �L�����N�^�[�̍X�V����
	// @ param SE�̉���
	void CharacterUpdate(int se_volume);

	//! @brief �L�����N�^�[�̍U���Ɋւ��Ă̍X�V����
	void AttackUpdate();

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
	// ���̃N���X�������̊֐��ł��悩�������ǒ���bool �^�̕ϐ��������̂ŃN���X�ɂ���
	Attack player_attack_hit;
	Attack monster_attack_hit;

	// �t�B�[���h�I�u�W�F�N�g
	Field field;
	
};