#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"


namespace Camera {
namespace Settings {
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;
} // namespace Settings

enum Movement { FORWARD, LEFT, BACKWARD, RIGHT, UP, DOWN };

class Camera {
private:
  glm::vec3 m_Position;
  glm::vec3 m_Front;
  glm::vec3 m_Up;
  glm::vec3 m_Right;
  glm::vec3 m_WorldUp;

  float m_Yaw;
  float m_Pitch;
  float m_MovementSpeed;
  float m_MouseSensitivity;
  float m_FOV;

  void updateCameraVectors();

public:
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = Settings::YAW, float pitch = Settings::PITCH);

  Camera(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f, float yaw = Settings::YAW, float pitch = Settings::PITCH);

  ~Camera();

  inline void SetPosition(glm::vec3 Position) { m_Position = Position; };
  inline void SetPosition(float x, float y, float z) { m_Position = glm::vec3(x, y, z); };

  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix();

  void ProcessKeyboard(Movement direction, float deltaTime);

  void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

  void ProcessMouseScroll(float yoffset);

  inline glm::vec3 GetPosition() const { return m_Position; }

  inline glm::vec3 GetFront() const { return m_Front; }

  inline glm::vec3 GetUp() const { return m_Up; }

  inline  glm::vec3 GetRight() const { return m_Right; }

  inline  glm::vec3 GetWorldUp() const { return m_WorldUp; }

  inline float GetYaw() const { return m_Yaw; }

  inline float GetPitch() const { return m_Pitch; }

  inline float GetMovementSpeed() const { return m_MovementSpeed; }

  inline float GetMouseSensitivity() const { return m_MouseSensitivity; }

  inline float GetFOV() const { return m_FOV; }
};

} // namespace Camera

#endif // CAMERA_H
