#ifndef INC_DRAW_CLASS_H
#define INC_DRAW_CLASS_H

#include <d3dx9.h>
#include <Windows.h>

class cDraw{
public:
	virtual void Draw(D3DXMATRIX);
	float PositionZ;
};

#endif