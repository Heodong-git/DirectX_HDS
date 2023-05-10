#pragma once
#include "CKatanaZero_Actor.h"

// º≥∏Ì : ∏ ø°º≠ ∞À¿∫ªˆ µﬁπË∞Ê ∑ª¥ı∑Ø ±Ú∞Ì Ω√¿€. 
class CMap : public CKatanaZero_Actor
{
public:
	// constrcuter destructer
	CMap();
	~CMap();

	// delete Function
	CMap(const CMap& _Other) = delete;
	CMap(CMap&& _Other) noexcept = delete;
	CMap& operator=(const CMap& _Other) = delete;
	CMap& operator=(CMap&& _Other) noexcept = delete;

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
