#pragma once
#include "CKatanaZero_Actor.h"

// 설명 : 플레이레벨에서 액터들의 데이터를 저장해두고 
// 저장한 데이터를 기반으로 역재생, 재생해서 출력하는 역할. 
class GameEngineRenderer;
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// 매 초마다 현재 레벨의 액터의 정보를 저장하는 기능
	// 저장해야할 정보
	// 1. 위치 . 일단 이거만가지고 해보자
	std::vector<float4> m_vecRecordingInfo;
};
