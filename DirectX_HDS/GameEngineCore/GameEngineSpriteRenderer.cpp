#include "PrecompileHeader.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineSprite.h"

std::shared_ptr<GameEngineTexture> AnimationInfo::CurFrameTexture()
{
	const SpriteInfo& Info = Sprite->GetSpriteInfo(CurFrame);
	return Info.Texture;
}

bool AnimationInfo::IsEnd()
{
	return IsEndValue;
}

void AnimationInfo::Reset()
{
	CurFrame = StartFrame;
	CurTime = 0.0f;
	IsEndValue = false;
}

void AnimationInfo::Update(float _DeltaTime)
{
	IsEndValue = false;
	CurTime -= _DeltaTime;

	if (0.0f >= CurTime)
	{
		++CurFrame;
		CurTime = Inter;

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
	GameEngineRenderer::Start();

	SetPipeLine("2DTexture");
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

std::shared_ptr<AnimationInfo> GameEngineSpriteRenderer::CreateAnimation(const std::string_view& _Name,
	const std::string_view& _SpriteName,
	float _FrameInter /*= 0.1f*/,
	int _Start /*= -1*/,
	int _End /*= -1*/,
	bool _Loop /*= true*/)
{
	if (nullptr != FindAnimation(_Name))
	{
		MsgAssert("이미 존재하는 이름의 애니메이션을 또 만들려고 했습니다." + std::string(_Name));
		return nullptr;
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(_SpriteName);

	if (nullptr == Sprite)
	{
		MsgAssert("존재하지 않는 스프라이트로 애니메이션을 만들려고 했습니다." + std::string(_Name));
		return nullptr;
	}

	std::shared_ptr<AnimationInfo> NewAnimation = std::make_shared<AnimationInfo>();
	Animations[_Name.data()] = NewAnimation;

	if (-1 != _Start)
	{
		if (_Start < 0)
		{
			MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 마들려고 했습니다." + std::string(_Name));
			return nullptr;
		}

		NewAnimation->StartFrame = _Start;
	}
	else
	{
		NewAnimation->StartFrame = 0;
	}

	if (-1 != _End)
	{
		if (_End >= Sprite->GetSpriteCount())
		{
			MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 마들려고 했습니다." + std::string(_Name));
			return nullptr;
		}

		NewAnimation->EndFrame = _End;
	}
	else
	{
		NewAnimation->EndFrame = Sprite->GetSpriteCount() - 1;
	}

	NewAnimation->Sprite = Sprite;
	NewAnimation->Parent = this;
	NewAnimation->Loop = _Loop;
	NewAnimation->Inter = _FrameInter;

	return NewAnimation;
}


void GameEngineSpriteRenderer::ChangeAnimation(const std::string_view& _Name, size_t _Frame, bool _Force)
{
	std::shared_ptr<AnimationInfo> Find = FindAnimation(_Name);

	if (CurAnimation == Find && false == _Force)
	{
		return;
	}

	CurAnimation = FindAnimation(_Name);
	CurAnimation->Reset();

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

		GetShaderResHelper().SetTexture("DiffuseTex", CurAnimation->CurFrameTexture());

	}

	GameEngineRenderer::Render(_Delta);
}