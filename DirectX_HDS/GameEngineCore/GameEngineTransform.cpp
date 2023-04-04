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
	// ������,ȸ��,�̵�
	LocalScaleMatrix.Scale(LocalScale);
	LocalRotationMatrix.RotationDeg(LocalRotation);
	LocalPositionMatrix.Pos(LocalPosition);

	LocalWorldMatrix = LocalScaleMatrix * LocalRotationMatrix * LocalPositionMatrix;

	// ������, ȸ��, �̵� , ����, �θ� , �����, �������, ����Ʈ��� 


	// �θ� ���ٸ� 
	if (nullptr == Parent)
	{
		WorldMatrix = LocalWorldMatrix;
	}
	else
	{
		// �θ� ���� ����� ����
		WorldMatrix = LocalWorldMatrix * Parent->GetWorldMatrixRef();
	}

}
