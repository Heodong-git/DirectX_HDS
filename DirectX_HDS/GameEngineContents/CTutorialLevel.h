#pragma once
#include "BaseLevel.h"

// Ό³Έν :
class CTutorialLevel : public BaseLevel
{
public:
	// constrcuter destructer
	CTutorialLevel();
	~CTutorialLevel();

	// delete Function
	CTutorialLevel(const CTutorialLevel& _Other) = delete;
	CTutorialLevel(CTutorialLevel&& _Other) noexcept = delete;
	CTutorialLevel& operator=(const CTutorialLevel& _Other) = delete;
	CTutorialLevel& operator=(CTutorialLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	void ResourcesLoad() override;
	void ActorLoad() override;
	
	std::shared_ptr<class CPlayManager> m_PlayManager = nullptr;
	std::shared_ptr<class TitleEditer> m_GUI = nullptr;
	// test 
	std::shared_ptr<class CRecordingManager> m_RecordingManager = nullptr;
};
