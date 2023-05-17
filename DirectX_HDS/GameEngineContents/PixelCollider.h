#pragma once
#include "BaseActor.h"

#include <GameEngineCore/GameEngineComponent.h>
#include <GameEngineCore/GameEngineTexture.h>

enum class ColMapName
{
	COLMAP0,
	COLMAP1,
	COLMAP2,
	COLMAP3,
	COLMAP4,
};

// ���� :
class PixelCollider : public GameEngineComponent
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

	void Start() override;
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

	// �ʿ��� find �Լ� ����� 
	
protected:

private:
	std::shared_ptr<class GameEngineTexture> m_CurColMap = nullptr;
	ColMapName m_CurColMapName = ColMapName::COLMAP0;

	// ���ڿ��� �浹������
	std::vector<std::shared_ptr<class GameEngineTexture>> m_ColMaps;

	
	GameEnginePixelColor m_BlackPixel = { static_cast<char>(0), static_cast<char>(0) , static_cast<char>(0) ,
										static_cast<char>(255) };
	GameEnginePixelColor m_WhitePixel = { static_cast<char>(255), static_cast<char>(255) , static_cast<char>(255) ,
										static_cast<char>(255) };
	GameEnginePixelColor m_GreenPixel = { static_cast<char>(0), static_cast<char>(255) , static_cast<char>(0) ,
										static_cast<char>(255) };
};
