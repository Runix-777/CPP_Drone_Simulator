#include "Entity.hpp"

uint32_t Entity::next_id_ = 0;

Entity::Entity() : id_(next_id_++),position_(0.0f) {

}

Entity::Entity(glm::vec3 position) : id_(next_id_++),position_(position){

}

uint32_t Entity::getId() const{
    return id_;
}