#pragma once
#include "BaseActor.h"

// Ό³Έν :
class Hud : public BaseActor
{
public: 
	static Hud* MainHud;
public:
	// constrcuter destructer
	Hud();
	~Hud();

	// delete Function
	Hud(const Hud& _Other) = delete;
	Hud(Hud&& _Other) noexcept = delete;
	Hud& operator=(const Hud& _Other) = delete;
	Hud& operator=(Hud&& _Other) noexcept = delete;

	void RenderOff();
	
protected:
	void Start() override;
private:
	std::shared_ptr<class GameEngineUIRenderer> m_MainRender = nullptr;
};
