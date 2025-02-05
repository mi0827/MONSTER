#pragma once
//! @file TitleScene.h
//! @brief �^�C�g���V�[���̃N���X
class TitleScene : public Scene_Base
{
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

	//! @brief �^�C�g���̍X�V����
	void TitleUpdate();

	

private:
	//! �^�C�g���`�掞��
	static constexpr int TITLE_TIME_MAX = 5;
	//! �t���[���J�E���g�̃}�b�N�X
	static constexpr int  FLAME_MAX = 60;
	//! �t���[���J�E���g�p�ϐ�
	int m_count_flame = 0;
	//! �t���[��������ۂ̎��Ԃ�����o���ē����p�̕ϐ�
	int m_count_time = 0;

	enum Title_se
	{
		DECISION, // �^�C�g����ʂŎw��̃{�^���������ꂽ��

		SE_MAX,   // SE�̍ő吔
	};

	enum BGM
	{
		TITLE_BGM,  // �^�C�g����ʂŗ���BGM

		BGM_MAX // BGM�̍ő吔
	};

	// �^�C�g����ʂł̐؂�ւ��p
	enum Title_SCENES
	{
		TITLE, // �^�C�g�����
		MOVIE, // ������
	};
	// �^�C�g���V�[���̏�Ԃ�ۑ�����ϐ��i�ŏ��̓^�C�g����Ԃ���n�߂�j
	int m_title_mode_num = Title;

	bool m_start_flag = false; // �^�C�g����ʂŃ{�^���������ꂽ���ǂ����̃t���O

	//! �J�����N���X�̃I�u�W�F�N�g
	Camera camera;
	

	//! �e�L�X�g�I�u�W�F�N�g
	Text m_text;
	//! �ǂ̃e�L�X�g�t�@�C�����J����
	int m_text_num = 0;


	//! �v���C���[����p�ϐ�
	int m_movie = 0;
	//! �w�i�摜�p�̕ϐ�
	int m_background_image = 0;
};
