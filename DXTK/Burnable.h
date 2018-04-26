#pragma once
#include <vector>
#include <d3d11.h>
#include <random>
#include <time.h>
#include "GeometricPrimitive.h"
#include "SimpleMath.h"
#include "VortexCube.h"

class Burnable
{
public:
	Burnable(ID3D11DeviceContext1*, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix, int, int);
	~Burnable();

	void Update(DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix);
	void Render();
	void SpreadFire();

	void Clear();

protected:
	std::vector<VortexCube*> m_vCubes;

private:
	int aBlaze;
	int m_width;
	int m_height;
	int m_totalCubes;
	
	float m_ignitRate;

	bool onFire = false;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;
};

