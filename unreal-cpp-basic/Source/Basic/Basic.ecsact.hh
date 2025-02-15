// GENERATED FILE - DO NOT EDIT
#pragma once

#include <cstdint>
#include <compare>
#include "ecsact/runtime/common.h"

namespace basic {

struct Count {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(1);
	int32_t value;
	auto operator<=>(const basic::Count&) const = default;
};
struct Counter {
	static constexpr auto id = static_cast<ecsact_system_id>(2);
	struct context;
	static void impl(context&);
};

}// namespace basic
