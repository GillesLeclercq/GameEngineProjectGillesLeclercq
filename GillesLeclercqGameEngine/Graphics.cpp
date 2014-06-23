#include "Graphics.h"

using namespace std;
using namespace DirectX;

//----------------------------------------------------------------------
// Subscribe to all needed events (Event_DeleteObject ...)
// Return true if successfull
bool Graphics::VInitialize( GameObjectManager* goManager )
{
	// Event_DeleteObject => OnDestroyGO
	EventManager::Instance().Bind( Event_DeleteObject::EventType(), fastdelegate::MakeDelegate( this, &IGraphics::OnDestroyGO ) );
	// Event_CreateObject => OnCreateGO
	EventManager::Instance().Bind( Event_CreateObject::EventType(), fastdelegate::MakeDelegate( this, &IGraphics::OnCreateGO ) );

	EventManager::Instance().Bind( Event_CreateGraphics::EventType() , (EventDelegate&) fastdelegate::MakeDelegate( this, &Graphics::CreateGraphics ) );

	EventManager::Instance().Bind( Event_LookForDevices::EventType() , (EventDelegate&) fastdelegate::MakeDelegate( this, &Graphics::SendBackDevice ) );

	EventManager::Instance().Bind( Event_NewCurrentCamera::EventType() , (EventDelegate&) fastdelegate::MakeDelegate( this, &Graphics::ReceiveNewCurrentCamera ) );

	goManager->RegisterComponentCreator( "GraphicsComponent", GraphicsComponent::CreateComponent );

	return true;
}

//----------------------------------------------------------------------

Graphics::~Graphics()
{
	if( m_pImmediateContext ) m_pImmediateContext->ClearState();
    if( m_pRenderTargetView ) m_pRenderTargetView->Release();
    if( m_pSwapChain ) m_pSwapChain->Release(); 
    if( m_pImmediateContext ) m_pImmediateContext->Release();
    if( m_pD3dDevice ) m_pD3dDevice->Release();
	if (m_pDepthStencil) m_pDepthStencil->Release();
	if (m_pDepthStencilView) m_pDepthStencilView->Release();
	if (m_pVertexLayout ) m_pVertexLayout->Release();

}

//----------------------------------------------------------------------
void Graphics::VDraw()
{ 
	
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, Colors::Blue );
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView,D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for( auto c : m_pGraphicComponents ) 
	{
		c.second->Draw(m_pImmediateContext, m_pCurrentCamera, m_pLightManager);
	}
	HRESULT HR = (m_pSwapChain->Present(0,0));
}

//----------------------------------------------------------------------

int Graphics::CreateGraphics(IEventPtr evt)
{
	shared_ptr<Event_CreateGraphics> createWindowEvt = static_pointer_cast<Event_CreateGraphics>(evt);
	
	HWND* hwnd = createWindowEvt->GetHwnd();

	HRESULT hr = S_OK;
    RECT rc;
    GetClientRect(*hwnd , &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
	#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = *hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
	
    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        m_DriverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain( nullptr, m_DriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pD3dDevice, &m_FeatureLevel, &m_pImmediateContext );

        if ( hr == E_INVALIDARG )
        {
            hr = D3D11CreateDeviceAndSwapChain( nullptr, m_DriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                                                D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pD3dDevice, &m_FeatureLevel, &m_pImmediateContext );
        }

        if( SUCCEEDED( hr ) )
            break;
    }
    if( FAILED( hr ) )
        return hr;



    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast<void**>( &pBackBuffer ) );
    if( FAILED( hr ) )
        return hr;

    hr = m_pD3dDevice->CreateRenderTargetView( pBackBuffer, nullptr, &m_pRenderTargetView );
    pBackBuffer->Release();
    if( FAILED( hr ) )
        return hr;

 	    // Create depth stencil texture
    D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory( &descDepth, sizeof(descDepth) );
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = m_pD3dDevice->CreateTexture2D( &descDepth, nullptr, &m_pDepthStencil );
    if( FAILED( hr ) )
        return hr;

    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory( &descDSV, sizeof(descDSV) );
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = m_pD3dDevice->CreateDepthStencilView( m_pDepthStencil, &descDSV, &m_pDepthStencilView );
    if( FAILED( hr ) )
        return hr;

	 m_pImmediateContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView );


    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_pImmediateContext->RSSetViewports( 1, &vp );
    
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	for( auto c : m_pGraphicComponents ) 
	{
		c.second->InitializeBuffers(m_pD3dDevice);
	} 
	
	return S_OK;
}

//----------------------------------------------------------------------
void Graphics::SendBackDevice(IEventPtr evt)
{
	EventManager::Instance().SendEvent ( 
		std::make_shared<Event_CreateShader>(
			Event_CreateShader(m_pD3dDevice, m_pImmediateContext, &m_pVertexLayout)));

	EventManager::Instance().SendEvent ( 
		std::make_shared<Event_CreateTextures>(
			Event_CreateTextures(m_pD3dDevice)));

	for( auto c : m_pGraphicComponents ) 
	{
		c.second->InitalizeEffects();
	} 
}

void Graphics::ReceiveNewCurrentCamera(IEventPtr evt)
{
	shared_ptr<Event_NewCurrentCamera> sendCurrentCameraEvt = static_pointer_cast<Event_NewCurrentCamera>(evt);
	m_pCurrentCamera = sendCurrentCameraEvt->GetCamera();
}