#include "PrecompileHeader.h"
#include "Monster_Gangster.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


Monster_Gangster::Monster_Gangster()
{
}

Monster_Gangster::~Monster_Gangster()
{
}

void Monster_Gangster::Start()
{
	// 리소스 로드
	LoadAndCreateAnimation();
	// 렌더러생성 및 세팅
	ComponentSetting();
}

void Monster_Gangster::Update(float _DeltaTime)
{
}

void Monster_Gangster::Render(float _DeltaTime)
{
}

void Monster_Gangster::ComponentSetting()
{
	// 렌더러, 충돌체 생성
}

void Monster_Gangster::LoadAndCreateAnimation()
{
	// 여기서 필요한 리소스 로드 후 애니메이션 만들어
}
