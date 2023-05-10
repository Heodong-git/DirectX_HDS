#pragma once
#include "BaseActor.h"

class RecordingManager : public BaseActor
{
public:
	// constrcuter destructer
	RecordingManager();
	~RecordingManager();

	// delete Function
	RecordingManager(const RecordingManager& _Other) = delete;
	RecordingManager(RecordingManager&& _Other) noexcept = delete;
	RecordingManager& operator=(const RecordingManager& _Other) = delete;
	RecordingManager& operator=(RecordingManager&& _Other) noexcept = delete;

	void Save();
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::vector<float4> m_vecTest;
};
