
// 0~ 16�� ������ �ְ�
// ������ ���ٰ� ����Ѵٴ� �ǹ̰� �ƴϴ�.
// 0�������� ����ϰڴٰ� �ϴ� �ǹ̰� �ȴ�. 
// constantbuffer (�������) : ����� ��ü���� �޶����� ��� �����͸� ��� ���� �������
cbuffer TransformData : register(b0)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;
    float4x4 LocalScaleMatrix;
    float4x4 LocalRotationMatrix;
    float4x4 LocalPositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}

// 1. � ������ ������ ����ü�� ������ ��
// 2. ��� ������, ��� �÷�����
// 3. �̸��� ���� ���ϸ� �ȴ�.
struct Input
{
	// �ø�ƽ : ��ǲ ����ü�� �������� � �ڷ�� ����� �� �˷��ִ� ��
    
    //           ������ ������ � ��������
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct Output
{
    // �����Ͷ��������� ������ ���� 
    // w ������ ���� �� ����Ʈ ���ϰ� �ȼ��� ������ �� ����� ������ ������ ���� �ž�
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

Output Texture_VS(Input _Value)
{
    Output OutPutValue = (Output)0;
	
    _Value.Pos.w = 1.0f;
    // �����Ʈ���� �� : mul �Լ��� ����Ͽ� ����
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    //OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
	
	// �����ܰ迡�� ����� ������.
    // _Value.Pos *= �������������;

    return OutPutValue;
}
 
cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

// �ؽ��ĸ� ����Ϸ��� 
Texture2D DiffuseTex : register(t0);

// ���÷� 
SamplerState CLAMPSAMPLER : register(s0);

float4 Texture_PS(Output _Value) : SV_Target0
{
    // ������ ǥ�����̶�� �ؼ�
    // float4
    // float4.xy == float2
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    return Color;
}
// 0��° Ÿ�ٿ� ����϶�� �ǹ̰� �ȴ�. 
//float4 Texture_PS(Output _Value) : SV_Target0
//{
//    return OutColor;
//}

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
