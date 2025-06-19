#include "D3D.h"
#include "Camera.h"
#include "Player.h"

ID3D11Device* D3D::dev = nullptr;

D3D::D3D() {
	devCon = nullptr;
	renderTargetView = nullptr;
	swapChain = nullptr;
	swapChain1 = nullptr;
	playGame = false;
	start_timer = 0;
	end_timer = 0;
}

void D3D::initD3DTest(HWND hWnd) {
	HRESULT hr;
	std::wostringstream debugString;

	IDXGIFactory2* dxgiFactory = nullptr;
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory2), (void**)&dxgiFactory);
	if (FAILED(hr)) {
		debugString << L"Couldn't create dxgi factory\n";
		OutputDebugString(debugString.str().c_str());
		debugString.clear();
		PostQuitMessage(0);
	}

	//Adapter 
	IDXGIAdapter* dxgiAdapter = nullptr, *bestDXGIAdapter = nullptr;
	SIZE_T maxRam = 0;
	UINT numAdapters = 0;
	while (dxgiFactory->EnumAdapters(numAdapters, &dxgiAdapter) != DXGI_ERROR_NOT_FOUND) {
		SIZE_T currMaxRam = 0;
		DXGI_ADAPTER_DESC adapterDesc;
		dxgiAdapter->GetDesc(&adapterDesc);

		debugString << L"Adaptor " << numAdapters << L"\n";
		debugString << "Adapter name: " << adapterDesc.Description << L"\n";
		debugString << "VendorID: " << adapterDesc.VendorId << L"\n";
		debugString << "Device ID: " << adapterDesc.DeviceId << L"\n";
		debugString << "SubSysID: " << adapterDesc.SubSysId << L"\n";
		debugString << "Revision: " << adapterDesc.Revision << L"\n";
		debugString << "Dedicated Video Memory: " << adapterDesc.DedicatedVideoMemory / (1024 * 1024)<< L"\n";
		debugString << "Dedicated System Memory: " << adapterDesc.DedicatedSystemMemory / (1024 * 1024) << L"\n";
		debugString << "Shared System Memory: " << adapterDesc.SharedSystemMemory / (1024 * 1024) << L"\n";

		numAdapters++;

		currMaxRam = adapterDesc.DedicatedVideoMemory;
		if (currMaxRam > maxRam) {
			maxRam = currMaxRam;
			bestDXGIAdapter = dxgiAdapter;
			
		}

		OutputDebugString(debugString.str().c_str());
		debugString.clear();
		debugString.str(L"");
	}

	debugString << L"Num of adapters are : " << numAdapters << L" and max Ram is " << maxRam / (1024 * 1024) << L"\n";
	OutputDebugString(debugString.str().c_str());
	debugString.clear();

	DXGI_ADAPTER_DESC bestDXGIAdapterDesc;
	bestDXGIAdapter->GetDesc(&bestDXGIAdapterDesc);
	debugString.str(L"");
	debugString << L"Best dxgi adapter is: " << bestDXGIAdapterDesc.Description << L"\n";
	OutputDebugString(debugString.str().c_str());
	debugString.clear();
	debugString.str(L"");

	//Create device
	D3D_FEATURE_LEVEL chosenFeatureLevel, featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	UINT featureLevelsSize = ARRAYSIZE(featureLevels);
	hr = D3D11CreateDevice(bestDXGIAdapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, D3D11_CREATE_DEVICE_DEBUG, featureLevels,
		featureLevelsSize, D3D11_SDK_VERSION, &dev, &chosenFeatureLevel, &devCon);
	//hr = D3D11CreateDevice(
	//	NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, featureLevels, featureLevelsSize,
	//	D3D11_SDK_VERSION, &dev, &chosenFeatureLevel, &devCon);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create device", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	debugString << L"Chosen feature level is: 0x" << std::hex << chosenFeatureLevel << L"\n";
	OutputDebugString(debugString.str().c_str());
	debugString.clear();
	debugString.str(L"");

	//Create swap chain
	UINT sampleCount = 8, qualityLevels = 0;
	hr = dev->CheckMultisampleQualityLevels(DXGI_FORMAT_R16G16B16A16_FLOAT, sampleCount, &qualityLevels);
	if (SUCCEEDED(hr)) {
		debugString << L"Quality levels for " << sampleCount << L" samples: " << qualityLevels << L"\n";
		OutputDebugString(debugString.str().c_str());
		debugString.clear();
		debugString.str(L"");
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc1;
	ZeroMemory(&swapChainDesc1, sizeof(DXGI_SWAP_CHAIN_DESC1));
	swapChainDesc1.Width = width;
	swapChainDesc1.Height = height;
	swapChainDesc1.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	swapChainDesc1.Stereo = false;
	swapChainDesc1.SampleDesc.Count = 1;
	swapChainDesc1.SampleDesc.Quality = 0;
	swapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc1.BufferCount = 2;
	swapChainDesc1.Scaling = DXGI_SCALING_NONE;
	swapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc1.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc;
	ZeroMemory(&fullScreenDesc, sizeof(DXGI_SWAP_CHAIN_FULLSCREEN_DESC));
	fullScreenDesc.RefreshRate.Numerator = 60;
	fullScreenDesc.RefreshRate.Denominator = 1;
	fullScreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	fullScreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	fullScreenDesc.Windowed = true;

	hr = dxgiFactory->CreateSwapChainForHwnd((IUnknown *)dev, hWnd, &swapChainDesc1, &fullScreenDesc, nullptr, &swapChain1);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create swap chain for hWnd", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	//Create render target view
	ID3D11Texture2D* backBuffer = nullptr;
	hr = swapChain1->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't get swap chain buffer", L"Error", MB_OK);
		PostQuitMessage(0);
	}

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	ZeroMemory(&renderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	renderTargetViewDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	hr = dev->CreateRenderTargetView(backBuffer, &renderTargetViewDesc, &renderTargetView);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create render target view", L"Error", MB_OK);
		PostQuitMessage(0);
	}
	backBuffer->Release();
	devCon->OMSetRenderTargets(1, &renderTargetView, nullptr);

	//Set the view port
	D3D11_VIEWPORT viewPortDesc;
	ZeroMemory(&viewPortDesc, sizeof(D3D11_VIEWPORT));
	viewPortDesc.TopLeftX = 0;
	viewPortDesc.Width = width;
	viewPortDesc.TopLeftY = 0;
	viewPortDesc.Height = height;
	viewPortDesc.MaxDepth = 1.0f;
	viewPortDesc.MinDepth = 0.0f;

	devCon->RSSetViewports(1, &viewPortDesc);
}

