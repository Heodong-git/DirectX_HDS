#pragma once
#include "GameEngineActor.h"
#include "GameEngineEnum.h"
#include <list>
#include <map>

class GameEngineRenderer;
class GameEngineRenderTarget;
class GameEngineCamera : public GameEngineActor
{
	friend GameEngineLevel;
	friend GameEngineRenderer;
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

	void Setting();

	void SetProjectionType(CameraType _Type)
	{
		ProjectionType = _Type;
	}

	inline bool IsFreeCamera()
	{
		return FreeCamera;
	}

	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void CameraTransformUpdate();

	std::shared_ptr<GameEngineRenderTarget> GetCamTarget()
	{
		return CamTarget;
	}
	
	// 카메라컬링을 위한 체크함수 
	bool IsView(const TransformData& _TransData);

protected:

	void Start() override;
	
private:
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> Renderers;

	DirectX::BoundingOrientedBox Box;

	bool FreeCamera = false;

	// 뷰
	float4x4 View;
	// 투영
	float4x4 Projection;
	// 뷰포트
	float4x4 ViewPort;

	TransformData OldData = {};
	CameraType ProjectionType = CameraType::None;

	// 초기화ㅇㅇ
	D3D11_VIEWPORT ViewPortData = {};

	// 가로세로
	float Width = 0.0f;
	float Height = 0.0f;

	// 시야각
	float FOV = 60.0f;
	// 최소거리, 최대거리 
	float Near = 0.1f;
	float Far = 10000.0f;
	
	void RenderRelease();

	void PushRenderer(std::shared_ptr<GameEngineRenderer> _Render);

	std::shared_ptr<GameEngineRenderTarget> CamTarget;
};

