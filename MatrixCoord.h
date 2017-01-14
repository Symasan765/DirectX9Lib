/*=========================================================//
//		概要	:	行列計算を扱うクラス
//					作成者　松本 雄之介 (AT12A606)
//						作成日	2016/11/2
//					  更新日
//
//=========================================================*/
#ifndef INC_MATRIX_COORD_H
#define INC_MATRIX_COORD_H
#include <d3dx9.h>

//変換用行列
typedef struct{
	D3DXMATRIX mtxWorld;	//ワールド行列
	D3DXMATRIX mtxScale;	//拡大縮小行列
	D3DXMATRIX mtxRot;		//回転行列
	D3DXMATRIX mtxTrans;	//移動行列
}MATRIX3D;


class cMatrix{
public:
	cMatrix();
	virtual ~cMatrix() = default;
	/*===拡大縮小・移動・回転===*/
	virtual void Scaling(const float);
	virtual void Translation(const D3DXVECTOR3);
	virtual void Rotation(const float, const float, const float);
	/*===拡大縮小・移動・回転の初期化===*/
	virtual void SetScaling(const float);
	void SetRotate(const float, const float, const float);
	void SetTrans(const D3DXVECTOR3);
	/*===ワールド行列へ計算を行う(これ残すだろうか…)===*/
	void MatrixCalculation();
	/*===向いている方向への移動===*/
	virtual void VectMove(const float);
	/*===各行列のポインタ取得===*/
	virtual D3DXMATRIX* GetWorldMatrix();
	D3DXMATRIX* GetScaleMatrix();
	D3DXMATRIX* GetRotatMatrix();
	D3DXMATRIX* GetTransMatrix();
	D3DXVECTOR3 GetPosition()const;
protected:
	void OwnAxisRotateX(const float);			//任意軸回転X
	void OwnAxisRotateY(const float);			//任意軸回転Y
	void OwnAxisRotateZ(const float);			//任意軸回転Z

	MATRIX3D mtxDate;	//構造体群
};

#endif