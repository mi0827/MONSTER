#pragma once
// #include "Character_Base.h"


class GameScene :public Scene_Base
{
public:
	GameScene();
	// ~GameScene();
	// ��������
	void Init()override;

	// �X�V����
	void Update(int bgm_volume, int se_volume)override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

	// SE�̏�����
	void SE_Init();
	// BGM�̏�����
	void BGM_Init();

	// ���C�g�̏�����
	void Light_Init();
	// ���C�g�̍X�V����
	void Light_Update();

	// �`���[�g���A���̍X�V����
	void Tutorial_Update();
	// ���C���v���C�V�[���̍X�V����
	void PlayMain_Update();
	// �v���C�G���h�̍X�V����
	void PlayEnd_Update();
	// �G���h�V�[���ł̏��s�Ɋւ���֐�
	void Play_Victory_Draw(CharacterBase* character1, CharacterBase* character2); // ���҂����߂�֐�

	// �`��p�̕�����̃T�C�Y����
	// ����
	// �P�F���̑傫��
	// �Q�F�c�̑傫��
	// �R�F������
	void Draw_String_Size(float* w, float* h, const char* sting);

	// �L�����N�^�[�̍X�V����
	void Character_Update(int se_volume);
	// �^�C�}�[�̍X�V����
	void Time_Update(int& time_count);
	// �^�C�}�[�̕`��
	void Time_Draw();
	// �`���[�g���A���ł̕`�揈��
	void Tutorial_Draw();
	// ����������`�悳���邾���̊֐�
	void Ready_Draw();
	// �G���h�ł̕`�揈��
	void End_Draw();

	// �U���̂����蔻����s���֐�
	void Attack_Hit(int player1, int player2);
	// �K�[�h�̓����蔻��
	void Block_Hit(int player1, int player2);
	// �L�����N�^�[�̃X�e�[�^�X�`�揈��
	void Draw_Status();

	// �Q�[���V�[��
	enum play_scene
	{
		Play_Tutorial, // �`���[�g���A���V�[��
		Play_Main,     // �Q�[�����C���V�[��
		Play_End,      // �v���CEND�V�[��

		Play_Max       // �v���C�V�[���̍ő�
	};

	// SE
	enum play_se
	{
		READY, // �`���[�g���A���̏�������

		SE_MAX // SE�̍ő吔
	};

	// BGM
	enum BGM
	{
		TUTORIAL_BGM,  // �`���[�g���A����BGM
		BATTLE_1_BGM,  // �v���C���C����BGM�P
		BATTLE_2_BGM,  // �v���C���C����BGM�Q
		BATTLE_3_BGM,  // �v���C���C����BGM�R
		BGM_MAX        // BGM�̍ő吔
	};

private:

	int m_time_count = 0;     // �t���[�����������̎��ԂŌv�Z����p�̕ϐ�
	int m_flame_count = 0;    // �t���[�������J�E���g������ϐ�
	int m_play_scene = 0;     // �`���[�g���A���̓r�����𔻕�
	int m_end_count = 0;      // �G���h�V�[���̎���
	bool m_status_flag = false;   // �X�e�[�^�X�X�V�������Ă������̃t���O

	//-------------------------------------------
	// �`���[�g���A���Ŏg���ϐ�
	//-------------------------------------------
	const int BUTTON_COUNT_MAX = 180; // �R�b
	// ���������t���O
	bool m_ready_flag1 = false;
	bool m_ready_flag2 = false;
	// �{�^���̒��������J�E���g����p�̕ϐ�
	float m_button_count1 = 0;
	int m_button_count2 = 0;

	// �q�b�g�X�g�b�v�̔��f�p�ϐ�
	bool m_stop = false;

	// ���C�g�p�̕ϐ�
	static const int light_MAX = 1;
	int m_light_handle[light_MAX] = {0}; // ���C�g�n���h��
	COLOR_F m_original_dif_color = { 0,0,0 };
	COLOR_F m_original_spc_color = { 0,0,0 };
	COLOR_F m_original_amb_color = { 0,0,0 };
	Vector3 m_original_light_rot = { 0,0,0 }; // �������C�g�̌���
	Vector3 m_light_rot = { 0.0f,0.0f,0.0f }; // ���C�g�̉�]
	Vector3 m_light_pos = { 0.0f,0.0f,0.0f }; // ���C�g�̃|�W�V����

	static const int FIGHT_START_COUNT_MAX = 300; // �킢���n�܂�܂ł̏�������
	bool m_fight_start_flag = false; // �킢���n�܂�p�̃t���O
	int m_fight_start_count = 0; // ���f�B�[���ꂩ��킢���n�܂�܂ł̃J�E���g

	int m_draw_fight_pos_x = 0; // Lady,Fight�̕`����W�p�ϐ�
	//int shadowmap_handle; // �V���h�[�}���v
};