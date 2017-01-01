/*=========================================================//
//		概要	:	入力処理を記述する
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//	入力系の処理を記述する。将来的にはここにゲームパッドやマウス処理を加える
//=========================================================*/
#ifndef INC_INPUT_H
#define INC_INPUT_H

#define GetKey Input::cKeyboard::getInstance()		//キーボード情報取得(ポインタ)

#include <dinput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")


//入力処理系のクラスを記述する
namespace Input{

	//キーボードクラス(シングルトン)
	class cKeyboard{
	public:
		friend int WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
		bool Press(int key);
		bool Trigger(int key);
		bool Repeat(int key);
		bool Release(int key);
		HRESULT UpdateKeyboard(void);

		//初回呼び出し時に実体生成
		static cKeyboard* getInstance(){
			static cKeyboard key;
			return &key;
		}
	private:
		cKeyboard();
		HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
		void UninitKeyboard(void);

		cKeyboard(const cKeyboard&) = delete;				//コピーコンストラクタを delete 指定
		cKeyboard& operator=(const cKeyboard&) = delete;	//コピー代入演算子も delete 指定
		cKeyboard(cKeyboard&&) = delete;						//ムーブコンストラクタを delete 指定
		cKeyboard& operator=(cKeyboard&&) = delete;			//ムーブ代入演算子も delete 指定
		~cKeyboard();
	};
}
#endif