#ifndef WINDFALL_ENTITY_DELEGATE_H_
#define WINDFALL_ENTITY_DELEGATE_H_

#include "entity/base.h"

namespace windfall::entity::delegate {

namespace impl {

namespace ebase = windfall::entity::base;

}  // namespace impl

class MoveDelegate {
public:
    MoveDelegate() = default;
    virtual ~MoveDelegate() = default;

    virtual void Move(impl::ebase::BaseEntity& self, float dt) = 0;
};

class NoMotion final : public MoveDelegate {
public:
    NoMotion() = default;

    void Move(impl::ebase::BaseEntity& self, float dt) override { /* NO-OP */ }
};

class GeneralMotion final : public MoveDelegate {
public:
    GeneralMotion() = default;

    void Move(impl::ebase::BaseEntity& self, float dt) override;
};

}  // namespace windfall::entity::delegate

#endif  // WINDFALL_ENTITY_DELEGATE_H_
