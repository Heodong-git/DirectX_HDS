#pragma once
#include <list>
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

	// 
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

protected:

private:
	void TransformUpdate();

	// 추후에 쓸것이고.
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;

	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Zero;
	float4 LocalPosition = float4::Zero;

	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;

	// 크기 * 회전 * 이동
	float4x4 LocalWorldMatrix;
};

