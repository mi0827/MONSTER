#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "BoxCollision.h"

//-----------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------
BoxCollision::BoxCollision()
{
}

//-----------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------
BoxCollision::~BoxCollision()
{
}

//-----------------------------------------------
// �`�揈��
//-----------------------------------------------
void BoxCollision::Draw(int color, int line_color)
{
	/*SetUseLighting(FALSE);*/
	// �F�̕ۑ�
	m_box.color = color;
	m_box.line_color = line_color;

	// �����̂̕`��
	DrawCube3D(m_box.pos1.VGet(), m_box.pos2.VGet(), m_box.color, m_box.color, TRUE);
	
	//DrawCube3D(m_box.pos1.VGet(), m_box.pos2.VGet(), m_box.color, m_box.line_color, FALSE);
	/*SetUseLighting(TRUE);*/
}

//-----------------------------------------------
// �{�b�N�X�쐬����
//-----------------------------------------------
void BoxCollision::CreateBox(Vector3 pos, Vector3 size )
{
	// ���W�̕ۑ�
	m_box.pos1.set(pos);
	// ���W2���ݒ�
	m_box.pos2.set(pos.x + size.x, pos.y + size.y, pos.z + size.z);
	// �T�C�Y�̕ۑ�
	m_box.size.set(size);
	// �����蔻��p�̔����̃T�C�Y�̐ݒ�
	m_box.half_size.set(size.x / 2.0f, size.y, size.z / 2.0f);
	// �����蔻��p�{�b�N�X���W�̐ݒ�
	m_box.hit_pos.set(pos.x + m_box.half_size.x, pos.y + m_box.half_size.y, pos.z + m_box.half_size.z);
	
}


void BoxCollision::SetPos(Vector3 pos)
{
	// ���W�̃Z�b�g
	m_box.pos1.set(pos);
	// ���W2���ݒ�
	m_box.pos2.set(pos.x + m_box.size.x, pos.y + m_box.size.y, pos.z + m_box.size.z);
	// �����蔻��p�{�b�N�X���W�̐ݒ�
	m_box.hit_pos.set(pos.x + m_box.half_size.x, pos.y + m_box.half_size.y, pos.z + m_box.half_size.z);
}

void BoxCollision::SetSize(Vector3 size)
{
	// �T�C�Y�̕ύX
	m_box.size.set(size);
	// �����蔻��p�̔����̃T�C�Y�̐ݒ�
	m_box.half_size.set(size.x / 2.0f, size.y, size.z / 2.0f);
}



