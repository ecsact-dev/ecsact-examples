// NOTE: most of this file is taken from ecsact_runtime/dylib/dylib.cc

#include <cstring>
#include <cassert>
#include "ecsact/runtime/dylib.h"

#ifdef ECSACT_META_API_LOAD_AT_RUNTIME
#	include "ecsact/runtime/meta.h"
#endif

#define ECSACT_DYLIB_UTIL_FN_PTR_DEFN(fn_name, unused) \
	decltype(fn_name)(fn_name) = nullptr

#define ECSACT_DYLIB_UTIL_FN_PTR_ASSIGN(fn_name) (fn_name) = nullptr

#ifdef ECSACT_META_API_LOAD_AT_RUNTIME
FOR_EACH_ECSACT_META_API_FN(ECSACT_DYLIB_UTIL_FN_PTR_DEFN);
#endif

#define HAS_FN_CHECK(fn_name, target_fn_name) \
	if(std::strcmp(target_fn_name, #fn_name) == 0) return true

#define ASSIGN_FN_IF(fn_name, target_fn_name, fn_ptr)      \
	if(std::strcmp(#fn_name, target_fn_name) == 0) {         \
		fn_name = reinterpret_cast<decltype(fn_name)>(fn_ptr); \
	}                                                        \
	static_assert(true, "macro requires ;")

bool ecsact_dylib_has_fn(const char* fn_name) {
#ifdef ECSACT_META_API_LOAD_AT_RUNTIME
	FOR_EACH_ECSACT_META_API_FN(HAS_FN_CHECK, fn_name);
#endif
	return false;
}

void ecsact_dylib_set_fn_addr(const char* fn_name, void (*fn_ptr)()) {
#ifdef ECSACT_META_API_LOAD_AT_RUNTIME
	FOR_EACH_ECSACT_META_API_FN(ASSIGN_FN_IF, fn_name, fn_ptr);
#endif
}
