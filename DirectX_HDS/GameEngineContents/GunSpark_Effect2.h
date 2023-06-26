#pragma once
#include "BaseActor.h"

// Ό³Έν :
class GunSpark_Effect2 : public BaseActor
{
public:
	// constrcuter destructer
	GunSpark_Effect2();
	~GunSpark_Effect2();

	// delete Function
	GunSpark_Effect2(const GunSpark_Effect2& _Other) = delete;
	GunSpark_Effect2(GunSpark_Effect2&& _Other) noexcept = delete;
	GunSpark_Effect2& operator=(const GunSpark_Effect2& _Other) = delete;
	GunSpark_Effect2& operator=(GunSpark_Effect2&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> GetRender()
	{
		return m_Render;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
};
