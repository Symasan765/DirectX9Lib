#include "Main.h"
#include "Debug.h"
#include "Input.h"
#include "XfileDX9.h"
#include "Camera.h"
#include "Light.h"
#include "BillBoard.h"
#include "GameManager.h"

/*===================================================
//	メイン処理
//	引数	一つ前の遷移クラスのポインタが渡される
//	戻値	遷移する場合、次に移る遷移先アドレスを渡す
===================================================*/
cGameTrans* MainLoop::update(cGameTrans* Parent){
	/*=====================メイン処理を書いて============================*/
	if (GetKey->Press(DIK_LEFT)){
		pCamera->PointRotatMove(0.0f, 1.0f, 0.0f);
	}
	else if (GetKey->Press(DIK_RIGHT)){
		pCamera->PointRotatMove(0.0f, -1.0f, 0.0f);
	}
	else if (GetKey->Press(DIK_UP)){
		pCamera->PointRotatMove(1.0f, 0.0f, 0.0f);
	}
	else if (GetKey->Press(DIK_DOWN)){
		pCamera->PointRotatMove(-1.0f, 0.0f, 0.0f);
	}
	
	return this;	//状態遷移がなければ自分を返す
}

/*===================================================
//	描画処理
//	描画機能をここに書き込みめば自動で呼び出される
===================================================*/
void MainLoop::draw(){
	/*=================描画処理===================*/
	pCamera->Projection(GetD3DDevice);
	D3DXMATRIX buf;
	D3DXMatrixIdentity(&buf);
	pShader->Draw(&buf,pCamera->GetWorldMatrix(),pCamera->GetPrjMatrix());
	//pShader->Draw(&buf);
	/*===========================================*/
}

/*===================================================
//	初期化処理
//	ゲーム中で使用する変数はヘッダーで定義しここで初期化
===================================================*/
MainLoop::MainLoop(){
	pShader = new cMetalReflection();

	pCamera = new cCamera({ 0.0f, 10.0f, -10.0f }, { 0, 0, 0 }, { 0, 1, 0 });
}

/*===================================================
//	解放処理
//	ゲーム中で使用した変数はきっちり後片付けしましょうね！
===================================================*/
MainLoop::~MainLoop(){
	
}