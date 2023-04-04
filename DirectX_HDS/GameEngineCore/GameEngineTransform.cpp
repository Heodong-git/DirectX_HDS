#include "GameEngineTransform.h"
#include "GameEngineObject.h"

GameEngineTransform::GameEngineTransform()
{
}

GameEngineTransform::~GameEngineTransform()
{
}


void GameEngineTransform::TransformUpdate()
{
	// 스케일,회전,이동
	LocalScaleMatrix.Scale(LocalScale);
	LocalRotationMatrix.RotationDeg(LocalRotation);
	LocalPositionMatrix.Pos(LocalPosition);

	LocalWorldMatrix = LocalScaleMatrix * LocalRotationMatrix * LocalPositionMatrix;

	// 스케일, 회전, 이동 , 공전, 부모 , 뷰행렬, 투영행렬, 뷰포트행렬 


	// 부모가 없다면 
	if (nullptr == Parent)
	{
		WorldMatrix = LocalWorldMatrix;
	}
	else
	{
		// 부모가 있을 경우의 연산
		WorldMatrix = LocalWorldMatrix * Parent->GetWorldMatrixRef();
	}

}
