#include "DxLib.h"
#include <math.h>
#include "src/WinMain.h"



// �L�[���͂Ɋւ���ϐ�
char KeyBuffer[256];
int KeyFrame[256];
// �}�E�X���͂Ɋւ���ϐ�
int MouseLeftFrame;
int MouseRightFrame;
// ���4�̕ϐ��̓L�[�{�[�h�ƃ}�E�X�̉����ꂽ��
// ���擾���邽�߂ɕK�v�Ȋ֕ϐ�

// �}�E�X�̍��E�ړ��Ɋւ���ϐ�
int NowMouseX;
int NowMouseY;
int BeforeMouseX;
int BeforeMouseY;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	int StageModelHandle;
	int CharaModelHandle;
	int StageShadowMapHandle;
	int CharaShadowMapHandle;
	float Angle;
	VECTOR CharaPosition;

	SetBackgroundColor(100, 100, 100);
	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
	{
		// �G���[������������I��
		return -1;
	}

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	// �L�����N�^�[���f���̓ǂݍ���
	CharaModelHandle = MV1LoadModel("Data/Model/Player/Player.mv1");

	// �X�e�[�W���f���̓ǂݍ���
	StageModelHandle = MV1LoadModel("Data/ground.mqoz");

	// �X�e�[�W���f���p�̃V���h�E�}�b�v�n���h���̍쐬
	StageShadowMapHandle = MakeShadowMap(2048, 2048);

	// �L�����N�^�[���f���p�̃V���h�E�}�b�v�n���h���̍쐬
	CharaShadowMapHandle = MakeShadowMap(2048, 2048);

	// �J�����̈ʒu�ƌ�����ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 1500.0f, -1500.0f), VGet(0.0f, 800.0f, -800.0f));

	// �`�悷�鉜�s�������͈̔͂�ݒ�
	SetCameraNearFar(160.000f, 80000.000f);

	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea(StageShadowMapHandle, VGet(-4000.0f, -1.0f, -4000.0f), VGet(4000.0f, 4000.0f, 4000.0f));
	SetShadowMapDrawArea(CharaShadowMapHandle, VGet(-4000.0f, -1.0f, -4000.0f), VGet(4000.0f, 4000.0f, 4000.0f));

	// ���C�g�̕�����ݒ�
	SetLightDirection(VGet(0.5f, -0.5f, 0.5f));

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(StageShadowMapHandle, VGet(0.5f, -0.5f, 0.5f));
	SetShadowMapLightDirection(CharaShadowMapHandle, VGet(0.5f, -0.5f, 0.5f));

	// �X�e�[�W���f���p�̃V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(StageShadowMapHandle);
	MV1SetScale(StageModelHandle, VGet(100, 100, 100)); // ���f���̑傫��(10���̂P�̃T�C�Y)
	// �X�e�[�W���f���p�̃V���h�E�}�b�v�փX�e�[�W���f���̕`��
	MV1DrawModel(StageModelHandle);

	// �X�e�[�W���f���p�̃V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	// �L�����N�^�[�̈ʒu�ƂȂ�p�x��������
	Angle = 0.0f;

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// ��ʂ��N���A
		ClearDrawScreen();


		// �L�����N�^�[�̈ʒu�ƂȂ�p�x��ύX
		Angle += 0.0125f;
		if (Angle > DX_PI_F * 2.0f)
		{
			Angle -= DX_PI_F * 2.0f;
		}

		// �L�����N�^�[�̍��W���Z�o
		CharaPosition.x = sin(Angle) * 1000.0f;
		CharaPosition.z = cos(Angle) * 1000.0f;
		CharaPosition.y = 0.0f;

		// �L�����N�^�[���f���̍��W��ύX
		MV1SetPosition(CharaModelHandle, CharaPosition);


		// �L�����N�^�[���f���p�̃V���h�E�}�b�v�ւ̕`��̏���
		ShadowMap_DrawSetup(CharaShadowMapHandle);

		// �L�����N�^�[���f���p�̃V���h�E�}�b�v�փL�����N�^�[���f���̕`��
		MV1DrawModel(CharaModelHandle);

		// �L�����N�^�[���f���p�̃V���h�E�}�b�v�ւ̕`����I��
		ShadowMap_DrawEnd();


		// �`��ɃL�����N�^�[���f���p�̃V���h�E�}�b�v��
		// �X�e�[�W���f���p�̃V���h�E�}�b�v�̂ǂ�����g�p����
		SetUseShadowMap(0, StageShadowMapHandle);
		SetUseShadowMap(1, CharaShadowMapHandle);

		// �X�e�[�W���f���̕`��
		MV1DrawModel(StageModelHandle);

		// �L�����N�^�[���f���̕`��
		MV1DrawModel(CharaModelHandle);

		// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
		SetUseShadowMap(0, -1);
		SetUseShadowMap(1, -1);


		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// �V���h�E�}�b�v�̍폜
	//DeleteShadowMap(StageShadowMapHandle);
	DeleteShadowMap(CharaShadowMapHandle);

	// �X�e�[�W���f���̍폜
	MV1DeleteModel(StageModelHandle);

	// �L�����N�^�[���f���̍폜
	MV1DeleteModel(CharaModelHandle);

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}


//---------------------------------------------------------------------------------
//	�L�[�������ꂽ�u�Ԃ��擾����
bool PushHitKey(int key)
{
	if (KeyFrame[key] == 1)
	{
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------
//	�}�E�X��������Ă��邩���擾����
bool CheckMouseInput(int button)
{
	if (GetMouseInput() & button)
	{
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------
//	�}�E�X�������ꂽ�u�Ԃ��擾����
bool PushMouseInput(int button)
{
	if (button & MOUSE_INPUT_LEFT)
	{
		if (MouseLeftFrame == 1)
		{
			return true;
		}
	}

	if (button & MOUSE_INPUT_RIGHT)
	{
		if (MouseRightFrame == 1)
		{
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------
//	�}�E�X�̍��W���擾����
int GetMouseX() // X���W
{
	int mouse_x;
	int mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	return mouse_x;
}
int GetMouseY() // Y���W
{
	int mouse_x;
	int mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	return mouse_y;
}
//---------------------------------------------------------------------------------
//	�}�E�X�̈ړ��ʂ��擾����
int GetMouseMoveX()
{
	return NowMouseX - BeforeMouseX;
}
int GetMouseMoveY()
{
	return NowMouseY - BeforeMouseY;
}

//---------------------------------------------------------------------------------
//	�x�����W�A���ɕϊ�����֐�
float TO_RADIAN(float degree)
{
	return degree * 3.14159265f / 180.0f;
}

//---------------------------------------------------------------------------------
//	���W�A����x�ɕϊ�����֐�
float TO_DEGREE(float radian)
{
	return radian * 180.0f / 3.14159265f;
}