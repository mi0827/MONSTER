#include "src/WinMain.h"
#include "src/System/Vector2.h"
#include "UIBar.h"

//-----------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------
UIBra::UIBra()
{
}

//-----------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------
UIBra::~UIBra()
{
}

//-----------------------------------------------
// �����ݒ�
//-----------------------------------------------
void UIBra::Set(Vector2 pos, Vector2 size, int* value, bool line)
{
	// �ݒ�̕ۑ�
	m_pos1 = pos;                // ���W�P
	m_size = size;                 // �T�C�Y
	m_pos2 = pos + size;	      // ���W�Q
	m_value = *value;			  // ���l
	m_value_max = *value;   // ���l�̍ő吔��ۑ�
	m_line_judgment = line;	  // �O�g����邩�ǂ���

	// �o�b�N�o�[�̐ݒ�
	m_back_pos1 = m_pos1;
	m_back_pos2 = m_pos2;

	// �O�g�̃��C���������ꍇ
	if (m_line_judgment) 
	{
		// �O�g�̃��C���̐ݒ�
		m_line_pos1 = m_pos1;
		m_line_size = m_size;
		m_line_pos2 = m_pos2;
		SetColor(255, 255, 255, &m_line_color);
	}
	// �e�J���[�̐ݒ�
	SetColor(128, 128, 128, &m_color);
	SetColor(0, 0, 0, &m_back_color);


	// value�̒l���P���邽�тɌ���ʂ̐ݒ�
	aaa = m_size.x / m_value;
}

//-----------------------------------------------
// �J���[�̃Z�b�g
//-----------------------------------------------
void UIBra::SetColor(int red, int green, int blue, int* color)
{
	// �F�̐ݒ�
	*color = GetColor(red, green, blue);
}

//-----------------------------------------------
// �X�V����
//-----------------------------------------------
void UIBra::Update(int*value)
{
	// value���ǂꂾ�������Ă���̂��𒲂ׂ�
	int value_difference = m_value_max - m_value ;
	// �����Ă��镪�̃o�[�����炵����
	new_aaa = aaa * value_difference;
}

//-----------------------------------------------
// �`�揈��
//-----------------------------------------------
void UIBra::Draw()
{
	
	// �o�b�N�o�[�̕`��
	DrawBox(m_back_pos1.x, m_back_pos1.y, m_back_pos2.x, m_back_pos2.y, m_back_color, TRUE);
	
	DrawBox(m_pos1.x, m_pos1.y, m_pos2.x + new_aaa, m_pos2.y, m_color, TRUE);
	
	// �O�g�̃��C���������ꍇ
	if (m_line_judgment)
	{
		DrawBox(m_line_pos1.x, m_line_pos1.y, m_line_pos2.x, m_line_pos2.y, m_line_color, FALSE);
	}

}
