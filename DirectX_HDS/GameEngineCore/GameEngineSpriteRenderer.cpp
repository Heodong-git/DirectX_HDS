#include "PrecompileHeader.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineSprite.h"

const SpriteInfo& AnimationInfo::CurSpriteInfo()
{
	// 스프라이트인포 클래스 변수에 스프라이트의 현재프레임의 정보를 담아서 반환한다. 
	const SpriteInfo& Info = Sprite->GetSpriteInfo(FrameIndex[CurFrame]);
	return Info;
}

bool AnimationInfo::IsEnd()
{
	return IsEndValue;
}

// 애니메이션 정보를 초기화
void AnimationInfo::Reset()
{
	CurFrame = 0;				// 현재프레임 초기화
	CurTime = FrameTime[0];		// 현재프레임의 진행시간 초기화
	IsEndValue = false;			// 애니메이션 종료 여부 초기화 
	IsPauseValue = false;		// 애니메이션의 정지 여부 초기화 

	for (std::pair<const size_t, AnimationStartEvent>& Pair : StartEventFunction)
	{
		Pair.second.IsEvent = false;
	}
}

// 애니메이션 정보의 업데이트
void AnimationInfo::Update(float _DeltaTime)
{
	if (true == Loop)
	{
		IsEndValue = false;
	}

	// 1;
	// 

	if (true == IsPauseValue)
	{
		return;
	}

	size_t CurFrameIndex = FrameIndex[CurFrame];


	if (StartEventFunction.end() != StartEventFunction.find(CurFrameIndex))
	{
		if (false == StartEventFunction[CurFrameIndex].IsEvent
			&& nullptr != StartEventFunction[CurFrameIndex].Function)
		{
			StartEventFunction[CurFrameIndex].Function();
			StartEventFunction[CurFrameIndex].IsEvent = true;
		}

	}


	if (UpdateEventFunction.end() != UpdateEventFunction.find(CurFrameIndex))
	{
		UpdateEventFunction[CurFrameIndex]();
	}

	CurTime -= _DeltaTime;

	if (0.0f >= CurTime)
	{
		++CurFrame;

		if (FrameIndex.size() <= CurFrame)
		{
			IsEndValue = true;

			if (true == Loop)
			{
				CurFrame = 0;

				for (std::pair<const size_t, AnimationStartEvent>& Pair : StartEventFunction)
				{
					Pair.second.IsEvent = false;
				}
			}
			else
			{
				IsEndValue = true;
				--CurFrame;
			}
		}



		CurTime += FrameTime[CurFrame];

		// 0 ~ 9

		// 9
	}

}





// ----------------------------------SpriteRenderer-------------------------------------

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}


void GameEngineSpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	SpriteRenderInit();
}

void GameEngineSpriteRenderer::SetTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);

	//Animation이 동작하는 SpriteRenderer에 다시 텍스처를 세팅할 때 사용됩니다.
	CurAnimation = nullptr;
	AtlasData = float4{ 0.0f, 0.0f, 1.0f, 1.0f };


	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_Name);
	if (nullptr == FindTex)
	{
		MsgAssert("존재하지 않는 이미지 입니다.");
		return;
	}
	CurTexture = FindTex;
}

void GameEngineSpriteRenderer::SetFlipX()
{
	Flip.x = Flip.x != 0.0f ? 0.0f : 1.0f;
}

void GameEngineSpriteRenderer::SetFlipY()
{
	Flip.y = Flip.y != 0.0f ? 0.0f : 1.0f;
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
	CurTexture = FindTex;
}

// 아틀라스 이미지
void GameEngineSpriteRenderer::SetSprite(const std::string_view& _SpriteName, size_t _Frame/* = 0*/)
{
	Sprite = GameEngineSprite::Find(_SpriteName);
	Frame = _Frame;

	const SpriteInfo& Info = Sprite->GetSpriteInfo(Frame);
	GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);
	AtlasData = Info.CutData;
	CurTexture = Info.Texture;
}

