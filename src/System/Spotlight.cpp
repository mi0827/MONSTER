#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Spotlight.h"

//---------------------------------------
// �R���X�g���N�^(������)
//---------------------------------------
Spotlight::Spotlight()
{
	
}

//---------------------------------------
// �f�X�g���N�^�[
//---------------------------------------
Spotlight::~Spotlight()
{
	// ���C�g�̍폜
	DeleteLightHandle(m_light_handle);
}

void Spotlight::InitSetLight(Vector3 pos, Vector3 spot_pos, float outAngle, float inangle, float range, float atten0, float atten1, float atten2)
{
	// ���C�g�̍쐬

	m_light_handle = CreateSpotLightHandle(
		pos.VGet(),
		spot_pos.VGet(),
		TO_RADIAN(outAngle), TO_RADIAN(inangle), range, atten0, atten1, atten2);
}

//---------------------------------------
// ���C�g�̍��W�ݒ�p�֐�
//---------------------------------------
void Spotlight::SetLightPos(Vector3* pos)
{
	// ���C�g�̍��W�ݒ�
	SetLightPositionHandle(m_light_handle, pos->VGet());
}

//---------------------------------------
// ���C�g�̏Ƃ炷�����ݒ�p�֐�
//---------------------------------------
void Spotlight::SetLightSpotPos(Vector3* spot_pos)
{
	// ���C�g�̌����̐ݒ�
	SetLightDirectionHandle(m_light_handle, spot_pos->VGet());
}

//---------------------------------------
// ���C�g�̍��W�֘A�̍X�V����
//---------------------------------------
void Spotlight::UpdateTransform(Vector3* pos, Vector3* spot_pos)
{
	// ���W�̐ݒ�
	SetLightPos(pos);
	// ���C�g�̌����̐ݒ�
	SetLightSpotPos(spot_pos);

}
