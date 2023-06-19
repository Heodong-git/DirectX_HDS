#include "PrecompileHeader.h"
#include "GameEngineFont.h"


IFW1Factory* GameEngineFont::Factory = nullptr;

class FontFactoryCreator
{
public:
	FontFactoryCreator()
	{
		FW1CreateFactory(FW1_VERSION, &GameEngineFont::Factory);
	}

	~FontFactoryCreator()
	{
		if (nullptr != GameEngineFont::Factory)
		{
			// 다시 사용할때 비어있다는것을 알려주기 위해서
			// 프로그램이 종료될때 되는것.
			GameEngineFont::Factory->Release();
			GameEngineFont::Factory = nullptr;
		}
	}
};

FontFactoryCreator InitFont;

GameEngineFont::GameEngineFont()
{
}

GameEngineFont::~GameEngineFont()
{
	if (nullptr != Font)
	{
		Font->Release();
		Font = nullptr;
	}

}

void GameEngineFont::LoadFont(const std::string_view& _Path)
{
	std::wstring WPath = GameEngineString::AnsiToUniCode(_Path.data());

	if (S_OK != GameEngineFont::Factory->CreateFontWrapper(GameEngineDevice::GetDevice(), WPath.c_str(), &Font))
	{
		MsgAssert("폰트 생성 실패");
		return;
	}
}

void GameEngineFont::FontDraw(const std::string_view& _Text, const float4& _Pos, float _FontScale, const float4& _Color)
{
	std::wstring Text = GameEngineString::AnsiToUniCode(_Text);

	float4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };

	Font->DrawString(GameEngineDevice::GetContext(), Text.c_str(), _FontScale, _Pos.x, _Pos.y, _Color.ColorToUint(), FW1_TOP);
}