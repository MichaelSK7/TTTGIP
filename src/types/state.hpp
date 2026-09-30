#pragma once

#include <stdint.h>

namespace TTT {
enum class State : uint8_t { InProgress, XWon, OWon, Draw };
}