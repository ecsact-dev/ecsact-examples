#include <format>
#include <array>
#include <sstream>
#include <string>
#include "ecsact/runtime/meta.hh"
#include "ecsact/codegen/plugin.hh"
#include "ecsact/lang-support/lang-cc.hh"
#include "ecsact/cpp_codegen_plugin_util.hh"

using namespace std::string_literals;

using ecsact::cc_lang_support::c_identifier;
using ecsact::cc_lang_support::cpp_identifier;
using ecsact::cpp_codegen_plugin_util::block;
using ecsact::cpp_codegen_plugin_util::inc_header;
using ecsact::cpp_codegen_plugin_util::inc_package_header;
namespace fs = std::filesystem;

constexpr int32_t GENERATED_HEADER_INDEX = 0;
constexpr int32_t GENERATED_SOURCE_INDEX = 1;

static auto inc_package_header_no_ext( //
	ecsact::codegen_plugin_context& ctx,
	ecsact_package_id               pkg_id,
	std::string                     suffix,
	std::string                     header_extension = ".h"
) -> void {
	auto main_ecsact_file_path = ecsact::meta::package_file_path(ctx.package_id);
	if(ctx.package_id == pkg_id) {
		main_ecsact_file_path =
			fs::path{main_ecsact_file_path.replace_extension("").string() + suffix}
				.replace_extension(header_extension);

		inc_header(ctx, main_ecsact_file_path.filename().string());
	} else {
		auto cpp_header_path = fs::path{
			ecsact::meta::package_file_path(pkg_id).replace_extension("").string() +
			suffix
		};
		cpp_header_path.replace_extension(header_extension);
		if(main_ecsact_file_path.has_parent_path()) {
			cpp_header_path =
				fs::relative(cpp_header_path, main_ecsact_file_path.parent_path());
		}
		inc_header(ctx, cpp_header_path.filename().string());
	}
}

static auto ecsact_decl_name_to_pascal(const std::string& input)
	-> std::string {
	auto result = std::stringstream{};
	auto capitalize_next = true;

	for(char ch : input) {
		if(ch == '.' || ch == '_') {
			capitalize_next = true; // Capitalize the next character after a separator
		} else if(capitalize_next) {
			result << static_cast<char>(std::toupper(ch));
			capitalize_next = false;
		} else {
			result << static_cast<char>(std::tolower(ch));
		}
	}

	return result.str();
}

auto ecsact_codegen_output_filenames( //
	ecsact_package_id package_id,
	char* const*      out_filenames,
	int32_t           max_filenames,
	int32_t           max_filename_length,
	int32_t*          out_filenames_length
) -> void {
	auto pkg_basename = //
		ecsact::meta::package_file_path(package_id)
			.filename()
			.replace_extension("")
			.string();
	ecsact::set_codegen_plugin_output_filenames(
		std::array{
			pkg_basename + "__ecsact__actorcomp.h"s, // GENERATED_HEADER_INDEX
			pkg_basename + "__ecsact__actorcomp.cpp"s, // GENERATED_SOURCE_INDEX
		},
		out_filenames,
		max_filenames,
		max_filename_length,
		out_filenames_length
	);
}

auto ecsact_codegen_plugin_name() -> const char* {
	return "EcsactComponentActor";
}

static auto generate_header(ecsact::codegen_plugin_context ctx) -> void {
	ctx.writef("#pragma once\n\n");

	inc_header(ctx, "CoreMinimal.h");
	inc_package_header_no_ext(
		ctx,
		ctx.package_id,
		"__ecsact__actorcomp.generated.h"
	);

	ctx.writef("\n");

	for(auto comp_id : ecsact::meta::get_component_ids(ctx.package_id)) {
		auto comp_decl_name = ecsact::meta::decl_full_name(comp_id);
		auto comp_pascal_name = ecsact_decl_name_to_pascal(comp_decl_name);

		block(
			ctx,
			std::format(
				"UCLASS(BlueprintType) class A{} : public AActor",
				comp_pascal_name
			),
			[&] {
				ctx.writef("GENERATED_BODY()\n\n");
				ctx.writef("public:\n");
				for(auto field_id : ecsact::meta::get_field_ids(comp_id)) {
					auto field_name = ecsact::meta::field_name(comp_id, field_id);
					ctx.writef("// TODO: do something with '{}' field\n", field_name);
				}
			}
		);
		ctx.writef(";\n");
	}
}

static auto generate_source(ecsact::codegen_plugin_context ctx) -> void {
	inc_package_header_no_ext(ctx, ctx.package_id, "__ecsact__actorcomp.h");
}

auto ecsact_codegen_plugin(
	ecsact_package_id          package_id,
	ecsact_codegen_write_fn_t  write_fn,
	ecsact_codegen_report_fn_t report_fn
) -> void {
	generate_header({package_id, GENERATED_HEADER_INDEX, write_fn, report_fn});
	generate_source({package_id, GENERATED_SOURCE_INDEX, write_fn, report_fn});
}
