/**
* @file Debug.cpp
* @brief �f�o�b�O�̎x���@�\
* @author ���{�Y�V��
* @date 2017/1/28
*/
#include "Debug.h"
#include <io.h>
#include <Fcntl.h>

/**
*	@brief �R���\�[����\��������R���X�g���N�^
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

	// �R���\�[���E�C���h�E�̃^�C�g�����擾	
	GetConsoleTitle(TitleBuffer, sizeof(TitleBuffer));

	// �^�C�g������E�C���h�E���������ăE�C���h�E�n���h�����擾
	ConsoleWindow = FindWindow(NULL, TitleBuffer);

	// ���݂̃E�C���h�E��`�̈ʒu���擾
	GetWindowRect(ConsoleWindow, &WindowRect);

	// �E�C���h�E�̍���[��( 0, 0 )�A�E���[��( WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top )�ɕύX
	MoveWindow(ConsoleWindow, 0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, TRUE);
#endif
}

cDebugConsole::~cDebugConsole(){

}

/**
*	@brief�R���\�[�����������郁�\�b�h
*/
void cDebugConsole::Destroy(){
#ifdef _DEBUG
	_close(hConsole);
#endif
}

/**
*	@brief �J�[�\���ʒu��ݒ肷��(0�`)
*	@param pos_x ���ʒu
*	@param pos_y ���ʒu
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
*	@brief ������
*	@param �ϐ��� ������
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