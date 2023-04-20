#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"


void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBuffer)
	{
		ConstantBuffer.insert(Setter);
	}
}

// 상수버퍼 세팅
void GameEngineConstantBufferSetter::Setting()
{
	Res->ChangeData(CPUData, static_cast<UINT>(CPUDataSize));

	ShaderType Type = ParentShader->GetType();

	switch (Type)
	{
	case ShaderType::None:
	{
		MsgAssert("어떤 쉐이더에 세팅될지 알수없는 상수버퍼 입니다.");
		break;
	}
	case ShaderType::Vertex:
	{
		Res->VSSetting(BindPoint);
		break;
	}
	case ShaderType::Pixel:
	{
		Res->PSSetting(BindPoint);
		break;
	}
	default:
		break;
	}
}


void GameEngineShaderResHelper::Setting()
{
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator StartIter = ConstantBuffer.begin();
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator EndIter = ConstantBuffer.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		GameEngineConstantBufferSetter& Setter = StartIter->second;
		Setter.Setting();
	}
}

void GameEngineShaderResHelper::SetConstantBufferLink(const std::string_view& _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBuffer.find(UpperName);

	if (ConstantBuffer.end() == FindIter)
	{
		MsgAssert("존재하지 않는 상수버퍼를 세팅하려고 했습니다." + UpperName);
		return;
	}

	// lower_bound : 같은 이름의 키값중 가장 앞에 있는 데이터를 가리키는 이터레이터 반환
	// upper_bound : 같은 이름의 키값중 가장 뒤쪽 데이터의 다음을 가리키는 이터레이터 반환 
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStartIter = ConstantBuffer.lower_bound(UpperName);
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEndIter = ConstantBuffer.upper_bound(UpperName);

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		GameEngineConstantBufferSetter& Setter = NameStartIter->second;

		// 버퍼의사이즈가 다르다면
		if (Setter.Res->GetBufferSize() != _Size)
		{
			MsgAssert("상수버퍼와 세팅하려는 데이터의 크기가 다릅니다. 상수버퍼 : " + std::to_string(Setter.Res->GetBufferSize()) + "유저가 세팅한 데이터" + std::to_string(_Size) + UpperName);
			return;
		}

		// 사이즈가 같다면
		Setter.CPUData = _Data;
		Setter.CPUDataSize = _Size;
	}

}