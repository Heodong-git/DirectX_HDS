#pragma once
#include "BaseActor.h"

// 설명 :
class Platform : public BaseActor
{
	// 테스트
public:
	static Platform* MainPlatform;
public:
	// constrcuter destructer
	Platform();
	~Platform();

	// delete Function
	Platform(const Platform& _Other) = delete;
	Platform(Platform&& _Other) noexcept = delete;
	Platform& operator=(const Platform& _Other) = delete;
	Platform& operator=(Platform&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer> m_Render = nullptr;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void DebugUpdate();
private:
};
