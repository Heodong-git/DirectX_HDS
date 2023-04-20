#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

struct TransformData
{
	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalQuaternion;
	float4 LocalPosition;
	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldQuaternion;
	float4 WorldPosition;
	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;
	float4x4 LocalWorldMatrix;
	float4x4 WorldMatrix;
	float4x4 View;
	float4x4 Projection;
	float4x4 ViewPort;
	float4x4 WorldViewProjectionMatrix;


public:
	TransformData()
	{
		LocalScale = float4::One;
		LocalRotation = float4::Null;
		LocalQuaternion = float4::Null;
		LocalPosition = float4::Zero;
		WorldScale = float4::One;
		WorldRotation = float4::Null;
		WorldQuaternion = float4::Null;
		WorldPosition = float4::Zero;
	}
};

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

		TransData.WorldScale = _Value;

		if (nullptr == Parent)
		{
			TransData.LocalScale = TransData.WorldScale;
		}
		else
		{
			TransData.LocalScale = TransData.WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
		}

		TransformUpdate();
		CalChild();
	}

	void SetWorldRotation(const float4& _Value)
	{
		if (true == IsDebug())
		{
			int a = 0;
		}

		// 90 0 0 
		// 여기에는 이미 최종값이 들어가 있다.
		// 내가 어떤 과정을 거쳐서 여기로 들어온 것이다.

		// 최종적으로 적용된 행렬이다.
		TransData.WorldRotation = _Value;
		// 부모가 적용됐기 때문에 나는 이상태가 된겁니다.

		// RotationMatrix 이게 최종 나의 회전행렬이다.
		// RotationMatrix <= 누구때문에 나는 이렇게 되었나?


		if (nullptr == Parent)
		{
			TransData.LocalRotation = TransData.WorldRotation;
		}
		else
		{
			//float4 Quaternion = WorldRotation.EulerDegToQuaternion();
			//float4x4 WorldRotationMatrix = WorldRotation.QuaternionToRotationMatrix();

			//float4x4 LocalRotationMatrix;
			//LocalRotationMatrix = Parent->GetWorldMatrixRef().InverseReturn() * WorldRotationMatrix;

			//LocalRotationMatrix.DecomposeRotQuaternion(LocalQuaternion);

			//LocalRotation = LocalQuaternion.QuaternionToEulerDeg();

			float4 Rot = Parent->GetWorldRotation();
			TransData.LocalRotation = TransData.WorldRotation - Parent->GetWorldRotation();
		}

		TransformUpdate();
		CalChild();
	}

	void SetWorldPosition(const float4& _Value)
	{
		TransData.WorldPosition = _Value;

		if (nullptr == Parent)
		{
			TransData.LocalPosition = TransData.WorldPosition;
		}
		else
		{
			TransData.LocalPosition = TransData.WorldPosition * Parent->GetWorldMatrixRef().InverseReturn();
		}

		TransformUpdate();
		CalChild();
	}

	void SetLocalScale(const float4& _Value)
	{
		TransData.LocalScale = _Value;

		if (nullptr == Parent)
		{
			TransData.WorldScale = TransData.LocalScale;
		}
		else
		{
			TransData.WorldScale = TransData.LocalScale * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	void SetLocalRotation(const float4& _Value)
	{
		TransData.LocalRotation = _Value;

		if (nullptr == Parent)
		{
			TransData.WorldRotation = TransData.LocalRotation;
		}
		else
		{
			//  180         90, 0,           90, 0, 0
			TransData.WorldRotation = TransData.LocalRotation + Parent->GetWorldRotation();
		}

		TransformUpdate();
		CalChild();
	}

	void SetLocalPosition(const float4& _Value)
	{
		TransData.LocalPosition = _Value;

		if (nullptr == Parent)
		{
			TransData.WorldPosition = TransData.LocalPosition;
		}
		else
		{
			TransData.WorldPosition = TransData.LocalPosition * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(TransData.LocalScale + _Value);
	}

	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(TransData.LocalRotation + _Value);
	}

	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(TransData.LocalPosition + _Value);
	}

	void AddWorldScale(const float4& _Value)
	{
		SetWorldScale(TransData.WorldScale + _Value);
	}

	void AddWorldRotation(const float4& _Value)
	{
		SetWorldRotation(TransData.WorldRotation + _Value);
	}

	void AddWorldPosition(const float4& _Value)
	{
		SetWorldPosition(TransData.WorldPosition + _Value);
	}


	float4 GetWorldForwardVector()
	{
		return TransData.WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetWorldUpVector()
	{
		return TransData.WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetWorldRightVector()
	{
		return TransData.WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetWorldBackVector()
	{
		return -GetWorldForwardVector();
	}

	float4 GetWorldDownVector()
	{
		return -GetWorldUpVector();
	}

	float4 GetWorldLeftVector()
	{
		return -GetWorldRightVector();
	}


	float4 GetLocalForwardVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetLocalUpVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetLocalRightVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetLocalPosition()
	{
		return TransData.LocalPosition;
	}

	float4 GetLocalScale()
	{
		return TransData.LocalScale;
	}

	float4 GetLocalRotation()
	{
		return TransData.LocalRotation;
	}


	float4 GetWorldPosition()
	{
		return TransData.WorldPosition;
	}

	float4 GetWorldScale()
	{
		return TransData.WorldScale;
	}

	float4 GetWorldRotation()
	{
		return TransData.WorldRotation;
	}


	float4x4 GetLocalWorldMatrix()
	{
		return TransData.LocalWorldMatrix;
	}

	const float4x4& GetLocalWorldMatrixRef()
	{
		return TransData.LocalWorldMatrix;
	}

	const float4x4 GetWorldMatrix()
	{
		return TransData.WorldMatrix;
	}

	const float4x4& GetWorldMatrixRef()
	{
		return TransData.WorldMatrix;
	}

	const float4x4 GetWorldViewProjectionMatrix()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		TransData.View = _View;
		TransData.Projection = _Projection;
		TransData.WorldViewProjectionMatrix = TransData.WorldMatrix * TransData.View * TransData.Projection;
	}

	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		TransData.ViewPort = _ViewPort;
		TransData.WorldViewProjectionMatrix *= TransData.ViewPort;
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

	const TransformData& GetTransDataRef()
	{
		return TransData;
	}

	void SetTransformData(const TransformData& _Data)
	{
		TransData = _Data;
	}

protected:

private:
	void TransformUpdate();

	TransformData TransData;

	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;
};

