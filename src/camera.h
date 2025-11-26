#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace SpaceGame {

class Camera {
public:
    Camera();

    void setPosition(const glm::dvec3& pos) { position_ = pos; }
    void setRotation(double pitch, double yaw, double roll);
    void lookAt(const glm::dvec3& target, const glm::dvec3& up = glm::dvec3(0, 1, 0));

    const glm::dvec3& getPosition() const { return position_; }
    double getPitch() const { return pitch_; }
    double getYaw() const { return yaw_; }
    double getRoll() const { return roll_; }

    glm::dmat4 getViewMatrix() const;
    glm::dmat4 getProjectionMatrix(int screenWidth, int screenHeight) const;

    // Convert 3D world position to 2D screen position
    bool worldToScreen(const glm::dvec3& worldPos, int screenWidth, int screenHeight,
                      double& screenX, double& screenY, double& depth) const;

    void moveForward(double distance);
    void moveRight(double distance);
    void moveUp(double distance);
    void rotate(double deltaPitch, double deltaYaw, double deltaRoll);

private:
    glm::dvec3 position_;
    double pitch_;  // Rotation around X axis
    double yaw_;    // Rotation around Y axis
    double roll_;   // Rotation around Z axis
    double fov_;    // Field of view
};

} // namespace SpaceGame
