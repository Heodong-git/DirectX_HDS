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
	friend class Player;
public:
	static PixelCollider* PixelCol;
public:
	// constrcuter destructer
	PixelCollider();
	~PixelCollider();

	// delete Function
	PixelCollider(const PixelCollider& _Other) = delete;
	PixelCollider(PixelCollider&& _Other) noexcept = delete;
	PixelCollider& operator=(const PixelCollider& _Other) = delete;
	PixelCollider& operator=(PixelCollider&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineTexture> GetColMap()
	{
		return m_CurColMap;
	}

	GameEnginePixelColor PixelCollision(const float4& _Pos);

	// �˻��ϱ��� ���� ������ ���� �˻��� �浹���� Ȯ���Ѵ�.
	bool ColMapSetting();

	bool GroundCheck(class GameEngineObject* _Object);

	// ������ üũ 
	bool RightPixelCheck();
	float4 RightWallCheck(float4& _Pos);
	// ���� üũ 
	bool LeftPixelCheck();
	// �� üũ 
	bool TopPixelCheck();

	// ��
	static GameEnginePixelColor g_BlackPixel;

	static GameEnginePixelColor g_WhitePixel;

	// ��
	static GameEnginePixelColor g_GreenPixel;

	// ����
	static GameEnginePixelColor g_ErrorPixel;
protected:
	void Start() override;
private:
	std::shared_ptr<class GameEngineTexture> m_CurColMap = nullptr;
	ColMapName m_CurColMapName = ColMapName::COLMAP0;

	static std::vector<std::shared_ptr<class GameEngineTexture>> m_ColMaps;

	

};
