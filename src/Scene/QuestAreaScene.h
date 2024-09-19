
#pragma once

// �^�C�g���V�[���̃N���X
class QuestAreaScene : public Scene_Base
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

	// �^�C�g����ʂł̐؂�ւ��p
	enum Title_SCENES
	{
		TITLE, // �^�C�g�����
		MOVIE, // ������
	};

	// ��ʐ؂�ւ��p�̕ϐ�
	int m_title_scene = 0;

	bool m_start_flag = false; // �^�C�g����ʂŃ{�^���������ꂽ���ǂ����̃t���O

	// �J�����N���X�̃I�u�W�F�N�g
	Camera camera;

	// �t�B�[���h�I�u�W�F�N�g
	TitleField field;

	// �v���C���[�̃I�u�W�F�N�g
	CharacterBase* player;

	// ��t��̃I�u�W�F�N�g
	Receptionist receptionist;
};
