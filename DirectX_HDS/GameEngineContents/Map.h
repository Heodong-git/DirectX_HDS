#pragma once
#include "BaseActor.h"

// 설명 : 맵에서 검은색 뒷배경 렌더러 깔고 시작. 
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
	void ComponentSetting();

	// 메인맵 렌더러 
	std::shared_ptr<class GameEngineSpriteRenderer> m_MapRender = nullptr;

	// 뒤에 깔릴 검은색배경, 백그라운드 렌더러
	std::shared_ptr<class GameEngineSpriteRenderer> m_BackGround = nullptr;
};
