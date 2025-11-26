#include "entity.h"

namespace SpaceGame {

Entity::Entity()
    : position_(0, 0, 0),
      rotation_(0, 0, 0),
      scale_(1, 1, 1) {}

Entity::~Entity() {}

glm::dmat4 Entity::getModelMatrix() const {
    glm::dmat4 model = glm::dmat4(1.0);
    model = glm::translate(model, position_);
    model = glm::rotate(model, rotation_.x, glm::dvec3(1, 0, 0));
    model = glm::rotate(model, rotation_.y, glm::dvec3(0, 1, 0));
    model = glm::rotate(model, rotation_.z, glm::dvec3(0, 0, 1));
    model = glm::scale(model, scale_);
    return model;
}

void Entity::update(double deltaTime) {
    // Base class does nothing
}

void Entity::draw() {
    // Base class does nothing
}

} // namespace SpaceGame
