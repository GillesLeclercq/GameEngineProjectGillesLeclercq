#include "TestComponent.h"

#include "GameObject.h"

using namespace std;

//----------------------------------------------------------------------
TestComponent::~TestComponent()
{
	m_pOwner->UnRegisterUpdateMethod( GetComponentType() );

	m_pOwner->UnRegisterGetMethod( "test" );
	m_pOwner->UnRegisterSetMethod( "test", fastdelegate::MakeDelegate( this, &TestComponent::SetTestVariable ) );
}

//----------------------------------------------------------------------
bool TestComponent::VInitialize( XmlMediator* pComponent )
{
	string value = "Value";
	XmlMediator* pValue = pComponent->GetChildren( value ).front();
	m_TestVariable = atoi( pValue->GetContent().c_str() );

	m_pOwner->RegisterUpdateMethod( GetComponentType(), fastdelegate::MakeDelegate( this, &TestComponent::Update ) );

	m_pOwner->RegisterGetMethod( "test", fastdelegate::MakeDelegate( this, &TestComponent::GetTestVariable ) );
	m_pOwner->RegisterSetMethod( "test", fastdelegate::MakeDelegate( this, &TestComponent::SetTestVariable ) );

	return true;
}

//----------------------------------------------------------------------
void TestComponent::Update( float& frameTime )
{
	//cout << "TestVariable = " << m_TestVariable << endl;
}