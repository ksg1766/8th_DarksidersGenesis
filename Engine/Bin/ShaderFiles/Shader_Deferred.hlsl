#include "Engine_Shader_Defines.hlsl"

matrix			g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;

vector			g_vLightDir;
Texture2D		g_NormalTexture;
Texture2D		g_DiffuseTexture;
Texture2D		g_ShadeTexture;

Texture2D		g_Texture;

struct VS_IN
{
	float3		vPosition : POSITION;
	float2		vTexcoord : TEXCOORD0;
};

struct VS_OUT
{	
	float4		vPosition : SV_POSITION;
	float2		vTexcoord : TEXCOORD0;
};

VS_OUT VS_MAIN(/* ���� */VS_IN In)
{
	VS_OUT			Out = (VS_OUT)0;
	
	matrix			matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	Out.vPosition = mul(float4(In.vPosition, 1.f), matWVP);

	Out.vTexcoord = In.vTexcoord;

	return Out;
}

struct PS_IN
{
	float4		vPosition : SV_POSITION;
	float2		vTexcoord : TEXCOORD0;
};


struct PS_OUT
{
	float4	vColor : SV_TARGET0;
};


PS_OUT PS_MAIN_DEBUG(PS_IN In)
{
	PS_OUT			Out = (PS_OUT)0;

	Out.vColor = g_Texture.Sample(LinearSampler, In.vTexcoord);

	return Out;
}

struct PS_OUT_LIGHT
{
	float4	vShade : SV_TARGET0;	
};

PS_OUT_LIGHT PS_MAIN_DIRECTIONAL(PS_IN In)
{
	PS_OUT_LIGHT		Out = (PS_OUT_LIGHT)0;

	vector		vNormalDesc = g_NormalTexture.Sample(PointSampler, In.vTexcoord);

	vector		vNormal = vector(vNormalDesc.xyz * 2.f - 1.f, 0.f);

	Out.vShade = saturate(dot(normalize(g_vLightDir) * -1.f, vNormal));

	return Out;
}

PS_OUT PS_MAIN_DEFERRED(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector		vDiffuse = g_DiffuseTexture.Sample(PointSampler, In.vTexcoord);
	if (vDiffuse.a == 0.f)
		discard;
	vector		vShade = g_ShadeTexture.Sample(LinearSampler, In.vTexcoord);

	Out.vColor = vDiffuse * vShade;

	return Out;
}

technique11 DefaultTechnique
{
	pass Target_Debug
	{
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_None, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 1.f), 0xffffffff);
		
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DEBUG();
	}

	pass Light_Directional
	{
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_None, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DIRECTIONAL();
	}

	pass Light_Point
	{
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_None, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DIRECTIONAL();
	}

	pass Deferred
	{
        SetRasterizerState(RS_Default);
        SetDepthStencilState(DSS_None, 0);
        SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DEFERRED();
	}
}




