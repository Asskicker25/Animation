#pragma once

#include "Debugger.h"
#include "Transform.h"
#include "EntityManager/Entity.h"

enum ECameraType
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class Camera : public Entity
{
private:
	ECameraType cameraType;
	float cameraWidth;
	float cameraHeight;
	float nearPlane;
	float farPlane;
	float fov;

	glm::mat4 cameraMatrix;


	void SetCameraProjection();

public:

	Camera();
	Camera(ECameraType _cameraType, float _cameraWidth, float _cameraHeight, float _nearPlane, float _farPlane, float _fov);
	Camera(ECameraType _cameraType, float _cameraWidth, float _cameraHeight, float _nearPlane, float _farPlane);
	void InitializeCamera(ECameraType _cameraType, float _cameraWidth, float _cameraHeight, float _nearPlane, float _farPlane, float _fov);
	void InitializeCamera(ECameraType _cameraType, float _cameraWidth, float _cameraHeight, float _nearPlane, float _farPlane);
	void InitializeCamera();
	void ChangeCameraType(ECameraType type);

	//void SetCameraPosition(const glm::vec3& pos);
	//void SetCameraRotation(const glm::vec3& rot);

	void SetCameraForward();

	void SetCameraWidth(const float& width);
	void SetCameraHeight(const float& height);

	Transform* GetTransform();

	glm::mat4 GetViewMatrix();

	inline glm::mat4 GetMatrix() const { return cameraMatrix; }


	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

	void OnPropertyDraw() override;
	void OnSceneDraw() override;

};

