#include "Client_Shader_Defines.hlsl"
#include "Shader_Lighting_Functions.hlsl"

matrix g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;

vector g_vLightDir = vector(1.f, -1.f, 1.f, 0.f);
vector g_vLightPos = vector(0.f, 0.f, 0.f, 1.f);
float g_fLightRange = 0.f;
vector g_vLightDiffuse = vector(1.f, 1.f, 1.f, 1.f);
vector g_vLightAmbient = vector(1.f, 1.f, 1.f, 1.f);
vector g_vLightSpecular = vector(1.f, 1.f, 1.f, 1.f);
vector g_vLightEmissive = vector(1.f, 1.f, 1.f, 1.f);

vector g_vMtrlAmbient = vector(0.4f, 0.4f, 0.4f, 1.f);
vector g_vMtrlSpecular = vector(1.f, 1.f, 1.f, 1.f);
vector g_vMtrlEmissive = vector(1.f, 0.f, 0.f, 1.f);

vector g_vCamPosition;

struct tagKeyframeDesc
{
    int animIndex;
    uint currFrame;
    uint nextFrame;
    float ratio;
    float sumTime;
    float speed;
    float2 padding;
};

struct tagTweenFrameDesc
{
    float tweenDuration;
    float tweenRatio;
    float tweenSumTime;
    float padding;
    tagKeyframeDesc curr;
    tagKeyframeDesc next;
};

tagTweenFrameDesc g_Tweenframes;

Texture2DArray g_TransformMap;
//matrix g_SocketWorld;
int g_iSocketBoneIndex;

struct VS_IN
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexcoord : TEXCOORD0;
    float3 vTangent : TANGENT;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
    float4 vNormal : NORMAL;
    float2 vTexcoord : TEXCOORD0;
    float4 vWorldPos : TEXCOORD1;
    float3 vTangent : TANGENT;
};

matrix GetSocketMatrix()
{
    int animIndex[2];
    int currFrame[2];
    int nextFrame[2];
    float ratio[2];
    
    animIndex[0] = g_Tweenframes.curr.animIndex;
    currFrame[0] = g_Tweenframes.curr.currFrame;
    nextFrame[0] = g_Tweenframes.curr.nextFrame;
    ratio[0] = g_Tweenframes.curr.ratio;
    
    animIndex[1] = g_Tweenframes.next.animIndex;
    currFrame[1] = g_Tweenframes.next.currFrame;
    nextFrame[1] = g_Tweenframes.next.nextFrame;
    ratio[1] = g_Tweenframes.next.ratio;
    
    float4 c0, c1, c2, c3;
    float4 n0, n1, n2, n3;
    
    matrix curr = 0;
    matrix next = 0;

    c0 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 0, currFrame[0], animIndex[0], 0));  // indices[i] 위치에 SocketBoneNumber를 던지자
    c1 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 1, currFrame[0], animIndex[0], 0));  // for문 순회 필요는 없다. 정점과 달리 소켓은 한뼈에만 영향을 받는다.
    c2 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 2, currFrame[0], animIndex[0], 0));
    c3 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 3, currFrame[0], animIndex[0], 0));
    curr = matrix(c0, c1, c2, c3);
    
    n0 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 0, nextFrame[0], animIndex[0], 0));
    n1 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 1, nextFrame[0], animIndex[0], 0));
    n2 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 2, nextFrame[0], animIndex[0], 0));
    n3 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 3, nextFrame[0], animIndex[0], 0));
    next = matrix(n0, n1, n2, n3);
    
    matrix result = lerp(curr, next, ratio[0]);
    
    if (g_Tweenframes.next.animIndex >= 0)
    {
        c0 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 0, currFrame[1], animIndex[1], 0));
        c1 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 1, currFrame[1], animIndex[1], 0));
        c2 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 2, currFrame[1], animIndex[1], 0));
        c3 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 3, currFrame[1], animIndex[1], 0));
        curr = matrix(c0, c1, c2, c3);

        n0 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 0, nextFrame[1], animIndex[1], 0));
        n1 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 1, nextFrame[1], animIndex[1], 0));
        n2 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 2, nextFrame[1], animIndex[1], 0));
        n3 = g_TransformMap.Load(int4(g_iSocketBoneIndex * 4 + 3, nextFrame[1], animIndex[1], 0));
        next = matrix(n0, n1, n2, n3);

        matrix nextResult = lerp(curr, next, ratio[1]);
        result = lerp(result, nextResult, g_Tweenframes.tweenRatio);
    }

    return result;
}

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;

    matrix matWV, matWVP;

    Matrix m = GetSocketMatrix();

    matWV = mul(g_WorldMatrix, g_ViewMatrix);
    matWVP = mul(matWV, g_ProjMatrix);
   
    vector vPosition = mul(vector(In.vPosition, 1.f), m);
    vector vNormal = mul(vector(In.vNormal, 0.f), m);

    Out.vPosition = mul(vPosition, matWVP);
    Out.vNormal = normalize(mul(vNormal, g_WorldMatrix));
    Out.vTexcoord = In.vTexcoord;
    Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
    Out.vTangent = normalize(mul(float4(In.vTangent, 0.f), g_WorldMatrix)).xyz;

    return Out;
}

