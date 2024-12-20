#include "WinMain.h"
#include "src/System/Random.h"
#include "System/Vector3.h"
#include "System/Vector2.h"
#include "src/System/Spotlight.h"
#include "src/System/Transform.h"
#include "Camera.h"


//	���̍��W�Ƀ}�E�X���Œ肵�悤�Ǝv���܂�
#define FIXED_X		(SCREEN_W/2)	//	�w���W
#define FIXED_Y		(SCREEN_H/2)	//	�x���W




//---------------------------------------
// �R���X�g���N�^(������)
//---------------------------------------
Camera::Camera()
{
	//! �J�������W�̏����ݒ�
	m_pos.set(0.0f, 0.0f, -20.0f);
	//! �J�����̌����͑S���O�x�ŊJ�n
	m_rot.set(0.0f, 0.0f, 0.0f);

	//! �J������������W
	m_look.set(0.0f, 0.0f, 0.0f); // ���ׂĂO�D�O���ŏ�����

	//! �}�E�X�̈ړ��ʂ̏������ŏ���0.0f����
	m_mouse_move_x = 0.0f;
	m_mouse_move_y = 0.0f;
	//! �p�l���̑傫��(�J�����𒆐S�Ƃ��Ĉ������ߔ����̑傫�����g��)
	// ���͎g���ĂȂ�
	m_hit_box_size.set(BOX_SIZE_HALF - (float)0.1, BOX_SIZE_HALF - (float)0.1, BOX_SIZE_HALF - (float)0.1);
	m_before_pos.set(m_pos); //< �ړ��O�̍��W�̐ݒ�

	// �J�����̌���ʒu�Ƌ����̐ݒ�
	SetCamera();

}

// ��������
void Camera::Init()
{
}

//---------------------------------------------------------------------------------
//	// �v���C��ʂ̏����ݒ�
//---------------------------------------------------------------------------------
void Camera::PlayFieldInit()
{
	//m_field_size.set(SCREEN_W , SCREEN_H);                                                                                          // �`�悷���ʂ̃T�C�Y�̐ݒ�
	//m_screen_field = MakeScreen((int)m_field_size.x, (int)m_field_size.y);                                             // �`���ʂ��������ނ��߂̏����ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 2.0f, -50.0f), VGet(0.0f, 0.0f, 1.0f));  // �J�����̐ݒ�
}



//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Camera::MouseCamera(Vector3* target_pos)
{
	//m_before_pos.set(m_pos); //< �ړ��O�̍��W�̐ݒ�
	// �v���C���[�̌��ɕt���ē���
	m_look.set(target_pos->x, target_pos->y + m_look_height, target_pos->z);


	// �J�������n�ʂɖ��܂�Ȃ��悤�ɂ��Ă���
	if (m_rot.x <= LOWER_ANGLE)
	{
		m_rot.x = LOWER_ANGLE;
	}

	// �J�������^��ɂ����Ȃ��悤�ɂ��Ă���
	if (m_rot.x >= UP_ANGLE_MAX)
	{
		m_rot.x = UP_ANGLE_MAX;
	}

	//==========================================
	// �Q�[���p�b�h�p�̏���
	//==========================================
	//	�Q�[���p�b�h�̉E�X�e�B�b�N�̒l���g���Č����ϐ��i m_rot �j�̒l��ύX
	// ���X�e�b�N�Ńv���C���[�̌�������W�̍X�V
	// �Q�[���p�b�h�̏����擾�iXINPUT �̏��j
	//XINPUT_STATE input;
	//// �Q�[���p�b�h�̏����ۂ��Ǝ擾
	//GetJoypadXInputState(pad_no, &input);
	//// �ړ��p�x�N�g���p�ϐ�
	//Vector3 rot;
	//// ���X�e�B�b�N�̒l��ݒ�
	//rot.y = input.ThumbRX;
	//rot.x = input.ThumbRY;
	//// -32768 �` 32767 ��-1.0f�@�`�@1.0f�ɂ��܂�
	//rot /= 32768.0f;
	//// ���̈ړ��p�x�N�g���̑傫����������x�傫���������ړ������悤�Ǝv���܂�
	//if (rot.GetLength() > 0.5f)
	//{
	//	m_rot.y += rot.y * PAD_CAMERA_ROT_SPEED;
	//	m_rot.x -= rot.x * PAD_CAMERA_ROT_SPEED;
	//	// m_rot += rot * PAD_CAMERA_ROT_SPEED;  // ���̈ړ��x�N�g�������W�ړ�
	//}

	//	�}�E�X�̈ړ���
	Vector2 move;

	//	�Œ肳�ꂽ�}�E�X�̂���ړ��p���Q�b�g
	move.x = GetFixedMouseMoveX();
	move.y = GetFixedMouseMoveY();

	// ��]�͂��̂܂܂��Ƒ傫������̂ŏ�����
	//�ړ��ʂ����������܂�
	move *= m_camera_mouse_sensi;
	m_rot.y += move.x;
	m_rot.x += move.y;


	// �܂��͉�]�O�̃x�N�g����p�ӂ��܂�
	// �J����������v���C���[�����̃x�N�g�����쐬���܂�
	VECTOR base_dir = VGet(0.0f, 0.0f, -m_length);

	// �s���p�ӂ��܂�
	// X����]�s��
	MATRIX mat_x = MGetRotX(TO_RADIAN(m_rot.x));
	// Y����]�s��
	MATRIX mat_y = MGetRotY(TO_RADIAN(m_rot.y));

	// X����]��Y����]�����������̂łQ�̍s����P�ɂ܂Ƃ߂܂�
	MATRIX mat = MMult(mat_x, mat_y);
	// ���̃x�N�g�����w����]�Ƃx����]�����܂�
	// �ȒP�Ɍ���������̋����̖_������Ă���
	VECTOR change_dir = VTransform(base_dir, mat);

	// �J�����̈ʒu�����Ă�����W������̈ʒu�ɍĐݒ�
	m_pos = m_look + change_dir;
}

