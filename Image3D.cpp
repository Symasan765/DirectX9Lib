/*=========================================================//
//		概要	:	3D空間上で使用する画像クラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/10
//					  更新日
//
//=========================================================*/
#include "Image3D.h"
#include "GameManager.h"

#define PI (3.14159)
void RotatePrimitive(VERTEX3D&, const COORD, const float);
void ScalePrimitive(VERTEX3D&, const COORD, const float);
void MovePrimitive(VERTEX3D&, const float, const float);

/*===================================================
//	関数	:	テクスチャファイルを読み込むコンストラクタ
//	引数	:	fileNmae - 読み込むテクスチャファイル名
//				anmNo - アニメーション番号
//				widthNo - 横方向アニメーション数
//				heightNo - 縦方向アニメーション数
//	備考	:	anmeNo以降省略可。省略した場合はテクスチャ一枚全体が指定される
//				座標は設定されていないのでまた必ず設定する
===================================================*/
Texture3D::Texture3D(const char* fileName, const short anmNo, const unsigned char widthNo, const unsigned char heightNo)
{
	bool result = true;	//テクスチャを読めたか格納する
	pTex = nullptr;		//テクスチャは初期では使用しない

	//テクスチャを読み込み真偽を格納
	if (fileName)
		result = SUCCEEDED(D3DXCreateTextureFromFile(GetD3DDevice, fileName, &pTex));

	//正常に読めたらUV値設定
	if (result)
	{
		//テクスチャ番号、テクスチャ個数(縦横)から描画位置を割り出す
		const float offset_tu = (float)1 / widthNo;			//tuサイズ
		const float offset_tv = (float)1 / heightNo;		//tvサイズ
		const unsigned char xNo = anmNo % widthNo;
		const unsigned char yNo = anmNo / widthNo;

		//実際にUVへ格納
		vx[0].tu = xNo * offset_tu;
		vx[0].tv = yNo * offset_tv;

		vx[1].tu = xNo * offset_tu + offset_tu;
		vx[1].tv = yNo * offset_tv;

		vx[2].tu = xNo * offset_tu + offset_tu;
		vx[2].tv = yNo * offset_tv + offset_tv;

		vx[3].tu = xNo * offset_tu;
		vx[3].tv = yNo * offset_tv + offset_tv;
	}
	else
		result = false;


	//Z座標クリア
	vx[0].z = vx[1].z = vx[2].z = vx[3].z = NULL;

	//カラー情報初期値
	vx[0].diffuse = vx[1].diffuse = vx[2].diffuse = vx[3].diffuse = D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF);

	//座標設定(とりあえず全てNULL)
	vx[0].x = NULL;
	vx[0].y = NULL;

	vx[1].x = NULL;
	vx[1].y = NULL;

	vx[2].x = NULL;
	vx[2].y = NULL;

	vx[3].x = NULL;
	vx[3].y = NULL;
}

/*===================================================
//	関数	:	確保していたテクスチャを解放するデストラクタ		//
===================================================*/
Texture3D::~Texture3D()
{
	pTex->Release();	//解放
	pTex = nullptr;	//安全のために
}

/*===================================================
//	関数	:	テクスチャを描画する関数						//
===================================================*/
void Texture3D::Draw(D3DXMATRIX* mtx){
	GetD3DDevice->SetTransform(D3DTS_WORLD, mtx);
	// ライティングモードをOFF
	GetD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	//テクスチャの有無で処理を分ける
	if (pTex)
	{
		GetD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		GetD3DDevice->SetTexture(0, pTex);
		GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX3D));
	}
	else
	{
		//GetD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);		//テクスチャなし
		//GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX3D));
	}
}


/*===================================================
//	関数	:	座標を設定する関数
//	引数	:	baseX - 左上座標X
//				baseY - 左上座標Y
//				sizeX - 大きさ(横方向)
//				sizeY - 大きさ（縦方向）
//	備考	:	頂点番号は0が左上スタートで時計周り設定(将来的に変更)
===================================================*/
void Texture3D::SetSize(const float sizeX, const float sizeY){

	//座標設定
	vx[0].x = -sizeX / 2;
	vx[0].y = sizeY / 2;

	vx[1].x = sizeX / 2;
	vx[1].y = sizeY / 2;

	vx[2].x = sizeX / 2;
	vx[2].y = -sizeY / 2;

	vx[3].x = -sizeX / 2;
	vx[3].y = -sizeY / 2;
}

