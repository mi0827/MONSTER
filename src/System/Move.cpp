#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/Collision/BoxCollision.h"
#include "src/Model/Model.h"
#include "src/Collision/CapsuleCollision.h"
#include "Move.h"


Move::Move()
{
}


Move::~Move()
{
}


//---------------------------------------------------------------------------
// �ړ��Ɋւ���X�V�����p�֐�
//---------------------------------------------------------------------------
void Move::Update(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, const float* mov_speed, Vector3* player_pos, PAD_NO m_pad_no, Vector3 m_mov)
{
	// �L�����ƃJ�����̌����̉�]�̍�
	m_difference_rot = player_rot->y - camera_rot->y;

	// �ړ����̓_�b�V������
		// �Q�[���p�b�h�̓��͏�Ԃ��Ƃ�
		//	�Q�[���p�b�h�̍��X�e�B�b�N�̒l���g���č��W�i m_pos �j�̒l��ύX
		// ���X�e�b�N�Ńv���C���[�̌�������W�̍X�V
		// �Q�[���p�b�h�̏����擾�iXINPUT �̏��j
	XINPUT_STATE input = { {'\0'}, '\0','\0',0,0,0,0 };
	// �Q�[���p�b�h�̏����ۂ��Ǝ擾
	// GetJoypadXInputState(DX_INPUT_PAD1, &input);
	// GetJoypadXInputState((int) pad_no, &input);
	//GetJoypadXInputState((int)((PAD_NO)pad_no), &input);
	switch (m_pad_no)
	{
	case PAD_NO::PAD_NO1:
		GetJoypadXInputState(DX_INPUT_PAD1, &input);
		break;
	case PAD_NO::PAD_NO2:
		GetJoypadXInputState(DX_INPUT_PAD2, &input);
		break;
	case PAD_NO::PAD_NO3:
		GetJoypadXInputState(DX_INPUT_PAD3, &input);
		break;
	case PAD_NO::PAD_NO4:
		GetJoypadXInputState(DX_INPUT_PAD4, &input);
		break;
	}
	// ���X�e�B�b�N�̒l��ݒ�
	m_mov.x = input.ThumbLX;
	m_mov.z = input.ThumbLY;
	// -32768 �` 32767 ��-1.0f�@�`�@1.0f�ɂ��܂�
	m_mov /= 32768.0f;

	if (m_mov.GetLength() > 0.5f)
	{
		Move_GamePad(m_check_move, &m_mov, camera_rot, player_rot, player_pos, mov_speed);
	}

	// �����ꂽ�u�ԂɐU������悤�̕⊮�p�J�E���g��������
	if (/*PushHitKey((KEY_INPUT_W)) ||*/ PushHitKey((KEY_INPUT_A)) || PushHitKey((KEY_INPUT_S)) || PushHitKey((KEY_INPUT_D)))
	{
		// �⊮�̒l�����Z�b�g����
		m_rot_complementation = 0;
		// ��x�����ꂽ��U������ۊǂ����Ȃ���������L�����̌�����ς���
		m_complementation_flag = true;
	}

	// WASD�L�[�Ńv���C���[�̈ړ�
	// �E��ړ�
	if (CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_W))
	{
		Move_Diagonally_Up_Right(m_check_move, camera_rot, player_rot, player_pos, mov_speed);
	}
	else //����ړ�
		if (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_W))
		{
			Move_Diagonally_Up_Left(m_check_move, camera_rot, player_rot, player_pos, mov_speed);
		}
		else // �E���ړ�
			if (CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_S))
			{
				Move_Oblique_Lower_Right(m_check_move, camera_rot, player_rot, player_pos, mov_speed);
			}
			else // �����ړ�
				if (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_S))
				{
					Move_Oblique_Lower_Left(m_check_move, camera_rot, player_rot, player_pos, mov_speed);
				}
				else // ��ړ�
					if (CheckHitKey(KEY_INPUT_W))
					{
						Move_Front(m_check_move, camera_rot, player_rot, player_pos, mov_speed);
					}
					else // ���ړ�
						if (CheckHitKey(KEY_INPUT_S))
						{
							Move_Dhindo(m_check_move, camera_rot, player_rot, player_pos, mov_speed);
						}
						else // ���ړ�
							if (CheckHitKey(KEY_INPUT_A))
							{
								Move_Left(m_check_move, camera_rot, player_rot, player_pos, mov_speed);
							}
							else // �E�ړ�
								if (CheckHitKey(KEY_INPUT_D))
								{
									Move_Right(m_check_move, camera_rot, player_rot, player_pos, mov_speed);
								}


	
	// �⊮��ԂȂ�
	if (m_complementation_flag)
	{
		m_rot_complementation += 5.0f;

		// �⊮�̒l�𑝂₷
		if (m_rot_flag)
		{
			// �⊮����Ă���l���v���C���[�̌�����ύX����
			player_rot->y = camera_rot->y + m_rot_complementation;
		}
		else
		{
			// �⊮����Ă���l���v���C���[�̌�����ύX����
			player_rot->y = camera_rot->y - m_rot_complementation;
		}

		// �⊮�̒l�����̒l�ȏ�ɂȂ�����
		if (m_rot_complementation >= m_rot_complementation_max)
		{
			//�⊮���������̂Ńt���O��������
			m_complementation_flag = false;
			//m_rot_complementation = 0;
		}
	}

}

