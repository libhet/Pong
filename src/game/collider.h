#ifndef COLLIDER_H
#define COLLIDER_H

#include "types.h"
#include <memory>
#include <vector>
#include <functional>

namespace game {


struct Rect {
    float x, y, width, height;
};

class CollideBox {
public:
    CollideBox(game::Vec2f &position, game::Vec2f dimensions)
        : m_position(position), m_dimensions(dimensions)
    {    }

    bool CollideWith(const CollideBox& other) { // too much calculations
        Rect rect1 = {
            .x = m_position.x - m_dimensions.x/2,
            .y = m_position.y - m_dimensions.y/2,
            .width = m_dimensions.x,
            .height = m_dimensions.y
        };

        Rect rect2 = {
            .x = other.m_position.x - other.m_dimensions.x/2,
            .y = other.m_position.y - other.m_dimensions.y/2,
            .width = other.m_dimensions.x,
            .height = other.m_dimensions.y
        };

        return rect1.x < rect2.x + rect2.width &&
                rect1.x + rect1.width > rect2.x &&
                rect1.y < rect2.y + rect2.height &&
                rect1.y + rect1.height > rect2.y;
    }

    void SetCollisionFunction(std::function<void(const CollideBox& other)> fun) {
        m_collision_function = fun;
    }

    virtual void OnCollisionDetected(const CollideBox& other) {
        if(m_collision_function) m_collision_function(other);
    }

private:
    std::function<void(const CollideBox&)> m_collision_function;
    game::Vec2f& m_position;
    game::Vec2f m_dimensions;
};

using CollideBoxPtr = std::shared_ptr<CollideBox>;
using CollideBoxWeakPtr = std::weak_ptr<CollideBox>;


class Collider { // todo make singleton
public:
    void AddBox(const CollideBoxPtr& box) {
        m_collide_boxes.push_back(box);
    }

    void Update() {
        ResolveCollisions();
    }

private:
    void ResolveCollisions() { // bad algorithm
        for(auto first_box = std::begin(m_collide_boxes); first_box != std::end(m_collide_boxes); ++first_box) {
            for(auto second_box = std::begin(m_collide_boxes); second_box != std::end(m_collide_boxes); ++second_box) {
                if(first_box != second_box) {
                    auto pointer_to_first = first_box->lock();
                    auto pointer_to_second = second_box->lock();
                    if(pointer_to_first && pointer_to_second) {
                        bool collision = pointer_to_first->CollideWith(*pointer_to_second.get());
                        if(collision) {
                            pointer_to_first->OnCollisionDetected(*pointer_to_second.get());
                        }
                    }
                }
            }
        }
    }

    void RemoveUnactive() {

    }

private:
    std::vector<CollideBoxWeakPtr> m_collide_boxes;
};

}
#endif // COLLIDER_H
