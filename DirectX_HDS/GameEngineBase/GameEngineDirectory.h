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
	
	// �������͸��� �̵�
	bool MoveParent();
	
	// �������͸��� ���ڿ��� �־��� ���͸��� �ִ��� Ȯ���Ͽ� �̵��Ѵ�.
	void MoveParentToDirectory(const std::string_view& _String);

	// ���ڷ� �־��� ��η� �̵��Ѵ�. 
	bool Move(const std::string_view& _String);

	// �н��� �߰���θ� �ٿ��ش�.
	GameEnginePath GetPlusFileName(const std::string_view& _String);

	// ������ ���� �ʰ� �� ���丮�� �ش��ϴ� ��� ���ϸ� ��ȯ���ش�.
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