//---------------------------------------------------------------------------
// �L�����N�^�[�̕ǎC��p�֐�(�{�b�N�X)
//---------------------------------------------------------------------------
void Move::Move_Hit(Vector3* player_pos, Vector3* before_pos, Vector3* hit_size, BoxCollision* box)
{
	if (before_pos->x + hit_size->x >= box->m_box.hit_pos.x - box->m_box.half_size.x && before_pos->x - hit_size->x <= box->m_box.hit_pos.x + box->m_box.half_size.x)
	{
		// �c���������߂�
		player_pos->z = before_pos->z;
	}
	if (before_pos->z + hit_size->z >= box->m_box.hit_pos.z - box->m_box.half_size.z && before_pos->z - hit_size->z <= box->m_box.hit_pos.z + box->m_box.half_size.z)
	{
		// �c���������߂�
		player_pos->x = before_pos->x;
	}
}


//---------------------------------------------------------------------------
// �L�����N�^�[�̕ǎC��p�֐�(�~)
//---------------------------------------------------------------------------
void Move::Move_Hit_Capsule(Vector3* player_pos, float r, CapsuleCollision* capsule)
{
	// ���ꂼ��̍X�V�������I������̂Ńv���C���[��NPC�̈ʒu�֌W�����苗���߂Â��Ȃ��悤�ɂ��܂�
	// �P�F�v���C���[��NPC�̋��������߂�
	float distance = GetVector3Distance(*player_pos, capsule->m_capsule.pos1);
	// �Q�F��̋��������߂�i���ꂼ��̔��a�j
	float radius = r + capsule->m_capsule.radius;

	// �R�F�Q�L�����̋�������̒��������Z��������
	if (distance < radius) {
		// 4�F�ǂꂭ�炢���ɓ����Ă��邩�i���̒����������~���d�Ȃ��Ă���
		float in_lengef = radius - distance;
		// �T�F�ǂ̂��炷��
		Vector3 dir = *player_pos - capsule->m_capsule.pos1;

		// �U�F���̃x�N�g���̒����𒆂ɓ����Ă����钷���ɔ����ɂ��܂�
		dir.SetLength(in_lengef);
		// 7�F���̕������v���C���[���W���ړ�������
		*player_pos += dir;

	}
}

//---------------------------------------------------------------------------
// �Q�[���p�b�h�̈ړ��p�֐�(�Q�[���p�b�h�p)
//---------------------------------------------------------------------------
void Move::Move_GamePad(bool* m_check_move, Vector3* mov, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed)
{

	*m_check_move = true; // �����Ă���
	// �����Ă�������ɍ��W�ړ�
	// �����蔻�肪���鎞�͍��W�ړ������Ȃ�
	//	���̃x�N�g������]�����邽�߂̍s����쐬���܂��B
	MATRIX mat_y = MGetRotY(TO_RADIAN(camera_rot->y));
	//	���̍s����g���ăx�N�g������]�����܂��B
	*mov = GetVector3VTransform(*mov, mat_y);
	// �ړ��x�N�g���̂����̂�����������߂܂�
	player_rot->y = TO_DEGREE(atan2f(mov->x, mov->z));
	// �ړ��x�N�g���̑傫���� PLAYER_MOV_SPEED �̂��������ɂ��܂�
	mov->SetLength(*mov_speed);
	// ���̈ړ��x�N�g�������W�ړ�
	*player_pos += *mov;

}

