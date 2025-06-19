cbuffer WorldViewProjection
{
    float4x4 WVP;
};

struct VS_Input
{
    float3 inputPosition : POSITION;
    float2 inputTexCoord : TEXCOORD;
    row_major float4x4 inputTransformMatrix : TRANSFORM_MATRIX;
    int size : SIZE;
};

struct VS_Output
{
    float4 outputPosition : SV_Position;
    float2 outputTexCoord : TEXCOORD;
    int size : SIZE;
};

VS_Output main(VS_Input input)
{
    float4 finalPosition = mul(float4(input.inputPosition, 1.0f), input.inputTransformMatrix);
    finalPosition = mul(finalPosition, WVP);
 
    VS_Output output;
    output.outputPosition = finalPosition;
    output.outputTexCoord = input.inputTexCoord;
    output.size = input.size;
    
    return output;
}