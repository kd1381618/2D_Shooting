#pragma once

class C_State
{
public:

	C_State() {}
	~C_State() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

};