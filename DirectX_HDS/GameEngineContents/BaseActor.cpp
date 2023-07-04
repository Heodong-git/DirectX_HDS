#include "PrecompileHeader.h"
#include "BaseActor.h"
#include "BaseLevel.h"

#include <GameEngineBase/GameEngineRandom.h>

BaseActor::BaseActor()
{
}

BaseActor::~BaseActor()
{
}

const int BaseActor::CreateRandomValue(const int _MAX)
{
	int RandomValue = GameEngineRandom::MainRandom.RandomInt(1, _MAX);
	return RandomValue;
}

BaseLevel* BaseActor::GetReturnCastLevel() const
{
	BaseLevel* Level = dynamic_cast<BaseLevel*>(GetLevel());
	
	if (nullptr == Level)
	{
		MsgAssert("Level 이 nullptr 입니다.");
		return nullptr;
	}

	return Level;
}

// 역재생함수 
void BaseActor::Reverse(GameEngineSpriteRenderer* _Renderer)
{
	if (nullptr == _Renderer)
	{
		MsgAssert("렌더러가 nullptr 입니다.");
		return;
	}

	// 만약 인포가 비어있다면 return; 
	if (true == Infos.empty())
	{
		// 여기서 bool 값 하나두고, 녹화완료 체크를 하고,
		// true로 바뀌었다면 외부 녹화 state 에서 상태를 종료시킨다. 
		m_Recording_Complete = true;
		return;
	}


	// 거꾸로 비긴.
	ReverseInfo& Info = *(Infos.rbegin());
	
	// 액터의 위치
	this->GetTransform()->SetTransformData(Info.ActorData);
	// 랜더러 위치세팅해주고
	_Renderer->GetTransform()->SetTransformData(Info.RendererData);
	// 랜더러의 텍스처와 
	_Renderer->SetTexture(Info.InfoData.Texture->GetName());

	// 아틀라스 데이터 세팅해주면.
	_Renderer->SetAtlasData(Info.InfoData.CutData);


	Infos.pop_back();
}

// 적절한 위치에서 이걸 호출?? 
void BaseActor::InfoSetting(GameEngineSpriteRenderer* _Renderer)
{
	SpriteInfo Info;

	GameEngineTextureSetter* Tex = _Renderer->GetShaderResHelper().GetTextureSetter("DiffuseTex");
	Info.Texture = Tex->Res;
	Info.CutData = _Renderer->GetAtlasData();

	Infos.push_back({ _Renderer->GetActor()->GetTransform()->GetTransDataRef(), _Renderer->GetTransform()->GetTransDataRef(), Info });
}

void BaseActor::Update(float _DeltaTime)
{
	
}

