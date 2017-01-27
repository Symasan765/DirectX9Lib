#include "Main.h"
#include "Texture_Class.h"

/*===================================================
//	メイン処理
//	引数	一つ前の遷移クラスのポインタが渡される
//	戻値	遷移する場合、次に移る遷移先アドレスを渡す
===================================================*/
cGameTrans* MainLoop::update(cGameTrans* Parent){
	/*=====================メイン処理を書いて============================*/

	draw();
	return this;	//状態遷移がなければ自分を返す
}

/*===================================================
//	描画処理
//	描画機能をここに書き込み、Updateで呼び出せばOK
===================================================*/
void MainLoop::draw(){
	DrawBegine();	//あらかじめBegineと…

	/*=================描画処理===================*/
	//各々描画するぜ

	int stage[6][10] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 0, 2, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
		{ 0, 3, 0, 2, 0, 0, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	Back->Draw();

	for (int height = 0; height < 6; height++){
		for (int width = 0; width < 10; width++){
			switch (stage[height][width])
			{
			case 0:		//スルー
				break;
			case 1:
				Block->SetPosition(width * 72,height * 72 + 10,72.0f,72.0f);
				Block->Draw();
				break;
			case 2:
				Adhesion->SetPosition(width * 72, height * 72 + 10, 72.0f, 72.0f);
				Adhesion->Draw();
				break;
			case 3:
				Character->SetPosition(width * 72, height * 72 + 10, 72.0f, 72.0f);
				Character->Draw();
				break;
			default:
				break;
			}
		}
	}
	/*===========================================*/

	DrawEnd();		//Endを書いておくとその間に処理を書けば済むよ！
}

/*===================================================
//	初期化処理
//	ゲーム中で使用する変数はヘッダーで定義しここで初期化
===================================================*/
MainLoop::MainLoop(){
	Back = new Texture2D("image/back.jpg");
	Back->SetPosition(0.0f, 0.0f, 720.0f, 480.0f);
	Character = new Texture2D("image/character.png");
	Block = new Texture2D("image/block.png");
	Adhesion = new Texture2D("image/special.png");
}

/*===================================================
//	解放処理
//	ゲーム中で使用した変数はきっちり後片付けしましょうね！
===================================================*/
MainLoop::~MainLoop(){
	delete Back;
	delete Character;
	delete Block;
	delete Adhesion;
}