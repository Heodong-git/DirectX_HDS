#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

// ���� :
class TitleEditer : public GameEngineCoreWindow
{
public:
	// constrcuter destructer
	TitleEditer();
	~TitleEditer();

	// delete Function
	TitleEditer(const TitleEditer& _Other) = delete;
	TitleEditer(TitleEditer&& _Other) noexcept = delete;
	TitleEditer& operator=(const TitleEditer& _Other) = delete;
	TitleEditer& operator=(TitleEditer&& _Other) noexcept = delete;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;
	
protected:

private:

};
