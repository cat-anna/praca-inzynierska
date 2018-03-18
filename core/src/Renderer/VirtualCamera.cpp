/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/VirtualCamera.cpp
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#include "stdafx.h"
#include "nRenderer.h"
#include <glm/glm/gtc/matrix_transform.hpp>

#ifdef DEBUG_VCAMERA
#define __LOG_ACTION_Debug_vcamera(A, T)			__LOG_ACTION_Debug(A, T)
#else
#define __LOG_ACTION_Debug_vcamera(A, T) 
#endif

namespace VisApp {
namespace Renderer { 
 
VirtualCamera::VirtualCamera() {
	SetPerspectiveMode();
	Reset();
}

VirtualCamera::~VirtualCamera() {
}

void VirtualCamera::SetOrthogonalMode() {
	m_UserPerspective = false;
	Renderer::Device()->ResetCamera(this);
	Renderer::Instance()->CenterView(NULL);
}

void VirtualCamera::SetPerspectiveMode() {
	m_UserPerspective = true;
	Renderer::Device()->ResetCamera(this);
	Renderer::Instance()->CenterView(NULL);
}

void VirtualCamera::UpdateMatrix() {
	if(m_UserPerspective) {
		glm::mat4 ViewMatrix = glm::lookAt(m_Position, m_LookPoint, m_UpVector);
		m_WorldMatrix =  m_ProjectionMatrix * ViewMatrix;
		AddLog(Debug_vcamera, "Camera perspective update  pos:" << m_Position << " look:" << m_LookPoint << " orbit:" << m_OrbitAngle);
	} else {
		glm::mat4 tmp = glm::scale(m_ProjectionMatrix, Math::fvec3(m_OrbitAngle[2], m_OrbitAngle[2], 0));
		m_WorldMatrix = glm::translate(tmp, m_Position);
		AddLog(Debug_vcamera, "Camera ortho update  pos:" << m_Position << " orbit:" << m_OrbitAngle);
	}
} 

void VirtualCamera::SetView(unsigned Width, unsigned Height) {
	Reset();
	if(m_UserPerspective)
		SetPerspective((float)Width / (float)Height);
	else
		SetOrthogonal((float)Width, (float)Height);
}

void VirtualCamera::SetPerspective(float Aspect, float FoV, float Near, float Far) {
	m_ProjectionMatrix = glm::perspective(FoV, Aspect, Near, Far);
	UpdateMatrix();
}

void VirtualCamera::SetOrthogonal(float Width, float Height) {
	Width /= 2.0f;
	Height /= 2.0f;
	m_ProjectionMatrix = glm::ortho(-Width, Width, Height, -Height);
	UpdateMatrix();
}
	
void VirtualCamera::Reset() {
	m_Position = Math::fvec3(0, 0, 0);
	m_LookPoint = Math::fvec3(0, 0, 0);
	m_UpVector = Math::fvec3(0, 0, 1);

	if(m_UserPerspective)
		m_OrbitAngle = Math::fvec3(0, 0, 5);
	else
		m_OrbitAngle = Math::fvec3(0, 0, 0);

	Orbit(Math::fvec2(m_OrbitAngle), false);
}

//----

void VirtualCamera::SetPosition(const Math::fvec3 &Pos, bool DoAdd) {
	if(DoAdd)
		m_Position += Pos;
	else
		m_Position = Pos;
	UpdateMatrix();
}

void VirtualCamera::SetLookAtPoint(const Math::fvec3 &Pos, bool DoAdd) {
	if(DoAdd)
		m_LookPoint += Pos;
	else
		m_LookPoint = Pos;
	UpdateMatrix();
}

void VirtualCamera::MoveCamera(const Math::fvec3 &Pos) {
	m_Position += Pos;
	m_LookPoint += Pos;
	UpdateMatrix();
}	

void VirtualCamera::Orbit(const Math::fvec2 &Angles, bool DoAdd) {
	if(!m_UserPerspective) return;
	if(DoAdd){
		m_OrbitAngle[0] += Angles[0];
		m_OrbitAngle[1] += Angles[1];
	} else {
		m_OrbitAngle[0] = Angles[0];
		m_OrbitAngle[1] = Angles[1];
	}

	float ox = -m_OrbitAngle[0];
	float oy = -m_OrbitAngle[1];
	float dist = -m_OrbitAngle[2];

	glm::vec3 direction(
		cos(oy) * sin(ox), 
		sin(oy),
		cos(oy) * cos(ox)
	);

	glm::vec3 right = glm::vec3(
		sin(ox - 3.14f/2.0f), 
		0,
		cos(ox - 3.14f/2.0f)
	);
	
	m_UpVector = glm::cross( right, direction );
	m_Position = m_LookPoint + direction * dist;

	UpdateMatrix();
}

void VirtualCamera::Magnify(float value) {
	m_OrbitAngle[2] += value;
	if(m_OrbitAngle[2] <= 0)
		m_OrbitAngle[2] = 0.01f;
	if(m_UserPerspective)
		Orbit(Math::fvec2(m_OrbitAngle), false);
	else
		UpdateMatrix();
}

} //namespace Renderer
} //namespace VisApp
