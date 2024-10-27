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
	void TextDraw(int line_num, Vector2 draw_pos);

	//void Exit();

public:
	// �������ۑ�����z��̍ő吔
	static constexpr int CHAE_MAX = 256;
	// ������̔w�i�̑傫��
	static constexpr int BACK_SIZE = 1000;

	// �e�L�X�g�t�@�C�����當�����ǂݎ�������̂�ۑ��������
	//char **m_text;
	// �����������
	std::vector<std::string> lines;


};

