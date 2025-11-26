#include "camera.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

namespace SpaceGame {

Camera::Camera()
    : position_(0.0, 0.0, 0.0),
      pitch_(0.0),
      yaw_(0.0),
      roll_(0.0),
      fov_(60.0) {}

void Camera::setRotation(double pitch, double yaw, double roll) {
    pitch_ = pitch;
    yaw_ = yaw;
    roll_ = roll;
}

void Camera::lookAt(const glm::dvec3& target, const glm::dvec3& up) {
    glm::dvec3 dir = glm::normalize(target - position_);
    yaw_ = std::atan2(dir.x, dir.z);
    pitch_ = std::asin(-dir.y);
    roll_ = 0; // Not implemented yet
}

glm::dmat4 Camera::getViewMatrix() const {
    glm::dmat4 view = glm::dmat4(1.0);
    view = glm::rotate(view, -pitch_, glm::dvec3(1, 0, 0));
    view = glm::rotate(view, -yaw_, glm::dvec3(0, 1, 0));
    view = glm::rotate(view, -roll_, glm::dvec3(0, 0, 1));
    view = glm::translate(view, -position_);
    return view;
}

glm::dmat4 Camera::getProjectionMatrix(int screenWidth, int screenHeight) const {
    return glm::perspective(glm::radians(fov_), (double)screenWidth / (double)screenHeight, 0.1, 1000.0);
}

void Camera::moveForward(double distance) {
    double yawRad = yaw_;
    double pitchRad = pitch_;
    position_.x += std::sin(yawRad) * std::cos(pitchRad) * distance;
    position_.y += -std::sin(pitchRad) * distance;
    position_.z += std::cos(yawRad) * std::cos(pitchRad) * distance;
}

void Camera::moveRight(double distance) {
    double yawRad = yaw_;
    position_.x += std::cos(yawRad) * distance;
    position_.z += -std::sin(yawRad) * distance;
}

void Camera::moveUp(double distance) {
    position_.y += distance;
}

void Camera::rotate(double deltaPitch, double deltaYaw, double deltaRoll) {
    pitch_ += deltaPitch;
    yaw_ += deltaYaw;
    roll_ += deltaRoll;

    // Clamp pitch to avoid flipping
    if (pitch_ > 1.5708) pitch_ = 1.5708;   // 90 degrees
    if (pitch_ < -1.5708) pitch_ = -1.5708;  // -90 degrees
}

bool Camera::worldToScreen(const glm::dvec3& worldPos, int screenWidth, int screenHeight,
                           double& screenX, double& screenY, double& depth) const {
    glm::dmat4 view = getViewMatrix();
    glm::dmat4 proj = getProjectionMatrix(screenWidth, screenHeight);
    glm::dmat4 viewProj = proj * view;

    glm::dvec4 clipPos = viewProj * glm::dvec4(worldPos, 1.0);

    if (clipPos.w <= 0.0) {
        return false;
    }

    glm::dvec3 ndcPos = glm::dvec3(clipPos) / clipPos.w;

    screenX = (ndcPos.x + 1.0) * 0.5 * screenWidth;
    screenY = (1.0 - ndcPos.y) * 0.5 * screenHeight;
    depth = ndcPos.z;

    return true;
}

} // namespace SpaceGame
