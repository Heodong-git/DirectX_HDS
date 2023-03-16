#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineFile::GameEngineFile() 
{
}

GameEngineFile::~GameEngineFile() 
{
}


GameEngineFile::GameEngineFile(std::filesystem::path _Path) 
	: Path(_Path)
{

}

void GameEngineFile::SaveBin(const GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	std::string PathString = Path.GetPathToString();
	std::string Text = "wb";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패했습니다." + PathString);
	}

	//                         500               1
	fwrite(_Data.GetConstData(), _Data.GetOffset(), 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

void GameEngineFile::SaveText(const std::string_view& _View)
{
	FILE* FilePtr = nullptr;
	std::string PathString = Path.GetPathToString();
	std::string Text = "wt";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패했습니다." + PathString);
	}

	//                         500               1
	fwrite(_View.data(), _View.size(), 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

void GameEngineFile::LoadBin(GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	std::string PathString = Path.GetPathToString();
	std::string Text = "rb";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패했습니다." + PathString);
	}

	size_t FileSize = std::filesystem::file_size(Path.Path);
	
	fread_s(_Data.GetData(), _Data.GetBufferSize(), FileSize, 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}