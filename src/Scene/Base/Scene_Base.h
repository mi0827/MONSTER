#pragma once

// �V�[���N���X�����̃x�[�X�N���X
class Scene_Base
{
public:
	//--------------------
	// �萔
	//--------------------
	static constexpr int SAMPLEPLAYER = 0; // �T���v���v���C���[�̔ԍ�
	static constexpr int MUTANT = 0;           // �~���[�^���g�̔ԍ�
	static constexpr int MONSTER = 1;         // �����X�^�[�̔ԍ�

	//! @brief �ǂ̃L�����N�^�[���g������ݒ肷��֐�
	//! @param �ǂ̃v���C���[���g�����̔ԍ�
	//! @param �ǂ̃����X�^�[���g�����̔ԍ�
	void SetCharacter(int player_num = 0, int monster_num = 0);

	//! @brief ��������
	virtual void Init() = 0;
	//! @brief
	//! @param BGM�̃{�����[��
	//! @param SE�̃{�����[��
	virtual void Update() = 0;
	//! @brief �`�揈��
	virtual void Draw() = 0;
	//! @brief �I������
	virtual void Exit() = 0;
	//! @brief �t�B�[���h�Ƃ̓����蔻��
	virtual void HitField() = 0;


	//! @bom,se �̉��ʂ�ݒ肷��p�̊֐�
	// void SetSoundSize(int bgm_volume, int se_volume);

	//! @brief �V���h�[�}�b�v�p�̏������֐�
	void ShadowMapInit();

	//! @brief �v���C���[�̃V���h�[�}�b�v�͈̔͂̐ݒ�
	void SetPlayerShadowMapArea(Vector3 player_pos);

	//! @brief �`��Ɏg�p����V���h�E�}�b�v�̐ݒ�������i������g��Ȃ��ƃV���h�[�}�b�v���g���Ȃ��j
	void UseShadowMapSet();

	//! @brief �V���h�[�}�b�v�̍폜
	void ExitShadowMap();

	//! @brief �X�N���[�����W�ɕ�����`�悷�邽�߂̍��W��ݒ肷��֐�
	//! @param �ݒ肵�������W
	//! @param �ݒ肵�����W����ǂꂾ�����炵�������̒l(�f�t�H���g�ł��炳�Ȃ��悤�ɐݒ肵�Ă���)
	VECTOR DrawStringWrold(Vector3 pos, Vector3 shift_pos = { 0.0f,0.0f,0.0f });

	//! @brief ���ɍs�������V�[�����Z�b�g����֐�
	//! @param ���ɍs�������V�[���ԍ�
	void SetNextScene(int next_scene);



public:
	//! ��b���t���[�����̕ϊ��p�萔
	const int FLAME_MAX = 60;

	//! �V�[���̐؂�ւ����s���Ă������t���O (true�ɂȂ�����V�[���̐؂�ւ��\)
	bool m_scene_change_judge = false;

	//! �v���C���[�p�̃V���h�[�}�b�v�p�ϐ�
	int m_player_shadowMap_handle = 0;
	//! �V���h�[�}�b�v�p�̕ϐ�
	int m_shadowMap_handle = 0;

	// �V���h�[�}�b�v�̃��C�g�̊p�x
	float m_light_angle = 0;
	// ���C�g�̃x�N�g��
	VECTOR m_light_direction;


	//! �ǂ̃v���C���[���g�����̔ԍ���ۑ�����
	int m_player_num = 0;
	//! �ǂ̃����X�^�[���g�����̔ԍ���ۑ�����
	int m_monster_num = 0;

	//! �J�����̌�����ۑ�����p�̕ϐ�
	Vector3 m_camera_rot{0.0f,0.0f,0.0f};


	// ���ׂẴV�[���ԍ�
	enum Scene
	{
		Title,
		QuestArea,
		Battle,
		End
	};


	//! ���݂̃V�[��
	int m_now_scene = Title;
	//! ���ɍs�������V�[��
	int m_next_scene = -1;

};