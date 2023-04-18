#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

// 설명 : 파이프라인 안에서 실행되는 프로그래밍 가능 셰이더에 상수 정보를 제공하는데 사용된다. 
class GameEngineConstantBuffer : public GameEngineResource<GameEngineConstantBuffer>, public GameEngineDirectBuffer
{
public:

	// constrcuter destructer
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

	// delete Function
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _Other) noexcept = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer& operator=(GameEngineConstantBuffer&& _Other) noexcept = delete;

	// 버퍼의 크기, 이름, Desc를 인자로 받고 
	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(int _Byte, const std::string_view& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
	{
		// 동일한 크기의 버퍼가 없다면 생성
		if (ConstantBufferRes.end() == ConstantBufferRes.find(_Byte))
		{
			ConstantBufferRes[_Byte];
			// 그 크기의 상수버퍼가 존재하지 않는다.
		}

		std::string UpperName = GameEngineString::ToUpper(_Name.data());

		// end == 라는건 데이터가 없다.
		// end != 라는건 데이터가 있다는건디??? 아아아아
		// 같은 크기의 버퍼중에 해당하는 이름으로 데이터가 있다면 녀석을 반환하고
		// 없다면 생성하여 추가한 후, 그 데이터를 반환한다. 이거구나 
		if (ConstantBufferRes[_Byte].end() != ConstantBufferRes[_Byte].find(UpperName))
		{
			return ConstantBufferRes[_Byte][UpperName];
		}

		// 데이터가 없다면 버퍼를 생성 후 
		std::shared_ptr<GameEngineConstantBuffer> Buffer = CreateUnNamed();
		// 인자로 들어온 string 을 키값으로 하여 저장 후 
		ConstantBufferRes[_Byte][UpperName] = Buffer;
		// 리소스생성
		Buffer->ResCreate(_BufferDesc);
		// 버퍼반환
		return Buffer;
	}

	static void ResourcesClear();

protected:
	void ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc);

private:
	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBufferRes;
};

