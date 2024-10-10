#pragma once

//---------------------------------------------------------------------------------
//	�J�����N���X
// Base�N���X���p��
class Camera
{
public:
	//---------------
	// �֐��̒�`
	//---------------
	// �R���X�g���N�^
	Camera();

	void Init();        //�@��������

	void PlayField_Init(); // �v���C��ʂ̏����ݒ�

	// �v���C���[�̏����󂯎��`�ɂ��܂�
	// ����̓v���C���[�̂����ɃJ�������������̏o
	// �v���C���[�̍��W�ƌ������󂯎���悤�ɂ��܂�
	//! @brief �X�V����
	//! @param �ڂ������ڕW�̍��W
	void Update(Vector3* target_pos);

	//! @brief �^�[�Q�b�g�J�����̍X�V����
	//! @param �J�����̎薈���ɂ���^�[�Q�b�g�̍��W�ƌ���
	//! @param �J�����̉����ɂ���^�[�Q�b�g�̍��W
	void TargetCamera(Transform* target1, Vector3* target_pos2);

	//! @brief �J�������ǂɖ��܂�Ȃ��悤�ɂ���
	void Hit_Object(Vector3* obj_pos, Vector3* obj_size);
	//! @brief �`�揈���̑O�ɃJ�����A��ʂ̃Z�b�g
	void Draw_Set();
	//! @brief �`�揈��
	void Draw();
	//! @brief �I������
	void Exit();

	//! @brief �J�����̍��������Ȃǂ�ݒ肷��֐�
	//! @param �J�����̌�����W�̍�����(�f�t�H���g�Ńv���C���[���̒l�����Ă���)
	//! @param �J��������ڕW�܂ł̋���(�f�t�H���g�Ńv���C���[���̒l�����Ă���)
	void SetCamera(float height = CAMERA_HEIGHT_PLAYER, float length = CAMERA_LENGTH);

	//! @brief �ڂ������ڕW���܂��悤�ɃJ�����̈ړ�����
	//! @param �ڂ������^�[�Q�b�g
	//! @param �U�������������(1 : �E, 2 : ��)
	//! @param �ړ�������������
	void MoveCamera(Vector3* target_pos, int direction, float speed);

	//! @brief �J�����V�F�C�N���s��(�ŏI�I�ɗh�ꂪ��܂�)�֐�
	//! @param �J�����̐U������p���[
	//! @param �ǂꂭ�炢�̎��ԗh��ė~������
	void CameraShakeLimited(float power, float time);

	//! @breif �J�����V�F�C�N���s��(�ꐶ�h���)�֐�
	//! @param �J�����̐U������p���[
	//void CameraShakeInfinite(float power);

	enum Direction
	{
		right, // �E
		left,   // ��
	};

	// �J�����ƈڂ��W�I�Ƃ̋���
	static constexpr float CAMERA_LENGTH = 50.0f;          // �v���C���[
	static constexpr float CAMERA_MONSER_LENGTH = 100.0f; // �����X�^�[
	// �J�������ڂ����������̂���y���W���ω�������l
	static constexpr float CAMERA_HEIGHT_PLAYER = 5.0f; // �v���C���[
	static constexpr float CAMERA_HEIGHT_MONSTER = 20.0f;

	// �J�����̉�]�X�s�[�h
	static constexpr float MOUSE_CAMERA_ROT_SPEED = 0.2f;  // �}�E�X�p
	static constexpr float PAD_CAMERA_ROT_SPEED = 3.0f;      // �p�b�h�p

	static constexpr float UP_ANGLE_MAX = 30.0f;           // �J�����̏�A���O���̍ő�
	static constexpr float LOWER_ANGLE = 0.0f;             // �J�����̉��A���O���̍Œ�i�n�ʂɖ��܂�Ȃ����x�j
	static constexpr float BOX_SIZE = 4.0f;                     // �{�b�N�X�̃T�C�Y
	static constexpr float BOX_SIZE_HALF = (BOX_SIZE / 2.0f); // �����̃T�C�Y

	// �^�[�Q�b�g�J�����̐U��������x
	static constexpr float TARGET_ROT_SPEED = 2.5f;
	// �^�[�Q�b�g�J�����̐U������\�͈�
	static constexpr float RANGE = 1000;

	//---------------
	// �ϐ��̒�`
	//---------------
public:
	//! �ڂ������^�[�Q�b�g�Ƃ̋���
	float m_length = 0;

	//! �J������������W
	Vector3 m_look;
	Vector3 m_look_2{ 0.0f,0.0f,0.0f };
	float m_look_height = 0; // �J������������W��Y���W�̃v���X���p�̕ϐ�
	//! �J�����̍��W
	Vector3 m_pos;
	//! �J�����̌���
	Vector3 m_rot;
public:
	//--------------------
	//! ��ʕ����p�̕ϐ�
	int m_screen_field = 0;   // �`�悷���ʂ�����摜�p�ϐ�
	Vector2 m_field_pos = { 0.0f, 0.0f };  // �`�悷����W
	Vector2 m_field_size = { 0.0f, 0.0f, }; // �`�悷��T�C�Y

private:
	//! �}�E�X�̈ړ��ʗp�̕ϐ�
	float m_mouse_move_x = 0.0f; //! X���W�̈ړ���
	float m_mouse_move_y = 0.0f; //! Y���W�̈ړ���
	Vector3 m_before_pos = { 0.0f,0.0f,0.0f };   //! ���t���[���ړ��O�̍��W�������p�̕ϐ�
	Vector3 m_hit_box_size = { 0.0f,0.0f,0.0f }; //! �ǂƂ̓����蔻��p�̕ϐ�


	//�I�J�����V�F�C�N�ł̐U���̋���
	float m_power = 0;
	//! �J�����V�F�C�N�łǂꂾ���̍��W�����炷��
	Vector3 m_shake_pos;
	// �ǂꂾ���h��Ă��Ăق����̂�
	float m_shake_time = 0;

public:
	int pad_no = 0;				//! ���Ԃ̃p�b�h���g���Ă���̂�
	void SetPadNo(int no)
	{
		pad_no = no;
	}



};
