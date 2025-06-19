Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

struct PS_Input
{
    float4 inputPosition : SV_Position;
    float2 inputTexCoord : TEXCOORD;
};

float4 main(PS_Input input) : SV_Target
{
    return myTexture.Sample(mySampler, input.inputTexCoord);
}