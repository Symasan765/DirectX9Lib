#include "BillBoard.h"
#include "Input.h"
cBillboard::cBillboard(Texture3D* texture) : cImage3D(texture){

}

cBillboard::~cBillboard(){

}

void cBillboard::Draw(D3DXMATRIX* wMtx){
	/*D3DXMATRIX Inv = *wMtx;
	Inv._41 = 1;
	Inv._42 = 1;
	Inv._43 = 1;
	D3DXMatrixInverse(&mtxDate.mtxWorld, NULL, &Inv);*/

	mtxDate.mtxWorld *= mtxDate.mtxTrans;
	
	pTex->Draw(GetWorldMatrix());
}