#pragma once
#include <GameEngineCore/GameEngineActor.h>

// �� Pomp���� �� 
class CMonster_Pomp : public GameEngineActor
{
public:
	// constrcuter destructer
	CMonster_Pomp();
	~CMonster_Pomp();

	// delete Function
	CMonster_Pomp(const CMonster_Pomp& _Other) = delete;
	CMonster_Pomp(CMonster_Pomp&& _Other) noexcept = delete;
	CMonster_Pomp& operator=(const CMonster_Pomp& _Other) = delete;
	CMonster_Pomp& operator=(CMonster_Pomp&& _Other) noexcept = delete;

protected:

private:

};
