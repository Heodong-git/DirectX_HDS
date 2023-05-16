#pragma once
#include "BaseActor.h"

// 보류 
#include <GameEngineCore/GameEngineComponent.h>

#include <GameEngineCore/GameEngineTexture.h>

// 설명 :
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

	// 나중에 맵에 저장하고 문자열키값으로 가져오는걸로 변경
	std::shared_ptr<class GameEngineTexture> GetColMap()
	{
		return m_CurColMap;
	}

	void Start();
	bool PixelCollision(class GameEngineObject* _Object);

	// 검사하기전 현재 레벨에 따라서 검사할 충돌맵을 확인한다.
	bool ColMapSetting();

	// 내가 현재 땅에 있는지
	// 진짜 땅만 체크. 
	bool GroundCheck(class GameEngineObject* _Object);

	// 오른쪽 체크 
	bool RightPixelCheck();

	// 왼쪽 체크 
	bool LeftPixelCheck();

	// 위 체크 
	bool TopPixelCheck();

protected:

private:
	std::shared_ptr<class GameEngineTexture> m_CurColMap = nullptr;

	// 땅
	GameEnginePixelColor m_BlackPixel = { static_cast<char>(0), static_cast<char>(0) , static_cast<char>(0) ,
										static_cast<char>(255) };
	GameEnginePixelColor m_WhitePixel = { static_cast<char>(255), static_cast<char>(255) , static_cast<char>(255) ,
										static_cast<char>(255) };
	GameEnginePixelColor m_GreenPixel = { static_cast<char>(0), static_cast<char>(255) , static_cast<char>(0) ,
										static_cast<char>(255) };
};
