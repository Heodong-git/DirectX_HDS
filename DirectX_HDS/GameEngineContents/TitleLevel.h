#pragma once
#include "BaseLevel.h"
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class TitleLevel : public BaseLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

	GameEngineSoundPlayer m_BgmSound;
	

protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ResourcesLoad() override;
	virtual void ActorLoad() override;

	

private:
	std::shared_ptr<class TitleManager> m_TitleManager = nullptr;
	std::shared_ptr<class TitleEditer> m_GUI = nullptr;
};