void GameEngineSpriteRenderer::SetFrame(size_t _Frame)
{
	Frame = _Frame;

	const SpriteInfo& Info = Sprite->GetSpriteInfo(Frame);
	GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);
	AtlasData = Info.CutData;
	CurTexture = Info.Texture;
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

	// 애니메이션인포 변수 생성 shared ptr 
	std::shared_ptr<AnimationInfo> NewAnimation = std::make_shared<AnimationInfo>();
	
	// SpriteRenderer 의 맵에 애니메이션인포를
	// 인자로 들어온 파라미터의 애니메이션네임 문자열로 저장
	// 데이터가 이미 있다면 그 데이터를 반환하고, 없다면 만들어서 저장하는 map 의 문법
	Animations[_Paramter.AnimationName.data()] = NewAnimation;

	// 프레임인덱스 vector가 0이 아닐 경우
	if (0 != _Paramter.FrameIndex.size())
	{
		// 프레임 인덱스 입력시
		NewAnimation->FrameIndex = _Paramter.FrameIndex;
	}
	else
	{
		// 프레임 인덱스 미 입력시

		// 시작 프레임 지정
		if (-1 != _Paramter.Start)
		{
			// 파라미터의 시작인덱스값이 0보다 작다면 
			if (_Paramter.Start < 0)
			{
				MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 만들려고 했습니다." + std::string(_Paramter.AnimationName));
				return nullptr;
			}

			// 제대로 들어왔다면 생성한 애니메이션의 시작프레임값은 파라미터의 start 값 
			NewAnimation->StartFrame = _Paramter.Start;
		}
		else
		{
			// -1 입력시 시작프레임 0
			NewAnimation->StartFrame = 0;
		}

		// 끝 프레임 지정
		if (-1 != _Paramter.End)
		{
			if (_Paramter.End >= Sprite->GetSpriteCount())
			{
				MsgAssert("스프라이트 범위를 초과하는 인덱스로 애니메이션을 만들려고 했습니다." + std::string(_Paramter.AnimationName));
				return nullptr;
			}

			NewAnimation->EndFrame = _Paramter.End;
		}
		else
		{
			// -1 입력시 끝프레임은 마지막
			NewAnimation->EndFrame = Sprite->GetSpriteCount() - 1;
		}

		// 시작프레임값이 엔드프레임값보다 크다면
		if (NewAnimation->EndFrame < NewAnimation->StartFrame)
		{
			MsgAssert("애니메이션을 생성할때 End가 Start보다 클 수 없습니다");
			return nullptr;
		}

		NewAnimation->FrameIndex.reserve(NewAnimation->EndFrame - NewAnimation->StartFrame + 1);

		// StartFrame 부터 EndFrame까지 순서대로 FrameIndex에 푸시
		for (size_t i = NewAnimation->StartFrame; i <= NewAnimation->EndFrame; ++i)
		{
			NewAnimation->FrameIndex.push_back(i);
		}
	}

	// 만약 인자에 FrameTime 을 입력해주었다면
	if (0 != _Paramter.FrameTime.size())
	{
		// 그대로 받아주고, 
		NewAnimation->FrameTime = _Paramter.FrameTime;

	}
	// 그게 아니라면 
	else
	{
		// 애니메이션 정보에 저장되어 있는 값을 푸쉬백
		for (size_t i = 0; i < NewAnimation->FrameIndex.size(); ++i)
		{
			NewAnimation->FrameTime.push_back(_Paramter.FrameInter);
		}
	}

	NewAnimation->Sprite = Sprite;
	NewAnimation->Parent = this;
	NewAnimation->Loop = _Paramter.Loop;
	NewAnimation->ScaleToTexture = _Paramter.ScaleToTexture;

	return NewAnimation;
}

