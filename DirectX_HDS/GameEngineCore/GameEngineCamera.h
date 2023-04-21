#pragma once
#include "GameEngineActor.h"
#include "GameEngineEnum.h"

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

protected:
	void Start() override;
	
private:
	bool FreeCamera = false;

	// ��
	float4x4 View;
	// ����
	float4x4 Projection;
	// ����Ʈ
	float4x4 ViewPort;

	TransformData OldData = {};
	CameraType ProjectionType = CameraType::None;

	// �ʱ�ȭ����
	D3D11_VIEWPORT ViewPortData = {};

	// ���μ���
	float Width = 0.0f;
	float Height = 0.0f;

	// �þ߰�
	float FOV = 60.0f;
	// �ּҰŸ�, �ִ�Ÿ� 
	float Near = 0.1f;
	float Far = 10000.0f;
	
};

