/*=========================================================//
//		�T�v	:	���͏������L�q����
//					�쐬�ҁ@���{ �Y�V�� (AT12A606)
//						�쐬��	2016/11/2
//					  �X�V��
//	���͌n�̏������L�q����B�����I�ɂ͂����ɃQ�[���p�b�h��}�E�X������������
//=========================================================*/
#ifndef INC_INPUT_H
#define INC_INPUT_H

#define GetKey Input::cKeyboard::getInstance()		//�L�[�{�[�h���擾(�|�C���^)

#include <dinput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")


//���͏����n�̃N���X���L�q����
namespace Input{

	//�L�[�{�[�h�N���X(�V���O���g��)
	class cKeyboard{
	public:
		friend int WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
		bool Press(int key);
		bool Trigger(int key);
		bool Repeat(int key);
		bool Release(int key);
		HRESULT UpdateKeyboard(void);

		//����Ăяo�����Ɏ��̐���
		static cKeyboard* getInstance(){
			static cKeyboard key;
			return &key;
		}
	private:
		cKeyboard();
		HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
		void UninitKeyboard(void);

		cKeyboard(const cKeyboard&) = delete;				//�R�s�[�R���X�g���N�^�� delete �w��
		cKeyboard& operator=(const cKeyboard&) = delete;	//�R�s�[������Z�q�� delete �w��
		cKeyboard(cKeyboard&&) = delete;						//���[�u�R���X�g���N�^�� delete �w��
		cKeyboard& operator=(cKeyboard&&) = delete;			//���[�u������Z�q�� delete �w��
		~cKeyboard();
	};
}
#endif