void GameEngineSpriteRenderer::SetAtlasConstantBuffer()
{
	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
}

void GameEngineSpriteRenderer::SetColorConstantBuffer()
{
	GetShaderResHelper().SetConstantBufferLink("ColorOption", ColorOptionValue);
}


void GameEngineSpriteRenderer::ChangeAnimation(const std::string_view& _Name, size_t _Frame, bool _Force)
{
	std::shared_ptr<AnimationInfo> Find = FindAnimation(_Name);

	if (nullptr == Find)
	{
		MsgAssert("이러한 이름의 애니메이션은 존재하지 않습니다" + std::string(_Name));
		return;
	}

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

void GameEngineSpriteRenderer::Update(float _Delta)
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
			CurTexture = Texture;
			float4 Scale = Texture->GetScale();

			Scale.x *= AtlasData.SizeX;
			Scale.y *= AtlasData.SizeY;
			Scale.z = 1.0f;

			Scale *= ScaleRatio;

			GetTransform()->SetLocalScale(Scale);
		}
	}
}

void GameEngineSpriteRenderer::Render(float _DeltaTime)
{
	GameEngineRenderer::Render(_DeltaTime);

	// 만약, 콜백함수가 nullptr이 아니라면 호출
	if (nullptr != RenderEndCallBack)
	{
		RenderEndCallBack(this);
	}
}

void GameEngineSpriteRenderer::SetAnimationUpdateEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event)
{
	std::shared_ptr<AnimationInfo> Info = FindAnimation(_AnimationName);

	if (nullptr == Info)
	{
		MsgAssert("존재하지 않는 애니메이션에 이벤트 세팅을 하려고 했습니다.");
	}

	Info->UpdateEventFunction[_Frame] = _Event;
}

void GameEngineSpriteRenderer::SetAnimationStartEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event)
{
	std::shared_ptr<AnimationInfo>  Info = FindAnimation(_AnimationName);

	if (nullptr == Info)
	{
		MsgAssert("존재하지 않는 애니메이션에 이벤트 세팅을 하려고 했습니다.");
	}

	Info->StartEventFunction[_Frame].IsEvent = false;
	Info->StartEventFunction[_Frame].Function = _Event;
}

std::string GameEngineSpriteRenderer::GetTexName()
{
	GameEngineTextureSetter* Tex = GetShaderResHelper().GetTextureSetter("DiffuseTex");
	std::string Name = Tex->Res->GetNameToString();
	return Name;
}

void GameEngineSpriteRenderer::SpriteRenderInit()
{
	SetMesh("Rect");
	SetPipeLine("2DTexture");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	//float4 HBSCMin = { 0.0f, 0.5f, 0.5f, 0.5f };

	ColorOptionValue.MulColor = float4::One;
	ColorOptionValue.PlusColor = float4::Null;
	//ColorOptionValue.HBSColor = HBSCMin;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("ColorOption", ColorOptionValue);
	GetShaderResHelper().SetConstantBufferLink("ClipData", Clip);
	GetShaderResHelper().SetConstantBufferLink("FlipData", Flip);
}

// 내 눈에 보이는 이미지에서 0.1;
void GameEngineSpriteRenderer::ImageClippingX(float _Ratio, ClipXDir _Dir)
{
	Clip.x = _Ratio;

	if (_Dir == ClipXDir::Left)
	{
		Clip.z = 0;
	}
	else {
		Clip.z = 1;
	}

	if (0.0f >= Clip.x)
	{
		Clip.x = 0.0f;
	}
}


void GameEngineSpriteRenderer::ImageClippingY(float _Ratio, ClipYDir _Dir)
{
	Clip.y = _Ratio;

	if (_Dir == ClipYDir::Top)
	{
		Clip.w = 0;
	}
	else {
		Clip.w = 1;
	}


	if (0.0f >= Clip.y)
	{
		Clip.y = 0.0f;
	}
}