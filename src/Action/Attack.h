#pragma once

//! @fule Attack.h
//! @brief �U���A�N�V�����̓����蔻��ɂ��ẴN���X

class Attack
{
public:
	//! �����蔻�肪���������x����������Ƃ�
	bool HitAttack(CapsuleCollision capsule1, CapsuleCollision capsule2, Animation anim);

	//! �����蔻�肪���������𒲂ׂ����
	bool hit = true;

};
