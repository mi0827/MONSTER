#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/Model/Model.h"
#include "HitField.h"


void SetHitGround(Model* ground_model)
{
	// ��������̍쐬
	MV1SetupCollInfo(ground_model->m_model);
}

void HitGroundCharacter(Vector3* character_pos, Model* ground_model)
{
	// ��������̍X�V
	MV1RefreshCollInfo(ground_model->m_model);

	// ���̊J�n���W(�L�����N�^�[�̏�̂ق��̍��W)
	Vector3 line_start = *character_pos + Vector3(0.0f, 100.0f, 0.0f);
	// ���̃S�[�����W(�v���C���[�̉��̂ق��̍��W)
	Vector3 line_goal = *character_pos + Vector3(0.0f, -100.0f, 0.0f);
	// �n�ʃ��f���Ɛ��̓����蔻��
	MV1_COLL_RESULT_POLY character_hit = MV1CollCheck_Line(ground_model->m_model, -1, line_start.VGet(), line_goal.VGet());

	// �������Ă�����̔���
	if (character_hit.HitFlag)
	{
		// �L�����N�^�\���W�����̍����ɍ��킹��
		character_pos->y = character_hit.HitPosition.y;
	}
}
