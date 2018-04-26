#include "pch.h"
#include "Camera.h"

Camera::Camera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance)
{
	m_worldMat = Matrix::Identity;

	m_pos = XMFLOAT4(50.0f, 25.0f, 50.0f, 0.0f);

	m_fieldOfView = _fieldOfView;
	m_aspectRatio = _aspectRatio;
	m_nearPlaneDistance = _nearPlaneDistance;
	m_farPlaneDistance = _farPlaneDistance;

	m_projMat = Matrix::CreatePerspectiveFieldOfView(m_fieldOfView, m_aspectRatio, m_nearPlaneDistance, m_farPlaneDistance);
}

Camera::~Camera()
{
}

void Camera::Update(Matrix _viewMat)
{
	m_viewMat = _viewMat;
	UpdateMovement();
}

void Camera::Tick(GameData* _GD)
{
}

void Camera::UpdateMovement()
{
	// Get Datas
	XMVECTOR cUp = XMLoadFloat4(&m_up);
	XMVECTOR cPos = XMLoadFloat4(&m_pos);
	XMVECTOR cTarg = XMLoadFloat4(&m_target);

	//Apply Y Rotate
	XMMATRIX rotYMat = XMMatrixRotationAxis(cUp, m_rotation.y);
	cTarg = XMVector4Transform(cTarg, rotYMat);

	//Apply Z Rotate
	XMMATRIX rotZMat = XMMatrixRotationAxis(cTarg, m_rotation.z);
	cUp = XMVector4Transform(cUp, rotZMat);

	//Calculate the vector wich follow X in camera relative space ( cUp is Y and cTarg is Z in this space)
	XMVECTOR xvect = XMVector3Cross(cTarg, cUp);

	//Apply X Rotate
	XMMATRIX rotXMat = XMMatrixRotationAxis(xvect, m_rotation.x);
	cUp = XMVector4Transform(cUp, rotXMat);
	cTarg = XMVector4Transform(cTarg, rotXMat);

	//Move Up and bottom
	if (GetAsyncKeyState('Q')) {
		cPos += XMVector3Normalize(cUp) / 50.0f;
	}
	else if (GetAsyncKeyState('E')) {
		cPos -= XMVector3Normalize(cUp) / 50.0f;
	}

	//Move Left and Right
	if (GetAsyncKeyState(VK_LEFT)) {
		cPos += XMVector3Normalize(xvect) / 10.0f;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		cPos -= XMVector3Normalize(xvect) / 10.0f;
	}

	//Rotate on Y Axis (Looking Left or Right)
	if (GetAsyncKeyState('D')) {
		m_rotation.y -= 0.01f;

	}
	else if (GetAsyncKeyState('A')) {
		m_rotation.y += 0.01f;
	}

	// Rotate On Z Axis (Spin camera Anticlockwise or Clockwise)
	if (GetAsyncKeyState('Z')) {
		m_rotation.z -= 0.01f;
	}
	else if (GetAsyncKeyState('X')) {
		m_rotation.z += 0.01f;
	}

	//Rotate on X Axis (Looking up or down)
	if (GetAsyncKeyState('W')) {
		m_rotation.x -= 0.01f;

	}
	else if (GetAsyncKeyState('S')) {
		m_rotation.x += 0.01f;
	}

	//Move Backward/Forward
	if (GetAsyncKeyState(VK_DOWN)) {
		cPos += XMVector3Normalize(cTarg) / 10.0f;
	}
	else if (GetAsyncKeyState(VK_UP)) {
		cPos -= XMVector3Normalize(cTarg) / 10.0f;
	}
	//Update position
	XMStoreFloat4(&m_pos, cPos);

	//Generate View Matrix of Camera
	XMMATRIX ViewMatrix = XMMatrixLookToLH(cPos, cTarg, cUp);
	XMStoreFloat4x4(&m_viewMat, ViewMatrix);
}
