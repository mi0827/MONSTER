#include "src/WinMain.h"
#include "src/System/Vector3.h"
#include "src/System/Transform.h"

Transform::Transform()
{
	// 値の初期化
	pos.set(0.0f, 0.0f, 0.0f);
	rot.set(0.0f, 0.0f, 0.0f);
	scale.set(0.0f, 0.0f, 0.0f);
}

Transform::~Transform()
{
}
