#pragma once

//! @fule Combo.h
//! @brief �R���{�p�̃N���X
class Combo
{
public:
	//! @brief �R���X�g���N�^
	Combo();
	//! @brief �f�X�g���N�^
	~Combo();

	//! @brief �R���{���Ă悢�̂����w��̃L�[����Ŕ��f����֐�
	//! @param �R���{�����Ă悢���̃t���O
	//! @param �}�E�X�̂ǂ������������������
	//! @param ������̃L�[�i�}�E�X�̃{�^���ł��j
	//! @param �R���{�������Ƃ��̃A�j���[�V�����̍Đ�����
	//! @param �R���{�������Ƃ��̃A�j���[�V�����̈�����̎���
	//! @detail �f�t�H���g�A�j���[�V�����̃Z�b�g�A�A�j���[�V�����̓��ꕨ�̊m��
	void Combo_Judgment_Key(bool* combo_flag, int* mouse_flag, int key, float play_anim_time, float anim_total,int *combo_count);


	//! @brief �R���{���Ă悢�̂����w��̏����Ŕ��f����֐�
	//! @param �R���{�����Ă悢���̃t���O
	//! @param �w������̃t���O�ibool�j
	//! @param �R���{�������Ƃ��̃A�j���[�V�����̍Đ�����
	//! @param �R���{�������Ƃ��̃A�j���[�V�����̈�����̎���
	//! @detail �f�t�H���g�A�j���[�V�����̃Z�b�g�A�A�j���[�V�����̓��ꕨ�̊m��
	void Combo_Judgment_Condition(bool* combo_flag, bool condition, float play_anim_time, float anim_total);
};
