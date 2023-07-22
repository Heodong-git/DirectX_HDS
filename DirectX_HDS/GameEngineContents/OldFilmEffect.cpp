#include "PrecompileHeader.h"
#include "OldFilmEffect.h"

OldFilmEffect::OldFilmEffect()
{
}

OldFilmEffect::~OldFilmEffect()
{
}

//
void OldFilmEffect::Start(GameEngineRenderTarget* _Target)
{
	// 리소스 로드
	if (nullptr == GameEngineSprite::Find("oldfilmeffect1"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("katanazero_resources");
		NewDir.Move("katanazero_resources");
		NewDir.Move("Texture");
		NewDir.Move("ClubLevel");
		NewDir.Move("oldfilmeffect");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("oldfilmeffect1").GetFullPath());
	}

	OldUnit = std::make_shared<GameEngineRenderUnit>();
	OldUnit->SetMesh("FullRect");
	OldUnit->SetPipeLine("OldFilm");

	OldData.x = 3.5f;

	OldUnit->ShaderResHelper.SetConstantBufferLink("OldFilmData", OldData);


	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void OldFilmEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	if (false == m_Update)
	{
		return;
	}
	
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("oldfilmeffect1");
	SpriteInfo Info = Sprite->GetSpriteInfo(Index);

	if (Sprite->GetSpriteCount() <= ++Index)
	{
		Index = 0;
	}

	OldUnit->ShaderResHelper.SetTexture("DiffuseTex", Info.Texture);

	ResultTarget->Clear();
	ResultTarget->Setting();
	OldUnit->Render(_DeltaTime);
	OldUnit->ShaderResHelper.AllResourcesReset();

	// _Target->Clear();
	_Target->Merge(ResultTarget);

}