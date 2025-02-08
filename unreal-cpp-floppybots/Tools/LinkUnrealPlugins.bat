@echo off

call :abspath ".."
set PROJECT_DIR=%abspath%

call :abspath "..\..\ecsact_unreal"
set ECSACT_PLUGIN_DIR=%abspath%

call :abspath "..\..\..\seaube\ecsact-net-unreal"
set ECSACT_NET_PLUGIN_DIR=%abspath%

call :abspath "Plugins\Ecsact"
set LOCAL_LINK_ECSACT_PLUGIN_DIR=%abspath%

call :abspath "Plugins\EcsactNet"
set LOCAL_LINK_ECSACT_NET_PLUGIN_DIR=%abspath%

rmdir /Q %LOCAL_LINK_ECSACT_PLUGIN_DIR%
rmdir /Q %LOCAL_LINK_ECSACT_NET_PLUGIN_DIR%
mklink /J %LOCAL_LINK_ECSACT_PLUGIN_DIR% %ECSACT_PLUGIN_DIR%
mklink /J %LOCAL_LINK_ECSACT_NET_PLUGIN_DIR% %ECSACT_NET_PLUGIN_DIR%

REM functions below here
exit /B

:abspath
  set ABSPATH=%~f1
  exit /B