//---------------------------------------------------------------------------
// �O�ړ�
//---------------------------------------------------------------------------
void Move::Move_Front(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed)
{
	//�@��ʉ��F�J�����̂�������̋t�̕���
	player_rot->y = camera_rot->y;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	player_pos->x += *mov_speed * sinf(TO_RADIAN(player_rot->y));
	player_pos->z += *mov_speed * cosf(TO_RADIAN(player_rot->y));
}

//---------------------------------------------------------------------------
// ���ړ�
//---------------------------------------------------------------------------
void Move::Move_Dhindo(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed)
{
	// ��ʎ�O�i�J�����̂�������j
	m_rot_flag = true;
	m_rot_complementation_max = 180.0f;
	//player_rot->y = camera_rot->y + 180.0f;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	player_pos->z += *mov_speed * cosf(TO_RADIAN(player_rot->y));
	player_pos->x += *mov_speed * sinf(TO_RADIAN(player_rot->y));
}

//---------------------------------------------------------------------------
// ���ړ�
//---------------------------------------------------------------------------
void Move::Move_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed)
{

	// ��ʂ��猩�āF��
	
	// ��ʂ��猩�āF�E
	if (m_difference_rot <= 90 && m_difference_rot >= -90)
	{
		m_rot_flag = false;
		m_rot_complementation_max = 90.0f;
	}
	else
	{
		m_rot_flag = true;
		m_rot_complementation_max = 90.0f;
	}
	if (m_complementation_flag == false)
	{
		player_rot->y = camera_rot->y - 90;
	}
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	player_pos->x += *mov_speed * sinf(TO_RADIAN(player_rot->y));
	player_pos->z += *mov_speed * cosf(TO_RADIAN(player_rot->y));
}

//---------------------------------------------------------------------------
// �E�ړ�
//---------------------------------------------------------------------------
void Move::Move_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed)
{
	// ��ʂ��猩�āF�E
	if (m_difference_rot < 90 && m_difference_rot > -90)
	{
		m_rot_flag = true;
		m_rot_complementation_max = 90.0f;
	}
	else
	{
		m_rot_flag = false;
		m_rot_complementation_max = 90.0f;
	}
	if (m_complementation_flag == false)
	{
		player_rot->y = camera_rot->y +90;
	}
	
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�	
	Vector3 move;
	player_pos->x += *mov_speed * sinf(TO_RADIAN(player_rot->y));
	player_pos->z += *mov_speed * cosf(TO_RADIAN(player_rot->y));
}

//---------------------------------------------------------------------------
// �E�΂ߏ�ւ̈ړ�
//---------------------------------------------------------------------------
void Move::Move_Diagonally_Up_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed)
{
	// ��ʂ��猩�āF�E
	m_rot_flag = true;
	//player_rot->y = camera_rot->y + 45;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�		
	player_pos->x += *mov_speed * sinf(TO_RADIAN(player_rot->y));
	player_pos->z += *mov_speed * cosf(TO_RADIAN(player_rot->y));
}

//---------------------------------------------------------------------------
// ���΂ߏ�ւ̈ړ�
//---------------------------------------------------------------------------
void Move::Move_Diagonally_Up_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed)
{
	// ��ʂ��猩�āF��
	m_rot_flag = false;
	// player_rot->y = camera_rot->y - 45;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�		
	player_pos->x += *mov_speed * sinf(TO_RADIAN(player_rot->y));
	player_pos->z += *mov_speed * cosf(TO_RADIAN(player_rot->y));
}

//---------------------------------------------------------------------------
// �E�΂߉��ւ̈ړ�
//---------------------------------------------------------------------------
void Move::Move_Oblique_Lower_Right(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed)
{
	// ��ʎ�O�i�J�����̂�������j
	player_rot->y = camera_rot->y + 135.0f;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	player_pos->x += *mov_speed * sinf(TO_RADIAN(player_rot->y));
	player_pos->z += *mov_speed * cosf(TO_RADIAN(player_rot->y));
}

//---------------------------------------------------------------------------
// ���΂߉��ւ̈ړ�
//---------------------------------------------------------------------------
void Move::Move_Oblique_Lower_Left(bool* m_check_move, Vector3* camera_rot, Vector3* player_rot, Vector3* player_pos, const float* mov_speed)
{
	// ��ʎ�O�i�J�����̂�������j
	player_rot->y = camera_rot->y + 225.0f;
	// �����Ă���
	*m_check_move = true;
	// �����Ă�������ɍ��W�ړ�
	player_pos->x += *mov_speed * sinf(TO_RADIAN(player_rot->y));
	player_pos->z += *mov_speed * cosf(TO_RADIAN(player_rot->y));
}
