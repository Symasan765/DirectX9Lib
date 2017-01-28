/**
* @file Debug.h
* @brief デバッグサポート機能を保有する
* @author 松本雄之介
* @date 2017/1/28
*/
#ifndef INC_DEBUG_H
#define INC_DEBUG_H

#include <iostream>
#include <crtdbg.h>
#include <Windows.h>

// デバッグモード時のみ使用されるprintf
#ifdef _DEBUG
#define D_printf(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define D_printf(...)
#endif

/*=======================よく使うのはここだよ============================*/
#define GetConsole cDebugConsole::GetInstance()							//クラスの実体を取得する
/*==================================================================*/

/**
*	@briefデバッグ用のコンソールウィンドウを管理する
*	
*/
class cDebugConsole{
public:
	void SetPos(const int, const int);
	void SetColor(WORD font_color, WORD back_color);
	void Clear();

	cDebugConsole(const cDebugConsole&) = delete;
	cDebugConsole& operator=(const cDebugConsole&) = delete;
	cDebugConsole(cDebugConsole&&) = delete;
	cDebugConsole& operator=(cDebugConsole&&);

	static cDebugConsole* GetInstance(){
		static cDebugConsole console;
		return &console;
	}
	void Destroy();
private:
	cDebugConsole();
	~cDebugConsole();
	int hConsole;		//コンソールハンドル
	HANDLE h_std_out;		//STDハンドル - output
};

/**
* @enum コンソール用カラー指定(CScreen準拠)
*/
enum {
	BLACK = 0,
	NAVY = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	PUPRLE = 5,
	BROWN = 6,
	GRAY = 7,
	DARK = 8,
	BLUE = 9,
	LIME = 10,
	SKYBULE = 11,
	CORAL = 12,
	PINK = 13,
	YELLOW = 14,
	WHITE = 15
};

//機能メモ
//		_ASSERT_EXPR(bool,テキスト)		条件が真の時にプログラムを強制的に止める
//		OutputDebugString(_T)			デバッグウィンドウに指定の文字列を表示させる

#endif