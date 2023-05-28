#pragma once
#include "BaseActor.h"

// ���̸��� ī�޶��ͷ� �ٲܱ�..? ���� �긦 ī�޶� ���ͷ� �ٲٰ� 

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

	// ������ ī�޶� �ʱ���ġ����
	void CameraSetting();

	static std::vector<float4> m_CameraPivots;

protected:
	void Start() override;

private:
	bool PlayerDeathCheck();
};
