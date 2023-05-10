#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

// Ό³Έν :
class StageEditer : public GameEngineCoreWindow
{
public:
	// constrcuter destructer
	StageEditer();
	~StageEditer();

	// delete Function
	StageEditer(const StageEditer& _Other) = delete;
	StageEditer(StageEditer&& _Other) noexcept = delete;
	StageEditer& operator=(const StageEditer& _Other) = delete;
	StageEditer& operator=(StageEditer&& _Other) noexcept = delete;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

protected:

private:

};
