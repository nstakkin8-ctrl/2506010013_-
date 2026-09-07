#pragma once
#include "Dxlib.h"
class Player
{
private:
	int modelHandle;
	VECTOR position;
	float moveSpeed;
	float collisionRadius;
public:
	Player();
	~Player();

	bool Load();
	void Update();
	void Draw();
	VECTOR GetPosition() const;
	float GetCollisionRadius() const;
	void SetPosition(VECTOR pos);
};


