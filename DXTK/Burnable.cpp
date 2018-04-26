#include "pch.h"
#include "Burnable.h"


Burnable::Burnable(ID3D11DeviceContext1* _d3dContext, DirectX::SimpleMath::Matrix _world, DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj, int _width, int _height)
{
	//Initilizing of the Burnable object
	m_d3dContext = _d3dContext;
	m_world = _world;
	m_view = _view;
	m_proj = _proj;

	m_width = _width;
	m_height = _height;
	m_totalCubes = (m_width * m_height) * m_width;

	m_ignitRate = 60.f;

	srand(time(NULL));
	int x = 0, y = 0, z = 0;
	int iterator = 0;
	int ziter = 0;

	//Loop for creating the Burnable object
	for (auto i = 0; i < m_totalCubes; i++)
	{

		//Push back each new vortex cube into a vector
		m_vCubes.push_back(new VortexCube(m_d3dContext.Get(), m_world, m_view, m_proj, x, y, z, false));

		x += 1;
		iterator++;
		if (iterator == m_width)
		{
			iterator = 0;
			ziter++;
			z += 1;
			x = 0;
			if (ziter == m_height)
			{
				y -= 1;
				z = 0;
				ziter = 0;
			}
		}
	}
}


Burnable::~Burnable()
{
}

void Burnable::Update(DirectX::SimpleMath::Matrix _world, DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj)
{
	m_view = _view;
	//On L press execute random fire location
	if (GetAsyncKeyState('L'))
	{
		aBlaze = rand() % m_totalCubes;
		if (m_vCubes[aBlaze]->isAlive())
		{
			m_vCubes[aBlaze]->setFire(true);
		}

	}
	//Update all vortex cubes -- Optimization Required!
	for (auto i = 0; i < m_vCubes.size(); i++)
	{
		m_vCubes[i]->Update(m_world, m_view, m_proj);
	}
	SpreadFire();
}

void Burnable::Render()
{
	// Render vortex cubes
	for (auto i = 0; i < m_vCubes.size(); i++)
	{
		m_vCubes[i]->Render();
	}
}

void Burnable::SpreadFire()
{
	for (auto i = 0; i < m_vCubes.size(); i++)
	{
		if (m_vCubes[i]->onFire() && m_vCubes[i]->isAlive())
		{
			if (m_vCubes[i]->GetHealth() <= m_ignitRate && m_vCubes[i]->GetHealth() >= m_ignitRate - 2.f)
			{
				if (i + 1 != m_totalCubes)
				{
					if (m_vCubes[i + 1]->getPosX() > m_vCubes[i]->getPosX()) //-
					{
						m_vCubes[i + 1]->setFire(true);
					}
				} // Check if the cube to be ignited is on a suitable X axis (Front & Back)- & within scope
				if (i - 1 >= 0)
				{
					if (m_vCubes[i - 1]->getPosX() < m_vCubes[i]->getPosX()) //-
					{
						m_vCubes[i - 1]->setFire(true);
					}
				}

				if (i + m_width <= m_totalCubes - 1)
				{
					if (m_vCubes[i + m_width]->getPosZ() > m_vCubes[i]->getPosZ()) //--
					{
						m_vCubes[i + m_width]->setFire(true);
					}
				} // Check if the cube to be ignited is on a suitable Z axis (Left & Right)-- & within scope
				if (i - m_width >= 0)
				{
					if (m_vCubes[i - m_width]->getPosZ() < m_vCubes[i]->getPosZ()) //--
					{
						m_vCubes[i - m_width]->setFire(true);
					}
				}

				if (i + (m_width * m_height) <= m_totalCubes - 1)
				{
					if (m_vCubes[i + (m_width * m_height)]->getPosY() < m_vCubes[i]->getPosY()) //---
					{
						m_vCubes[i + (m_width * m_height)]->setFire(true);
					}
				} // Check if the cube to be ignited is on a suitable Y axis (Top & Bot)--- & within scope
				if (i - (m_width * m_height) >= 0)
				{
					if (m_vCubes[i - (m_width * m_height)]->getPosY() > m_vCubes[i]->getPosY()) //---
					{
						m_vCubes[i - (m_width * m_height)]->setFire(true);
					}
				}
			}
		}
	}
}

void Burnable::Clear()
{
	for (auto i = 0; i < m_vCubes.size(); i++)
	{
		m_vCubes[i]->Clear();
	}
}
