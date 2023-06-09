#include "PrecompileHeader.h"
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

// 바이너리로 저장
void GameEngineFile::SaveBin(const GameEngineSerializer& _Data)
{
	// c스타일의 파일입출력, 파일포인터 준비
	FILE* FilePtr = nullptr;

	// 경로를 받아온다. 
	std::string PathString = Path.GetFullPath();
	
	// 저장 유형 설정, write , binary 
	std::string Text = "wb";

	// 파일포인터, 경로, 유형을 인자로 넣어준다. 
	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	// 만약 파일포인터가 nullptr 이라면 터뜨린다.
	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패했습니다." + PathString);
	}

	// 열어준 파일에 입력
	// 1번인자 : 데이터
	// 2번인자 : 데이터의 크기
	// 3번인자 : 파일포인터
	fwrite(_Data.GetConstData(), _Data.GetOffset(), 1, FilePtr);

	// 파일을 열었다면 닫아준다.
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

// 텍스트로 저장
void GameEngineFile::SaveText(const std::string_view& _View)
{
	FILE* FilePtr = nullptr;
	std::string PathString = Path.GetFullPath();
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

// 바이너리로 저장되어 있는 파일로드
void GameEngineFile::LoadBin(GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	std::string PathString = Path.GetFullPath();
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

void GameEngineFile::LoadText(GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	std::string PathString = Path.GetFullPath();
	std::string Text = "rt";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패했습니다." + PathString);
	}

	size_t FileSize = std::filesystem::file_size(Path.Path);

	_Data.BufferResize(FileSize);

	fread_s(_Data.GetData(), _Data.GetBufferSize(), FileSize, 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

std::string GameEngineFile::GetString()
{

	uintmax_t size = GetFileSize();
	GameEngineSerializer Ser;
	Ser.BufferResize(size + 1);
	LoadText(Ser);

	return Ser.GetString();
}

uintmax_t GameEngineFile::GetFileSize()
{
	return std::filesystem::file_size(Path.Path);
}