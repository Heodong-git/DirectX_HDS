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
	// ���ҽ� �ε�
	LoadAndCreateAnimation();
	// ���������� �� ����
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
	// ������, �浹ü ����
}

void Monster_Gangster::LoadAndCreateAnimation()
{
	// ���⼭ �ʿ��� ���ҽ� �ε� �� �ִϸ��̼� �����
}
