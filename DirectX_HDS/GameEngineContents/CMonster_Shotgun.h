#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ¼¦°Ç¸Ç
class CMonster_Shotgun : public GameEngineActor
{
public:
	// constrcuter destructer
	CMonster_Shotgun();
	~CMonster_Shotgun();

	// delete Function
	CMonster_Shotgun(const CMonster_Shotgun& _Other) = delete;
	CMonster_Shotgun(CMonster_Shotgun&& _Other) noexcept = delete;
	CMonster_Shotgun& operator=(const CMonster_Shotgun& _Other) = delete;
	CMonster_Shotgun& operator=(CMonster_Shotgun&& _Other) noexcept = delete;

protected:

private:

};
