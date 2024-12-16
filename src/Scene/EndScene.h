#pragma once

//! @file EndScene.h
//! @brief �^�C�g���V�[���̃N���X
class EndScene : public Scene_Base
{
	//int effeckt_h;
public:

	//! �R���X�g���N�^
	EndScene();
	//! �f�X�g���N�^
	~EndScene();


	//! @brief ��������
	void Init()override;

	//! @brief �X�V����
	void Update()override;

	//! @brief �`�揈��
	void Draw()override;

	//! @brief �I������
	void Exit()override;

	//! @brief �t�B�[���h�ƃL�����N�^�[�Ƃ̓����蔻��
	void HitField()override;

	//! @brief �I�v�V�������j���[�ł�����Ă����l�𔽉f����֐�
    //! @param BGM�̉���
	//! @param SE�̉���
	//! @param �}�E�X���x
	void OptionValuesReflect(int bgm, int se, int mouse)override;

public:
	

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

private:
	////! �`�悵�����e�L�X�g��ԍ��ŊǗ�
	//enum Text
	//{
	//	// end_text,             // �G���h�V�[���Ƃ����̂��킩��₷������
	//	return_title,          // �^�C�g���V�[���Ɉړ�����
	//	return_qusetarea, // �N�G�X�g�I���G���A�Ɉړ�

	//	text_max
	//};


	// �e�L�X�g�I�u�W�F�N�g
	Text m_text;
	
	// �G���h�V�[���ŕ`�悷��e�L�X�g�̐�
	enum EndText
	{
		text1,
		text2,
		text3,
		text4,
		text_max
	};



	// ��ʐ؂�ւ��p�̕ϐ�
	int m_title_scene = 0;

	bool m_start_flag = false; // �^�C�g����ʂŃ{�^���������ꂽ���ǂ����̃t���O

	// �J�����N���X�̃I�u�W�F�N�g
	Camera camera;

	// �t�B�[���h�I�u�W�F�N�g
	Field field;

	// �v���C���[�̃I�u�W�F�N�g
	CharacterBase* player;

private:
	//! �V�[���ύX�łǂ���̃V�[���Ɉړ����邩��ۑ�����
	int m_change_scene = 0;
};
