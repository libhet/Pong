#include "types.h"
#include <memory>
#include <vector>

struct Rect {
    float x, y, width, height;
};

class CollideBox {
public:
    CollideBox(game::vec2 &position, game::vec2 dimensions)
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

private:
    game::vec2& m_position;
    game::vec2 m_dimensions;
};

using CollideBoxPtr = std::shared_ptr<CollideBox>;
using CollideBoxWeakPtr = std::weak_ptr<CollideBox>;


class Collider { // todo make singleton
public:
    Add

    void Update() {
        for
    }
private:
    std::vector<CollideBoxWeakPtr> m_collide_boxes;
};
