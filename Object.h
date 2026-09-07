#pragma once
#include "DXlib.h"
class Object3D
{
private:

	int modelHandle;
	VECTOR position;
	float collisionRadius;
public:
	Object3D();
	~Object3D();

	bool Load(const char* fileName, float radius);

	void SetPosition(VECTOR pos);
	VECTOR GetPosition() const;
	float GetCollisionRadius() const;

	void Draw();
};
