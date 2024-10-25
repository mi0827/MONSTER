#include "src/WinMain.h"
#include "src/System/Vector2.h"
#include "Text.h"
#include <fstream>
#include <string>
using namespace std;

// ���̃\�[�X���Ȃ��ƌx�������o�ăG���[�ɂȂ�
#pragma warning(disable : 4996)

Text::Text()
{
}

Text::~Text()
{
	delete[] m_text;
}

//---------------------------------------------------------------------------
// �e�L�X�g�t�@�C���̓ǂݍ��ݏ���
//---------------------------------------------------------------------------
void Text::LoadText(const char file_path[256], const int line_max)
{

	m_text = new char* [line_max];
	for (int i = 0; i < line_max; i++)
	{
		m_text[i] = new char[256];
	}


	// �e�L�X�g�t�@�C���̓ǂݍ���
	// �t�@�C���̃f�[�^���������
	ifstream file(file_path);
	if (file.is_open() __ true)
	{
		// �����������
		vector<string> lines;
		while (true)
		{
			string line;
			getline(file, line);
			// �f�[�^�̈�ԍŌ�ɍs������
			if (file.eof())
			{
				break;
			}
			// vector�̔z��ɒǉ�
			lines.emplace_back(line);
		}
		// �t�@�C�������
		file.close();
	}



	FILE** fp = 0;
	fopen_s(fp, file_path, "r");
	if (fp)
	{
		// �s�����J��Ԃ�
		for (int i = 0; i < line_max; i++)
		{
			fgets(m_text[i], 256, *fp);
		}


		// �t�@�C�������
		fclose(*fp);
	} 

}

//---------------------------------------------------------------------------
// �`�揈��
//---------------------------------------------------------------------------
void Text::TextDraw(int line_num, Vector2 draw_pos)
{
	// �`�揈��
	DrawStringF(draw_pos.x, draw_pos.y, lines[line_num], GetColor(255, 255, 255));

}
