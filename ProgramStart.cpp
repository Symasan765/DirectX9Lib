/////////////////////////////////////////////////////////////
//					作成者　松本 雄之介 (AT12A606)					　//
//						作成日　											  //
//					  更新日												  //
/////////////////////////////////////////////////////////////

/*=======================#include========================*/
#include "GameManager.h"
#include "GameTrans.h"
#include "time.h"
#include "Input.h"
cGameManager* cGameManager::pGameManager = nullptr;		//実体ポインタを初期化

/*================================================================================
//									WinMain関数													//
================================================================================*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;				//メッセージ構造体
	cGameManager::Create(hInstance, nCmdShow);	//インスタンス作成

	if (!cGameManager::GetInstance()->SystemError)
		return -1;

	/*===============メインループ====================*/
	srand((unsigned)time(NULL));
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0) == 0)		//"WM_QUIT"メッセージを取得した場合0を返却
			{
				break;
			}
			//メッセージの翻訳と送出
			TranslateMessage(&msg);			//仮想キーメッセージを文字メッセージへ変換
			DispatchMessage(&msg);			//ウィンドウプロシージャへメッセージを送出
		}
		else
		{
			if (cGameManager::GetInstance()->pFrameRate->FrameStart())	//フレームレート制御
			{
				GetKey->UpdateKeyboard();
				GetGameManager->GameLoop->update(GetGameManager->GameLoop);	//ゲームループ内部
			}
		}
	}

	//DirectX終了処理関数
	cGameManager::GetInstance()->Destroy();
	return (int)msg.wParam;
}