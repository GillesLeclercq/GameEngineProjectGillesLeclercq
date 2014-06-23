#include "GraphicsComponent.h"
#include "GameObject.h"

using namespace std;
using namespace DirectX;

//----------------------------------------------------------------------
bool GraphicsComponent::VInitialize( XmlMediator* pComponent )
{
	return true;
}

//----------------------------------------------------------------------

GraphicsComponent::~GraphicsComponent()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);

	SAFE_RELEASE(m_pEffectMatrixWorViewProj);
	SAFE_RELEASE(m_pEffectMatrixWorld);
	SAFE_RELEASE(m_pEffectMatrixView);
	SAFE_RELEASE(m_pEffectMatrixProj);
	SAFE_RELEASE(m_pEffectworldInvTrans);
	SAFE_RELEASE(m_pEffectTexTransform);
	SAFE_RELEASE(m_pEffectMaterial);
	SAFE_RELEASE(m_pEffectTextureVar);
	SAFE_RELEASE(m_pEffectEyePosition);
	SAFE_RELEASE(m_pEffectDirectionalLights);
	SAFE_RELEASE(m_pEffectPointLights);
	SAFE_RELEASE(m_pEffectSpotLights);
	SAFE_RELEASE(m_pEffectNbOfDirectionalLights);
	SAFE_RELEASE(m_pEffectNbOfPointLights);
	SAFE_RELEASE(m_pEffectworldInvTrans);
}


//----------------------------------------------------------------------
void GraphicsComponent::Draw(ID3D11DeviceContext* pImmediateContext, Camera* pCamera, ILightManager* pLightManager)
{
	auto mWorld = static_cast< XMFLOAT4X4* >(m_pOwner->GetVariable("GetmWorld"));
	auto mView = pCamera->GetViewMatrix();
	auto mProj = pCamera->GetProjMatrix();

	XMMATRIX matrixWorld = XMLoadFloat4x4(mWorld);
	XMMATRIX matrixView = XMLoadFloat4x4(&mView);
	XMMATRIX matrixProj = XMLoadFloat4x4(&mProj);
	XMMATRIX matrixWorldViewProj = matrixWorld*matrixView*matrixProj;

	XMMATRIX matWorldInv = XMMatrixInverse(nullptr, matrixWorld);
	XMMATRIX matWorldInvTrans = XMMatrixTranspose(matWorldInv);

	XMMATRIX I = XMMatrixIdentity();

	m_pEffectTexTransform->SetMatrix(reinterpret_cast<float*>(&I));
	m_pEffectMatrixWorViewProj->SetMatrix(reinterpret_cast<float*>(&matrixWorldViewProj));
	m_pEffectMatrixWorld->SetMatrix(reinterpret_cast<float*>(&mWorld));
	m_pEffectMatrixView->SetMatrix(reinterpret_cast<float*>(&mView));
	m_pEffectMatrixProj->SetMatrix(reinterpret_cast<float*>(&mProj));
	m_pEffectworldInvTrans->SetMatrix(reinterpret_cast<float*>(&matWorldInvTrans));

	XMFLOAT3 CameraPosition = pCamera->GetPosition();

	m_pEffectEyePosition->SetRawValue(&CameraPosition, 0, sizeof(XMFLOAT3));

	vector<DirectionalLight> pDirectionalLights = pLightManager->GetVectorDirectionalLights();
	vector<PointLight> pPointLights = pLightManager->GetVectorPointLights();

	if (pDirectionalLights.size() != 0)
	{
		DirectionalLight* directionalLights = &pDirectionalLights[0];
		m_pEffectDirectionalLights->SetRawValue(directionalLights, 0 , sizeof(*directionalLights));
		int directionalLightsSize = (sizeof(*directionalLights))/sizeof(DirectionalLight);
		m_pEffectNbOfDirectionalLights->SetRawValue(&directionalLightsSize , 0 , sizeof(int));
	}

	if (pPointLights.size() != 0)
	{	
		PointLight* pointLights = &pPointLights[0];
		m_pEffectPointLights->SetRawValue(pointLights, 0 , sizeof(*pointLights));
		int pointLightsSize = (sizeof(*pointLights))/sizeof(PointLight);
		m_pEffectNbOfPointLights->SetRawValue(&pointLightsSize , 0 , sizeof(int));
	}


	auto shaderTechniqueptr = static_cast< ID3DX11EffectTechnique** >(m_pOwner->GetVariable("GetTechnique"));
	auto shaderTechnique = *shaderTechniqueptr;

	auto shapes = static_cast< map<string,Shape*>* >(m_pOwner->GetVariable("GetShapes"));
	auto materials = static_cast< map<string, MaterialContainer*>* >(m_pOwner->GetVariable("GetMaterials"));
	auto textures = static_cast< map<string, Texture*>* >(m_pOwner->GetVariable("GetTextures"));

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;

	pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);


	for (auto shape : *shapes)
	{
		Material shapeMaterial = materials->find(shape.first)->second->s_Material;
		Texture* shapeTexture = textures->find(shape.first)->second;
		ID3D11ShaderResourceView* _textureRV = shapeTexture->s_pTextureRV;
		m_pEffectMaterial->SetRawValue(&shapeMaterial, 0, sizeof(shapeMaterial));

		m_pEffectTextureVar->SetResource(_textureRV);
		D3DX11_TECHNIQUE_DESC techDesc;
		shaderTechnique->GetDesc(&techDesc);
		for (UINT p = 0 ; p < techDesc.Passes ; ++p)
		{
			shaderTechnique->GetPassByIndex(p)->Apply(0,pImmediateContext);
			pImmediateContext->DrawIndexed(shape.second->s_vIndices.size(),0,0);
		}
	}

}