//---------------------------------------------------------------------------------
//	�^�[�Q�b�g�J�����̍X�V����
//---------------------------------------------------------------------------------
void Camera::TargetCamera(Vector3* target_pos1, Vector3* target_pos2)
{
	// �������^�[�Q�b�g�̐ݒ�i����͉��̃^�[�Q�b�g������j
	m_look.set(target_pos1->x, target_pos1->y + m_look_height, target_pos1->z);

	// ��O�̃^�[�Q�b�g���������̂�
	m_look_2.set(target_pos2->x, target_pos2->y, target_pos2->z);

	Vector3 start;
	start.set(m_pos);
	Vector3 goal;
	goal.set(0.0f, 0.0f, 0.0f);
	Vector3 m_cross;
	m_cross.set(0.0f, 0.0f, 0.0f);

	// ��̃x�N�g���쐬
	// ���̒l��������ƐU������̂����������܂��ɂȂ�
	Vector3 base(0.0f, 0.0f, 50.0f);
	// ���̖{�̂̌����ɍ��킹�����̂ŉ�]�s����쐬
	MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));
	// ��ō쐬������̃x�N�g�����s��ŕϊ�
	Vector3 change = GetVector3VTransform(base, mat);
	// �S�[�����W�͊J�n���W����ύX�����x�N�g������̂Ƃ�
	goal = start + change;
	// �X�^�[�g���W�ƃS�[�����W���m�肵���̂ŊJ�n���W�����ꂼ��̃x�N�g�����쐬
	// ���̊J�n���W����S�[�����W�ւ̃x�N�g��
	Vector3 line_dir = goal - start;
	line_dir.y = 0;
	// ���̊J�n���W����v���C���[���W�ւ̃x�N�g��
	Vector3 target_dir = *target_pos2 - start;
	target_dir.y = 0;
	// �O�ς��g�������f���������̂ŏ�ō�����Q�̃x�N�g���̊O�ς����߂܂�
	m_cross = GetVector3Cross(line_dir, target_dir);
	// ��ō쐬�������C����������悤�ɂ���
	{
		// ���̂܂܂̍��W���Ɛ����n�ʂɖ��܂��Ă��܂��̂ł����������Ă��܂�
		Vector3 start = start + Vector3(0.0f, 1.0f, 0.0f);
		Vector3 goal = goal + Vector3(0.0f, 1.0f, 0.0f);
		// �J�n���W�ƃS�[�����W������Ő��̕`��
		DrawLine3D(start.VGet(), goal.VGet(), GetColor(255, 255, 0));

		// �J�n���W�̏ꏊ�Ƃ��낢����
		DrawSphere3D(start.VGet(), 0.3f, 100, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
		// �S�[�����W�̉��F����
		DrawSphere3D(goal.VGet(), 0.3f, 100, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);
	}

	// ���͈̔͂ɓ�������U���������߂�
	if (m_cross.y > RANGE) {
		// �O�ς̂x�̒l���v���X�̎��̓v���C���[�͐��̉E�ɂ��܂�
		m_rot.y += TARGET_ROT_SPEED;
	}
	else
		if (m_cross.y < -RANGE)
		{
			// �O�ς̂x�̒l���}�C�i�X�̎��̓v���C���[�͐��̍��ɂ��܂�	
			m_rot.y -= TARGET_ROT_SPEED;
		}
	// �܂��͉�]�O�̃x�N�g����p�ӂ��܂�
   // �J����������v���C���[�����̃x�N�g�����쐬���܂�
	VECTOR base_dir = VGet(0.0f, 0.0f, -m_length);

	// �s���p�ӂ��܂�
	// X����]�s��
//	MATRIX mat_x = MGetRotX(TO_RADIAN(target1->rot.y));
	// Y����]�s��
	MATRIX mat_y = MGetRotY(TO_RADIAN(m_rot.y));

	// X����]��Y����]�����������̂łQ�̍s����P�ɂ܂Ƃ߂܂�
//	MATRIX mat = MMult(mat_x, mat_y);
	// ���̃x�N�g�����w����]�Ƃx����]�����܂�
	// �ȒP�Ɍ���������̋����̖_������Ă���
	VECTOR change_dir = VTransform(base_dir, mat_y);

	// �J�����̈ʒu�����Ă�����W������̈ʒu�ɍĐݒ�
	m_pos = m_look + change_dir;
}

