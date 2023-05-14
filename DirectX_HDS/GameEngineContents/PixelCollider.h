#pragma once
#include "BaseActor.h"

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
	bool PixelCollision(class GameEngineTransform* _Transform);
protected:

private:
	std::shared_ptr<class GameEngineTexture> m_CurColMap = nullptr;
	
};
