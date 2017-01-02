#include "Main.h"
#include "GameManager.h"
#include "Camera.h"
#include "Light.h"
#include <ctime>
#include "Input.h"


/*===================================================
//	メイン処理
//	引数	一つ前の遷移クラスのポインタが渡される
//	戻値	遷移する場合、次に移る遷移先アドレスを渡す
===================================================*/
cGameTrans* MainLoop::update(cGameTrans* Parent){
	/*=====================メイン処理を書いて============================*/
	if (GetKey->Press(DIK_UP))
		pCamera->PointRotatMove(1.0f, 0.0f, 0.0f);
	if (GetKey->Press(DIK_DOWN))
		pCamera->PointRotatMove(-1.0f, 0.0f, 0.0f);
	if (GetKey->Press(DIK_LEFT))
		pCamera->PointRotatMove(0.0f, 1.0f, 0.0f);
		//pCamera->PointRotatMove(0.0f, 1.0f, 0.0f);
	if (GetKey->Press(DIK_RIGHT))
		pCamera->PointRotatMove(0.0f, -1.0f, 0.0f);

	if (GetKey->Press(DIK_RETURN))
		pCamera->PointRotatMove(0.0f, 0.0f, 1.0f);

	draw();		//描画は散らかるからdrawに書いてね
	return this;	//状態遷移がなければ自分を返す
}

/*===================================================
//	描画処理
//	描画機能をここに書き込み、Updateで呼び出せばOK
===================================================*/
void MainLoop::draw(){
	DrawBegine();	//あらかじめBegineと…

	/*=================描画処理===================*/
	pLight->InitLight();
	pCamera->Projection(GetD3DDevice);
	imaage->Draw();
	//いらない処理
	D3DXMATRIX wld;
	D3DXMatrixIdentity(&wld);
	pTex->Draw(pCamera->GetCameraPos(),pCamera->GetLookPos(),pCamera->GetUpVect());

	
	
	/*===========================================*/

	DrawEnd();		//Endを書いておくとその間に処理を書けば済むよ！
}

/*===================================================
//	初期化処理
//	ゲーム中で使用する変数はヘッダーで定義しここで初期化
===================================================*/
MainLoop::MainLoop(){
	srand((unsigned)time(NULL));
	pCamera = new cCamera({ 100.0f, 0.0f, -20.0f }, { 100, 0, 0 }, { 0, 1, 0 });		//カメラ
	
	pTex = new cBillboard(new Texture3D("004.jpg"));
	pTex->SetTexSize(10.0f, 10.0f);
	pTex->Translation({ 100.0f, 0.0f, 0.0f });

	imaage = new cImage3D(new Texture3D("004.jpg"));
	imaage->SetTexSize(10.0f, 10.0f);
	imaage->Translation({ 100.0f, 0.0f, 10.0f });

	pLight = new cLight;
}

/*===================================================
//	解放処理
//	ゲーム中で使用した変数はきっちり後片付けしましょうね！
===================================================*/
MainLoop::~MainLoop(){
	delete pCamera;
	pCamera = nullptr;

	delete pLight;
	pLight = nullptr;

	delete pTex;
	pTex = nullptr;
}