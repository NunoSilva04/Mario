cbuffer WorldViewProjection
{
    float4x4 WVP;
};

struct VS_Input
{
    float3 inputPosition : POSITION;
    float2 inputTexCoord : TEXCOORD;
    row_major float4x4 transformMatrix : TRANSFORM_MATRIX;
    float2 v0UV : V0_UV;
    float2 v1UV : V1_UV;
    float2 v2UV : V2_UV;
    float2 v3UV : V3_UV;
    uint vertexID : SV_VertexID;
};

struct VS_Output
{
    float4 outputPosition : SV_Position;
    float2 outputTexCoord : TEXCOORD;
};

float2 assignOutputTexCoord(VS_Input input);

VS_Output main(VS_Input input)
{
    VS_Output output;
    
    float4 finalPosition = mul(float4(input.inputPosition, 1.0f), input.transformMatrix);
    finalPosition = mul(finalPosition, WVP);
    output.outputPosition = finalPosition;
    
    output.outputTexCoord = assignOutputTexCoord(input);
    
    return output;
}

float2 assignOutputTexCoord(VS_Input input)
{
    float2 newPosition;
    if (input.vertexID == 0)
    {
        newPosition = input.v0UV;
    }
    else if (input.vertexID == 1)
    {
        newPosition = input.v1UV;
    }
    else if (input.vertexID == 2)
    {
        newPosition = input.v2UV;
    }
    else
    {
        newPosition = input.v3UV;
    }
    
    return newPosition;
}