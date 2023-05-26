#pragma once
#include "BaseActor.h"

class PlayManager : public BaseActor
{
public:
	static PlayManager* MainManager;

public:
	// constrcuter destructer
	PlayManager();
	~PlayManager();

	// delete Function
	PlayManager(const PlayManager& _Other) = delete;
	PlayManager(PlayManager&& _Other) noexcept = delete;
	PlayManager& operator=(const PlayManager& _Other) = delete;
	PlayManager& operator=(PlayManager&& _Other) noexcept = delete;


	void Update(float _DeltaTime);

	// 레벨별 카메라 초기위치세팅
	void CameraSetting();

	static std::vector<float4> m_CameraPivots;

protected:
	void Start() override;

private:
	bool PlayerDeathCheck();
};
