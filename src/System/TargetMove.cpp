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
}

//---------------------------------------------------------------------------
// �ړ��Ɋւ���X�V�����p�֐�
// Vector2 �ɂ����W���Ȃ��̂ł����͂������Ƃ��Ďg�p���Ă���
//---------------------------------------------------------------------------
void TargetMove::Update(Transform* transform, const float mov_speed, const float rot_speed, Vector3* target_pos)
{
	// �P�ڂ̃x�N�g���i�{�̑O�����̃x�N�g���j
	Vector2 front;
	front.x = 1.0f * cosf(TO_RADIAN(transform->rot.y));
	front.y = 1.0f * sinf(TO_RADIAN(transform->rot.y));

	// 2�ڂ̃x�N�g���i�{�̂���^�[�Q�b�g���ǂ����̕����ɂ��邩�̃x�N�g���j
	// Vector3����������u��������
	// �^�[�Q�b�g���W
	Vector2 taget_poition{ target_pos->x,target_pos->z }; 
	// �{�̂̍��W
	Vector2 pos{ transform->pos.x,transform->pos.z };
	Vector2 target = taget_poition - pos;
	// ���̃x�N�g���𐳋K������i������ 1.0f �ɂ���j
	target.normalize();


	// ��ŋ��߂��Q�̃x�N�g���ifront, target�j�̓��ς��擾���܂�
	float front_dot = GetVector2Dot(front, target);

	// ���̎擾�������ς̒l���v���X�������ꍇ�A�v���C���[��NPC�̑O�ɂ���Ɣ��f���܂�
	if (front_dot >= 0.0f) {
		// �v���C���[�̕����Ɍ�����ς���
		// �v���C���[��NPC���猩�Ă݂��ɂ���̂��𔻒f������
		// ���̔��f�����邽�߂�NPC�̉E�����̃x�N�g�����쐬
		Vector2 right;
		// NPC�̉E�����́FNPC�̌����im_rot�j��90�x����������
		right.x = 1.0f * cosf(TO_RADIAN(transform->rot.y + 90.0f));
		right.y = 1.0f * sinf(TO_RADIAN(transform->rot.y + 90.0f));

		// ��������E�x�N�g���ƃv���C���[�܂ł̃x�N�g���̂Q�̃x�N�g���̓��ς��擾
		float right_dot = GetVector2Dot(right, target);

		// ���̓��ς̒l���v���X��������v���C���[��NPC����݂ĉE�ɂ���
		if (right_dot > 0.0f) {
			transform->rot.y += rot_speed;
		}
		// �}�C�i�X�������ꍇ�͍��ɉ�]
		if (right_dot < 0.0f) {
			transform->rot.y -= rot_speed;
		}


		// �����Ă������
		transform->pos.x += mov_speed * cosf(TO_RADIAN(transform->rot.y));
		transform->pos.z += mov_speed * sinf(TO_RADIAN(transform->rot.y));
	}
}
