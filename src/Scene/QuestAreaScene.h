#pragma once
//! @file QusetAreaScene.h
//! @brief �^�C�g���V�[���̃N���X
class QuestAreaScene : public Scene_Base
{
public:
	//! �R���X�g���N�^
	QuestAreaScene();
	//! �f�X�g���N�^
	~QuestAreaScene();

	//!  �b����悤�ɂȂ�͈͂̔��a
	static constexpr float AREA_FIELD_R = 15.0f;

	//! @brief ��������
	void Init()override;

	//! @brief �X�V����
	void Update()override;

	//! @brief �`�揈��
	void Draw()override;

	//! @brief �I������
	void Exit()override;

	//! @brief �t�B�[���h�ƃL�����N�^�[�̓����蔻��
	void HitField()override;

	//! @brief �I�v�V�������j���[�ł�����Ă����l�𔽉f����֐�
	//! //! @param BGM�̉���
	//! @param SE�̉���
	//! @param �}�E�X���x
	void OptionValuesReflect(int bgm, int se, int mouse)override;

	//! @brief �b����悤�ɂȂ�G���A�̐ݒ�
	void InitArea();



private:


	bool m_start_flag = false; // �^�C�g����ʂŃ{�^���������ꂽ���ǂ����̃t���O

	//! �J�����N���X�̃I�u�W�F�N�g
	Camera camera;

	//! �t�B�[���h�I�u�W�F�N�g
	TitleField field;

	//! �v���C���[�̃I�u�W�F�N�g
	CharacterBase* player;

	//! ��t��̃I�u�W�F�N�g
	Receptionist receptionist;
	//! �G���A�p�̃J�v�Z��
	CapsuleCollision m_area;
	//! �b����G���A�ɓ������������Ă��Ȃ����̃t���O
	bool m_area_hit = false;

	//! @brief �N�G�X�g���j���[�e�L�X�g
	Text m_quest_text;
	//! @brief �N�G�X�g�G���A�ł̃e�L�X�g
	Text m_quest_area_text;

	//�@�G���A�ł̃e�L�X�g�̐�
	enum StoryText
	{
		story1,
		story2,
		story_max
	};
	
	// �N�G�X�g�e�L�X�g�̐�
	enum QuestText
	{
		quest1,
		quest2,
		quest_max
	};

	//! �`�悷��e�L�X�g�̔ԍ��Ƃ��ĊǗ�
	enum Text
	{
		f_text,                // F�{�^����������̃��b�Z�[�W
		excamation_pos, // �r�b�N���}�[�N

		text_max
	};

	//! ������X�N���[�����W�ɕ`�悷�邽�߂̍\����
	struct TextState
	{
		////! �t�H���g�T�C�Y
		//int font_size;
		//! �������ۑ����邽�߂̂���
		const char* text;
		//! �`�悵�������W
		Vector3 draw_pos;
		//! ���炵�������̍��W
		Vector3 shift_pos;
		//! ���̃X�N���[����ʂ���o����`�悵�Ȃ��悤�ɂ��邽�߂̂���
		bool draw_flag;
	};
	// �`�悵����������̐����쐬
	TextState m_text[text_max]
	{
		{	/*100,*/"F : �b��", {0.0f,0.0f,0.0f},{-8.0f,10.0f,0.0f},false},
		{	/*100,*/" ! ", {0.0f,0.0f,0.0f},{0.0f,20.0f,0.0f},false},
	};
	static constexpr int FONT_SIZE = 100;

};
