@echo off
@rem NOTE: This script is only necessary when the Ecsact SDK is _NOT_ installed on your system
@rem If you would prefer to use a simpler setup please install the Ecsact SDK here
@rem     https://ecsact.dev/start

setlocal enabledelayedexpansion

set "EngineDir=%1"
set "ProjectDir=%2"
set "MarketplacePluginsDir=%EngineDir%\Plugins\Marketplace"
set "EcsactPluginDir="

cd /d %EngineDir%


echo Searching for Ecsact.uplugin in %MarketplacePluginsDir%
for /d %%D in ("%MarketplacePluginsDir%\*") do (
	if exist "%%D\Ecsact.uplugin" (
		set "EcsactPluginDir=%%D"
		goto :FoundEcsactPlugin
	)
)

echo
echo ERROR: failed to find Ecsact Plugin
echo When using this script you must have the Ecsact Unreal plugin installed from Fab.com
echo
echo     https://ecsact.dev/start/unreal#fab
echo
exit 1

:FoundEcsactPlugin

echo Found Ecsact Unreal plugin installed at %EcsactPluginDir%
set EcsactUnrealCodegen="%EcsactPluginDir%\Source\ThirdParty\EcsactSDK\bin\EcsactUnrealCodegen.exe"

cd /d %ProjectDir%
"%EcsactUnrealCodegen%" %ProjectDir% --engine-dir "%EngineDir%" || exit /b 1
endlocal
