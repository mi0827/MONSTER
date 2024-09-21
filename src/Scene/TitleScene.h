#pragma once

// �^�C�g���V�[���̃N���X
class TitleScene : public Scene_Base
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

	//! @brief �G���ABOX�̏����ݒ�
	void SetAeraBoxSet();


public:
	

	

private:
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

	// ���Ԋu�ő��݂���G���A���܂Ƃ߂�����
	enum Area
	{
		next_scene, // ���̃V�[���ɍs�����߂̃G���A

		max
	};


	// ��ʐ؂�ւ��p�̕ϐ�
	int m_title_scene = 0;

	bool m_start_flag = false; // �^�C�g����ʂŃ{�^���������ꂽ���ǂ����̃t���O

	//! �J�����N���X�̃I�u�W�F�N�g
	Camera camera;

	// �t�B�[���h�I�u�W�F�N�g
	TitleField field;

	// �v���C���[�̃I�u�W�F�N�g
	CharacterBase* player;

	// �G���A�p��BOX
	BoxCollision m_area_box[max];
	// BOX�̍��W
	Vector3 m_box_pos[max];
	// BOX�̃T�C�Y�i�S���ꏏ�j
	Vector3 m_box_size;
};
