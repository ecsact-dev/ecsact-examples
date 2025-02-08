// GENERATED FILE - DO NOT EDIT
#pragma once

#include <cstdint>
#include <compare>
#include "ecsact/runtime/common.h"

namespace benchmark {

struct Counter {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(1);
	int32_t value;
	auto operator<=>(const benchmark::Counter&) const = default;
};
struct MassOnly {
	static constexpr bool transient = false;
	static constexpr bool has_assoc_fields = false;
	static constexpr auto id = static_cast<ecsact_component_id>(2);
	auto operator<=>(const benchmark::MassOnly&) const = default;
};
struct IterateCounter {
	static constexpr auto id = static_cast<ecsact_system_id>(3);
	struct context;
	static void impl(context&);
};

}// namespace benchmark
