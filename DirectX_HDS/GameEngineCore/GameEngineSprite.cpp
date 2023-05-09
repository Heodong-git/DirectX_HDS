#include "PrecompileHeader.h"
#include "GameEngineSprite.h"

GameEngineSprite::GameEngineSprite()
{
}

GameEngineSprite::~GameEngineSprite()
{
}

std::shared_ptr<GameEngineSprite> GameEngineSprite::LoadFolder(const std::string_view& _Path)
{
	GameEngineDirectory Dir = _Path;

	if (false == Dir.GetPath().IsDirectory())
	{
		MsgAssert("디렉토리가 아닌 경로입니다." + std::string(_Path));
	}

	std::vector<GameEngineFile> AllFile = Dir.GetAllFile({ ".png", ".jpg" });

	if (0 >= AllFile.size())
	{
		MsgAssert("이미지가 존재하지 않는 경로입니다." + std::string(_Path));
	}

	std::string FileName = Dir.GetPath().GetFileName();

	std::shared_ptr<GameEngineSprite> NewTexture = GameEngineResource::Create(FileName);

	return NewTexture;
}

