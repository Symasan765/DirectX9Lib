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
	pTex->SetColor(pLight->GetLightColor());
	return this;	//状態遷移がなければ自分を返す
}

/*===================================================
//	描画処理
//	描画機能をここに書き込みめば自動で呼び出される
===================================================*/
void MainLoop::draw(){
	/*=================描画処理===================*/
	pLight->DayNightUpdate(30);
	pLight->InitLight();
	pCamera->Projection(GetD3DDevice);

	pTex->Draw(pCamera->GetCameraPos(), pCamera->GetLookPos(), pCamera->GetUpVect());
	pDate->Draw(pDate->GetWorldMatrix());
	
	/*===========================================*/
}

/*===================================================
//	初期化処理
//	ゲーム中で使用する変数はヘッダーで定義しここで初期化
===================================================*/
MainLoop::MainLoop(){
	pDate = new cModel3D;
	pDate->LoadFile("MODEL/F15.x");

	//pSky = new cModel3D;
	//pSky->LoadFile("MODEL/Dome_Y301.x");

	pCamera = new cCamera({ -10, 5, 10 }, { 0, 0, 0 }, { 0, 1, 0 });

	pLight = new cLight;

	pTex = new cBillboard(new Texture3D("IMAGE/Sky.jpg"));
	pTex->SetTexSize(640, 360);
	pTex->SetTrans({ 100, -50, -100 });
}

/*===================================================
//	解放処理
//	ゲーム中で使用した変数はきっちり後片付けしましょうね！
===================================================*/
MainLoop::~MainLoop(){
	delete pDate;
	delete pCamera;
	delete pLight;
	delete pTex;
}