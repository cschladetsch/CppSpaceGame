#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SpaceGame {

class Entity {
public:
    Entity();
    virtual ~Entity();

    void setPosition(const glm::dvec3& pos) { position_ = pos; }
    const glm::dvec3& getPosition() const { return position_; }

    void setRotation(const glm::dvec3& rot) { rotation_ = rot; }
    const glm::dvec3& getRotation() const { return rotation_; }

    void setScale(const glm::dvec3& scale) { scale_ = scale; }
    const glm::dvec3& getScale() const { return scale_; }

    glm::dmat4 getModelMatrix() const;

    virtual void update(double deltaTime);
    virtual void draw();

protected:
    glm::dvec3 position_;
    glm::dvec3 rotation_;
    glm::dvec3 scale_;
};

} // namespace SpaceGame
