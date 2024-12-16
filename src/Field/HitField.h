#pragma once


//! @brief �n�ʃ��f���̓����蔻��̐ݒ� 
void SetHitGround(Model* ground_model);


//! @brief �n�ʃ��f���ƃL�����N�^�[���f���̃��f�����m�̓����蔻��
//! @param �L�����N�^�[�̍��W
//! @param �n�ʂ̃��f��
void HitGroundCharacter(Vector3* character_pos, Model*  ground_model);

//! @brief �n�ʃ��f���ƃL�����N�^�[���f���̃��f�����m�̓����蔻��(�W�����v���s���ꍇ)
//! @param �L�����N�^�[�̍��W
//! @param �W�����v�Ɏg��Vector3
//! @param �W�����v�t���O
//! @param ��ɏオ��X�s�[�h
//! @param ���ɗ�����X�s�[�h
//! @param �n�ʂ̃��f��
void HitGroundCharacterJump(Vector3* character_pos, Vector3* jump_mov, bool* jump_flag, float up_speed, float down_speed, Model* ground_model);



//VECTOR GetGroundPos(Vector3* character_pos, Model* ground_model);