#ifndef WINDFALL_ROUTINE_EVENT_H_
#define WINDFALL_ROUTINE_EVENT_H_

#include "interface/keyboard.h"
#include "interface/mouse.h"

namespace windfall::routine::event {

namespace impl {

namespace kbd = windfall::interface::keyboard;
namespace mouse = windfall::interface::mouse;

}  // namespace impl

bool HandleEvents(impl::kbd::Keyboard& kbd, impl::mouse::Mouse& mouse);

}  // namespace windfall::routine::event

#endif  // WINDFALL_ROUTINE_EVENT_H_
