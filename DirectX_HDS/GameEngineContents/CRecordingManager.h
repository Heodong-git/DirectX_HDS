#pragma once
#include "CKatanaZero_Actor.h"

class CRecordingManager : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CRecordingManager();
	~CRecordingManager();

	// delete Function
	CRecordingManager(const CRecordingManager& _Other) = delete;
	CRecordingManager(CRecordingManager&& _Other) noexcept = delete;
	CRecordingManager& operator=(const CRecordingManager& _Other) = delete;
	CRecordingManager& operator=(CRecordingManager&& _Other) noexcept = delete;

	void Save(GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager);
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::vector<float4> m_vecTest;
};
