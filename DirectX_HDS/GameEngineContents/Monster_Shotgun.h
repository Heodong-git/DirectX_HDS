#pragma once
#include "BaseActor.h"

// ¼¦°Ç¸Ç
class Monster_Shotgun : public BaseActor
{
public:
	// constrcuter destructer
	Monster_Shotgun();
	~Monster_Shotgun();

	// delete Function
	Monster_Shotgun(const Monster_Shotgun& _Other) = delete;
	Monster_Shotgun(Monster_Shotgun&& _Other) noexcept = delete;
	Monster_Shotgun& operator=(const Monster_Shotgun& _Other) = delete;
	Monster_Shotgun& operator=(Monster_Shotgun&& _Other) noexcept = delete;

protected:

private:

};
