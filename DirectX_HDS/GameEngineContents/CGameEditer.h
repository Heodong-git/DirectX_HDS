#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

// Ό³Έν :
class CGameEditer : public GameEngineCoreWindow
{
public:
	// constrcuter destructer
	CGameEditer();
	~CGameEditer();

	// delete Function
	CGameEditer(const CGameEditer& _Other) = delete;
	CGameEditer(CGameEditer&& _Other) noexcept = delete;
	CGameEditer& operator=(const CGameEditer& _Other) = delete;
	CGameEditer& operator=(CGameEditer&& _Other) noexcept = delete;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;
	
protected:

private:

};
