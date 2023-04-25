#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include <GameEngineCore/GameEngineNameObject.h>

// ���߻�� 
class GameEngineObject : 
	public GameEngineObjectBase, 
	public GameEngineNameObject,
	public std::enable_shared_from_this<GameEngineObject>
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

	// ���ӿ���������Ʈ�� ��ӹ��� Ŭ������ shared ptr�� ����Ϸ��� �� �� 
	// ��ü���� ȣ���ϰ� �Ǹ� shared ptr �� dynamic cast �� �ش��ϴ� Ŭ������ ����ȯ �Ͽ� ��ȯ
	template<typename PtrType>
	std::shared_ptr<PtrType> Shared_This_dynamic_pointer()
	{
		return std::dynamic_pointer_cast<PtrType>(std::enable_shared_from_this<GameEngineObject>::shared_from_this());
	}

protected:

private:
	
	////////////////////////////////////////////////////////////// Transform ���ϱ���
private:
	GameEngineTransform Transform;
};