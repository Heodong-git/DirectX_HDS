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

// 설명 :
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

	// 검사하기전 현재 레벨에 따라서 검사할 충돌맵을 확인한다.
	bool ColMapSetting();

	bool GroundCheck(class GameEngineObject* _Object);

	// 오른쪽 체크 
	bool RightPixelCheck();
	float4 RightWallCheck(float4& _Pos);
	// 왼쪽 체크 
	bool LeftPixelCheck();
	// 위 체크 
	bool TopPixelCheck();

	// 땅
	static GameEnginePixelColor g_BlackPixel;

	static GameEnginePixelColor g_WhitePixel;

	// 벽
	static GameEnginePixelColor g_GreenPixel;

	// 에러
	static GameEnginePixelColor g_ErrorPixel;
protected:
	void Start() override;
private:
	std::shared_ptr<class GameEngineTexture> m_CurColMap = nullptr;
	ColMapName m_CurColMapName = ColMapName::COLMAP0;

	static std::vector<std::shared_ptr<class GameEngineTexture>> m_ColMaps;

	

};
