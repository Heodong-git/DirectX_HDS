#pragma once
#include "GameEngineTexture.h"


// 텍스쳐가 로드되지 않았다면 로드도 처리해줌, 무조건 한개 이상의 이미지 정보가 들어있어야함. 
class GameEngineSprite : public GameEngineResource<GameEngineSprite>
{
private:
	class SpriteInfo
	{
		std::shared_ptr<GameEngineTexture> Sprite;
		float4 CutData;
	};

public:
	// constrcuter destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;


	static std::shared_ptr<GameEngineSprite> LoadFolder(const std::string_view& _Path);

	//// 텍스처를 기반으로 생성되고 
	//static std::shared_ptr<GameEngineTexture> CreateTexture(const std::string_view& _TexureName, int X, int Y)
	//{
	//	return;
	//}


protected:

private:
	std::vector<SpriteInfo> Sprites;

};

