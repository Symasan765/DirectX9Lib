/*=========================================================//
//		概要	:	入力処理を記述する
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//=========================================================*/
#include "Input.h"
#include "GameManager.h"
#define DIRECTINPUT_VERSION 0x0800

//他のファイルから隠ぺい
namespace{
	const int NUM_KEY_MAX = 256;
	LPDIRECTINPUT8			pDInput = NULL;						// IDirectInput8インターフェースへのポインタ
	LPDIRECTINPUTDEVICE8	pDIDevKeyboard = NULL;				// IDirectInputDevice8インターフェースへのポインタ(キーボード)
	LPDIRECTINPUTDEVICE8	pDIDevMouse = NULL;					// IDirectInputDevice8インターフェースへのポインタ(マウス)
	BYTE						keyState[NUM_KEY_MAX];				// キーボードの状態を受け取るワーク
	BYTE						keyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
	BYTE						keyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
	BYTE						keyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
	int							keyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
	DIMOUSESTATE2			mouseState;							// マウスの状態を受け取るワーク
	DIMOUSESTATE2			mouseStateTrigger;					// マウスの状態を受け取るワーク
	POINT						MousePoint;							// マウスの現在座標
}
using namespace Input;

cKeyboard::cKeyboard(){
	HRESULT hr;
	if (!pDInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(GetHINSTANCE, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&pDInput, NULL);
	}
	InitKeyboard(GetHINSTANCE,GetWindHandle);
}

HRESULT cKeyboard::InitKeyboard(HINSTANCE hInst, HWND hWnd){
	HRESULT hr = 0;

	// デバイスオブジェクトを作成
	hr = pDInput->CreateDevice(GUID_SysKeyboard, &pDIDevKeyboard, NULL);
	if (FAILED(hr) || pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	pDIDevKeyboard->Acquire();

	return S_OK;
}

HRESULT cKeyboard::UpdateKeyboard(void){
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, keyState, NUM_KEY_MAX);

	// デバイスからデータを取得
	hr = pDIDevKeyboard->GetDeviceState(sizeof(keyState), keyState);
	if (SUCCEEDED(hr))
	{
		for (int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			// トリガーとリリースを取得
			keyStateTrigger[cnt] = (keyState[cnt] ^ keyStateOld[cnt]) & keyState[cnt];
			keyStateRelease[cnt] = (keyState[cnt] ^ keyStateOld[cnt]) & keyStateOld[cnt];

			// キーが押されているならリピートの判定処理
			if (keyState[cnt])
			{
				if (keyStateRepeatCnt[cnt] < 20)
				{
					keyStateRepeatCnt[cnt]++;
					// 「初回入力」もしくは「ボタンを押してから20フレーム経過」
					// した場合、リピート用配列のデータを有効にする
					// 上記条件以外はリピート用配列のデータを無効にする
					if (keyStateRepeatCnt[cnt] == 1 || keyStateRepeatCnt[cnt] >= 20) {
						keyStateRepeat[cnt] = 0x80;
					}
					else {
						keyStateRepeat[cnt] = 0;
					}
				}
			}
			else
			{
				keyStateRepeatCnt[cnt] = 0;
				keyStateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		hr = pDIDevKeyboard->Acquire();
	}

	return hr;
}

void cKeyboard::UninitKeyboard(void){
	if (pDIDevKeyboard)
	{
		pDIDevKeyboard->Unacquire();

		pDIDevKeyboard->Release();
		pDIDevKeyboard = nullptr;
	}
}

cKeyboard::~cKeyboard(){
	// キーボードの終了処理
	UninitKeyboard();

	if (pDInput){
		pDInput->Release();
		pDInput = nullptr;
	}
}

bool cKeyboard::Press(int key){
	return ((keyState[key] & 0x80) != 0);
}

bool cKeyboard::Trigger(int key){
	return ((keyStateTrigger[key] & 0x80) != 0);
}