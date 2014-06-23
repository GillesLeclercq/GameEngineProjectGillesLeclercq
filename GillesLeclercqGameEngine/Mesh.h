#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "EventManager.h"
#include "Event_CreateTextures.h"

#include <directxmath.h>
#include <Windows.h>
#include "tiny_obj_loader.h"
#include <d3d11_1.h>
#include <directxmath.h>
#include "DDSTextureLoader.h"

#include "IComponent.h"

struct	SimpleVertex	
{	
		DirectX::XMFLOAT3	s_Position;							
		DirectX::XMFLOAT3	s_Normal;	
		DirectX::XMFLOAT2	s_TexCoord;
};	

struct Material
{
		DirectX::XMFLOAT4		s_Ambient;	
		DirectX::XMFLOAT4		s_Diffuse;
		DirectX::XMFLOAT4		s_Specular;	
};

struct	MaterialContainer	
{	
	Material				s_Material;
	std::string				MaterialName;
};	

struct Texture
{
	ID3D11ShaderResourceView*	s_pTextureRV;
	std::string					s_filePath;
};

struct Shape
{
	std::vector<UINT>			s_vIndices;
	std::vector<SimpleVertex>	s_vVertex;
};

struct FaceIndices
{
	int s_vIndices1, s_vIndices2, s_vIndices3;
	int s_tIndices1, s_tIndices2, s_tIndices3;
	int s_nIndices1, s_nIndices2, s_nIndices3;
};

class Mesh : public IComponent
{
private:
	static const unsigned long	s_CompType = 0xad2b39b0;

	std::map<std::string,Shape*>					m_pShapes;
	std::map<std::string, MaterialContainer*>		m_pMaterial;
	std::map<std::string, Texture*>					m_pTextureRV;

public:
	Mesh( GameObject* owner ): IComponent( owner ) {}
	~Mesh();

	bool VInitialize( XmlMediator* pComponent ) override;

	bool CreateTextures(IEventPtr evt);

	const unsigned long& VGetComponentType() const { return s_CompType; }

	const void* GetShapes() const { return (void*) &m_pShapes; }
	const void* GetMaterials() const { return (void*) &m_pMaterial; }
	const void* GetTextures() const { return (void*) &m_pTextureRV; }

	static const unsigned long& GetComponentType() { return s_CompType; }
	static IComponent* CreateComponent( GameObject* owner ) { return new Mesh( owner ); }
};
