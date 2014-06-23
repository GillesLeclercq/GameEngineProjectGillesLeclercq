#include "ShaderManager.h"

using namespace std;

bool ShaderManager::VInitialize( GameObjectManager* goManager )
{
	// Event_DeleteObject => OnDestroyGO
	EventManager::Instance().Bind( Event_DeleteObject::EventType(), fastdelegate::MakeDelegate( this, &IShaderManager::OnDestroyGO ) );
	// Event_CreateObject => OnCreateGO
	EventManager::Instance().Bind( Event_CreateObject::EventType(), fastdelegate::MakeDelegate( this, &IShaderManager::OnCreateGO ) );

	EventManager::Instance().Bind( Event_CreateShader::EventType(), (EventDelegate&)fastdelegate::MakeDelegate( this, &ShaderManager::CreateShader ) );


	goManager->RegisterComponentCreator( "Shader", Shader::CreateComponent );

	return true;
}

bool ShaderManager::CreateShader(IEventPtr evt)
{
	shared_ptr<Event_CreateShader> createShaderEvt = static_pointer_cast<Event_CreateShader>(evt);
	ID3D11Device* device = createShaderEvt->GetDevice();
	ID3D11DeviceContext* immediateContext = createShaderEvt->GetImmediateContext();
	ID3D11InputLayout** vertexLayout = createShaderEvt->GetVertexLayout();

	for (auto shader : m_pShaders)
	{
		shader.second->InitShader(device, immediateContext, vertexLayout);
	}
	return true;
}