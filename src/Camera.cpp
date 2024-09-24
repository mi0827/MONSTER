#include "WinMain.h"
#include "System/Vector3.h"
#include "System/Vector2.h"
#include "src/System/Spotlight.h"
#include "src/System/Transform.h"
#include "Camera.h"


constexpr float CAMERA_LENGTH = 50.0f;          // �v���C���[����J�����܂ł̋���
// �J�����̉�]�X�s�[�h
constexpr float MOUSE_CAMERA_ROT_SPEED = 0.2f;  // �}�E�X�p
constexpr float PAD_CAMERA_ROT_SPEED = 3.0f;    // �p�b�h�p
constexpr float UP_ANGLE_MAX = 30.0f;           // �J�����̏�A���O���̍ő�
constexpr float LOWER_ANGLE = -5.0f;            // �J�����̉��A���O���̍Œ�i�n�ʂɖ��܂�Ȃ����x�j
constexpr float BOX_SIZE = 4.0f;                   // �{�b�N�X�̃T�C�Y
constexpr float BOX_SIZE_HALF = (BOX_SIZE / 2.0f); // �����̃T�C�Y

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
}

// ��������
void Camera::Init()
{
}

//---------------------------------------------------------------------------------
//	// �v���C��ʂ̏����ݒ�
//---------------------------------------------------------------------------------
void Camera::PlayField_Init()
{
	//m_field_size.set(SCREEN_W , SCREEN_H);                                                                                          // �`�悷���ʂ̃T�C�Y�̐ݒ�
	//m_screen_field = MakeScreen((int)m_field_size.x, (int)m_field_size.y);                                             // �`���ʂ��������ނ��߂̏����ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 2.0f, -50.0f), VGet(0.0f, 0.0f, 1.0f));  // �J�����̐ݒ�
}

//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Camera::Update(Vector3* target_pos)
{
	m_before_pos.set(m_pos); //< �ړ��O�̍��W�̐ݒ�
	// �v���C���[�̌��ɕt���ē���
	m_look.set(target_pos->x, target_pos->y + 5.0f, target_pos->z);
	// �}�E�X�̈ړ���
	m_mouse_move_x = (float)GetMouseMoveX();
	m_mouse_move_y = (float)GetMouseMoveY();

	// �J�����̌�����ς���
	// �i�QD�̃}�E�X�̈ړ��ʂ����̂܂܊p�x�ɓn���Ƒ傫���̂ŏ������������Ă��܂��j
	m_rot.x += m_mouse_move_y * MOUSE_CAMERA_ROT_SPEED;
	m_rot.y += m_mouse_move_x * MOUSE_CAMERA_ROT_SPEED;

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

	//	�Q�[���p�b�h�̉E�X�e�B�b�N�̒l���g���Č����ϐ��i m_rot �j�̒l��ύX
	// ���X�e�b�N�Ńv���C���[�̌�������W�̍X�V
	// �Q�[���p�b�h�̏����擾�iXINPUT �̏��j
	XINPUT_STATE input;
	// �Q�[���p�b�h�̏����ۂ��Ǝ擾
	GetJoypadXInputState(pad_no, &input);
	// �ړ��p�x�N�g���p�ϐ�
	Vector3 rot;
	// ���X�e�B�b�N�̒l��ݒ�
	rot.y = input.ThumbRX;
	rot.x = input.ThumbRY;
	// -32768 �` 32767 ��-1.0f�@�`�@1.0f�ɂ��܂�
	rot /= 32768.0f;
	// ���̈ړ��p�x�N�g���̑傫����������x�傫���������ړ������悤�Ǝv���܂�
	if (rot.GetLength() > 0.5f)
	{
		m_rot.y += rot.y * PAD_CAMERA_ROT_SPEED;
		m_rot.x -= rot.x * PAD_CAMERA_ROT_SPEED;
		// m_rot += rot * PAD_CAMERA_ROT_SPEED;  // ���̈ړ��x�N�g�������W�ړ�
	}

	// �܂��͉�]�O�̃x�N�g����p�ӂ��܂�
	// �J����������v���C���[�����̃x�N�g�����쐬���܂�
	VECTOR base_dir = VGet(0.0f, 0.0f, -CAMERA_LENGTH);

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
// �J�������ǂɖ��܂�Ȃ��悤�ɂ���(���܂������Ȃ�)
//---------------------------------------------------------------------------------
void Camera::Hit_Object(Vector3* obj_pos, Vector3* obj_size)
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
void Camera::Draw_Set()
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
	
}

//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}

//---------------------------------------------------------------------------------
//	�ڂ������ڕW���܂��悤�ɃJ�����̈ړ�����
//---------------------------------------------------------------------------------
void Camera::MoveCamera(Vector3* target_pos, int direction, float speed)
{
	// �v���C���[�̌��ɕt���ē���
	m_look.set(target_pos->x, target_pos->y + 5.0f, target_pos->z);
	
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
	VECTOR base_dir = VGet(0.0f, 0.0f, -CAMERA_LENGTH);

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
