#pragma once

//! @brief �����m�̓����蔻��
//! @param ���̍��W�P
//! @param ���̔��a�P
//! @param ���̍��W�Q
//! @param ���̔��a�Q
bool CheckBallHit(Vector3 center1, float radius1, Vector3 center2, float radius2);


//! @brief �{�b�N�X���m�̓����蔻��
//! @param �{�b�N�X�P�̍��W�@�i�����蔻��p�̍��W�j
//! @param �{�b�N�X�P�̃T�C�Y�@�i���S���猩�����̃T�C�Y�j
//! @param �{�b�N�X�Q�̍��W�@�i�����蔻��p�̍��W�j
//! @param �{�b�N�X�Q�̃T�C�Y�@�i���S���猩�����̃T�C�Y�j
//! @detail �ǎC�蔻��Ɏg��
bool CheckBoxHit3D(Vector3 box_pos1, Vector3 box_size1, Vector3 box_pos2, Vector3 box_size2);

//! @brief �{�b�N�X���m�̓����蔻��
//! @param �{�b�N�X�P�̏��
//! @param �{�b�N�X�Q�̏��
bool CheckBoxHit(BoxCollision box1, BoxCollision box2);

//! @brief �J�v�Z�����m�̂����蔻��
//! @param �J�v�Z���P�̏��
//! @param �J�v�Z���Q�̏��
bool CheckCapsuleHit(CapsuleCollision capsule1, CapsuleCollision capsule2);