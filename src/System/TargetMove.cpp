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
void TargetMove::SetInfo(Information* info, TargetInformation* target_info)
{
	// ���g�̏����Z�b�g
	m_info = *info;
	// �^�[�Q�b�g�̃Z�b�g
	m_target_info = *target_info;
}

//---------------------------------------------------------------------------
// �ړ��Ɋւ���X�V�����p�֐�
// Vector2 �ɂ����W���Ȃ��̂ł����͂������Ƃ��Ďg�p���Ă���
//---------------------------------------------------------------------------
void TargetMove::Update()
{
	// �P�ڂ̃x�N�g���i�{�̑O�����̃x�N�g���j
	Vector2 front;
	front.x = 1.0f * cosf(TO_RADIAN(m_info.m_transform->rot.y));
	front.y = 1.0f * sinf(TO_RADIAN(m_info.m_transform->rot.y));

	// 2�ڂ̃x�N�g���i�{�̂���^�[�Q�b�g���ǂ����̕����ɂ��邩�̃x�N�g���j
	// Vector3����������u��������
	// �^�[�Q�b�g���W
	Vector2 taget_poition{ m_target_info.m_target->x,m_target_info.m_target->z };
	// �{�̂̍��W
	Vector2 pos{ m_info.m_transform->pos.x,m_info.m_transform->pos.z };
	Vector2 target = taget_poition - pos;

	// �^�[�Q�b�g�Ƃ̋�����������悤�ɂ��Ă���
	// ��ŏ���
	printfDx("����%3f", target);

	// ���̃x�N�g���𐳋K������i������ 1.0f �ɂ���j
	target.normalize();



	// ��ŋ��߂��Q�̃x�N�g���ifront, target�j�̓��ς��擾���܂�
	float front_dot = GetVector2Dot(front, target);

	// ���̎擾�������ς̒l���v���X�������ꍇ�A�v���C���[��NPC�̑O�ɂ���Ɣ��f���܂�
	//if (front_dot >= 0.0f) {
		// �v���C���[�̕����Ɍ�����ς���
		// �v���C���[��NPC���猩�Ă݂��ɂ���̂��𔻒f������
		// ���̔��f�����邽�߂�NPC�̉E�����̃x�N�g�����쐬
	Vector2 right;
	// NPC�̉E�����́FNPC�̌����im_rot�j��90�x����������
	right.x = 1.0f * cosf(TO_RADIAN(m_info.m_transform->rot.y + 90.0f));
	right.y = 1.0f * sinf(TO_RADIAN(m_info.m_transform->rot.y + 90.0f));

	// ��������E�x�N�g���ƃv���C���[�܂ł̃x�N�g���̂Q�̃x�N�g���̓��ς��擾
	float right_dot = GetVector2Dot(right, target);

	// ���̓��ς̒l���v���X��������v���C���[��NPC����݂ĉE�ɂ���
	if (right_dot > 0.0f) {
		m_info.m_transform->rot.y += m_info.M_ROT_SPEED;
	}
	// �}�C�i�X�������ꍇ�͍��ɉ�]
	if (right_dot < 0.0f) {
		m_info.m_transform->rot.y -= m_info.M_ROT_SPEED;
	}


	// �����Ă������
	m_info.m_transform->pos.x += m_info.M_MOV_SPEED * cosf(TO_RADIAN(m_info.m_transform->rot.y));
	m_info.m_transform->pos.z += m_info.M_MOV_SPEED * sinf(TO_RADIAN(m_info.m_transform->rot.y));
	/*}*/
}

void TargetMove::Target_Hit()
{
}
