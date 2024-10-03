#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Vector2.h"
#include "src/Collision/BoxCollision.h"
#include "src/System/Transform.h"
#include "TargetMove.h"

TargetMove::TargetMove()
{
}

TargetMove::~TargetMove()
{
	// �|�C���^�̉��
	//delete m_transform;
	//delete m_target;
}

//---------------------------------------------------------------------------
// �����Z�b�g����p�̊֐�
//---------------------------------------------------------------------------
void TargetMove::SetInfo(Transform* transform, const float hit_r, const float MOV_SPEED, const float ROT_SPEED)
{
	// ���g�̏����Z�b�g
	m_info.m_transform = transform;
	// �ړ������̔��a�̐ݒ�
	m_info.m_hit_r = hit_r;
	// �ړ��X�y�[�h�̐ݒ�
	m_info.M_MOV_SPEED = MOV_SPEED;
	// ��]�X�s�[�h�̐ݒ�
	m_info.M_ROT_SPEED = ROT_SPEED;
}

//---------------------------------------------------------------------------
// �^�[�Q�b�g�̏����Z�b�g����p�̊֐�
//---------------------------------------------------------------------------
void TargetMove::SetTargetInfo(Transform* target_pos, const float target_hit_r)
{
	// �^�[�Q�b�g�̍��W�̐ݒ�
	m_target_info.m_target = target_pos;
	// �^�[�Q�b�g�̔��a�̂��ݒ�
	m_target_info.m_target_hit_r = target_hit_r;
}

//---------------------------------------------------------------------------
// �ړ��Ɋւ���X�V�����p�֐�
// Vector2 �ɂ����W���Ȃ��̂ł����͂������Ƃ��Ďg�p���Ă���
//---------------------------------------------------------------------------
void TargetMove::Update(bool* run_flag)
{
	// �{�̂̌����̐ݒ�
	Set_Direction();
	// �^�[�Q�b�g�ƈ��̋����ɓ����������󂯎��
	m_hit = Target_Hit();
	// �͈͂ɓ����Ă��Ȃ��Ƃ�
	if (m_hit)
	{
		// �����Ă�������Ɉړ�
		m_info.m_transform->pos.x += m_info.M_MOV_SPEED * sinf(TO_RADIAN(m_info.m_transform->rot.y));
		m_info.m_transform->pos.z += m_info.M_MOV_SPEED * cosf(TO_RADIAN(m_info.m_transform->rot.y));
		// �ړ����Ȃ̂�
		*run_flag = true;
	}
}

//---------------------------------------------------------------------------
// �{�̂̌����̐ݒ�
//---------------------------------------------------------------------------
void TargetMove::Set_Direction()
{
	// ���C���̃X�^�[�g�ʒu��{�̂̈ʒu�ɐݒ肷��
	m_line_start.set(m_info.m_transform->pos);

	// ��̃x�N�g���쐬
	// ���̒l��������ƐU������̂����������܂��ɂȂ�
	Vector3 base(0.0f, 0.0f, 50.0f);
	// ���̖{�̂̌����ɍ��킹�����̂ŉ�]�s����쐬
	MATRIX mat = MGetRotY(TO_RADIAN(m_info.m_transform->rot.y));
	// ��ō쐬������̃x�N�g�����s��ŕϊ�
	Vector3 change = GetVector3VTransform(base, mat);
	// �S�[�����W�͊J�n���W����ύX�����x�N�g������̂Ƃ�
	m_line_goal = m_line_start + change;

	// �X�^�[�g���W�ƃS�[�����W���m�肵���̂ŊJ�n���W�����ꂼ��̃x�N�g�����쐬
	// ���̊J�n���W����S�[�����W�ւ̃x�N�g��
	Vector3 line_dir = m_line_goal - m_line_start;
	line_dir.y = 0;
	// ���̊J�n���W����v���C���[���W�ւ̃x�N�g��
	Vector3 target_dir = m_target_info.m_target->pos - m_line_start;
	target_dir.y = 0;
	// �O�ς��g�������f���������̂ŏ�ō�����Q�̃x�N�g���̊O�ς����߂܂�
	m_cross = GetVector3Cross(line_dir, target_dir);

	// ��ō쐬�������C����������悤�ɂ���
	{
		// ���̂܂܂̍��W���Ɛ����n�ʂɖ��܂��Ă��܂��̂ł����������Ă��܂�
		Vector3 start = m_line_start + Vector3(0.0f, 0.1f, 0.0f);
		Vector3 goal = m_line_goal + Vector3(0.0f, 0.1f, 0.0f);
		// �J�n���W�ƃS�[�����W������Ő��̕`��
		//DrawLine3D(start.VGet(), goal.VGet(), GetColor(255, 255, 0));

		// �J�n���W�̏ꏊ�Ƃ��낢����
		//DrawSphere3D(start.VGet(), 0.3f, 100, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
		// �S�[�����W�̉��F����
		//DrawSphere3D(goal.VGet(), 0.3f, 100, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);
	}
}

//---------------------------------------------------------------------------
// �^�[�Q�b�g�ƈ��̋����ɓ���������Ԃ��֐�
//---------------------------------------------------------------------------
bool TargetMove::Target_Hit()
{
	Set_Direction();
	// ���ꂼ��̍X�V�������I������̂Ńv���C���[��NPC�̈ʒu�֌W�����苗���߂Â��Ȃ��悤�ɂ��܂�
	// �{�̂ƃ^�[�Q�b�g�̋��������߂�
	float distance = Get_Target_Distance();
	// ��̋��������߂�i���ꂼ��̔��a�j
	float radius = m_info.m_hit_r + m_target_info.m_target_hit_r;
	// ��]���Ă����Ƃ�������]����
	if (m_can_rot)
	{
		// ���͈̔͂ɓ�������U���������߂�
		if (m_cross.y > RANGE) {
			// �O�ς̂x�̒l���v���X�̎��̓v���C���[�͐��̉E�ɂ��܂�
			m_info.m_transform->rot.y += m_info.M_ROT_SPEED;
		}
		else
			if (m_cross.y < -RANGE)
			{
				// �O�ς̂x�̒l���}�C�i�X�̎��̓v���C���[�͐��̍��ɂ��܂�	
				m_info.m_transform->rot.y -= m_info.M_ROT_SPEED;
			}
			else
			{
				// �ݒ肳�ꂽ�l���߂Â�����
				if (distance < radius) {
					// �����X�^�[�̌�����������������
					// �ړ��ɐ�����������
					return false;
				}
			}
	}
	// �܂��͈͊O�̎��͈ړ����ł���悤�ɂ��Ă���
	return true;
}

//---------------------------------------------------------------------------
// �^�[�Q�b�g�Ƃ̋�����Ԃ��֐�
//---------------------------------------------------------------------------
float TargetMove::Get_Target_Distance()
{
	// �{�̂ƃ^�[�Q�b�g�̋��������߂�
	float distance = GetVector3Distance(m_info.m_transform->pos, m_target_info.m_target->pos);
	return distance;
}

//---------------------------------------------------------------------------
// �{�̂̌�������]���Ă������̃t���O���Ă悤�̊֐�
//---------------------------------------------------------------------------
void TargetMove::Set_Can_Rotate(bool can)
{
	m_can_rot = can;
}
