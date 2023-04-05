#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"

class GameEngineObject : public GameEngineObjectBase
{
	friend class GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineObject();
	// �Ҹ��� virtual �� �ϴ� ����
	// - ��ӹ��� �ڽ� Ŭ������ �Ҹ��ڸ� ����� ȣ���ϱ� ���ؼ�
	// �Ҹ��ڸ� ���� �����Լ��� ������ ����
	// 1. ������ ���������Լ��� ������ �Լ��� ���. 
	// ���� �����Լ��� ����� ����
	// 1. �ڽĿ��� �������̽��� �����ϱ� ���ؼ�
	// 2. �� Ŭ������ ��ü�� ������ ���ϰ� �ϱ� ���ؼ�
	virtual ~GameEngineObject() = 0;

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	GameEngineTransform* GetTransform()
	{
		return &Transform;
	}
protected:

private:
	
	////////////////////////////////////////////////////////////// Transform ���ϱ���
private:
	GameEngineTransform Transform;
};