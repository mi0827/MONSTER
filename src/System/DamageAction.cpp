#include "DamageAction.h"

//-----------------------------------------------
// �_���[�W�v�Z�p�֐�
//-----------------------------------------------
void DamageCount(int damage_value, int defense_value, int* hp_value)
{
	// �_���[�W�v�Z(�A���e���I�X�v�Z�����g�p)
	// �ǂꂾ���̃_���[�W��H��������̌v�Z
	int damage = (int)(damage_value / 2 - defense_value / 4);
	// �_���[�W��HP�����炷
	*hp_value -= damage;
}
