/**
* @file Debug.h
* @brief �f�o�b�O�T�|�[�g�@�\��ۗL����
* @author ���{�Y�V��
* @date 2017/1/28
*/
#ifndef INC_DEBUG_H
#define INC_DEBUG_H

#include <iostream>
#include <crtdbg.h>
#include <Windows.h>

// �f�o�b�O���[�h���̂ݎg�p�����printf
#ifdef _DEBUG
#define D_printf(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define D_printf(...)
#endif

/*=======================�悭�g���̂͂�������============================*/
#define GetConsole cDebugConsole::GetInstance()							//�N���X�̎��̂��擾����
/*==================================================================*/

/**
*	@brief�f�o�b�O�p�̃R���\�[���E�B���h�E���Ǘ�����
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
	int hConsole;		//�R���\�[���n���h��
	HANDLE h_std_out;		//STD�n���h�� - output
};

/**
* @enum �R���\�[���p�J���[�w��(CScreen����)
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

//�@�\����
//		_ASSERT_EXPR(bool,�e�L�X�g)		�������^�̎��Ƀv���O�����������I�Ɏ~�߂�
//		OutputDebugString(_T)			�f�o�b�O�E�B���h�E�Ɏw��̕������\��������

#endif