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

void BaseActor::ForcedReset()
{
	Infos.clear();
	m_Recording_Complete = true;
}

BaseLevel::LevelState BaseActor::GetLevelState()
{
	BaseLevel* CurLevel = GetReturnCastLevel();
	return CurLevel->GetCurState();
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

	// 뒤쪽 데이터 부터 받아온다. 

	BaseLevel::LevelState CurLevelState = GetLevelState();

	switch (CurLevelState)
	{
	case BaseLevel::LevelState::RECORDING_PROGRESS:
	{
		ReverseInfo& Info = *(Infos.rbegin());

		if (true == Info.IsRecording)
		{
			_Renderer->On();
		}

		else if (false == Info.IsRecording)
		{
			Infos.pop_back();
			return;
		}

		this->GetTransform()->SetTransformData(Info.ActorData);
		_Renderer->GetTransform()->SetTransformData(Info.RendererData);
		_Renderer->SetTexture(Info.InfoData.Texture->GetName());
		_Renderer->SetAtlasData(Info.InfoData.CutData);

		// 데이터 세팅 후 삭제 
		Infos.pop_back();
	}
		break;
	case BaseLevel::LevelState::RECORDING_PROGRESS_FORWARD:
	{
		ReverseInfo& Info = *(Infos.begin());

		if (true == Info.IsRecording)
		{
			_Renderer->On();
		}

		else if (false == Info.IsRecording)
		{
			Infos.pop_front();
			return;
		}

		this->GetTransform()->SetTransformData(Info.ActorData);
		_Renderer->GetTransform()->SetTransformData(Info.RendererData);
		_Renderer->SetTexture(Info.InfoData.Texture->GetName());
		_Renderer->SetAtlasData(Info.InfoData.CutData);

		// 데이터 세팅 후 삭제 
		Infos.pop_front();
	}
		break;
	default:
		break;
	}
	
}

// 적절한 위치에서 이걸 호출?? 
void BaseActor::InfoSetting(GameEngineSpriteRenderer* _Renderer)
{
	SpriteInfo Info;

	GameEngineTextureSetter* Tex = _Renderer->GetShaderResHelper().GetTextureSetter("DiffuseTex");
	Info.Texture = Tex->Res;
	Info.CutData = _Renderer->GetAtlasData();

	Infos.push_back({ _Renderer->GetActor()->GetTransform()->GetTransDataRef(), _Renderer->GetTransform()->GetTransDataRef(), Info , m_IsRecording });
}

void BaseActor::Update(float _DeltaTime)
{
	
}

