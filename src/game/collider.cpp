#include "collider.h"

void game::Collider::ResolveCollisions() { // bad algorithm
    for(auto first_object = std::begin(m_game_objects); first_object != std::end(m_game_objects); ++first_object) {
        for(auto second_object = std::begin(m_game_objects); second_object != std::end(m_game_objects); ++second_object) {
            if(first_object != second_object) {
                game::GameObjectPtr pointer_to_first = first_object->lock();
                game::GameObjectPtr pointer_to_second = second_object->lock();
                if(pointer_to_first && pointer_to_second) {
                    bool collision = pointer_to_first->GetCollideBox()->CollideWith(pointer_to_second->GetCollideBox());
                    if(collision) {
                        pointer_to_first->OnCollisionDetected(pointer_to_second);
                    }
                }
            }
        }
    }
}
