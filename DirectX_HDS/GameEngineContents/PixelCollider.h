#pragma once
#include "BaseActor.h"

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
	bool PixelCollision(class GameEngineTransform* _Transform);
protected:

private:
	std::shared_ptr<class GameEngineTexture> m_CurColMap = nullptr;
	
};
