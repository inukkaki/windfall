#ifndef WINDFALL_ROUTINE_EVENT_H_
#define WINDFALL_ROUTINE_EVENT_H_

#include "interface/keyboard.h"

namespace windfall::routine::event {

namespace impl {

namespace kbd = windfall::interface::keyboard;

}  // namespace impl

bool HandleEvents(impl::kbd::Keyboard& kbd);

}  // namespace windfall::routine::event

#endif  // WINDFALL_ROUTINE_EVENT_H_
