#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"


class GameEngineFile;
class GameEngineDirectory
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	~GameEngineDirectory();

	GameEngineDirectory(const std::string_view& _Path)
		: Path(_Path)
	{

	}

	GameEngineDirectory(std::filesystem::path _Path)
		: Path(_Path)
	{

	}

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	bool IsFile(const std::string_view& _FileName);
	
	// 상위디렉터리로 이동
	bool MoveParent();
	
	// 상위디렉터리에 문자열로 넣어준 디렉터리가 있는지 확인하여 이동한다.
	void MoveParentToDirectory(const std::string_view& _String);

	// 인자로 넣어준 경로로 이동한다. 
	bool Move(const std::string_view& _String);

	// 패스에 추가경로를 붙여준다.
	GameEnginePath GetPlusFileName(const std::string_view& _String);

	// 하위는 돌지 않고 그 디렉토리에 해당하는 모든 파일만 반환해준다.
	std::vector<GameEngineFile> GetAllFile(std::vector<std::string_view> _Ext);

	const GameEnginePath& GetPath()
	{
		return Path;
	}

protected:

private:
	// "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\";
	GameEnginePath Path;
};

