#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"
#include <map>

// 애니메이션 정보
class AnimationInfo : public std::enable_shared_from_this<AnimationInfo>
{
	friend class GameEngineSpriteRenderer;

private:
	GameEngineSpriteRenderer* Parent = nullptr;
	std::shared_ptr<GameEngineSprite> Sprite = nullptr;

	// 애니메이션이 종료된 시점에서 true 
	bool IsEndValue = false;

	void Reset();
	void Update(float _DeltaTime);

	// 현재프레임의 텍스쳐 반환 
	std::shared_ptr<GameEngineTexture> CurFrameTexture();

public:
	size_t CurFrame = 0;		// 현재 프레임값 
	size_t StartFrame = -1;		// 시작 프레임값
	size_t EndFrame = -1;		// 종료 프레임값
	float CurTime = 0.0f;		// 
	float Inter = 0.1f;			// 
	bool Loop = true;			// 반복여부 
	bool ScaleToImage = false;	// 이미지의 크기로 세팅할 것인지에 대한 여부 

	bool IsEnd();				// 애니메이션이 종료되었다면 
};

// 
class AnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view SpriteName = "";
	float FrameInter = 0.1f;
	int Start = -1;
	int End = -1;
	bool Loop = true;
	bool ScaleToImage = false;

};

// 설명 :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	// 텍스쳐의 크기그대로 세팅
	void SetScaleToTexture(const std::string_view& _Name);
	void SetTexture(const std::string_view& _Name);

	void SetFlipX();
	void SetFlipY();

	std::shared_ptr<AnimationInfo> FindAnimation(const std::string_view& _Name);

	std::shared_ptr<AnimationInfo> CreateAnimation(const std::string_view& _Name,
		const std::string_view& _SpriteName,
		float _FrameInter = 0.1f,			   // 프레임당 간격 
		int _Start = -1,
		int _End = -1,
		bool _Loop = true,
		bool _ScaleToImage = false);

	// 파라미터를 인자로 넣어줄 경우 넣어준 구조체의 값으로 CreateAnimation 
	std::shared_ptr<AnimationInfo> CreateAnimation(const AnimationParameter& _Paramter)
	{
		return CreateAnimation(_Paramter.AnimationName,
			_Paramter.SpriteName,
			_Paramter.FrameInter,
			_Paramter.Start,
			_Paramter.End,
			_Paramter.Loop,
			_Paramter.ScaleToImage);
	}

	void ChangeAnimation(const std::string_view& _Name, bool _Force, size_t _Frame = -1)
	{
		ChangeAnimation(_Name, _Frame, _Force);
	}

	void ChangeAnimation(const std::string_view& _Name, size_t _Frame = -1, bool _Force = true);

protected:

private:
	void Render(float _Delta) override;

	std::map<std::string, std::shared_ptr<AnimationInfo>> Animations;

	std::shared_ptr<AnimationInfo> CurAnimation = nullptr;

	void Start() override;
};

