/*=========================================================//
//		�T�v	:	�Q�[���S�̂��Ǘ�����N���X
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//
//			�Q�[���}�l�[�W���[�N���X���L�q����
//=========================================================*/
#include "GameManager.h"
#include "System.h"
#include "Input.h"
#include "GameTrans.h"
#include "Main.h"
#include "XAudio2.h"		//TODO
#include "Debug.h"

//�O�Ɍ�����K�v�̂Ȃ��ǂ����悤���Ȃ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

cGameManager* cGameManager::GetInstance(){
	return pGameManager;
}

void cGameManager::Init(HINSTANCE arghInstance, int argnCmdShow){
	//�f�o�b�O���[�h���͂܂��R���\�[���𐶐�����
#if _DEBUG
	GetConsole;
#endif

	SystemError = true;	//�G���[�i�V���

	WNDCLASSEX wc;		//�E�B���h�E�N���X
	hInstance = arghInstance;
	nCmdShow = argnCmdShow;

	wc.cbSize = sizeof(WNDCLASSEX);							//�\���̂̃T�C�Y
	wc.style = CS_HREDRAW | CS_VREDRAW;						//�E�B���h�E�X�^�C��
	wc.hInstance = arghInstance;								//�C���X�^���X�̒l�ݒ�
	wc.lpszClassName = "DX21";
	wc.lpfnWndProc = (WNDPROC)WndProc;						//�E�B���h�E���b�Z�[�W�֐�
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);			//���[�W�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);			//�X���[���A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				//�J�[�\���X�^�C��
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);		//�w�i�F
	wc.lpszMenuName = NULL;									//���j���[�Ȃ�
	wc.cbClsExtra = 0;											//�G�L�X�g���i�V
	wc.cbWndExtra = 0;											//

	/*=============�E�B���h�E�N���X�̓o�^===============*/
	//�G���[����
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "�E�B���h�E�N���X�\���̂̏������G���[", "", MB_OK);
	}

	hWnd = CreateWindow(
		wc.lpszClassName,						//�E�B���h�E�N���X�̖��O
		PROGRAM_TITLE,						//�^�C�g��
		WS_CAPTION | WS_SYSMENU,			//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						//�E�B���h�E�ʒu
		CW_USEDEFAULT,						//�E�B���h�E�ʒu
		WINDOW_SCREEN_X,						//�E�B���h�E�T�C�Y
		WINDOW_SCREEN_Y,
		NULL,									//�e�E�B���h�E�i�V
		NULL,									//���j���[�i�V
		hInstance,								//�C���X�^���X�n���h��
		NULL									//�ǉ������i�V
		);

	//DirectX�������֐�
	if (FAILED(InitD3D(hWnd))) SystemError = false;		//�G���[����

	/*==========�E�B���h�E�\��===========*/
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	InitSound();

	//====================�e����������======================
	pFrameRate = new cFrameRateCtrl();	//FPS�R���g���[���N���X
	GameLoop = new MainLoop;				//���C����������
}

/*========================================================
//	�֐�	:	D3D�̏��������s��
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
//	�֐�	:	�t���[������N���X�̃R���X�g���N�^
===================================================*/
cFrameRateCtrl::cFrameRateCtrl() : frameTime(1000 / FRAME_RATE)
{
	timeBeginPeriod(1);	//�^�C�}�̐��x���ō���
	fpsCnt = 0;
	fpsDispCnt = 0;
	nowTime = 0;
	frameCnt = 0;
	oldTime = timeGetTime();
}

/*===================================================
//	�֐�	:	�t���[������̃T�C����Ԃ��֐�
===================================================*/
bool cFrameRateCtrl::FrameStart()
{
	this->nowTime = timeGetTime();	//�����ԑ���

	const float EXspeed = static_cast<float>(nowTime - oldTime);		//1�t���[���ɂ����������Ԃ��i�[

	//1�t���[���̎��Ԃ��Œ�t���[�����Ԃ𒴂���Ώ������s��
	if (EXspeed >= frameTime)
	{
		fpsDispCnt = 1000.0f / EXspeed;		//���݂̃t���[�����[�g���i�[
		oldTime = nowTime;
		return true;			//�t���[������OK
	}
	else
	{
		return false;			//�܂��_���I
	}
}

/*================================================
//					�E�B���h�E�v���V�[�W��		//
//					����ȓz�g��Ȃ���
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