//----------------------------------------------------------------------
bool GraphicsComponent::InitializeBuffers(ID3D11Device* m_pD3dDevice)
{
	map<std::string,Shape*>* shapes = static_cast< map<std::string,Shape*>* >(m_pOwner->GetVariable("GetShapes"));

	int indiceBufferSize = 0, vertexBufferSize = 0;
	vector<SimpleVertex> vertexBufferVector;
	vector<UINT> indiceBufferVector;
	for (auto shape : *shapes)
	{
		vertexBufferSize += shape.second->s_vVertex.size();
		indiceBufferSize += shape.second->s_vIndices.size();
		vertexBufferVector.insert(vertexBufferVector.end() , shape.second->s_vVertex.begin() , shape.second->s_vVertex.end() );
		indiceBufferVector.insert(indiceBufferVector.end() , shape.second->s_vIndices.begin() , shape.second->s_vIndices.end() );
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
    bd.Usage = D3D11_USAGE_IMMUTABLE;
    bd.ByteWidth = sizeof( SimpleVertex ) * vertexBufferSize;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory( &InitData, sizeof(InitData) );
	SimpleVertex* verticesArray = &vertexBufferVector[0];
    InitData.pSysMem = verticesArray;
    m_pD3dDevice->CreateBuffer( &bd, &InitData, &m_pVertexBuffer );

	ZeroMemory( &bd, sizeof(bd) );
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = sizeof( unsigned int ) * indiceBufferSize; 
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iInitData;
	unsigned int* indicesArray = &indiceBufferVector[0];
    iInitData.pSysMem = indicesArray;
    m_pD3dDevice->CreateBuffer( &ibd, &iInitData, &m_pIndexBuffer );

	return true;
}

//----------------------------------------------------------------------
bool GraphicsComponent::InitalizeEffects()
{
	auto effectPtr = static_cast< ID3DX11Effect** >(m_pOwner->GetVariable("GetEffect"));
	auto effect = *effectPtr;

	m_pEffectMatrixWorViewProj = effect->GetVariableByName("WVP")->AsMatrix();
	m_pEffectMatrixWorld = effect->GetVariableByName("World")->AsMatrix();
	m_pEffectMatrixView = effect->GetVariableByName("View")->AsMatrix();
	m_pEffectMatrixProj = effect->GetVariableByName("Projection")->AsMatrix();
	m_pEffectworldInvTrans = effect->GetVariableByName("WorldInvTrans")->AsMatrix();
	m_pEffectTexTransform = effect->GetVariableByName("TexTransform")->AsMatrix();
	m_pEffectMaterial = effect->GetVariableByName("material");
	m_pEffectTextureVar = effect->GetVariableByName("gTexture")->AsShaderResource();
	m_pEffectEyePosition = effect->GetVariableByName("EyePosW");
	m_pEffectDirectionalLights = effect->GetVariableByName("directionalLights");
	m_pEffectPointLights = effect->GetVariableByName("pointLights");
	m_pEffectSpotLights = effect->GetVariableByName("spotLights");

	m_pEffectNbOfDirectionalLights = effect->GetVariableByName("nbOfDirectionalLight");
	m_pEffectNbOfPointLights = effect->GetVariableByName("nbOfPointLight");

	return true ;
}
