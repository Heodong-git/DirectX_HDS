#pragma once
#include "CKatanaZero_Level.h"

// Ό³Έν :
class CTutorialLevel : public CKatanaZero_Level
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

	float4 m_CurMouseLocalPos = {};
	std::shared_ptr<class CPlayManager> m_PlayManager = nullptr;

	// test
	std::shared_ptr<class CRecordingManager> m_RecordingManager = nullptr;
};
