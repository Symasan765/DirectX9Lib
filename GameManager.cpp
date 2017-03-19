/*=========================================================//
//		概要	:	ゲーム全体を管理するクラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//			ゲームマネージャークラスを記述する
//=========================================================*/
#include "GameManager.h"
#include "System.h"
#include "Input.h"
#include "GameTrans.h"
#include "Main.h"
#include "XAudio2.h"		//TODO
#include "Debug.h"

//外に見せる必要のないどうしようもないやつ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

cGameManager* cGameManager::GetInstance(){
	return pGameManager;
}

void cGameManager::Init(HINSTANCE arghInstance, int argnCmdShow){
	//デバッグモード中はまずコンソールを生成する
#if _DEBUG
	GetConsole;
#endif

	SystemError = true;	//エラーナシ状態

	WNDCLASSEX wc;		//ウィンドウクラス
	hInstance = arghInstance;
	nCmdShow = argnCmdShow;

	wc.cbSize = sizeof(WNDCLASSEX);							//構造体のサイズ
	wc.style = CS_HREDRAW | CS_VREDRAW;						//ウィンドウスタイル
	wc.hInstance = arghInstance;								//インスタンスの値設定
	wc.lpszClassName = "DX21";
	wc.lpfnWndProc = (WNDPROC)WndProc;						//ウィンドウメッセージ関数
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);			//ラージアイコン
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);			//スモールアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				//カーソルスタイル
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);		//背景色
	wc.lpszMenuName = NULL;									//メニューなし
	wc.cbClsExtra = 0;											//エキストラナシ
	wc.cbWndExtra = 0;											//

	/*=============ウィンドウクラスの登録===============*/
	//エラー処理
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "ウィンドウクラス構造体の初期化エラー", "", MB_OK);
	}

	hWnd = CreateWindow(
		wc.lpszClassName,						//ウィンドウクラスの名前
		PROGRAM_TITLE,						//タイトル
		WS_CAPTION | WS_SYSMENU,			//ウィンドウスタイル
		CW_USEDEFAULT,						//ウィンドウ位置
		CW_USEDEFAULT,						//ウィンドウ位置
		WINDOW_SCREEN_X,						//ウィンドウサイズ
		WINDOW_SCREEN_Y,
		NULL,									//親ウィンドウナシ
		NULL,									//メニューナシ
		hInstance,								//インスタンスハンドル
		NULL									//追加引数ナシ
		);

	//DirectX初期化関数
	if (FAILED(InitD3D(hWnd))) SystemError = false;		//エラー処理

	/*==========ウィンドウ表示===========*/
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	InitSound();

	//====================各初期化処理======================
	pFrameRate = new cFrameRateCtrl();	//FPSコントロールクラス
	GameLoop = new MainLoop;				//メイン処理部分
}

/*========================================================
//	関数	:	D3Dの初期化を行う
========================================================*/
HRESULT cGameManager::InitD3D(HWND hWnd)
{
	D3DPRESENT_PARAMETERS d3dpp;

	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&pD3DDevice)))
	{
		return E_FAIL;
	}

	pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->LightEnable(0, TRUE);

	return S_OK;
}

LPDIRECT3DDEVICE9& cGameManager::GetD3dDevice(){
	return pD3DDevice;
}

HWND& cGameManager::GethWnd(){
	return hWnd;
}

HINSTANCE& cGameManager::GetHInstance(){
	return hInstance;
}

void cGameManager::Create(HINSTANCE arghInstance, int argnCmdShow){
	if (!pGameManager){
		pGameManager = new cGameManager;
		pGameManager->Init(arghInstance, argnCmdShow);
	}
}

void cGameManager::Destroy(){
	delete pGameManager;
	pGameManager = nullptr;
	UninitSound();
}

cGameManager::~cGameManager(){
	GetConsole->Destroy();
	if (cGameManager::GetInstance()->GetD3dDevice() != NULL)
		cGameManager::GetInstance()->GetD3dDevice()->Release();

	if (pD3D != NULL)
		pD3D->Release();

	delete pFrameRate;
	pFrameRate = nullptr;
	delete GameLoop;
	GameLoop = nullptr;
}



/*===================================================
//	関数	:	フレーム制御クラスのコンストラクタ
===================================================*/
cFrameRateCtrl::cFrameRateCtrl() : frameTime(1000 / FRAME_RATE)
{
	timeBeginPeriod(1);	//タイマの精度を最高に
	fpsCnt = 0;
	fpsDispCnt = 0;
	nowTime = 0;
	frameCnt = 0;
	oldTime = timeGetTime();
}

/*===================================================
//	関数	:	フレーム制御のサインを返す関数
===================================================*/
bool cFrameRateCtrl::FrameStart()
{
	this->nowTime = timeGetTime();	//現時間測定

	const float EXspeed = static_cast<float>(nowTime - oldTime);		//1フレームにかかった時間を格納

	//1フレームの時間が固定フレーム時間を超えれば処理を行う
	if (EXspeed >= frameTime)
	{
		fpsDispCnt = 1000.0f / EXspeed;		//現在のフレームレートを格納
		oldTime = nowTime;
		return true;			//フレーム制御OK
	}
	else
	{
		return false;			//まだダメ！
	}
}

/*================================================
//					ウィンドウプロシージャ		//
//					こんな奴使わないよ
================================================*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}