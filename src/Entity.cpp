#include "simulator/Entity.hpp"

uint32_t Entity::next_id_ = 0;

Entity::Entity() : id_(next_id_++),position_(0.0f) {

}

Entity::Entity(glm::vec3 position,glm::vec3 orientation):
    id_(next_id_++),
    position_(position),
    orientation_(orientation)
    {}

uint32_t Entity::getId() const{
    return id_;
}

glm::vec3 Entity::getOrientation() const{
    return orientation_;
}

glm::vec3 Entity::getPosition() const{
    return position_;
}

glm::mat4 Entity::getRotationMatrix() const{
    glm::mat4 rotation(1.0f);
    rotation = glm::rotate(rotation, orientation_.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Yaw
    rotation = glm::rotate(rotation, orientation_.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Pitch
    rotation = glm::rotate(rotation, orientation_.x, glm::vec3(1.0f, 0.0f, 0.0f)); // Roll
    return rotation;
}
void Entity::setPosition(const glm::vec3& position){
    position_ = position;
}

void Entity::setOrientation(const glm::vec3& orientation){
    orientation_ = orientation; 
}
