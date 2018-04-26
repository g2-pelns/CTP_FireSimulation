#include "pch.h"
#include "VortexCube.h"


VortexCube::VortexCube(ID3D11DeviceContext1* _d3dContext, DirectX::SimpleMath::Matrix _world, DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj, int _x, int _y, int _z, bool _fire)
{
	m_alive = true;

	//Apply random fuel amount (80 - 100)
	m_fuel = rand() % 21 + 80;

	//Change heatRate to .0 decimal place (.4 - .6)
	m_heatRate = rand() % 7 + 4;
	m_heatRate = m_heatRate / 10;

	m_world = _world;
	m_view = _view;
	m_proj = _proj;

	m_PosX = _x;
	m_PosY = _y;
	m_PosZ = _z;

	m_onFire = _fire;
	m_d3dContext = _d3dContext;

	m_shape = DirectX::GeometricPrimitive::CreateCube(m_d3dContext.Get());
	m_world.Translation(DirectX::SimpleMath::Vector3(m_PosX, m_PosY, m_PosZ));
}

VortexCube::~VortexCube()
{

}

void VortexCube::Update(DirectX::SimpleMath::Matrix _world, DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj)
{
	m_view = _view;
	if (m_onFire)
	{
		if (r < 1.f)
		{
			r += 0.01f;
		}
		else
		{
			r = 1.f;
			g += 0.01f;
			b += 0.01f;
		}
		m_fuel -= m_heatRate;
	}

	if (m_fuel < 0.f)
	{
		m_alive = false;
	}
}

void VortexCube::Render()
{
	if (m_alive)
	{
		m_shape->Draw(m_world, m_view, m_proj, DirectX::SimpleMath::Color(r, g, b), nullptr, true);
	}
}

void VortexCube::Clear()
{
	m_shape.reset();
}

void VortexCube::setFire(bool _state)
{
	m_onFire = _state;
}

bool VortexCube::isAlive()
{
	return m_alive;
}

int VortexCube::getPosX()
{
	return m_PosX;
}

int VortexCube::getPosY()
{
	return m_PosY;
}

int VortexCube::getPosZ()
{
	return m_PosZ;
}

bool VortexCube::onFire()
{
	return m_onFire;
}

float VortexCube::GetHealth()
{
	return m_fuel;
}
