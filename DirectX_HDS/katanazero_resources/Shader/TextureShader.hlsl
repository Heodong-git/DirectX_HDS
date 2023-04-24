

// Ʈ������ �����͸� ������ �������

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
struct VertexInputType
{
    // ���ؽ����̴��� �Էµ� ����
	// �ø�ƽ : ��ǲ ����ü�� �������� � �ڷ�� ����� �� �˷��ִ� ��
    
    //           ������ ������ � ��������
    float4 Pos : POSITION;
    // UV��ǥ�� : 3���� ������ �����￡ �ؽ��ĸ� ������ ���� ������ �Ǵ� 2���� ��ǥ���Դϴ�. 
    // UV��ǥ�� �ּ� 0 �ִ� 1�� ��ǥ�� ������ 1�� �Ѿ�ų� 0 �̸��� �� ��� �ؽ��İ� �ݺ��Ǿ� ��µȴ�. 
    // �ִ밪�� ��������. ���ϴ� ������ ������ �����ϴٰ���. 
    float4 UV : TEXCOORD;
};

struct PixelInputType
{
    // �ȼ����̴��� �Է� �� ����
    // �����Ͷ��������� ������ ���� 
    // w ������ ���� �� ����Ʈ ���ϰ� �ȼ��� ������ �� ����� ������ ������ ���� �ž�
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

PixelInputType Texture_VS(VertexInputType _Value)
{
    PixelInputType PixelInputValue = (PixelInputType) 0;
	
    _Value.Pos.w = 1.0f;
    // �����Ʈ���� �� : mul �Լ��� ����Ͽ� ����
    PixelInputValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    //OutPutValue.Pos = _Value.Pos;
    PixelInputValue.UV = _Value.UV;
	
	// �����ܰ迡�� ����� ������.
    // _Value.Pos *= �������������;

    return PixelInputValue;
}
 
cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}

// �ؽ��ĸ� ����Ϸ��� 
Texture2D GameTex : register(t0);

// ���÷�
SamplerState CLAMPSAMPLER : register(s0);

float4 Texture_PS(PixelInputType _Value) : SV_Target0
{
    // ������ ǥ����
    // float4
    // float4.xy == float2
    // float4.xyz == float3 
    float4 Color = GameTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
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
