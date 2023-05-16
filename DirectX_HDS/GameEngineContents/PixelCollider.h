#pragma once
#include "BaseActor.h"

// ���� 
#include <GameEngineCore/GameEngineComponent.h>

#include <GameEngineCore/GameEngineTexture.h>

// ���� :
class PixelCollider : public BaseActor
{
public:
	// constrcuter destructer
	PixelCollider();
	~PixelCollider();

	// delete Function
	PixelCollider(const PixelCollider& _Other) = delete;
	PixelCollider(PixelCollider&& _Other) noexcept = delete;
	PixelCollider& operator=(const PixelCollider& _Other) = delete;
	PixelCollider& operator=(PixelCollider&& _Other) noexcept = delete;

	// ���߿� �ʿ� �����ϰ� ���ڿ�Ű������ �������°ɷ� ����
	std::shared_ptr<class GameEngineTexture> GetColMap()
	{
		return m_CurColMap;
	}

	void Start();
	bool PixelCollision(class GameEngineObject* _Object);

	// �˻��ϱ��� ���� ������ ���� �˻��� �浹���� Ȯ���Ѵ�.
	bool ColMapSetting();

	// ���� ���� ���� �ִ���
	// ��¥ ���� üũ. 
	bool GroundCheck(class GameEngineObject* _Object);

	// ������ üũ 
	bool RightPixelCheck();

	// ���� üũ 
	bool LeftPixelCheck();

	// �� üũ 
	bool TopPixelCheck();

protected:

private:
	std::shared_ptr<class GameEngineTexture> m_CurColMap = nullptr;

	// ��
	GameEnginePixelColor m_BlackPixel = { static_cast<char>(0), static_cast<char>(0) , static_cast<char>(0) ,
										static_cast<char>(255) };
	GameEnginePixelColor m_WhitePixel = { static_cast<char>(255), static_cast<char>(255) , static_cast<char>(255) ,
										static_cast<char>(255) };
	GameEnginePixelColor m_GreenPixel = { static_cast<char>(0), static_cast<char>(255) , static_cast<char>(0) ,
										static_cast<char>(255) };
};
