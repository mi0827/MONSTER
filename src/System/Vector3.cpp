#include "src/WinMain.h"
#include "Vector3.h"

//--------------------
// �R���X�g���N�^(�������j

Vector3::Vector3() // ���ׂĂO�ŏ���������
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float x, float y, float z) // �����œn���ꂽ�l�ɏ�����
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(VECTOR v) // ���̈��������Ȃ̂����R���搶�ɕ���
{
	x = v.x;
	y = v.y;
	z = v.z;
}

//---------------------
// �e�֐�����

//	�[���������i�w�x�y�̒l���O�ɂ��܂��j
void Vector3::clear()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

// �l�̃Z�b�g ( X Y Z �����ꂼ��Ŏ󂯎��o�[�W����)
void Vector3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//	�l�̃Z�b�g�i Vector3 ���󂯎��o�[�W���� �j
void Vector3::set(Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

//	�����擾
float Vector3::GetLength()
{
	return sqrtf(x * x + y * y + z * z);
}

//	���K���i�x�N�g���̒������P�ɂ���j
void Vector3::normalize()
{
	float length = GetLength();
	if (length > 0.0f) 
	{
		x = x / length;
		y = y / length;
		z = z / length;
	}
}

//	�����ݒ�
void Vector3::SetLength(float length)
{
	normalize();
	x = x * length;
	y = y * length;
	z = z * length;
}


//	= ���Z�q�̃I�[�o�[���[�h
Vector3& Vector3::operator = (const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

//	+= ���Z�q�̃I�[�o�[���[�h
Vector3& Vector3::operator += (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

//	-= ���Z�q�̃I�[�o�[���[�h
Vector3& Vector3::operator -= (const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

//	*= ���Z�q�̃I�[�o�[���[�h
Vector3& Vector3::operator *= (const float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

//	/= ���Z�q�̃I�[�o�[���[�h
Vector3& Vector3::operator /= (const float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}


//	+ ���Z�q�̃I�[�o�[���[�h
Vector3 operator + (const Vector3& v0, const Vector3& v1)
{
	Vector3 v;
	v.x = v0.x + v1.x;
	v.y = v0.y + v1.y;
	v.z = v0.z + v1.z;
	return v;
}

//	- ���Z�q�̃I�[�o�[���[�h
Vector3 operator - (const Vector3& v0, const Vector3& v1)
{
	Vector3 v;
	v.x = v0.x - v1.x;
	v.y = v0.y - v1.y;
	v.z = v0.z - v1.z;
	return v;
}
//---------------------------------------------------------------------------------
//	* ���Z�q�̃I�[�o�[���[�h
//---------------------------------------------------------------------------------
Vector3 operator * (const Vector3& v, const float f)
{
	Vector3 r;
	r.x = v.x * f;
	r.y = v.y * f;
	r.z = v.z * f;
	return r;
}

//	/ ���Z�q�̃I�[�o�[���[�h
Vector3 operator / (const Vector3& v, const float f)
{
	Vector3 r;
	r.x = v.x / f;
	r.y = v.y / f;
	r.z = v.z / f;
	return r;
}


//	DX���C�u�����Ŏg�� VECTOR ��Ԃ�
VECTOR Vector3::VGet()
{
	VECTOR v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

//	DX���C�u�����Ŏg�� VECTOR �̒l���擾���Đݒ�
void Vector3::VSet(VECTOR v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}


//	�Q�� Vector3 �̋��������߂�
float GetVector3Distance(Vector3& p0, Vector3& p1)
{
	Vector3 v = p0 - p1;
	return v.GetLength();
}

//	�Q�� Vector3 �̓��ς����߂�
float GetVector3Dot(Vector3& v0, Vector3& v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

//---------------------------------------------------------------------------------
//	�Q�� Vector3 �̊O�ς����߂�
Vector3 GetVector3Cross(Vector3& v0, Vector3& v1)
{
	Vector3 v;
	v.x = v0.y * v1.z - v0.z * v1.y;
	v.y = v0.z * v1.x - v0.x * v1.z;
	v.z = v0.x * v1.y - v0.y * v1.x;
	return v;
}

//---------------------------------------------------------------------------------
//	Vector3 �� MATRIX �ŕϊ����� Vector3 ��Ԃ�
Vector3 GetVector3VTransform(Vector3& v, MATRIX& mat)
{
	VECTOR base = v.VGet();
	VECTOR change = VTransform(base, mat);

	Vector3 ret(change);
	return ret;
}
