#!/usr/bin/env pwsh

# This is an example batch file for building your Ecsact system implementations
# with Emscripten. In a more sophisticated setup you will likely use a build
# system such as bazel, cmake, zig, etc.

param (
	[Parameter(Mandatory)] $ProjectDir
)

if (${env:UE-ZenSubprocessDataPath})
{
	Write-Host "Detected live coding enabled"
	Write-Host "Skipping system impl re-build"
	exit 0
}

$ErrorActionPreference = 'Stop'

if (-not $env:EMSDK)
{
	if (Test-Path -Path "C:\emsdk\emsdk_env.ps1" -PathType Leaf)
	{
		(. C:\emsdk\emsdk_env.ps1) 2> $null
	}

	if (-not $env:EMSDK)
	{
		throw "Unable to find the Emscripten SDK installed on your system"
	}
}

$EcsactFiles = @(
	"$ProjectDir/Source/EcsactBenchmark/EcsactBenchmark.ecsact"
)

$Sources = @(
	"$ProjectDir/SystemImpls/EcsactSystemImpls.cpp"
)

$GeneratedOutDir = "$ProjectDir/SystemImpls/generated"

# TODO: don't hard set generated sources
$GeneratedSources = @(
	"$ProjectDir/SystemImpls/generated/EcsactBenchmark.ecsact.systems.cc"
)

$EcsactInc = (ecsact config include_dir)

ecsact codegen $EcsactFiles `
	--plugin=cpp_header `
	--plugin=systems_header `
	--plugin=cpp_systems_header `
	--plugin=cpp_systems_source `
	--outdir=$GeneratedOutDir

emcc -v

mkdir -Force "$ProjectDir/Binaries" | Out-Null

$WasmOutputFilePath = "$ProjectDir/Binaries/SystemImpls.wasm"

Write-Host "Building $WasmOutputFilePath ..."

# NOTE: PURE_WASI=1 removes emscripten_* functions that are not compatible with the Ecsact SI Wasm host
emcc -std=c++20 --no-entry -I"$EcsactInc" -I"SystemImpls/generated" `
	-s ERROR_ON_UNDEFINED_SYMBOLS=0 `
	-s WASM=1 `
	-s STANDALONE_WASM=1 `
	-s PURE_WASI=1 `
	-O3 `
	-Wno-js-compiler `
	-o $WasmOutputFilePath `
	$Sources `
	$GeneratedSources

if (-not $?)
{
	throw "emcc exited with code ${LastExitCode}"
}


Write-Host "Uploading $WasmOutputFilePath to Ecsact Net ..."