//---------------------------------------------------------------------------------
// �J�������ǂɖ��܂�Ȃ��悤�ɂ���(���܂������Ȃ�)
//---------------------------------------------------------------------------------
void Camera::UseCameraUpdate(bool change_camera, Vector3* target_pos1, Vector3* target_pos2)
{
	if (change_camera)
	{
		MouseCamera(target_pos1);
	}
	else
	{
		TargetCamera(target_pos1, target_pos2);
	}
}

//---------------------------------------------------------------------------------
// �J�������ǂɖ��܂�Ȃ��悤�ɂ���(���܂������Ȃ�)
//---------------------------------------------------------------------------------
void Camera::HitObject(Vector3* obj_pos, Vector3* obj_size)
{
	if (m_before_pos.x + m_hit_box_size.x >= obj_pos->x - obj_size->x && m_before_pos.x - m_hit_box_size.x <= obj_pos->x + obj_size->x)
	{
		m_pos.z = m_before_pos.z;
		m_pos.x = m_before_pos.x;
	}
	if (m_before_pos.z + m_hit_box_size.z >= obj_pos->z - obj_size->z && m_before_pos.z - m_hit_box_size.z <= obj_pos->z + obj_size->z)
	{
		m_pos.z = m_before_pos.z;
		m_pos.x = m_before_pos.x;
	}
}

//---------------------------------------------------------------------------------
//	�`��O�̃J�����̃Z�b�g
//---------------------------------------------------------------------------------
// �߂�ǂ��������Ǌ撣���čH������
void Camera::DrawSet()
{

}

//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Camera::Draw()
{
	

	//	�J�����̐ݒ�
	SetCameraNearFar(0.1f, 3000.0f);
	SetupCamera_Perspective(TO_RADIAN(45.0f));
	// �J�������W�ƌ�����W��n���ăJ�����̐ݒ�
	SetCameraPositionAndTarget_UpVecY(m_pos.VGet(), m_look.VGet());

	// Effekseer��3D�\���̐ݒ��DX���C�u������3D�\���̐ݒ�ɓ���������B
	Effekseer_Sync3DSetting();
}

//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}

//---------------------------------------------------------------------------------
//	�J�����ړ��̍ۂ̃}�E�X�̊��x��ݒ�
//---------------------------------------------------------------------------------
void Camera::SetCameraSensi(float mouse_sensi)
{
	// �}�E�X���x�ɂӂ��킵���l�ɏC�����Ă���ۑ�����
	m_camera_mouse_sensi = mouse_sensi * MOUSE_SENSI_CORRECT;
}

