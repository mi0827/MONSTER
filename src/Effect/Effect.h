#pragma once
//! @file Effect.h
//! @brief �G�t�F�N�g�p�̃N���X
class Effect
{
public:
	//! @brief �R���X�g���N�^
	Effect();
	//! @brief �f�X�g���N�^
	~Effect();

	//! @brief �G�t�F�N�g�p�̔z��ϐ��̊m�ۊ֐�
	//! @param �G�t�F�N�g�̍ő��
	void NewArraySecure(int effect_max);

	//! @brief �m�ۂ����G�t�F�N�g���J������֐�
	void EffectDelete();

	//! @brief �G�t�F�N�g�̓ǂݍ��ݗp�֐�
	//! @param �G�t�F�N�g�ۑ��p�ԍ�
	//! @param �G�t�F�N�g�̍Đ����x
	void LoadEffect(const char file_path[256], int effect_noint ,float effect_play_speed);

	//! @brief �G�t�F�N�g���Đ�
	//! @param �Đ��������G�t�F�N�g�ԍ�
	//! @param �G�t�F�N�g�̍��W
	
	void PlayEffect(int effect_num, Vector3 pos);

	//! @brief �G�t�F�N�g�̍��W��ݒ�
	//! @param �ݒ肵�����G�t�F�N�g�̔ԍ�
	//! @param �ݒ肵�������W
	//! @param ���炵�������W
	void SetEffectPos(int effect_num,Vector3 pos, Vector3 pos2 = { 0.0f,0.0f,0.0f });

	//! @brief �G�t�F�N�g�̍��W�����f���̌����ɍ��킹�Ă��炷�֐�
	//! @param �ݒ肵�����G�t�F�N�g�̔ԍ�
	//! @param �ݒ肵�������W
	//! @param ���炵�������W
	//! @param �ݒ肵�������f���̌���
	void SetEffectRotPos(int effect_num, Vector3 pos, Vector3 pos2, Vector3 rot);

	//! @brief �G�t�F�N�g�̌����̐ݒ�
	//! @param �ݒ肵�����G�t�F�N�g�̔ԍ�
	//! @param �G�t�F�N�g�̌���
	void SetEffectRot(int effect_num, Vector3 rot);

	//! @brief �G�t�F�N�g�ׂ̍����T�C�Y�̐ݒ�
	//! @param �ݒ肵�����G�t�F�N�g�̔ԍ�
	//! @param �e�����ɑ΂��Ă̊g�嗦(Vector3)
	void SetEffectSize(int effect_num, Vector3 size);

	//! @brief �G�t�F�N�g�̍Đ����x�̐ݒ�
	//! @param �ݒ肵�����G�t�F�N�g�̔ԍ�
	//! @param �Đ����x
	void SetEffectPlaySpeed(int effect_num, float speed);

	//! @brief �G�t�F�N�g�̐F�̐ݒ�
	//! @param �ݒ肵�����G�t�F�N�g�̔ԍ�
	//! @param �ݒ肵�����J���[
	void SetEffectColor(int effect_num, COLOR_F color);
private:
	//! �G�t�F�N�g��ۑ�����p�̕ϐ�
	struct EffectInfo
	{
		//! �G�t�F�N�g�̓��ꕨ
		int effect_handle;
		//! �G�t�F�N�g�̍Đ����x
		int effect_play_speed;
		//! �G�t�F�N�g�̍��W
		Vector3 pos;
		//! �G�t�F�N�g�̃T�C�Y
		Vector3 size{ 1.0f,1.0f ,1.0f };
	};
	std::vector<EffectInfo>m_effect_info;

	//! ���ݍĐ����̃G�t�F�N�g�̂�ۑ�����ϐ�
	//int  m_now_play_effect = -1;
};
