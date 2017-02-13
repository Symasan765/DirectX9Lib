/**
* @file Debug.cpp
* @brief デバッグの支援機能
* @author 松本雄之介
* @date 2017/1/28
*/
#include "Debug.h"
#include <io.h>
#include <Fcntl.h>
#include "System.h"

/**
*	@brief コンソールを表示させるコンストラクタ
*/
cDebugConsole::cDebugConsole(){
	hConsole = 0;
	h_std_out = NULL;

#ifdef _DEBUG
	AllocConsole();
	hConsole = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	*stdout = *_fdopen(hConsole, "w");
	setvbuf(stdout, NULL, _IONBF, 0);

	h_std_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
	char TitleBuffer[512];
	HWND ConsoleWindow;
	RECT WindowRect;

	// コンソールウインドウのタイトルを取得	
	GetConsoleTitle(TitleBuffer, sizeof(TitleBuffer));

	// タイトルからウインドウを検索してウインドウハンドルを取得
	ConsoleWindow = FindWindow(NULL, TitleBuffer);

	// 現在のウインドウ矩形の位置を取得
	GetWindowRect(ConsoleWindow, &WindowRect);

	// ウインドウの左上端を( 0, 0 )、右下端を( WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top )に変更
	MoveWindow(ConsoleWindow, 0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, TRUE);

	SetConsoleTitle(TEXT("DebugWindow"));	//ウィンドウのタイトルを変更する
#endif
}

cDebugConsole::~cDebugConsole(){

}

/**
*	@briefコンソールを消去するメソッド
*/
void cDebugConsole::Destroy(){
#ifdef _DEBUG
	_close(hConsole);
#endif
}

/**
*	@brief カーソル位置を設定する(0～)
*	@param pos_x 横位置
*	@param pos_y 盾位置
*/
void cDebugConsole::SetPos(const int pos_x, const int pos_y){
#ifdef _DEBUG
	COORD pos;
	pos.X = (SHORT)pos_x;
	pos.Y = (SHORT)pos_y;
	SetConsoleCursorPosition(h_std_out, pos);
#endif
}

/**
*	@brief 説明文
*	@param 変数名 説明文
*/
void cDebugConsole::SetColor(WORD font_color, WORD back_color){
#ifdef _DEBUG
	::SetConsoleTextAttribute(h_std_out, ((back_color << 4) | (font_color)));
#endif
}

void cDebugConsole::Clear(){
#ifdef _DEBUG
	SetColor(15, 0);
	system("cls");
#endif
}

void cDebugConsole::FrameRateDisp(){
	static DWORD backTickCount, nowTickCount;
	static int fps = 0;  // FPSカウント

	nowTickCount = timeGetTime();

	/* ＦＰＳを求めて表示する */
	fps++;
	if (nowTickCount - backTickCount >= 1000)
	{
		backTickCount = nowTickCount;
		SetPos(0, 0);
		if (fps > FRAME_RATE / 10 * 9){
			SetColor(WHITE, BLACK);
		}
		else if (fps > FRAME_RATE / 10 * 5){
			SetColor(BLACK, YELLOW);
		}
		else{
			SetColor(WHITE, RED);
		}
		printf("FPS %d", fps);
		fps = 0;
	}
}