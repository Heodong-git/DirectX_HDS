#pragma once
#include "BaseActor.h"

// º≥∏Ì : ∏ ø°º≠ ∞À¿∫ªˆ µﬁπË∞Ê ∑ª¥ı∑Ø ±Ú∞Ì Ω√¿€. 
class Map : public BaseActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineSpriteRenderer>& GetRender()
	{
		return m_MapRender;
	}
	
protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> m_MapRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> m_BackGround = nullptr;
};
