
// 0~ 16�� ������ �ְ�
// ������ ���ٰ� ����Ѵٴ� �ǹ̰� �ƴϴ�.
// 0�������� ����ϰڴٰ� �ϴ� �ǹ̰� �ȴ�. 
// constantbuffer (�������) : ����� ��ü���� �޶����� ��� �����͸� ��� ���� �������
cbuffer TransformData : register(b0)
{
    float4x4 WorldMatrix;
}

// 1. � ������ ������ ����ü�� ������ ��
// 2. ��� ������, ��� �÷�����
// 3. �̸��� ���� ���ϸ� �ȴ�.
struct Input
{
	// �ø�ƽ : ��ǲ ����ü�� �������� � �ڷ�� ����� �� �˷��ִ� ��
    
    //           ������ ������ � ��������
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct Output
{
    // �����Ͷ��������� ������ ���� 
    // w ������ ���� �� ����Ʈ ���ϰ� �ȼ��� ������ �� ����� ������ ������ ���� �ž�
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

Output Texture_VS(Input _Value)
{
    Output OutPutValue = (Output)0;
	
    _Value.Pos.w = 1.0f;
    // �����Ʈ���� �� : mul �Լ��� ����Ͽ� ����
    OutPutValue.Pos = mul(_Value.Pos, WorldMatrix);
    //OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;
	
	// �����ܰ迡�� ����� ������.
    // _Value.Pos *= �������������;

    return OutPutValue;
}
 
cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

// 0��° Ÿ�ٿ� ����϶�� �ǹ̰� �ȴ�. 
float4 Texture_PS(Output _Value) : SV_Target0
{
    return OutColor;
}

// �Ʒ� ������ �����Ͽ� �� �ڵ�ó�� �ۼ��� �����ϴ�. 
//struct OutColor
//{
//    // ��Ƴ��� ��ȭ���� 0��° ��ȭ���� ����ض�.
//    float4 Color : SV_Target0;
//};

//OutColor Texture_PS(Output _Value)
//{
//    OutColor ReturnColor = (OutColor) 0;
//    ReturnColor.Color = _Value.Color;
//    return ReturnColor;
//}
