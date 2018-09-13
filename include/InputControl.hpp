#ifndef INPUTCONTROL_HPP
#define INPUTCONTROL_HPP

#include "math/Math.hpp"

namespace renderel {

class InputControl {
  private:
    float amount = 0;

  public:
    InputControl() = default;

    void AddAmount(float amountToAdd) { amount += amountToAdd; }

    float GetAmount() const { return math::clamp(amount, -1.0f, 1.0f); }
};

} // namespace renderel

#endif // INPUTCONTROL_HPP
