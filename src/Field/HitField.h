#pragma once


//! @brinf �n�ʃ��f���̓����蔻��̐ݒ� 
void SetHitGround(Model* ground_model);


//! @brinf �n�ʃ��f���ƃL�����N�^�[���f���̃��f�����m�̓����蔻��
//! @param �L�����N�^�[�̍��W
//! @param �n�ʂ̃��f��
void HitGroundCharacter(Vector3* charcter_pos, Model*  ground_model);