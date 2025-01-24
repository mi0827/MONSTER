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

	//! @brief ��t��̖ڈ�̍X�V����
	void LandMarkUpdate();

	//! @brief �N�G�X�g�G���A�̍X�V����
	void QuestAreaUpdate();

	//! @brief ��b���Ă��Ȃ���Ԃ̍X�V����
	void ModeNormalUpdate();

	//! @brief ��b�p�[�g�̍X�V����
	void ConvoUpdate();

	//! @breif �N�G�X�g���󂯂Ă���Ƃ��̍X�V����
	void AcceptingQuestUpdate();

	//! @brief ��b���Ă��Ȃ���Ԃ̕`�揈��
	void ModeNormalDraw();

	//! @brief ��b�p�[�g�̕`�揈��
	void ConvoDraw();

	//! @breif �N�G�X�g���󂯂Ă���Ƃ��̕`�揈��
	void AcceptingQuestDraw();


private:
	// ���̃V�[���̏�Ԃ��Ǘ�
	enum SecenNum
	{
		normal, // ��b�����Ă��Ȃ��Ƃ�
		convo,  // ��b��
		accepting_quest, // �N�G�X�g��t��

		secen_max
	};
	// �N�G�X�g�V�[�����ǂ̏�ԉ���⊮����
	int secen_mode_num = normal;

	bool m_start_flag = false; // �^�C�g����ʂŃ{�^���������ꂽ���ǂ����̃t���O

	//! �J�����N���X�̃I�u�W�F�N�g
	Camera camera;

	//! ��t��̃I�u�W�F�N�g
	Receptionist receptionist;
	//! �G���A�p�̃J�v�Z��
	CapsuleCollision m_area;
	//! �b����G���A�ɓ������������Ă��Ȃ����̃t���O
	bool m_area_hit = false;

	//! �v���C���[����b�����ǂ���
	bool m_convo_flag = false;

	//! �N�G�X�g���j���[�e�L�X�g
	Text m_quest_text;
	//! �N�G�X�g�G���A�̃e�L�X�g
	Text m_quest_area_text;
	//! �N�G�X�g��t��̃e�L�X�g
	Text m_reception_text;
	//! �e�e�L�X�g�̃t�H���g�T�C�Y
	static constexpr int TEXT_FONT_SIZE = 60;
	//! �e�e�L�X�g�̉��s�ڂ��Ă�ł���̂���ۑ����邽�߂̕ϐ�
	int m_text_line_num;
	//�@�G���A�ł̃e�L�X�g�̐�
	enum PlayerText
	{
		story1,
		story_max
	};

	// �N�G�X�g�e�L�X�g�̐�
	enum QuestText
	{
		quest1,
		quest2,
		confirmatio1,
		yes,
		no,
		confirmation2,
		quest_max
	};

	// ��t��̃e�L�X�g�̐�
	enum ReceptionText
	{
		convo_text_1,
		convo_text_2,
		convo_text_3,
		convo_text_4,
		teception_max
	};

	//! �`�悷��e�L�X�g�̔ԍ��Ƃ��ĊǗ�
	enum LandMarkText
	{
		f_text,                // F�{�^����������̃��b�Z�[�W
		excamation_pos, // �r�b�N���}�[�N

		landmark_text_max
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
	TextState m_landmark_text[landmark_text_max]
	{
		{	/*100,*/"F : �b��", {0.0f,0.0f,0.0f},{-8.0f,10.0f,0.0f},false},
		{	/*100,*/" ! ", {0.0f,0.0f,0.0f},{0.0f,20.0f,0.0f},false},
	};
	// �ڈ�̕����̑傫��
	static constexpr int FONT_SIZE = 100;

	// ���݂ǂ̃e�L�X�g��`�悷��̂����Ǘ����邽�߂̗񋓑�
	enum TextNum
	{
		landmark_text, // �ڈ�ƂȂ��Ă���e�L�X�g
		player_text,      // �v���C���[���b���Ă���Ƃ��ɏo�Ă���e�L�X�g
		reception_text, // ��t�삪�b���Ă���Ƃ��ɏo�Ă���e�L�X�g
		quest_text,      // �N�G�X�g��ʂ�`�悵�Ă���Ƃ��̏���

		text_max
	};

	//---------------------------------------------
	// �N�G�X�g�֘A
	//---------------------------------------------
	// �N�G�X�g�I����ʂ̏��
	enum QuestSelectionMode
	{
		quest_selection,
		reply_selection,
	};
	// �N�G�X�g�I����ʂ̏��
	int m_quest_selection_num;
	// �ǂ̃N�G�X�g��I�񂾂��ۑ�����ϐ�
	int m_quest_num;
	// �ԓ����ǂ��炩�Ȃ̂���ۑ�����ϐ�
	int m_reply_num;
	// �I����ʂőI�����Ă�����̂��������߂̕ϐ�
	int m_select_num = 0;


	Vector2 m_quest_draw_pos[quest_max] =
	{
		{SCREEN_W / 2, SCREEN_H / 2},
		{SCREEN_W / 2, SCREEN_H / 2},
		{SCREEN_W / 2, SCREEN_H / 2},
		{SCREEN_W / 2, SCREEN_H / 2},
		{SCREEN_W / 2, SCREEN_H / 2},
		{SCREEN_W / 2, SCREEN_H / 2},
	};


	//---------------------------------------------
    // ��b�֘A(��̏��A��t��)
    //---------------------------------------------
	// ��t��̉�b���ǂ̏�ԂȂ̂����Ǘ�
	enum ConvoMode
	{
		convo_mode_1, // �N�G�X�g��������O
		convo_mode_2, // �N�G�X�g�o���m�F
		convo_mode_3, // ��قǐ���������悤�ɑ���

		convo_mode_max
	};
	int m_convo_mode_num = convo_mode_1;

	// �N���b���Ă���̂���`�悷�邽�߂̂���
	struct TextName
	{
		//! �N���b���Ă���̂��̖��O
		const char* name;
		//! �`�悵�������W
		Vector2 draw_pos;
	};

	TextName m_text_info[text_max]
	{
		{"Player", {0.0f,0.0f}},
		{"Player", {0.0f,0.0f}},
		{"��̏�", {0.0f,0.0f}},
		{"�N�G�X�g", {0.0f,0.0f}},

	};
	static constexpr int MANE_FONT_SIZE = 30;
	// �e�L�X�g�̕`����p
	Vector2 m_text_draw_pos;
	// �ڈ�̕`����W
	Vector2 m_landmark_draw_pos;



};
