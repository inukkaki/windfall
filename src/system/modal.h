#ifndef WINDFALL_SYSTEM_MODAL_H_
#define WINDFALL_SYSTEM_MODAL_H_

namespace windfall::system::modal {

void ShowErrorMessage(const char title[], const char message[]);
void ShowErrorMessage(
    const char title[], const char message[], const char quotation[]);

}  // namespace windfall::system::modal

#endif  // WINDFALL_SYSTEM_MODAL_H_
