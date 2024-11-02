#pragma once

class Text
{
public:

	//! @brief �R���X�g���N�^
	Text();
	//! @brief �f�X�g���N�^
	~Text();

	//void Init();

	//! @brief �e�L�X�g�t�@�C�����當����̓ǂݍ��ݏ���
	//! @param �t�@�C���̃p�X
	//! @param �e�L�X�g�t�@�C���̒��g�̍s��
	void LoadText(const char file_path[256], const int line_max);

	//void Update();

	//! @brief �e�L�X�g�̕`��
	//! @param �`�悵�����e�L�X�g�̍s�ԍ�
	//! @param �`�悵�������W
	void TextDraw(int line_num, Vector2 draw_pos, int back_size);

	//void Exit();

public:
	// �������ۑ�����z��̍ő吔
	static constexpr int CHAE_MAX = 256;

	// �������`�悷��ۉ�ʂ̏㉺�̏ꍇ�ɊJ���Ăق������Ԃ̑傫��
	static constexpr int CREVICE_SIZE = 50;

	// ������̔w�i�̑傫��
	static constexpr int TITLE_BACK_SIZE = 1000; //�^�C�g���X�g�[���[ (�N�G�X�g�G���A�ł��g���Ă���)
	static constexpr int OPTION_BACK_SIZE = 500; // �I�v�V�������j���[
	static constexpr int END_BACK_SIZE = 650;    // �G���h�V�[��
	// �����̃T�C�Y
	static constexpr int  TITLE_BACK_HALF_SIZE = TITLE_BACK_SIZE / 2; //�^�C�g���o�[�W���� (�N�G�X�g�G���A�ł��g���Ă���)
	static constexpr int OPTION_BACK_HALF_SIZE = OPTION_BACK_SIZE / 2; // �I�v�V�������j���[
	static constexpr int  END_BACK_HALF_SIZE = END_BACK_SIZE / 2;       // �G���h�V�[��
	// �e�L�X�g�t�@�C�����當�����ǂݎ�������̂�ۑ��������
	// �����������
	std::vector<std::string> lines;
};

