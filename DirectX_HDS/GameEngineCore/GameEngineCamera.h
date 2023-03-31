#pragma once
#include "GameEngineActor.h"

class GameEngineCamera : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	inline float4x4 GetView()
	{
		return View;
	}

	inline float4x4 GetProjection()
	{
		return Projection;
	}

	inline float4x4 GetViewPort()
	{
		return ViewPort;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool FreeCamera = false;

	// 뷰
	float4x4 View;
	// 투영
	float4x4 Projection;
	// 뷰포트
	float4x4 ViewPort;

	// 최소거리, 최대거리 
	float Near = 0.1f;
	float Far = 10000.0f;
	
};

