#pragma once
#include <vector>
#include <d3d11.h>
#include <random>
#include <time.h>
#include "GeometricPrimitive.h"
#include "SimpleMath.h"
class VortexCube
{
public:
	VortexCube(ID3D11DeviceContext1*, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix, int, int, int, bool);
	~VortexCube();

	void Update(DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix, DirectX::SimpleMath::Matrix);
	void Render();
	void Clear();

	void setFire(bool);

	bool onFire();
	bool isAlive();

	int getPosX();
	int getPosY();
	int getPosZ();

	float GetHealth();
private:
	
	float m_fuel;
	float m_mass;
	float m_heatRate;
	float r = 0.f, g = 0.f, b = 0.f;

	int m_PosX, m_PosY, m_PosZ;

	bool m_alive;
	bool m_onFire;

	std::unique_ptr<DirectX::GeometricPrimitive> m_shape;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
};

