#pragma once

//---------------------------------------------------------------------------------
//	Vector2 �N���X
//---------------------------------------------------------------------------------
class Vector2
{
public:
	float x;
	float y;

	Vector2();									//	�R���X�g���N�^
	Vector2( float x, float y );

	void clear();								//	�[��������
	void set( float x, float y );				//	�l�̃Z�b�g
	void set( Vector2 &v );

	float GetLength();							//	�����擾
	void normalize();							//	���K��
	void SetLength( float length );				//	�����ݒ�

	Vector2& operator = ( const Vector2 &v );	//	= ���Z�q�̃I�[�o�[���[�h

	Vector2& operator += ( const Vector2 &v );	//	+= ���Z�q�̃I�[�o�[���[�h
	Vector2& operator -= ( const Vector2 &v );	//	-= ���Z�q�̃I�[�o�[���[�h
	Vector2& operator *= ( const float f );		//	*= ���Z�q�̃I�[�o�[���[�h
	Vector2& operator /= ( const float f );		//	/= ���Z�q�̃I�[�o�[���[�h
};

//	+ ���Z�q�̃I�[�o�[���[�h
Vector2 operator + ( const Vector2 &v0, const Vector2 &v1 );
//	- ���Z�q�̃I�[�o�[���[�h
Vector2 operator - ( const Vector2 &v0, const Vector2 &v1 );
//	* ���Z�q�̃I�[�o�[���[�h
Vector2 operator * ( const Vector2 &v, const float f );
//	/ ���Z�q�̃I�[�o�[���[�h
Vector2 operator / ( const Vector2 &v, const float f );

//	�Q�� Vector2 �̋��������߂�
float GetVector2Distance( Vector2 &p0, Vector2 &p1 );
//	�Q�� Vector2 �̓��ς����߂�
float GetVector2Dot( Vector2 &v0, Vector2 &v1 );
//	�Q�� Vector2 �̊O�ς����߂�
float GetVector2Cross( Vector2 &v0, Vector2 &v1 );
