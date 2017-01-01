///*=========================================================//
////		概要	:	カメラクラス用ヘッダー
////					作成者　松本 雄之介 (AT12A606)
////						作成日　2016/10/20
////					  更新日
////
////			カメラを定義するヘッダーファイル
////=========================================================*/
//#ifndef INC_CAMERA_CLASS_H
//#define INC_CAMERA_CLASS_H
//
//#define MAXIMUM_MAGNIFICATION (90)		//最大撮影倍率
//#define MINIMUM_MAGNIFICATION (1)			//最短撮影倍率
//
//
//#include <d3dx9.h>
////座標3D用
//typedef struct{
//	float x, y, z;
//}COORD3D;
//
//
////カメラ位置クラス
////	カメラ座標セット
////	カメラ移動ムーブ
//class cCameraP{
//public:
//	cCameraP();
//	~cCameraP();
//	void Set(const float,const float,const float);
//	void Move(const float,const float,const float);
//	D3DXVECTOR3 cP;
//private:
//	bool ellor;
//};
//
////カメラ
////	カメラ視認位置クラス
////	視認位置セット
////	視認位置ムーブ
//class cCameraR{
//public:
//	cCameraR();
//	~cCameraR();
//	void Set(const float, const float, const float);
//	void Move(const float, const float, const float);
//	D3DXVECTOR3 cR;	//見ている位置
//private:
//	bool ellor;
//};
//
////カメラ傾斜クラス
////	リセット
////	カメラ傾斜
//class cCameraU{
//public:
//	cCameraU();
//	~cCameraU();
//	void Set(const float, const float, const float);
//	D3DXVECTOR3 cU;
//private:
//	bool ellor;
//};
//
////カメラ構造体
//typedef struct{
//	cCameraP cameraP;
//	cCameraR cameraR;
//	cCameraU cameraU;
//	float AngleOfView;		//画角
//	float ViewScopeMax;		//視野最大
//	float ViewScopeMin;		//視野最小
//}CameraMnj;
//
//typedef struct{
//	D3DXMATRIX mtxWorld;
//	D3DXMATRIX mtxScale;
//	D3DXMATRIX mtxRot;
//	D3DXMATRIX mtxTrans;
//}CAMERA_MATRIX;
//
////カメラ用構造体を定義
//class cCamera{
//public:
//	cCamera();
//	~cCamera();
//	//セット系関数
//	void SetCamera(COORD3D, COORD3D, COORD3D);						//カメラ初期設定
//	void Projection(const LPDIRECT3DDEVICE9);						//カメラ設定
//	void scaling(const float);
//	void translation(const float, const float, const float);		//平行移動
//	void rotation(const float, const float, const float);			//視点を起点にした回転
//	void rotation(D3DXMATRIX);											//回転
//	void PovUpVectorRotat(D3DXMATRIX);								//カメラの上方向を回転
//	void PovBaseXRotation(const float);
//	void SetLookPos(D3DXMATRIX);										//視点位置セット
//	void SetLookPos(const float, const float, const float);		//視点位置セット
//	D3DXVECTOR3 GetLookVector()const;								//視点位置取得
//	D3DXVECTOR3 GetpUpVector()const;									//カメラ上方向取得
//	D3DXMATRIX* GetWorldMtx();
//private:
//	void WorldMatrixCalcu();
//	void MtxInit(D3DXMATRIX*);
//	CAMERA_MATRIX mtxCamera;
//	CameraMnj machine;
//	bool ellor;
//};
//
//
//
//
//
//#endif