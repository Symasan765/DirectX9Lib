/**
* @file Camera.h
* @brief カメラクラスの定義
* @author 松本雄之介
* @date 2016/12/26
*/
#ifndef INC_CAMERA_H
#define INC_CAMERA_H
#include "MatrixCoord.h"
#include <d3dx9.h>

/**
* @def MAXIMUM_MAGNIFICATION
* @brief 最大撮影倍率
*/
#define MAXIMUM_MAGNIFICATION (90)

/**
* @def MINIMUM_MAGNIFICATION
* @brief 最短撮影倍率
*/
#define MINIMUM_MAGNIFICATION (1)


/**
*	カメラクラス
*	座標位置は行列クラスが管理する
*/
class cCamera : public cMatrix{
public:
	cCamera(D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3);
	~cCamera();
	void Projection(const LPDIRECT3DDEVICE9);
	virtual void Scaling(const float);
	virtual void Rotation(const float, const float, const float);		//FPS回転
	void SetLookPos(D3DXVECTOR3);		//視点位置セット
	void PointRotatMove(const float, const float, const float);					//注視点を中心にした回転移動	TPS回転
	void PointRotatMove(const float, const float, const float, D3DXVECTOR3);	//指定の起点を中心にした回転移動
	D3DXVECTOR3 GetLookPos()const;
	D3DXVECTOR3 GetUpVect()const;
	D3DXVECTOR3 GetCameraPos()const;
	D3DXMATRIX* GetWorldMatrix();
private:
	void RotationAxisX(const D3DXVECTOR3&, const float);
	void RotationAxisY(const D3DXVECTOR3&, const float);
	void RotationAxisZ(const D3DXVECTOR3&, const float);
	D3DXVECTOR3 LookPt;		//!<　@brief 注視点
	D3DXVECTOR3 UpVect;		//!<　@brief カメラ上方向
	float AngleOfView;		//!<　@brief 画角
	float ViewScopeMax;		//!<　@brief 視野最大
	float ViewScopeMin;		//!<　@brief 視野最小
};



#endif