/*===================================================
//	関数	:	テクスチャファイルを読み込む関数
//	引数	:	anmNo - アニメーション番号
//				widthNo - 横方向アニメーション数
//				heightNo - 縦方向アニメーション数
//	備考	:	anmeNo以降省略可。省略した場合はテクスチャ一枚全体が指定される
===================================================*/
void Texture3D::SetTextureUV(short anmNo, const unsigned char widthNo, const unsigned char heightNo){
	anmNo %= widthNo * heightNo;

	//テクスチャ番号、テクスチャ個数(縦横)から描画位置を割り出す
	const float offset_tu_size = (float)1 / widthNo;			//tuサイズ
	const float offset_tv_size = (float)1 / heightNo;			//tvサイズ
	const unsigned char xNo = anmNo % widthNo;
	const unsigned char yNo = anmNo / widthNo;

	//実際にUVへ格納
	vx[0].tu = xNo * offset_tu_size;
	vx[0].tv = yNo * offset_tv_size;

	vx[1].tu = xNo * offset_tu_size + offset_tu_size;
	vx[1].tv = yNo * offset_tv_size;

	vx[2].tu = xNo * offset_tu_size + offset_tu_size;
	vx[2].tv = yNo * offset_tv_size + offset_tv_size;

	vx[3].tu = xNo * offset_tu_size;
	vx[3].tv = yNo * offset_tv_size + offset_tv_size;
}

/*===================================================
//	関数	:	ポリゴンの色を変更する関数
//	引数	:	DIF - 表示する色(RGB 0 ~ 255)
//	備考	:	全ての頂点が同じ色になる
===================================================*/
void Texture3D::SetColor(D3DCOLOR DIF)
{
	vx[0].diffuse = vx[1].diffuse = vx[2].diffuse = vx[3].diffuse = DIF;
}


/*============================================通常関数==========================================================*/

/*===================================================
//	関数	:	渡された座標を起点から回転する関数
//	引数	:	src - 回転する座標
base - 回転の起点(軸)
rad - ラジアン
===================================================*/
void RotatePrimitive(VERTEX3D& src, const COORD base, const float rad)
{
	VERTEX3D buf = src;		//バッファ

	//回転処理
	src.x = ((buf.x - base.X) * cosf(rad) - (buf.y - base.Y) * sinf(rad)) + base.X;
	src.y = ((buf.x - base.X) * sinf(rad) + (buf.y - base.Y) * cosf(rad)) + base.Y;
}


/*===================================================
//	関数	:	渡された座標を起点を中心に拡縮する関数
//	引数	:	src - 変更する頂点情報
//				base - 起点(中心)
rate - 拡大・縮小率(0.0 == 0%,1.0 == 100%)
===================================================*/
void ScalePrimitive(VERTEX3D& src, const COORD base, const float rate)
{
	VERTEX3D buf = src;

	//拡大・縮小処理
	src.x = (buf.x - base.X) * rate + base.X;
	src.y = (buf.y - base.Y) * rate + base.Y;
}

/*===================================================
//	関数	:	頂点の移動を行う関数
//	引数	:	src - 変更する頂点
//				moveX - 横移動量
//				moveY - 縦移動量
===================================================*/
void MovePrimitive(VERTEX3D& src, const float moveX, const float moveY)
{
	src.x += moveX;
	src.y += moveY;
}

void Texture3D::ScrollUV(const float moveU, const float moveV){
	vx[0].tu += moveU;
	vx[0].tv += moveV;

	vx[1].tu += moveU;
	vx[1].tv += moveV;

	vx[2].tu += moveU;
	vx[2].tv += moveV;

	vx[3].tu += moveU;
	vx[3].tv += moveV;
}

Texture3D* cImage3D::GetTexture(){
	return pTex;
}

void cImage3D::SetTexSize(const float sizeX, const float sizeY){
	if (pTex)
		pTex->SetSize(sizeX, sizeY);
}

void cImage3D::Draw(){
	if (pTex){
		MatrixCalculation();
		pTex->Draw(GetWorldMatrix());
	}
}

cImage3D::cImage3D(Texture3D* texture){
	if (!pTex)
		delete pTex;

	pTex = texture;
}
cImage3D::~cImage3D(){
	if (pTex){
		delete pTex;
		pTex = nullptr;
	}
}

//void Texture3D::SetBillboard(D3DXVECTOR3 LookVct, D3DXVECTOR3 UpVct){
//	D3DXMatrixIdentity(&Inv);
//	D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0, 0, 0), &LookVct, &UpVct);
//	D3DXMatrixInverse(&Inv, NULL, &Inv);
//
//	if (BillBoardFlg == false){
//		for (int i = 0; i < 4; i++){
//			vx[i].y = vx[i].z;	//縦方向に立たせる
//			vx[i].z = 0;
//		}
//		BillBoardFlg = true;
//	}
//}