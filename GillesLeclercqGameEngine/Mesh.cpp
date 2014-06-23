#include "Mesh.h"
#include "GameObject.h"
#include <string>

using namespace std;
using namespace DirectX;

//----------------------------------------------------------------------
bool Mesh::VInitialize( XmlMediator* pComponent )
{

	EventManager::Instance().Bind( Event_CreateTextures::EventType(), (EventDelegate&) fastdelegate::MakeDelegate( this, &Mesh::CreateTextures ) );

	string meshFileName = pComponent->GetChildren((string)"Shapes").front()->GetContent();
	string materialFileName = pComponent->GetChildren((string)"Material").front()->GetContent();

	vector<tinyobj::shape_t> shapes;

	string err = tinyobj::LoadObj(shapes, meshFileName.c_str(),materialFileName.c_str());

	if (!err.empty()) 
	{
		std::cerr << err << std::endl;
		return false;
	}

	int shapeNumber = 0;
	for ( auto shape : shapes )
	{
		Shape * newShape = new Shape;
		newShape->s_vIndices = shape.mesh.indices;
		newShape->s_vVertex = vector<SimpleVertex> (shape.mesh.positions.size() / 3);

		for ( int i = 0 ; i < shape.mesh.positions.size() / 3 ; i++)
		{
			newShape->s_vVertex[i].s_Position = XMFLOAT3(shape.mesh.positions[i*3 + 0], shape.mesh.positions[i*3 + 1], -1.0* shape.mesh.positions[i*3 + 2]);
			newShape->s_vVertex[i].s_Normal = XMFLOAT3(shape.mesh.normals[i*3 + 0], shape.mesh.normals[i*3 + 1], -1.0* shape.mesh.normals[i*3 + 2]);
		}

		for ( int i = 0 ; i < shape.mesh.texcoords.size() / 2 ; i++)
		{
			newShape->s_vVertex[i].s_TexCoord = XMFLOAT2(shape.mesh.texcoords[i*2 + 0], -1.0f - shape.mesh.texcoords[i*2 + 1]);
		}
		if (shape.name.size() == 0)
		{
			shape.name = "Unknown"+ shapeNumber;
			shapeNumber++;
		}
		m_pShapes[shape.name] = newShape;

		MaterialContainer * newMaterial = new MaterialContainer;

		if (shape.material.name.size() != 0)
		{
			newMaterial->s_Material.s_Ambient = XMFLOAT4(shape.material.ambient[0] , shape.material.ambient[1] , shape.material.ambient[2], 1.0f);
			newMaterial->s_Material.s_Diffuse = XMFLOAT4(shape.material.specular[0] , shape.material.specular[1] , shape.material.specular[2], shape.material.specular[2]);
			newMaterial->s_Material.s_Specular = XMFLOAT4(shape.material.transmittance[0] , shape.material.transmittance[1] , shape.material.transmittance[2], 1.0f);
			newMaterial->MaterialName = shape.material.name;
		}
		else
		{
			newMaterial->s_Material.s_Ambient = XMFLOAT4(1.0f , 1.0f , 1.0f, 1.0f);
			newMaterial->s_Material.s_Diffuse = XMFLOAT4(1.0f , 1.0f , 1.0f, 1.0f);
			newMaterial->s_Material.s_Specular = XMFLOAT4(1.0f , 1.0f , 1.0f, 1.0f);
			newMaterial->MaterialName = "Unknown"+ shapeNumber;
		}

		m_pMaterial[shape.name] = newMaterial;

		Texture * newTexture = new Texture;
		newTexture->s_filePath = "Mesh\\" + shape.material.diffuse_texname;
		newTexture->s_pTextureRV = nullptr;
		m_pTextureRV[shape.name] = newTexture;

	}
	
	m_pOwner->RegisterGetMethod( "GetShapes", (GetMethod&) fastdelegate::MakeDelegate( this, &Mesh::GetShapes ) );
	m_pOwner->RegisterGetMethod( "GetMaterials", (GetMethod&) fastdelegate::MakeDelegate( this, &Mesh::GetMaterials ) );
	m_pOwner->RegisterGetMethod( "GetTextures", (GetMethod&) fastdelegate::MakeDelegate( this, &Mesh::GetTextures ) );

	return true;
}

Mesh::~Mesh()
{
	for(auto s : m_pShapes)
	{
		SAFE_DELETE(s.second);
	}
	for(auto m : m_pMaterial)
	{
		SAFE_DELETE(m.second);
	}
	for(auto t : m_pTextureRV)
	{
		SAFE_DELETE(t.second);
	}
}

//----------------------------------------------------------------------
bool Mesh::CreateTextures(IEventPtr evt)
{
	shared_ptr<Event_CreateTextures> createTexturesEvt = static_pointer_cast<Event_CreateTextures>(evt);

	for (auto texture : m_pTextureRV)
	{
		size_t origsize = strlen(texture.second->s_filePath.c_str()) + 1;
		size_t convertedChars = 0;
		int size = texture.second->s_filePath.size();
		wchar_t wcstring[100];
		mbstowcs_s(&convertedChars, wcstring, origsize, texture.second->s_filePath.c_str(), _TRUNCATE);
		HRESULT createTexture = CreateDDSTextureFromFile(createTexturesEvt->GetD3dDevice() , wcstring , nullptr , &texture.second->s_pTextureRV);
		if (FAILED(createTexture))
		{
			const wchar_t *error = L"Mesh//error.dds";
			HRESULT truc = CreateDDSTextureFromFile(createTexturesEvt->GetD3dDevice() , error , nullptr , &texture.second->s_pTextureRV);
			if (FAILED(truc))
			{
				return false;
			}
		}
	}

	return true;
}