struct PS_IN
{
    float4 vPosition : SV_POSITION;
    float4 vNormal : NORMAL;
    float2 vTexcoord : TEXCOORD0;
    float4 vWorldPos : TEXCOORD1;
    float3 vTangent : TANGENT;
};

struct PS_OUT
{
    float4 vColor : SV_TARGET0;
};

PS_OUT PS_MAIN(PS_IN In)
{
    ComputeNormalMapping(In.vNormal, In.vTangent, In.vTexcoord);
	
    PS_OUT Out = (PS_OUT) 0;
	
    vector vMtrlDiffuse = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord);

    if (vMtrlDiffuse.a < 0.3f)
        discard;
	
    vector vShade = max(dot(normalize(g_vLightDir) * -1.f, normalize(In.vNormal)), 0.f) +
		g_vLightAmbient * g_vMtrlAmbient;

    vector vReflect = reflect(normalize(g_vLightDir), normalize(In.vNormal));
    vector vLook = In.vWorldPos - g_vCamPosition;

    float fSpecular = pow(max(dot(normalize(vLook) * -1.f, normalize(vReflect)), 0.f), 30.f);

    Out.vColor = (g_vLightDiffuse * vMtrlDiffuse) * saturate(vShade) +
		(g_vLightSpecular * g_vMtrlSpecular) * fSpecular;

    return Out;
}

PS_OUT PS_RIM_MAIN(PS_IN In)
{
    ComputeNormalMapping(In.vNormal, In.vTangent, In.vTexcoord);
	
    PS_OUT Out = (PS_OUT) 0;
	
    vector vMtrlDiffuse = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord);

    if (vMtrlDiffuse.a < 0.3f)
        discard;
	
    vector vShade = max(dot(normalize(g_vLightDir) * -1.f, normalize(In.vNormal)), 0.f) +
		g_vLightAmbient * g_vMtrlAmbient;

    vector vReflect = reflect(normalize(g_vLightDir), normalize(In.vNormal));
    vector vLook = In.vWorldPos - g_vCamPosition;

    float fSpecular = pow(max(dot(normalize(vLook) * -1.f, normalize(vReflect)), 0.f), 30.f);
	
    // Rim Light
    float3 E = normalize(-vLook);

    float value = saturate(dot(E, float3(In.vNormal.xyz)));
    float fEmissive = 1.0f - value;

	// min, max, x
    fEmissive = smoothstep(0.0f, 1.0f, fEmissive);
    fEmissive = pow(fEmissive, 2);
	//
    Out.vColor = (g_vLightDiffuse * vMtrlDiffuse) * saturate(vShade) +
		(g_vLightSpecular * g_vMtrlSpecular) * fSpecular +
	(g_vLightEmissive * g_vMtrlEmissive) * fEmissive;
    
    return Out;
}

PS_OUT PS_DISSOLVE_MAIN(PS_IN In)
{
    ComputeNormalMapping(In.vNormal, In.vTangent, In.vTexcoord);
	
    PS_OUT Out = (PS_OUT) 0;
	
    vector vMtrlDiffuse = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord);

    if (vMtrlDiffuse.a < 0.3f)
        discard;
	
    vector vShade = max(dot(normalize(g_vLightDir) * -1.f, normalize(In.vNormal)), 0.f) +
		g_vLightAmbient * g_vMtrlAmbient;

    vector vReflect = reflect(normalize(g_vLightDir), normalize(In.vNormal));
    vector vLook = In.vWorldPos - g_vCamPosition;

    float fSpecular = pow(max(dot(normalize(vLook) * -1.f, normalize(vReflect)), 0.f), 30.f);

    Out.vColor = (g_vLightDiffuse * vMtrlDiffuse) * saturate(vShade) +
		(g_vLightSpecular * g_vMtrlSpecular) * fSpecular;

    ComputeDissolveColor(Out.vColor, In.vTexcoord);
    
    return Out;
}

technique11 DefaultTechnique
{
    pass Mesh
    {
        SetRasterizerState(RS_Default);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        HullShader = NULL;
        DomainShader = NULL;
        PixelShader = compile ps_5_0 PS_MAIN();
    }

    pass RimMesh
    {
        SetRasterizerState(RS_Default);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        HullShader = NULL;
        DomainShader = NULL;
        PixelShader = compile ps_5_0 PS_RIM_MAIN();
    }

    pass DissolveMesh
    {
        SetRasterizerState(RS_Default);

        VertexShader = compile vs_5_0 VS_MAIN();
        GeometryShader = NULL;
        HullShader = NULL;
        DomainShader = NULL;
        PixelShader = compile ps_5_0 PS_DISSOLVE_MAIN();
    }
}