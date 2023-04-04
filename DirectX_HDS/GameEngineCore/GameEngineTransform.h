#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>

// 특정한 물체의 크기 회전 이동에 관련된 기하속성 관리
class GameEngineTransform
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

	void SetWorldScale(const float4& _Value)
	{
		//float4 LocalPostionValue = WorldPostion * Parent.InverseReturn();
		//float4 WorldPostionValue = LocalPostion * Parent;

		WorldScale = _Value;

		if (nullptr == Parent)
		{
			LocalScale = WorldScale;
			TransformUpdate();
			CalChild();
			//for (GameEngineTransform* Parent : Child)
			//{
			//	Parent->SetLocalScale(Parent->GetLocalScale());
			//	Parent->TransformUpdate();
			//}
			return;
		}

		LocalScale = WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
		TransformUpdate();
		CalChild();
	}

	void SetWorldRotation(const float4& _Value)
	{
		WorldRotation = _Value;

		if (nullptr == Parent)
		{
			LocalRotation = WorldRotation;
		}


		TransformUpdate();
	}

	void SetWorldPosition(const float4& _Value)
	{
		WorldPosition = _Value;
		TransformUpdate();
	}


	// 위치,회전,크기 등 변화가 있다면 반드시 트랜스폼 업데이트 실행
	void SetLocalScale(const float4& _Value)
	{
		LocalScale = _Value;
		TransformUpdate();
	}

	void SetLocalRotation(const float4& _Value)
	{
		LocalRotation = _Value;
		TransformUpdate();
	}

	void SetLocalPosition(const float4& _Value)
	{
		LocalPosition = _Value;
		TransformUpdate();
	}

	void AddLocalScale(const float4& _Value)
	{
		LocalScale += _Value;
		TransformUpdate();
	}

	void AddLocalRotation(const float4& _Value)
	{
		LocalRotation += _Value;
		TransformUpdate();
	}

	void AddLocalPosition(const float4& _Value)
	{
		LocalPosition += _Value;
		TransformUpdate();
	}

	float4 GetLocalForwardVector()
	{
		return LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetLocalUpVector()
	{
		return LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetLocalRightVector()
	{
		return LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetLocalPosition()
	{
		return LocalPosition;
	}

	float4 GetLocalScale()
	{
		return LocalScale;
	}

	float4 GetLocalRotation()
	{
		return LocalRotation;
	}
	// 월드매트릭스 반환
	float4x4 GetLocalWorldMatrix()
	{
		return LocalWorldMatrix;
	}

	// 월드매트릭스 레퍼런스 반환
	const float4x4& GetLocalWorldMatrixRef()
	{
		return LocalWorldMatrix;
	}

	const float4x4 GetWorldMatrix()
	{
		return WorldMatrix;
	}

	const float4x4& GetWorldMatrixRef()
	{
		return WorldMatrix;
	}

	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		View = _View;
		Projection = _Projection;
		WorldMatrix = WorldMatrix * View * Projection;
	}

	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		ViewPort = _ViewPort;
		WorldMatrix *= ViewPort;
	}

	void CalChild()
	{
	}

protected:

private:
	void TransformUpdate();

	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Zero;
	float4 LocalPosition = float4::Zero;

	float4 WorldScale = float4::One;
	float4 WorldRotation = float4::Zero;
	float4 WorldPosition = float4::Zero;

	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;

	// 크기 * 회전 * 이동
	float4x4 LocalWorldMatrix;
	float4x4 WorldMatrix;
	float4x4 View;

	// 투영행렬
	float4x4 Projection;

	// 뷰포트행렬 
	float4x4 ViewPort;

	GameEngineTransform* Parent = nullptr;
	std::list <GameEngineTransform*> Child;
};

// 