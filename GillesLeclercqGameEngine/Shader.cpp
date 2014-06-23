#include "Shader.h"
#include "GameObject.h"

// TEST PURPOSE
#include <thread>
#include <chrono>
#include <string>
//

using namespace std;

//----------------------------------------------------------------------
bool Shader::VInitialize( XmlMediator* pComponent )
{

	m_pOwner->RegisterGetMethod( "GetEffect", (GetMethod&) fastdelegate::MakeDelegate( this, &Shader::GetEffect ) );
	m_pOwner->RegisterGetMethod( "GetTechnique", (GetMethod&) fastdelegate::MakeDelegate( this, &Shader::GetTechnique ) );

	auto resultFilename = pComponent->GetChildren((string)"Filename");
	if (resultFilename.size() != 1)
	{
		cerr<< "ERROR: fail to find shader file";
		return false;
		
	}
	m_ShaderFilename = resultFilename.front()->GetContent();

	auto resultTechnique = pComponent->GetChildren((string)"Technique");
	if (resultTechnique.size() != 1)
	{
		cerr<< "ERROR: fail to find tech name";
		return false;	
	}
	m_TechniqueName = resultTechnique.front()->GetContent();

	auto resultTarget = pComponent->GetChildren((string)"Target");
	if (resultTarget.size() != 1)
	{
		cerr<< "ERROR: fail to find shader target";
		return false;
	}
	m_Target = resultTarget.front()->GetContent();
	return true;
}

//----------------------------------------------------------------------
void Shader::InitShader(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, ID3D11InputLayout** pVertexLayout)
{
	
	wstring wFilename (m_ShaderFilename.begin(), m_ShaderFilename.end());

	ID3D10Blob* compliationMsgs = nullptr;
	ID3D10Blob* compliationCode = nullptr;
	HRESULT hr2 = D3DCompileFromFile(wFilename.c_str(),
									 NULL,
									 NULL, 
									 (LPCSTR)m_TechniqueName.c_str(),
									 (LPCSTR)m_Target.c_str(),
									 0,
									 D3DCOMPILE_EFFECT_CHILD_EFFECT,
									 &compliationCode,
									 &compliationMsgs);

	if(compliationMsgs != nullptr)
	{
		MessageBoxA(0,(char*)compliationMsgs->GetBufferPointer(),0,0);
	}
	if (FAILED(hr2))
	{
		return;
	}

	HRESULT hr3 = D3DX11CreateEffectFromMemory(compliationCode->GetBufferPointer(),
											   compliationCode->GetBufferSize(),
											   0, pDevice, &m_pFx);

	
	if (FAILED(hr3))
	{
		return;
	}

	m_pTech = m_pFx->GetTechniqueByName((LPCSTR)m_TechniqueName.c_str());

		D3D11_INPUT_ELEMENT_DESC	ied[3]	=	{	
		{"POSITION", 0,	DXGI_FORMAT_R32G32B32_FLOAT, 0,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0},	
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}	
	};
	
	
	D3DX11_PASS_DESC passDesc;
	m_pTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HRESULT hr5 = pDevice->CreateInputLayout(ied, 3, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, pVertexLayout);
	if (FAILED(hr5))
	{
		return;
	}
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

