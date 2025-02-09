#pragma once
#pragma once
//! @file StoryScene.h
//! @brief �^�C�g���V�[���̃N���X
class StoryScene : public Scene_Base
{
	//int effeckt_h;
public:
	// ��������
	void Init()override;

	// �X�V����
	void Update()override;

	// �`�揈��
	void Draw()override;

	// �I������
	void Exit()override;

	//! @brief �t�B�[���h�ƃL�����N�^�[�Ƃ̓����蔻��
	void HitField()override;

	//! @brief �I�v�V�������j���[�ł�����Ă����l�𔽉f����֐�
	//! //! @param BGM�̉���
	//! @param SE�̉���
	//! @param �}�E�X���x
	void OptionValuesReflect(int bgm, int se, int mouse)override;

	//! @brief �G���ABOX�̏����ݒ�
	void SetAeraBoxSet();

private:
	enum SE
	{
		DECISION, // �X�g�[���[��ʂŎw��̃{�^���������ꂽ��

		SE_MAX,   // SE�̍ő吔
	};

	//enum BGM
	//{
	//	Story_BGM,  // �^�C�g����ʂŗ���BGM

	//	BGM_MAX // BGM�̍ő吔
	//};

	

	// ���Ԋu�ő��݂���G���A���܂Ƃ߂����́i���̃G���A�Ńe�L�X�g�̐i�s���i�߂�j
	enum Area
	{

		story1, // �X�g�[���[�P
		story2, // �X�g�[���[�Q
		story3, // �X�g�[���[�R
		story4, // �X�g�[���[�S
		story5, // �X�g�[���[�T
		story6, // �X�g�[���[6
		next_scene, // ���̃V�[���ɍs�����߂̃G���A

		Area_Max
	};

	// �X�g�[���[�̐�
	static constexpr int STORY_NUM_MAX = next_scene;

	// ��ʐ؂�ւ��p�̕ϐ�
	int m_title_scene = 0;

	bool m_start_flag = false; // �^�C�g����ʂŃ{�^���������ꂽ���ǂ����̃t���O

	//! �J�����N���X�̃I�u�W�F�N�g
	Camera camera;

	// �G���A�p��BOX
	BoxCollision m_area_box[Area_Max];
	// BOX�̍��W
	Vector3 m_box_pos[Area_Max]
	{
		{0.0f, 50.0f, 750},
		{0.0f, 50.0f, 650},
		{0.0f, 30.0f, 550},
		{0.0f, 30.0f, 450},
		{0.0f, 0.0f, 350},
		{0.0f, 0.0f, 250},
		{0.0f, 0.0f, 150},
	};
	// BOX�̃T�C�Y�i�S���ꏏ�j
	Vector3 m_box_size;

	// �e�L�X�g�I�u�W�F�N�g
	Text m_text;
	// �ǂ̃e�L�X�g�t�@�C�����J����
	int m_text_num = 0;

	// ���Ԃ̃G���A�Ɠ����蔻�肪����������ۑ�����
	int hit_area = 0;
};
