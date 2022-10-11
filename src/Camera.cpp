#include "Camera.h"

namespace Camera {
void Camera::updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
  front.y = sin(glm::radians(m_Pitch));
  front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
  m_Front = glm::normalize(front);
  m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
  m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
  : m_Position(position), m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
  m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_MovementSpeed(Settings::SPEED),
  m_MouseSensitivity(Settings::SENSITIVITY), m_FOV(Settings::FOV) {

  updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
  : m_Position(glm::vec3(posX, posY, posZ)),
  m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
  m_WorldUp(glm::vec3(upX, upY, upZ)), m_Yaw(yaw), m_Pitch(pitch),
  m_MovementSpeed(Settings::SPEED), m_MouseSensitivity(Settings::SENSITIVITY), m_FOV(Settings::FOV) {
  updateCameraVectors();
}

Camera::~Camera() {}

glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::GetProjectionMatrix() {
  return glm::perspective(glm::radians(m_FOV), 1280.0f / 720.0f, 0.1f, 100.0f);
}

void Camera::ProcessKeyboard(Movement direction, float deltaTime) {
  float velocity = m_MovementSpeed * deltaTime;
  if (direction == FORWARD) {
    m_Position += m_Front * velocity;
  }
  if (direction == BACKWARD) {
    m_Position -= m_Front * velocity;
  }
  if (direction == LEFT) {
    m_Position -= m_Right * velocity;
  }
  if (direction == RIGHT) {
    m_Position += m_Right * velocity;
  }
  if (direction == UP) {
    m_Position += m_Up * velocity;
  }
  if (direction == DOWN) {
    m_Position -= m_Up * velocity;
  }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
  xoffset *= m_MouseSensitivity;
  yoffset *= m_MouseSensitivity;

  m_Yaw += xoffset;
  m_Pitch += yoffset;

  if (constrainPitch) {
    if (m_Pitch > 89.0f)
      m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
      m_Pitch = -89.0f;
  }

  updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
  m_FOV -= yoffset;
  if (m_FOV < 1.0f)
    m_FOV = 1.0f;
  if (m_FOV > 45.0f)
    m_FOV = 45.0f;
}



} //    namespace Camera
