#include "src/WinMain.h"
#include "src/System/Vector2.h"
#include "Text.h"
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

	m_text = new char*[line_max];
	for (int i = 0; i < line_max; i++)
	{
		m_text[i] = new char[256];
	}

	// �e�L�X�g�t�@�C���̓ǂݍ���
	FILE* fp = fopen(file_path, "r");
	if (fp)
	{
		// �s�����J��Ԃ�
		for (int i = 0; i < line_max; i++)
		{
			fgets(m_text[i], 256, fp);
		}

		
		// �t�@�C�������
		fclose(fp);
	}
	
}

//---------------------------------------------------------------------------
// �`�揈��
//---------------------------------------------------------------------------
void Text::TextDraw(int line_num, Vector2 draw_pos)
{
	// �`�揈��
	DrawStringF(draw_pos.x, draw_pos.y, m_text[line_num], GetColor(255, 255, 255));
	
}
