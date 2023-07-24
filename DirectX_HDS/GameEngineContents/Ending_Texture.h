#pragma once
#include "BaseActor.h"

// Ό³Έν :
class Ending_Texture : public BaseActor
{
public:
	// constrcuter destructer
	Ending_Texture();
	~Ending_Texture();

	// delete Function
	Ending_Texture(const Ending_Texture& _Other) = delete;
	Ending_Texture(Ending_Texture&& _Other) noexcept = delete;
	Ending_Texture& operator=(const Ending_Texture& _Other) = delete;
	Ending_Texture& operator=(Ending_Texture&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> m_MainRender = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> m_SubRender = nullptr;
};
