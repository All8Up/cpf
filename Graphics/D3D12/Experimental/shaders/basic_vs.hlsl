cbuffer CbViewProj : register(b0)
{
	matrix View;
	matrix InvView;
	matrix Projection;
	float Near;
	float Far;
};

// TODO: Use ifdefs to remove this when instancing or unique shaders?  Probably unique.
cbuffer CbModelTransform : register(b1)
{
	float3x3 Orientation;
	float3 Scale;
	float3 Translation;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float4 color: COLOR;
	float3 translation : TRANSLATION;
//	float3x3 orientation : ORIENTATION;
};


struct VS_OUTPUT
{
	float4 pos: SV_POSITION;
	float4 color: COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;

	float3 position = input.pos;
	float4 model = float4(mul(position * Scale, Orientation) + Translation, 1.0);
	model = model + float4(input.translation, 0.0f);
	float4 world = mul(model, View);
	float4 projection = mul(world, Projection);
	output.pos = projection;
	output.color = input.color;
	return output;
}