//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::SetCamera(float height, float length)
{
	// �J�����̌���Y���W�̃v���X���̐ݒ�
	m_look_height = height;
	// �J��������ڕW�܂ł̋����̐ݒ�
	m_length = length;
}


//---------------------------------------------------------------------------------
//	�ڂ������ڕW���܂��悤�ɃJ�����̈ړ�����
//---------------------------------------------------------------------------------
void Camera::MoveCamera(Vector3* target_pos, int direction, float speed)
{
	// �v���C���[�̌��ɕt���ē���
	m_look.set(target_pos->x, target_pos->y + m_look_height, target_pos->z);

	if (direction == 0)
	{
		m_rot.y -= speed;
	}
	else // ������
	{
		m_rot.y += speed;
	}

	// �܂��͉�]�O�̃x�N�g����p�ӂ��܂�
	// �J����������v���C���[�����̃x�N�g�����쐬���܂�
	VECTOR base_dir = VGet(0.0f, 0.0f, -m_length);

	// �s���p�ӂ��܂�
	// X����]�s��
	MATRIX mat_x = MGetRotX(TO_RADIAN(m_rot.x));
	// Y����]�s��
	MATRIX mat_y = MGetRotY(TO_RADIAN(m_rot.y));

	// X����]��Y����]�����������̂łQ�̍s����P�ɂ܂Ƃ߂܂�
	MATRIX mat = MMult(mat_x, mat_y);
	// ���̃x�N�g�����w����]�Ƃx����]�����܂�
	// �ȒP�Ɍ���������̋����̖_������Ă���
	VECTOR change_dir = VTransform(base_dir, mat);

	// �J�����̈ʒu�����Ă�����W������̈ʒu�ɍĐݒ�
	m_pos = m_look + change_dir;
}

//---------------------------------------------------------------------------------
// �J�����V�F�C�N���s��
//---------------------------------------------------------------------------------
void Camera::CameraShakeLimited(float power, float time)
{
	// �U���̃p���[��0�̎�
	if (m_power == 0.0f)
	{
		// �U���p���[��ݒ�
		m_power = power;
		m_shake_time = power / time;
	}

	// �h��̋��������X�Ɏキ����
	m_power -= m_shake_time;
	// 0��艺���Ȃ��悤�ɂ���
	m_power = max(0.0f, m_power);

	// �h�ꂪ����Ƃ�
	if (m_power > 0.0f)
	{
		// �h�炷
		m_shake_pos.x = GetRandomF(-m_power, m_power);
		m_shake_pos.y = GetRandomF(-m_power, m_power);
		m_shake_pos.z = GetRandomF(-m_power, m_power);
	}
	else
	{
		// ��������Ȃ��Ƃ��͗h��Ȃ�
		m_shake_pos.clear();
	}
	// ������܂߂����W
	m_pos += m_shake_pos;
}


//---------------------------------------------------------------------------------
// �����̐ݒ�p�֐�
//---------------------------------------------------------------------------------
void Camera::SetCameraRot(Vector3 rot)
{
	m_rot.y = rot.y;
	// �܂��͉�]�O�̃x�N�g����p�ӂ��܂�
	// �J����������v���C���[�����̃x�N�g�����쐬���܂�
	VECTOR base_dir = VGet(0.0f, 0.0f, -m_length);

	// �s���p�ӂ��܂�
	// X����]�s��
	MATRIX mat_x = MGetRotX(TO_RADIAN(m_rot.x));
	// Y����]�s��
	MATRIX mat_y = MGetRotY(TO_RADIAN(m_rot.y));

	// X����]��Y����]�����������̂łQ�̍s����P�ɂ܂Ƃ߂܂�
	MATRIX mat = MMult(mat_x, mat_y);
	// ���̃x�N�g�����w����]�Ƃx����]�����܂�
	// �ȒP�Ɍ���������̋����̖_������Ă���
	VECTOR change_dir = VTransform(base_dir, mat);

	// �J�����̈ʒu�����Ă�����W������̈ʒu�ɍĐݒ�
	m_pos = m_look + change_dir;
}

//-------------------------------------------------------------------------------- -
// �J������������擾����֐�
//---------------------------------------------------------------------------------
Vector3 Camera::GetCameraRot()
{
	return m_rot;
}
