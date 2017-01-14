#include "Texture_Class.h"
#include "GameManager.h"
#include <cmath>
#define PI (3.14159265)

/*===================================================
//	関数	:	テクスチャファイルを読み込むコンストラクタ
//	引数	:	fileNmae - 読み込むテクスチャファイル名
//				anmNo - アニメーション番号
//				widthNo - 横方向アニメーション数
//				heightNo - 縦方向アニメーション数
//	備考	:	anmeNo以降省略可。省略した場合はテクスチャ一枚全体が指定される
//				座標は設定されていないのでまた必ず設定する
===================================================*/
Texture2D::Texture2D(const char* fileName, const short anmNo, const unsigned char widthNo, const unsigned char heightNo){
	bool result = true;	//テクスチャを読めたか格納する
	pTex = nullptr;		//テクスチャは初期では使用しない

	//テクスチャを読み込み真偽を格納
	if (fileName)
		result = SUCCEEDED(D3DXCreateTextureFromFile(GetD3DDevice, fileName, &pTex));

	//正常に読めたらUV値設定
	if (result)
	{
		//テクスチャ番号、テクスチャ個数(縦横)から描画位置を割り出す
		const float offset_tu = (float)1 / widthNo;		//tuサイズ
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
	vx[0].z = vx[1].z = vx[2].z = vx[3].z = 0;

	//2Dフラグ
	vx[0].rhw = vx[1].rhw = vx[2].rhw = vx[3].rhw = 1;

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


	//中心座標設定(初期では座標設定されていないので中心を消去)
	center.x = NULL;
	center.y = NULL;

	uvReversFlag = true;
}


/*===================================================
//	関数	:	確保していたテクスチャを解放するデストラクタ		//
===================================================*/
Texture2D::~Texture2D(){
	pTex->Release();	//解放
	pTex = nullptr;	//安全のために
}


/*===================================================
//	関数	:	テクスチャを描画する関数						//
===================================================*/
void Texture2D::Draw() const{
	//テクスチャの有無で処理を分ける
	if (pTex){
		GetD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);	//色をつける(初期はコンストラクタにより白)
		//テクスチャ反転処理
		if (uvReversFlag){
			GetD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
			GetD3DDevice->SetTexture(0, pTex);
			GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX2D));
		}
		else{
			VERTEX2D buf[4];
			for (int i = 0; i < 4; i++){
				buf[i] = vx[i];
			}

			buf[0].tu = vx[1].tu;
			buf[0].tv = vx[1].tv;
			buf[1].tu = vx[0].tu;
			buf[1].tv = vx[0].tv;

			GetD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
			GetD3DDevice->SetTexture(0, pTex);
			GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX2D));
		}
		
	}
	else{
		GetD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);		//テクスチャなし
		GetD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vx, sizeof(VERTEX2D));
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
void Texture2D::SetPosition(const float baseX, const float baseY, const float sizeX, const float sizeY){
	//座標設定
	vx[0].x = baseX;
	vx[0].y = baseY;

	vx[1].x = baseX + sizeX;
	vx[1].y = baseY;

	vx[2].x = baseX + sizeX;
	vx[2].y = baseY + sizeY;

	vx[3].x = baseX;
	vx[3].y = baseY + sizeY;

	//中心座標設定
	center.x = (vx[1].x - vx[0].x) / 2 + vx[0].x;
	center.y = (vx[2].y - vx[0].y) / 2 + vx[0].y;
}


/*===================================================
//	関数	:	テクスチャファイルを読み込む関数
//	引数	:	anmNo - アニメーション番号
//				widthNo - 横方向アニメーション数
//				heightNo - 縦方向アニメーション数
//	備考	:	anmeNo以降省略可。省略した場合はテクスチャ一枚全体が指定される
===================================================*/
void Texture2D::SetTextureUV(short anmNo, const unsigned char widthNo, const unsigned char heightNo){
		anmNo %= widthNo * heightNo;

		//テクスチャ番号、テクスチャ個数(縦横)から描画位置を割り出す
		const float offset_tu_size = (float)1 / widthNo;			//tuサイズ
		const float offset_tv_size = (float)1 / heightNo;		//tvサイズ
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
void Texture2D::SetColor(D3DCOLOR DIF){
	vx[0].diffuse = vx[1].diffuse = vx[2].diffuse = vx[3].diffuse = DIF;
}

/*===================================================
//	関数	:	図形を回転させる関数
//	引数	:	angle - 回転角度(0 ~ 360)
===================================================*/
void Texture2D::Rotat(const float angle){
	//回転角度のラジアンを出しておく
	const float rad = static_cast<float>(angle * PI / 180.0f);

	//回転処理
	for (int i = 0; i < 4; ++i)
		RotatePrimitive(vx[i], center, rad);
}

/*===================================================
//	関数	:	図形を拡大・縮小する関数
//	引数	:	rate - 拡縮率(1.0 == 100%,0.0 == 0%)
===================================================*/
void Texture2D::Scale(const float rate){
	for (int i = 0; i < 4; ++i)
		ScalePrimitive(vx[i], center, rate);
}

/*===================================================
//	関数	:	移動処理を行う関数
//	引数	:	moveX - 横移動量,moveY - 縦移動量
===================================================*/
void Texture2D::Move(const float moveX, const float moveY){
	//各頂点を移動
	for (int i = 0; i < 4; ++i)
	{
		MovePrimitive(vx[i], moveX, moveY);
	}

	//最後に中心座標も移動
	center.x += moveX;
	center.y += moveY;
}


/*===================================================
//	関数	:	移動処理を行う関数
//	戻値	:	中心座標が返却
===================================================*/
POS2D Texture2D::GetCenter() const{
	return center;
}


/*============================================通常関数(外部に見せる必要なし)==========================================================*/

/*===================================================
//	関数	:	渡された座標を起点から回転する関数
//	引数	:	src - 回転する座標
base - 回転の起点(軸)
rad - ラジアン
===================================================*/
void Texture2D::RotatePrimitive(VERTEX2D& src, const POS2D base, const float rad){
	VERTEX2D buf = src;		//バッファ

	//回転処理
	src.x = ((buf.x - base.x) * cosf(rad) - (buf.y - base.y) * sinf(rad)) + base.x;
	src.y = ((buf.x - base.x) * sinf(rad) + (buf.y - base.y) * cosf(rad)) + base.y;
}


/*===================================================
//	関数	:	渡された座標を起点を中心に拡縮する関数
//	引数	:	src - 変更する頂点情報
//				base - 起点(中心)
rate - 拡大・縮小率(0.0 == 0%,1.0 == 100%)
===================================================*/
void Texture2D::ScalePrimitive(VERTEX2D& src, const POS2D base, const float rate){
	VERTEX2D buf = src;

	//拡大・縮小処理
	src.x = (buf.x - base.x) * rate + base.x;
	src.y = (buf.y - base.y) * rate + base.y;
}

/*===================================================
//	関数	:	頂点の移動を行う関数
//	引数	:	src - 変更する頂点
//				moveX - 横移動量
//				moveY - 縦移動量
===================================================*/
void Texture2D::MovePrimitive(VERTEX2D& src, const float moveX, const float moveY){
	src.x += moveX;
	src.y += moveY;
}

/*===================================================
//	関数	:	テクスチャをスクロールする関数
//	引数	:	moveU - 移動量U
//				moveV - 移動量V
===================================================*/
void Texture2D::TexUVScroll(const float moveU, const float moveV){
	for (int i = 0; i < 4; ++i){
		vx[i].tu += moveU;
		vx[i].tv += moveV;
	}
}