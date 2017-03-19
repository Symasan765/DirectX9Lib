/*=========================================================//
//		概要	:	ゲーム全体を管理するクラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//			ゲームマネージャークラスを記述する
//=========================================================*/
#ifndef INC_GAME_MANAGER_H
#define INC_GAME_MANAGER_H
#include <Windows.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

/*=======================よく使うのはここだよ============================*/
#define GetGameManager cGameManager::GetInstance()							//クラスの実体を取得する
#define GetD3DDevice cGameManager::GetInstance()->GetD3dDevice()		//pD3DDeviceを取得する
#define GetWindHandle cGameManager::GetInstance()->GethWnd()				//ウィンドウハンドラを取得する
#define GetHINSTANCE cGameManager::GetInstance()->GetHInstance()		//HInstanceを取得する
/*=================================================================*/

class cFrameRateCtrl;	//フレーム制御クラス
class cGameTrans;		//状態遷移クラス
class DebugFont;			//デバッグ文字クラス

class cGameManager{
public:
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	static cGameManager* GetInstance();							//インスタンス生成＆インスタンスゲット

	LPDIRECT3DDEVICE9& GetD3dDevice();
	HWND& GethWnd();
	HINSTANCE& GetHInstance();
	//シングルトン設定
	cGameManager(const cGameManager&) = delete;					//コピーコンストラクタを delete 指定
	cGameManager& operator=(const cGameManager&) = delete;	//コピー代入演算子も delete 指定
	cGameManager(cGameManager&&) = delete;						//ムーブコンストラクタを delete 指定
	cGameManager& operator=(cGameManager&&) = delete;			//ムーブ代入演算子も delete 指定
private:
	cGameManager(){};
	void cGameManager::Init(HINSTANCE arghInstance, int argnCmdShow);	//DX初期化
	~cGameManager();																//DX解放
	static void Create(HINSTANCE arghInstance, int argnCmdShow);			//作成
	static  void Destroy();														//解放
	HRESULT InitD3D(HWND);

	/*==================管理されるものたち===================*/
	static cGameManager* pGameManager;		//吸引力の劣らないただ一つの実態
	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pD3DDevice;
	HWND hWnd;
	HINSTANCE hInstance;
	int nCmdShow;
	bool SystemError;							//初期化時にエラーが出たか保持

	cFrameRateCtrl* pFrameRate;				//フレーム制御
	cGameTrans* GameLoop;						//最上位遷移
};

//フレームレート制御
class cFrameRateCtrl{
public:
	cFrameRateCtrl();
	bool FrameStart();
private:
	float fpsDispCnt;		//現FPS表示用カウンター
	const float frameTime;	//1フレームの時間
	int fpsCnt;
	DWORD oldTime;			//1フレーム前の計測時間
	DWORD nowTime;			//現フレーム計測時間
	DWORD frameCnt;			//フレームレートカウント
};

#endif