void D3D::renderD3DTest() {
	devCon->ClearRenderTargetView(renderTargetView, DirectX::SimpleMath::Color(1.0f, 0.0f, 1.0f, 0.0f));

	swapChain1->Present(0, 0);
}

void D3D::initD3D(HWND hWnd) {
	HRESULT hr;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Windowed = true;					//Set to false for fullscreen once the game is done
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;			//take out the comment once the game is done for fullscreen
	swapChainDesc.SampleDesc.Count = 1;

	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &dev, NULL, &devCon);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create device and swap chain", L"Error", MB_OK);
		exit(-1);
	}

	ID3D11Texture2D* pSwapChain;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pSwapChain);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't get swap chain buffer", L"Error", MB_OK);
		exit(-1);
	}

	hr = dev->CreateRenderTargetView(pSwapChain, NULL, &renderTargetView);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't create render target view", L"Error", MB_OK);
		exit(-1);
	}

	devCon->OMSetRenderTargets(1, &renderTargetView, NULL);

	//Set View port
	D3D11_VIEWPORT viewPortDesc;
	viewPortDesc.TopLeftX = 0;
	viewPortDesc.Width = width;
	viewPortDesc.TopLeftY = 0;
	viewPortDesc.Height = height;
	viewPortDesc.MaxDepth = 1.0f;
	viewPortDesc.MinDepth = 0.0f;

	devCon->RSSetViewports(1, &viewPortDesc);

	//Set full screen			//Enable it once the game is complete
	/*
	hr = swapChain->SetFullscreenState(true, NULL);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Couldn't set full screen", L"Error", MB_OK);
		exit(-1);
	}
	*/

	//Init Camera
	Camera.initCamera(dev);
	//Initialize all main menu
	MainMenu.initMainMenu(dev, devCon);
	Game.initGame(dev);

	PLAYER& player = PLAYER::getInstance();
	if (!player.checkFileExists()) {
		player.createPlayerStat();
	}
	else {
		player.openPlayerStat();
	}
}

void D3D::updateD3D(float frame_time) {
	if (!playGame) {
		playGame = MainMenu.updateMainMenu(devCon, frame_time, playGame);
	}
	else {
		if (end_timer - start_timer >= 1 /*Change to 5 when game is done*/) {
			Game.updateGame(devCon, frame_time);
		}
	}
}

void D3D::renderD3D(int time) {
	devCon->ClearRenderTargetView(renderTargetView, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 1.0f));

	//Camera
	Camera.renderCamera(devCon);

	//Main Menu
	if (playGame == false) {
		MainMenu.renderMainMenu(devCon, time);
		start_timer = time;
		end_timer = start_timer;
	}
	else {
		if (end_timer - start_timer < 1/*Change to 5 seconds when game is done*/) {
			end_timer = time;
			devCon->ClearRenderTargetView(renderTargetView, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 1.0f));
			MainMenu.renderLoadingMenu(devCon);
		}
		else {	//Play Game
			devCon->ClearRenderTargetView(renderTargetView, DirectX::SimpleMath::Color(0.3608f, 0.5804f, 0.9882f, 1.0f));
			Game.renderGame(devCon);
		}
	}

	swapChain->Present(0, 0);
}

void D3D::cleanD3D() {
	//swapChain->SetFullscreenState(false, NULL);			//Put it back when the game is complete
	dev->Release();
	devCon->Release();
	swapChain->Release();
	//swapChain1->Release();
	renderTargetView->Release();
	Camera.cleanCamera();
	MainMenu.cleanMainMenu();
	Game.cleanGame();
}

ID3D11Device* D3D::getDevice() {
	return dev;
}