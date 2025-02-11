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
	static constexpr int TITLE_TIME_MAX = 60;
	//! �t���[���J�E���g�̃}�b�N�X
	static constexpr int  FLAME_MAX = 60;
	//! �t���[���J�E���g�p�ϐ�
	int m_count_flame = 0;
	//! �t���[��������ۂ̎��Ԃ�����o���ē����p�̕ϐ�
	int m_count_time = 0;

	// �X�y�[�X�L�[���������������邽�߂̂���
	//! �t�H���g�̓����x�̍ő�l
	static constexpr int TEXT_BLEND_MAX = 255;
	//! �t�H���g�̓����x�̍ŏ��l
	static constexpr int TEXT_BLEND_MIN = 0;
	//! �u�����h����ύX���邽�߂̕ϐ�
	int m_text_blend_value = 0;
	//! �u�����h��������A�����ɒB�����Ƃ��𔻒f���邽�߂̃t���O
	//! true : �B�����Afalse : �B���Ă��Ȃ�
	bool m_blend_flag = false;
	//! �u�����h�����グ�邩�����邩�̃t���O
	//! true : ���₷�Afalse : ���炷
	bool m_blend_change_flag = true;


	//! �^�C�g���V�[����SE
	Sound m_sound;
	enum Title_se
	{
		decision, // �^�C�g����ʂŎw��̃{�^���������ꂽ��
		
		SE_MAX,   // SE�̍ő吔
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
