#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ±Ÿ¿∞∏«
class CMonster_Grunt : public GameEngineActor
{
public:
	// constrcuter destructer
	CMonster_Grunt();
	~CMonster_Grunt();

	// delete Function
	CMonster_Grunt(const CMonster_Grunt& _Other) = delete;
	CMonster_Grunt(CMonster_Grunt&& _Other) noexcept = delete;
	CMonster_Grunt& operator=(const CMonster_Grunt& _Other) = delete;
	CMonster_Grunt& operator=(CMonster_Grunt&& _Other) noexcept = delete;

protected:

private:

};
