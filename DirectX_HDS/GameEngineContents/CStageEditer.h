#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

// Ό³Έν :
class CStageEditer : public GameEngineCoreWindow
{
public:
	// constrcuter destructer
	CStageEditer();
	~CStageEditer();

	// delete Function
	CStageEditer(const CStageEditer& _Other) = delete;
	CStageEditer(CStageEditer&& _Other) noexcept = delete;
	CStageEditer& operator=(const CStageEditer& _Other) = delete;
	CStageEditer& operator=(CStageEditer&& _Other) noexcept = delete;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

protected:

private:

};
