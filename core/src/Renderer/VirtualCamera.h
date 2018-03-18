/* 
 *  VisApp source file  
 *
 *  Release version: 1.1 December 2014
 *  File: VisApp/core/src/Renderer/VirtualCamera.h
 *  Author: Paweu
 *  Header Date: Sun Dec  7 18:03:47 GMT 2014
 *
 */
/*--END OF HEADER BLOCK--*/
#pragma once
#ifndef VirtualCamera_H
#define VirtualCamera_H

namespace VisApp {
namespace Renderer { 
 
class VirtualCamera {
public:
	VirtualCamera();
	~VirtualCamera();

	void UpdateMatrix();

	const glm::mat4& GetWorldMatrix() const { return m_WorldMatrix; }

//Core::iCamera implementation
	void SetPosition(const Math::fvec3 &Pos, bool DoUpdate = false);
	void SetLookAtPoint(const Math::fvec3 &Pos, bool DoUpdate = false);
	void MoveCamera(const Math::fvec3 &Pos);		
	void Orbit(const Math::fvec2 &Angles, bool DoAdd = true);
	void Magnify(float value);
	void SetOrthogonalMode();
	void SetPerspectiveMode();

	void Reset();

	void SetView(unsigned Width, unsigned Height);

	bool UsePerspective() const { return m_UserPerspective; }

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetLookPoint() const { return m_LookPoint; }

	DefineRWAcces(OrbitAngle, glm::vec3)
private:
	void SetPerspective(float Aspect, float FoV = 45.0f, float Near = 0.1f, float Far = 10000.0f);
	void SetOrthogonal(float Width, float Height);

	bool m_UserPerspective;

	glm::vec3 m_Position;
	glm::vec3 m_LookPoint;
	glm::vec3 m_OrbitAngle;
	glm::vec3 m_UpVector;
//single projection matrix, to avoid unnecessary recalculation of it.
	glm::mat4 m_ProjectionMatrix;
//combined projection and view matrix. transforms from model space to camera space.
	glm::mat4 m_WorldMatrix;
};

} //namespace Renderer
} //namespace VisApp

#endif
