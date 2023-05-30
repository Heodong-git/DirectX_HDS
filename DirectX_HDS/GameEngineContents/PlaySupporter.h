#pragma once
#include "BaseActor.h"

// 설명 :
class PlaySupporter : public BaseActor
{
	friend class Player;
public:
	static PlaySupporter* MainSupporter;

public:
	// constrcuter destructer
	PlaySupporter();
	~PlaySupporter();

	// delete Function
	PlaySupporter(const PlaySupporter& _Other) = delete;
	PlaySupporter(PlaySupporter&& _Other) noexcept = delete;
	PlaySupporter& operator=(const PlaySupporter& _Other) = delete;
	PlaySupporter& operator=(PlaySupporter&& _Other) noexcept = delete;

	static std::shared_ptr<class GameEngineUIRenderer> g_SuccessRender;
	static std::shared_ptr<class GameEngineUIRenderer> g_FailRender;
	static std::shared_ptr<class GameEngineUIRenderer> g_BlackBoxRender;
	static std::shared_ptr<class GameEngineUIRenderer> g_ClearRender;

	static std::shared_ptr<class GameEngineCollision>  g_MouseCheckCollision;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Move(float _DeltaTime);
	bool RangeOverCheck(float _DeltaTime);
	bool PlayerDeathCheck();

	std::shared_ptr<class GameEngineCamera> m_MainCamera = nullptr;
	float m_MoveSpeed = 200.0f;
	
	// 좌상단, 우상단, 좌하단 , 우하단 순서로 
	std::map<int, std::vector<float4>> m_MapRanges = std::map<int, std::vector<float4>>();
	virtual void Reset() override;
};
