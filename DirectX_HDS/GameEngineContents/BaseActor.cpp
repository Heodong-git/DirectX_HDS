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
		MsgAssert("Level �� nullptr �Դϴ�.");
		return nullptr;
	}

	return Level;
}

// ������Լ� 
void BaseActor::Reverse(GameEngineSpriteRenderer* _Renderer)
{
	if (nullptr == _Renderer)
	{
		MsgAssert("�������� nullptr �Դϴ�.");
		return;
	}

	// ���� ������ ����ִٸ� return; 
	if (true == Infos.empty())
	{
		// ���⼭ bool �� �ϳ��ΰ�, ��ȭ�Ϸ� üũ�� �ϰ�,
		// true�� �ٲ���ٸ� �ܺ� ��ȭ state ���� ���¸� �����Ų��. 
		m_Recording_Complete = true;
		return;
	}


	// �Ųٷ� ���.
	ReverseInfo& Info = *(Infos.rbegin());
	
	// ������ ��ġ
	this->GetTransform()->SetTransformData(Info.ActorData);
	// ������ ��ġ�������ְ�
	_Renderer->GetTransform()->SetTransformData(Info.RendererData);
	// �������� �ؽ�ó�� 
	_Renderer->SetTexture(Info.InfoData.Texture->GetName());

	// ��Ʋ�� ������ �������ָ�.
	_Renderer->SetAtlasData(Info.InfoData.CutData);


	Infos.pop_back();
}

// ������ ��ġ���� �̰� ȣ��?? 
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

