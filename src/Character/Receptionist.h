#pragma once

//! @file Receptionist.h
//! @brief ��t��̃N���X

class Receptionist
{
public:

	static constexpr float BDOY_R = 5.0f;


	//! @brief �R���X�g���N�^
	Receptionist();
	//! @brief �f�X�g���N�^
	~Receptionist();

    //! @brief �����ݒ�
	void Init();

	//! @brief �X�V����
	void Update();

	//! @brief �`�揈��
	void Draw();

	//! @brief �I������
	void Exit();

	// �A�j���[�V�����̎�ޗp�̗񋓑�
	enum Animation_Max
	{
		idle, // �A�C�h���A�j���[�V����
		idle2,
		anim_max // �A�j���[�V�����̍ő吔
	};


	//! ���W�A�����A�傫��
	Transform m_transform;

	//!���f���N���X
	Model m_model;

	//! �A�j���[�V�����N���X
	Animation m_animation;

	//! �J�v�Z���̓����蔻��̐ݒ�
	CapsuleCollision m_hit_body;
	
};