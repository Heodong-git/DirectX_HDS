#include "PrecompileHeader.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineSprite.h"

// 테스트
#include <GameEngineCore/GameEngineObject.h>

const SpriteInfo& AnimationInfo::CurSpriteInfo()
{
	const SpriteInfo& Info = Sprite->GetSpriteInfo(CurFrame);
	return Info;
}

bool AnimationInfo::IsEnd()
{
	return IsEndValue;
}

void AnimationInfo::Reset()
{
	CurFrame = StartFrame;
	CurTime = Inter;
	IsEndValue = false;
}

void AnimationInfo::Update(float _DeltaTime)
{
	IsEndValue = false;
	CurTime -= _DeltaTime;

	if (0.0f >= CurTime)
	{
		++CurFrame;
		CurTime += Inter;

		// 0 ~ 9

		// 9
		if (CurFrame > EndFrame)
		{
			IsEndValue = true;

			if (true == Loop)
			{
				CurFrame = StartFrame;
			}
			else
			{
				--CurFrame;
			}
		}
	}
}

// SpriteRenderer

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}


void GameEngineSpriteRenderer::Start()
{
	// 디버깅용 임시
	GameEngineObject* Ptr = this;

	GameEngineRenderer::Start();

	SetPipeLine("2DTexture");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);

	// AtlasData
}

void GameEngineSpriteRenderer::SetTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
}

void GameEngineSpriteRenderer::SetFlipX()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.x = -LocalScale.x;
	GetTransform()->SetLocalScale(LocalScale);
}

void GameEngineSpriteRenderer::SetFlipY()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.y = -LocalScale.y;
	GetTransform()->SetLocalScale(LocalScale);
}

void GameEngineSpriteRenderer::SetScaleToTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_Name);

	if (nullptr == FindTex)
	{
		MsgAssert("존재하지 않는 이미지 입니다.");
		return;
	}

	float4 Scale = float4(static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1);
	GetTransform()->SetLocalScale(Scale);
}

std::shared_ptr<AnimationInfo> GameEngineSpriteRenderer::FindAnimation(const std::string_view& _Name)
{
	std::map<std::string, std::shared_ptr<AnimationInfo>>::iterator FindIter = Animations.find(_Name.data());

	if (FindIter == Animations.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

std::shared_ptr<AnimationInfo> GameEngineSpriteRenderer::CreateAnimation(const AnimationParameter& _Paramter)
{
	if (nullptr != FindAnimation(_Paramter.AnimationName))
	{
		MsgAssert("이미 존재하는 이름의 애니메이션을 또 만들려고 했습니다." + std::string(_Paramter.AnimationName));
		return nullptr;
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(_Paramter.SpriteName);

	if (nullptr == Sprite)
	{
		MsgAssert("존재하지 않는 스프라이트로 애니메이션을 만들려고 했습니다." + std::string(_Paramter.AnimationName));
		return nullptr;
	}

	std::shared_ptr<AnimationInfo> NewAnimation = std::make_shared<AnimationInfo>();
	Animations[_Paramter.AnimationName.data()] = NewAnimation;

	if (-1 != _Paramter.Start)
	{
		if (_Paramter.Start < 0)
		{
			MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 마들려고 했습니다." + std::string(_Paramter.AnimationName));
			return nullptr;
		}

		NewAnimation->StartFrame = _Paramter.Start;
	}
	else
	{
		NewAnimation->StartFrame = 0;
	}

	if (-1 != _Paramter.End)
	{
		if (_Paramter.End >= Sprite->GetSpriteCount())
		{
			MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 마들려고 했습니다." + std::string(_Paramter.AnimationName));
			return nullptr;
		}

		NewAnimation->EndFrame = _Paramter.End;
	}
	else
	{
		NewAnimation->EndFrame = Sprite->GetSpriteCount() - 1;
	}

	NewAnimation->Sprite = Sprite;
	NewAnimation->Parent = this;
	NewAnimation->Loop = _Paramter.Loop;
	NewAnimation->Inter = _Paramter.FrameInter;
	NewAnimation->ScaleToTexture = _Paramter.ScaleToTexture;

	return NewAnimation;
}


void GameEngineSpriteRenderer::SetAtlasConstantBuffer()
{
	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
}

void GameEngineSpriteRenderer::ChangeAnimation(const std::string_view& _Name, size_t _Frame, bool _Force)
{
	// 애니메이션 정보를 찾아온다. 
	std::shared_ptr<AnimationInfo> Find = FindAnimation(_Name);

	// 애니메이션이 없다면
	if (nullptr == Find)
	{
		MsgAssert("이러한 이름의 애니메이션은 존재하지 않습니다" + std::string(_Name));
		return;
	}

	// 현재 애니메이션과 찾아온 애니메이션이 같고, force가 false라면 return 
	if (CurAnimation == Find && false == _Force)
	{
		return;
	}

	// 현재 애니메이션은 찾아온 애니메이션이 되고
	CurAnimation = FindAnimation(_Name);
	// 한번 초기화해준다. 
	CurAnimation->Reset();

	// 인자로들어온 프레임이 -1이 아니라면 현재프레임은 ~ 
	if (_Frame != -1)
	{
		CurAnimation->CurFrame = _Frame;
	}

}

void GameEngineSpriteRenderer::Render(float _Delta)
{
	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_Delta);

		const SpriteInfo& Info = CurAnimation->CurSpriteInfo();

		GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);
		AtlasData = Info.CutData;

		if (true == CurAnimation->ScaleToTexture)
		{
			std::shared_ptr<GameEngineTexture> Texture = Info.Texture;

			float4 Scale = Texture->GetScale();

			Scale.x *= Info.CutData.SizeX;
			Scale.y *= Info.CutData.SizeY;

			Scale *= ScaleRatio;

			GetTransform()->SetLocalScale(Scale);
		}

	}

	GameEngineRenderer::Render(_Delta);
}