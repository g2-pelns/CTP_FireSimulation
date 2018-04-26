#pragma once

#include <d3d11.h>
#include "SimpleMath.h"
#include "GameData.h"
#include "GameObject.h"

using namespace DirectX::SimpleMath;

class Camera
{
public:
	Camera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance);
	~Camera();

	void Tick(GameData* _GD);
	void Update(Matrix _viewMat);
	void UpdateMovement();

	//Getters
	Matrix GetProj() { return m_projMat; }
	Matrix GetView() { return m_viewMat; }
	Matrix GetWorldMatrix() { return m_worldMat; }

protected:

	//Principle transforms/matrices for this camera
	Matrix m_projMat;
	Matrix m_viewMat;
	Matrix m_worldMat;

	//parameters for setting up a camera
	float m_fieldOfView;
	float m_aspectRatio;
	float m_nearPlaneDistance;
	float m_farPlaneDistance;

	XMFLOAT4 m_target = XMFLOAT4(0.1f,0.1f,0.1f,0.1f);
	XMFLOAT4 m_up = XMFLOAT4(0.0f, 10.0f, 0.0f, 0.0f);
	XMFLOAT4 m_pos = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
	XMFLOAT3 m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

};