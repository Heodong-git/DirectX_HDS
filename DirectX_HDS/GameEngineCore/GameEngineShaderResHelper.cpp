#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"


void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBufferSetters)
	{
		ConstantBufferSetters.insert(Setter);
	}

	for (const std::pair<std::string, GameEngineTextureSetter>& Setter : _ResHelper.TextureSetters)
	{
		TextureSetters.insert(Setter);
	}

	for (const std::pair<std::string, GameEngineSamplerSetter>& Setter : _ResHelper.SamplerSetters)
	{
		SamplerSetters.insert(Setter);
	}

}

void GameEngineConstantBufferSetter::Setting()
{
	Res->ChangeData(CPUData, CPUDataSize);

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


void GameEngineTextureSetter::Setting()
{
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

void GameEngineSamplerSetter::Setting()
{
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
	{
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator StartIter = ConstantBufferSetters.begin();
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator EndIter = ConstantBufferSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineConstantBufferSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}

	{
		std::multimap<std::string, GameEngineTextureSetter>::iterator StartIter = TextureSetters.begin();
		std::multimap<std::string, GameEngineTextureSetter>::iterator EndIter = TextureSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineTextureSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}

	{
		std::multimap<std::string, GameEngineSamplerSetter>::iterator StartIter = SamplerSetters.begin();
		std::multimap<std::string, GameEngineSamplerSetter>::iterator EndIter = SamplerSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineSamplerSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}


}

void GameEngineShaderResHelper::SetConstantBufferLink(const std::string_view& _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBufferSetters.find(UpperName);

	if (ConstantBufferSetters.end() == FindIter)
	{
		MsgAssert("존재하지 않는 상수버퍼를 세팅하려고 했습니다." + UpperName);
		return;
	}

	// 중복된 키값의 데이터중 가장 앞데이터 반환
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStartIter = ConstantBufferSetters.lower_bound(UpperName);
	// 중복된 키값의 데이터중 가장 마지막데이터의 다음 데이터 반환
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEndIter = ConstantBufferSetters.upper_bound(UpperName);

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		GameEngineConstantBufferSetter& Setter = NameStartIter->second;

		if (Setter.Res->GetBufferSize() != _Size)
		{
			MsgAssert("상수버퍼와 세팅하려는 데이터의 크기가 다릅니다. 상수버퍼 : " + std::to_string(Setter.Res->GetBufferSize()) + "유저가 세팅한 데이터" + std::to_string(_Size) + UpperName);
			return;
		}

		Setter.CPUData = _Data;
		Setter.CPUDataSize = _Size;
	}

}