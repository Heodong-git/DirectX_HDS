#pragma once
#include "CKatanaZero_Level.h"

// Ό³Έν :
class CTestLevel : public CKatanaZero_Level
{
public:
	// constrcuter destructer
	CTestLevel();
	~CTestLevel();

	// delete Function
	CTestLevel(const CTestLevel& _Other) = delete;
	CTestLevel(CTestLevel&& _Other) noexcept = delete;
	CTestLevel& operator=(const CTestLevel& _Other) = delete;
	CTestLevel& operator=(CTestLevel&& _Other) noexcept = delete;

	// test
	std::shared_ptr<class GameEngineVideo> Video;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResourcesLoad() override;
	void ActorLoad() override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class CPlayManager> m_PlayManager = nullptr;
	std::shared_ptr<class CRecordingManager> m_RecordingManager = nullptr;
};
