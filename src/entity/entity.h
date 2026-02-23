#ifndef WINDFALL_ENTITY_ENTITY_H_
#define WINDFALL_ENTITY_ENTITY_H_

#include <memory>

#include "entity/base.h"
#include "entity/delegate.h"
#include "system/assert.h"

namespace windfall::entity::entity {

namespace impl {

namespace ebase = windfall::entity::base;
namespace edlgt = windfall::entity::delegate;

}  // namespace impl

class Entity : public impl::ebase::BaseEntity {
public:
    Entity(const impl::ebase::PhysicalProperty& phys,
           std::unique_ptr<impl::edlgt::MoveDelegate>&& move)
        : BaseEntity(phys), move_(std::move(move))
    {
        INUK_ASSERT(move_);
    }

    virtual ~Entity() = default;

    void Move(float dt);

private:
    std::unique_ptr<impl::edlgt::MoveDelegate> move_;
};

}  // namespace windfall::entity::entity

#endif  // WINDFALL_ENTITY_ENTITY_H_
