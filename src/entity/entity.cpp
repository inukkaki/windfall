#include "entity/entity.h"

#include "system/assert.h"

namespace windfall::entity::entity {

void Entity::Move(float dt)
{
    INUK_ASSERT(move_);
    move_->Move(*this, dt);
}

}  // namespace windfall::entity::entity
