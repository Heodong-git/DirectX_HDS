#include "PrecompileHeader.h"
#include "GameEngineTransform.h"
#include "GameEngineObject.h"

GameEngineTransform::GameEngineTransform()
{
	TransformUpdate();
}

GameEngineTransform::~GameEngineTransform()
{
}


void GameEngineTransform::TransformUpdate()
{
	TransData.ScaleMatrix.Scale(TransData.Scale);

	TransData.Rotation.w = 0.0f;
	TransData.Quaternion = TransData.Rotation.EulerDegToQuaternion();
	TransData.RotationMatrix = TransData.Quaternion.QuaternionToRotationMatrix();
	TransData.PositionMatrix.Pos(TransData.Position);

	TransData.LocalWorldMatrix = TransData.ScaleMatrix * TransData.RotationMatrix * TransData.PositionMatrix;


	if (nullptr == Parent)
	{
		TransData.WorldMatrix = TransData.LocalWorldMatrix;
	}
	else // 차이
	{
		float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
		float4 PScale, PRoatation, PPosition;
		ParentWorldMatrix.Decompose(PScale, PRoatation, PPosition);


		if (true == AbsoluteScale)
		{
			// 부모쪽 행렬의 스케일을 1
			PScale = float4::One;
		}
		if (true == AbsoluteRotation)
		{
			// 부모의 회전 
			PRoatation = float4::Zero;
			PRoatation.EulerDegToQuaternion();
		}
		if (true == AbsolutePosition)
		{
			PPosition = float4::Zero;
		}

		float4x4 MatScale, MatRot, MatPos;

		//scale
		MatScale.Scale(PScale);

		//rot
		MatRot = PRoatation.QuaternionToRotationMatrix();

		//pos
		MatPos.Pos(PPosition);

		TransData.WorldMatrix = TransData.LocalWorldMatrix * (MatScale * MatRot * MatPos);
	}

	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();
	// ParentWorldMatrix.Decompose(PScale, PRoatation, PPosition);

}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	Parent = _Parent;

	// 내가 이미 다른 부모가 있다면

	Parent->Child.push_back(this);
}




void GameEngineTransform::CalChild()
{
	for (GameEngineTransform* ChildTrans : Child)
	{
		if (false == ChildTrans->AbsoluteScale)
		{
			ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
		}

		if (false == ChildTrans->AbsoluteRotation)
		{
			ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
		}

		if (false == ChildTrans->AbsolutePosition)
		{
			ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition());
		}
	}
}



float4 GameEngineTransform::GetLocalPosition()
{
	return TransData.LocalPosition;
}

float4 GameEngineTransform::GetLocalScale()
{
	return TransData.LocalScale;
}

float4 GameEngineTransform::GetLocalRotation()
{
	return TransData.LocalRotation;
}

float4 GameEngineTransform::GetWorldPosition()
{
	return TransData.WorldPosition;
}

float4 GameEngineTransform::GetWorldScale()
{
	return TransData.WorldScale;
}

float4 GameEngineTransform::GetWorldRotation()
{
	return TransData.WorldRotation;
}