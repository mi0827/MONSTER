#pragma once


//! @fule Animation.h
//! @brief �A�j���[�V�����p�̃N���X


//! �A�j���[�V�����p�̃N���X

class Animation
{
private:
	//! �u�����h������t���[���ŕω����镪
	static constexpr float BLEND_VALUE = 1.0f / 5.0f;
	//! �u�����h���̍ő�l
	static constexpr float BLEND_VALUE_MAX = 1.0f;
	//! �u�����h���̍Œ�l
	static constexpr float BLEND_VALUE_MIN = 0.0f;
public:

	//!@brief �R���X�g���N�^
	Animation();
	//!@brief �f�X�g���N�^
	virtual ~Animation();

	//=========================================================================
	// �\���̂̒�`
	//=========================================================================

	//! �A�j���[�V�����̃f�[�^�p�̍\����
	struct AnimData
	{
		int handle = -1;       //! �A�j���[�V�����̓��ꕨ
		int index = -1;        //! �A�j���V�����̃C���f�b�N�X
		float play_speed = -1; //! �A�j���[�V�����̍Đ����x
	};
	std::vector<AnimData*> anim_handle;

	//! �Đ����̃A�j���[�V�����̏��\����
	struct Information
	{
		bool  is_playing = false;         //!< �Đ������ǂ���
		bool  is_loop = false;              //!< ���[�v�Đ����ǂ���
		int   animation_index = -1;         //!< ���݂̍Đ����̔ԍ�
		int   animation_attach_index = -1;  //!< �A�^�b�`���ꂽ�X���b�g�ԍ�
		float m_blend_ratio = 0.0f;         //!< �u�����h��(0.0f�`1.0f)
		float animation_total_time = 0.0;   //!< ���Đ�����
		float play_time = 0.0f;             //!< ���ݍĐ����̎���
	};
	//! �\���̂̓A�j���[�V�����u�����h�̂���2�n��������
	//! [0]���݂̃A�j���[�V����
	//! [1]�O�̃A�j���[�V����
	Information m_contexts[2];


	//=========================================================================
	// �֐��̒�`
	//=========================================================================

	//! @brief �A�j���[�V�����̏��̏������֐�
	//! @param �ǂ���̍\���̂����������邩�̔ԍ�
	void Information_Init(int num);

	//! @brief �A�j���[�V�����̏����ݒ�
	//! @param �A�j���[�V�����̐�
	//! @param �f�t�H���g�ݒ肵�����A�j���[�V�����̔ԍ�
	//! @detail �f�t�H���g�A�j���[�V�����̃Z�b�g�A�A�j���[�V�����̓��ꕨ�̊m��
	void Init_Animation(int anim_max, int default_anim);

	//! @brief�ǂݍ��ݗp�֐�
	//! @param �t�@�C���̃p�X
	//! @param �A�j���[�V�����ԍ�
	void Load_Animation(const char file_path[256], int anim_no, int anim_index, float anim_play_speed);

	//! @brief�A�j���[�V�������Z�b�g����֐�
	//! @param �x�[�X�̃��f��
	//! @param �A�b�^�`���������f���ԍ�
	//! @param ���[�v�Đ������邩�ǂ���
	void Init_Attach_Animation(Model* model, int anim_num, bool loop);

	//! @brief�A�j���[�V�������Z�b�g����֐�
	//! @param �x�[�X�̃��f��
	//! @param �A�b�^�`���������f���ԍ�
	//! @param ���[�v�Đ������邩�ǂ���
	void Attach_Animation(Model* model, int anim_num, bool loop);

	//! @brief���Ă���A�j���[�V���������O���悤�̊֐�
	//! @param �x�[�X�̃��f��
	//! @param �f�^�b�`���������f���ԍ�
	void Detach_Animation(Model* model);

	//! @brief �u�����h���̕ύX�֐�
	void Change_Blend();

	//! @brief �A�j���[�V�����̕ύX���s���Ă����ȉ��𔻒f����֐�
	bool Change_Flag(bool flag1);

	//! @brief�A�j���[�V�����̐؂�ւ��p�֐�
	//! @param �x�[�X�̃��f��
	//! @param ���ɃZ�b�g�������A�j���[�V�����ԍ�
	//! @param �A�j���[�V���������[�v�����邩�ǂ���
	void Change_Animation(Model* model, int anim_num, bool loop);

	//! @brief �A�j���[�V�����̐؂�ւ��p�֐�
	//! @param �x�[�X�̃��f��
	//! @param ���ɃZ�b�g�������A�j���[�V�����ԍ�
	//! @param �A�j���[�V���������[�v�����邩�ǂ�
	//! @param �R���{�t���O
	//! @detail �A�j���[�V�������I���^�C�~���O�Ő؂�ւ����Change_Animation���Ăт������p�̊֐�
	void Action_Change_Animation(Model* model, int anim_num, bool loop, bool* combo_flag);

	//! @brief�A�j���[�V�����̍Đ�
	//! @param �x�[�X�̃��f��
	//! @param �R���{�t���O
	void Play_Animation(Model* model, bool combo_flag);

	//! @brief�A�j���[�V���������[�v������
	void Loop_Animation();

	//! @brief���[�v�����Ȃ��ꍇ
	//! @param �x�[�X�̃��f��
	void Not_Loop(Model* model);

private:
	//! �A�j���[�V�����̍ő吔
	int m_anim_max = 0;
	//! �f�t�H���g�ŃZ�b�g�����A�j���[�V�����ԍ��p�̕ϐ�
	int m_default_anim = -1;
	//! ��A�j���[�V�������t���Ă��邩�ǂ���
	bool m_attached = false;
	//! �f�^�b�`�ς݂��ǂ����𒲂ׂ�
	bool m_detach_flag = false;
	//! �ǂ̃A�j���[�V�����������Ă��邩��ۑ��������
	int m_anim_num = -1;

public:
	//! �A�j���[�V�����̐؂�ւ����s���Ă������̃t���O
	//! �t���O�̏グ�͏����L�����N���X�ōs��
	//! �t���O�̉����̓A�j���[�V�����ύX�֐��ŉ�����
	//! ���̃t���O�����グ��^�C�~���O���厖
	bool m_anim_change_flag = true;

	bool m_playing_anim = false;
};