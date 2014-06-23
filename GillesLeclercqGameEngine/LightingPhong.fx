#define MaxLights 10

struct VS_IN
{
	float3 posL		: POSITION;
	float3 normalL	: NORMAL;
	float2 texCo	: TEXCOORD;
};

struct VS_OUT
{
	float4 Pos		: SV_POSITION;
	float3 PosW		: POSITION;
	float3 Norm		: NORMAL;
	float2 texCo	: TEXCOORD;
};

SamplerState gAnioSampler
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

struct DirectionalLight
{
	float4 ambientDirecLight;
	float4 diffuseDirecLight;
	float4 specularDirecLight;
	float3 directionDirecLight;
	float padDirecLight;
};

struct PointLight
{
	float4 ambientPointLight;
	float4 diffusePointLight;
	float4 specularPointLight;

	float3 positionPointLight;
	float rangePointLight;

	float3 attPointLight;
	float pad;
};


struct Material
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
};

cbuffer cbData
{
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4x4 WVP;
	float4x4 WorldInvTrans;
	float4x4 TexTransform;

	float3 EyePosW;

	int nbOfDirectionalLight;
	int nbOfPointLight;

	Material material;

	DirectionalLight directionalLights[MaxLights];
	PointLight pointLights[MaxLights];
};

Texture2D gTexture;

//----------------------------------------------------------------------
void ComputeDirectionalLight(Material mat, DirectionalLight L, 
                             float3 normal, float3 toEye,
					         out float4 ambient,
						     out float4 diffuse,
						     out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 vectorLight = -L.directionDirecLight;

	ambient = mat.ambient * L.ambientDirecLight;	

	
	float diffuseFactor = dot(vectorLight, normal);

	if( diffuseFactor > 0.0f )
	{
		float3 v         = reflect(-vectorLight, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.specular.w);
					
		diffuse = diffuseFactor * mat.diffuse * L.diffuseDirecLight;
		spec    = specFactor * mat.specular * L.specularDirecLight;
	}
};

//----------------------------------------------------------------------
void ComputePointLight(Material mat, PointLight L, float3 pos, float3 normal, float3 toEye,
				   out float4 ambient, out float4 diffuse, out float4 spec)
{

	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 vectorLight = L.positionPointLight - pos;	
	float distance = length(vectorLight);	
	if( distance > L.rangePointLight )
		return;
		
	vectorLight = vectorLight/distance; 	
	ambient = mat.ambient * L.ambientPointLight;	
	float diffuseFactor = dot(vectorLight, normal);

	if( diffuseFactor > 0.0f )
	{
		float3 v         = reflect(-vectorLight, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.specular.w);
					
		diffuse = diffuseFactor * mat.diffuse * L.diffusePointLight;
		spec    = specFactor * mat.specular * L.specularPointLight;
	}

	float att = 1.0f / dot(L.attPointLight, float3(1.0f, distance, distance*distance));

	diffuse *= att;
	spec    *= att;
};


//----------------------------------------------------------------------
VS_OUT VS(VS_IN vIn)
{
	VS_OUT output;
	
	output.PosW = mul(float4(vIn.posL, 1.0f), World).xyz;
	output.Norm = mul(vIn.normalL, (float3x3)WorldInvTrans);
		
	output.Pos = mul(float4(vIn.posL, 1.0f), WVP);
	output.texCo = mul(float4(vIn.texCo,0.0f,1.0f),TexTransform).xy;
	
	return output;
}

//----------------------------------------------------------------------
float4 PS(VS_OUT pIn) : SV_Target
{

    pIn.Norm = normalize(pIn.Norm); 

	float3 toEyeW = normalize(EyePosW - pIn.PosW);

	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 A, D, S;

	for(int i = 0; i < nbOfPointLight ; i++)
	{
		ComputePointLight(material, pointLights[i], pIn.PosW, pIn.Norm, toEyeW, A, D, S);
		ambient += A;  
		diffuse += D;
		spec    += S;
	}

	for(int l = 0;l < nbOfDirectionalLight ; l++)
	{	
		ComputeDirectionalLight(material,directionalLights[l], pIn.Norm, toEyeW, A, D, S);
		ambient += A;
		diffuse += D;
		spec    += S;
	}
	
	float4 tex = gTexture.Sample(gAnioSampler, pIn.texCo);
	   
	float4 litColor = tex*(ambient + diffuse) + spec;

	litColor.a = material.diffuse.a*tex.a;
    return litColor;
}

//----------------------------------------------------------------------
technique11 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0,VS() ) );
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0,PS() ) );
	}
}

