#pragma once
#include "GameEngineTexture.h"

// 스프라이트 정보 
class SpriteInfo
{
public:
	std::shared_ptr<GameEngineTexture> Texture = nullptr;
	float4 CutData = {};
};

// 설명 : 스프라이트는 무조건 1개 이상의 이미지 정보가 들어가있어야함. 
class GameEngineSprite : public GameEngineResource<GameEngineSprite>
{
public:
	// constrcuter destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;
	
	// 폴더전체로드 
	static std::shared_ptr<GameEngineSprite> LoadFolder(const std::string_view& _Path)
	{
		GameEnginePath NewPath = std::string(_Path);

		std::shared_ptr<GameEngineSprite> NewTexture = GameEngineResource::Create(NewPath.GetFileName());
		NewTexture->ResLoadFolder(_Path);
		return NewTexture;
	}

	// 스프라이트 이름으로 폴더로드
	static std::shared_ptr<GameEngineSprite> LoadFolder(std::string _Spritename, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineSprite> NewTexture = GameEngineResource::Create(_Spritename);
		NewTexture->ResLoadFolder(_Path);
		return NewTexture;
	}

	// 아틀라스이미지로드 , 사용할려나? 
	static std::shared_ptr<GameEngineSprite> LoadSheet(const std::string_view& _Path, size_t _X, size_t _Y)
	{
		GameEnginePath NewPath = std::string(_Path);

		std::shared_ptr<GameEngineSprite> NewTexture = GameEngineResource::Create(NewPath.GetFileName());
		NewTexture->ResLoadSheet(_Path, _X, _Y);
		return NewTexture;
	}

	size_t GetSpriteCount()
	{
		return Sprites.size();
	}

	// 해당 인덱스의 스프라이트정보 반환 
	const SpriteInfo& GetSpriteInfo(size_t _Index)
	{
		if (_Index < 0)
		{
			MsgAssert("0이하의 스프라이트 인덱스 입니다.");
		}

		if (_Index >= Sprites.size())
		{
			MsgAssert("스프라이트의 인덱스를 오버했습니다.");
		}

		return Sprites[_Index];
	}

	static std::shared_ptr<GameEngineSprite> UnLoad(const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineSprite> FindSprite = GameEngineResource::Find(_Name);

		if (nullptr == FindSprite)
		{
			MsgAssert("존재하지 않는 스프라이트를 언로드 하려고 했습니다.");
		}

		FindSprite->Release();
		return FindSprite;
	}


	static std::shared_ptr<GameEngineSprite> ReLoad(const std::string_view& _Path)
	{
		GameEnginePath NewPath(_Path);
		return ReLoad(_Path, NewPath.GetFileName());
	}

	static std::shared_ptr<GameEngineSprite> ReLoad(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineSprite> NewTexture = GameEngineResource<GameEngineSprite>::Find(_Name);

		if (nullptr == NewTexture)
		{	
			// 리로드할 스프라이트가 존재하지 않는다면 로드폴더를 하도록 수정 
			return LoadFolder(_Name.data(), _Path);
		}

		NewTexture->ReLoad();
		return NewTexture;
	}

	void ReLoad();
	void Release();

protected:

private:
	void ResLoadFolder(const std::string_view& _Path);
	void ResLoadSheet(const std::string_view& _Path, size_t _X, size_t _Y);

	std::vector<SpriteInfo> Sprites = std::vector<SpriteInfo>();

};

