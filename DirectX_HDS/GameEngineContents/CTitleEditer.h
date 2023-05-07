#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

// Ό³Έν :
class CTitleEditer : public GameEngineCoreWindow
{
public:
	// constrcuter destructer
	CTitleEditer();
	~CTitleEditer();

	// delete Function
	CTitleEditer(const CTitleEditer& _Other) = delete;
	CTitleEditer(CTitleEditer&& _Other) noexcept = delete;
	CTitleEditer& operator=(const CTitleEditer& _Other) = delete;
	CTitleEditer& operator=(CTitleEditer&& _Other) noexcept = delete;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;
	
protected:

private:

};
