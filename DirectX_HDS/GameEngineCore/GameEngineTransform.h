#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

// 설명 : 특정한 문체의 크기 회전 이동에 관련된 기하속성을 관리해준다.
class GameEngineTransform : public GameEngineObjectBase
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
		}
		else
		{
			LocalScale = WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
		}

		TransformUpdate();
		CalChild();
	}

	void SetWorldRotation(const float4& _Value)
	{
		/*if (true == IsDebug())
		{
			int a = 0;
		}*/

		WorldRotation = _Value;

		if (nullptr == Parent)
		{
			LocalRotation = WorldRotation;
		}
		else
		{
			float4 Rot = Parent->GetWorldRotation();
			LocalRotation = WorldRotation - Parent->GetWorldRotation();
		}

		TransformUpdate();
		CalChild();
	}

	void SetWorldPosition(const float4& _Value)
	{
		WorldPosition = _Value;

		if (nullptr == Parent)
		{
			LocalPosition = WorldPosition;
		}
		else
		{
			LocalPosition = WorldPosition * Parent->GetWorldMatrixRef().InverseReturn();
		}

		TransformUpdate();
		CalChild();
	}

	void SetLocalScale(const float4& _Value)
	{
		LocalScale = _Value;

		if (nullptr == Parent)
		{
			WorldScale = LocalScale;
		}
		else
		{
			WorldScale = LocalScale * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	void SetLocalRotation(const float4& _Value)
	{
		LocalRotation = _Value;

		if (nullptr == Parent)
		{
			WorldRotation = LocalRotation;
		}
		else
		{
			WorldRotation = LocalRotation + Parent->GetWorldRotation();
		}

		TransformUpdate();
		CalChild();
	}

	void SetLocalPosition(const float4& _Value)
	{
		LocalPosition = _Value;

		if (nullptr == Parent)
		{
			WorldPosition = LocalPosition;
		}
		else
		{
			WorldPosition = LocalPosition * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(LocalScale + _Value);
	}

	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(LocalRotation + _Value);
	}

	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(LocalPosition + _Value);
	}

	float4 GetWorldForwardVector()
	{
		return WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetWorldUpVector()
	{
		return WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetWorldRightVector()
	{
		return WorldMatrix.ArrVector[0].NormalizeReturn();
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

	float4 GetWorldPosition()
	{
		return WorldPosition;
	}

	float4 GetWorldScale()
	{
		return WorldScale;
	}

	float4 GetWorldRotation()
	{
		return WorldRotation;
	}


	float4x4 GetLocalWorldMatrix()
	{
		return LocalWorldMatrix;
	}

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

	const float4x4 GetWorldViewProjectionMatrix()
	{
		return WorldViewProjectionMatrix;
	}

	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return WorldViewProjectionMatrix;
	}

	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		View = _View;
		Projection = _Projection;
		WorldViewProjectionMatrix = WorldMatrix * View * Projection;
	}

	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		ViewPort = _ViewPort;
		WorldViewProjectionMatrix *= ViewPort;
	}

	void CalChild()
	{
		for (GameEngineTransform* ChildTrans : Child)
		{
			ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
			ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
			ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition());
		}
	}

	void SetParent(GameEngineTransform* _Parent);

protected:

private:
	void TransformUpdate();

	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Null;
	Quaternion LocalQuaternion = DirectX::XMQuaternionIdentity();
	float4 LocalPosition = float4::Zero;

	float4 WorldScale = float4::One;
	float4 WorldRotation = float4::Null;
	float4 WorldPosition = float4::Zero;

	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	Quaternion WorldQuaternion = DirectX::XMQuaternionIdentity();
	float4x4 LocalPositionMatrix;

	// scale * rotation * position
	float4x4 LocalWorldMatrix;


	float4x4 WorldMatrix;
	float4x4 WorldViewProjectionMatrix;

	float4x4 View;
	float4x4 Projection;
	float4x4 ViewPort;

	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;
};

