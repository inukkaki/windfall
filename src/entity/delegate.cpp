#include "entity/delegate.h"

#include "entity/base.h"

namespace windfall::entity::delegate {

namespace impl {

namespace ebase = windfall::entity::base;

}  // namespace impl

void GeneralMotion::Move(impl::ebase::BaseEntity& self, float dt)
{
    self.UpdateA();
    self.UpdateV(dt);
    self.UpdateR(dt);
}

}  // namespace windfall::entity::delegate
