#include "PrecompileHeader.h"

#include "CBoss_HeadHunter.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineShaderResHelper.h>


CBoss_HeadHunter::CBoss_HeadHunter()
{
}

CBoss_HeadHunter::~CBoss_HeadHunter()
{
}

void CBoss_HeadHunter::Start()
{
	Render0 = CreateComponent<GameEngineRenderer>();
	// 파이프라인세팅 
	Render0->SetPipeLine("2DTexture");
	Render0->GetShaderResHelper().SetTexture("DiffuseTex", "headhunter_idle_10.png");
	Render0->GetTransform()->SetLocalScale(m_Scale);
}

void CBoss_HeadHunter::Update(float _DeltaTime)
{
	float4 pos = GetTransform()->GetLocalPosition();

	int a = 0; 
}

void CBoss_HeadHunter::Render(float _DeltaTime)
{
	
}

