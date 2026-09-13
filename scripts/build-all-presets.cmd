@echo off
setlocal enabledelayedexpansion
REM Comprehensive build script for CommonLibSSE-NG
REM Builds all presets and stops at first failure for faster LLM iteration
REM
REM Usage: build-all-presets.cmd [--clang]
REM   --clang    Use clang-cl compiler instead of MSVC

REM Parse arguments
set "COMPILER=msvc"
for %%A in (%*) do (
    if /i "%%A"=="--clang" set "COMPILER=clang-cl"
)

REM Try to find Visual Studio installation dynamically
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VCVARS_PATH="

REM First try vswhere.exe
if exist "%VSWHERE%" (
    for /f "delims=" %%i in ('"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath 2^>nul') do (
        if exist "%%i\VC\Auxiliary\Build\vcvars64.bat" (
            set "VCVARS_PATH=%%i\VC\Auxiliary\Build\vcvars64.bat"
            goto :vcvars_found
        )
    )
)

REM Fallback: Check common paths on all drives
if not defined VCVARS_PATH (
    for %%D in (C D E F G H I J K L M N O P Q R S T U V W X Y Z) do (
        if exist "%%D:\" (
            REM Check VS 2022 Community
            if exist "%%D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
                set "VCVARS_PATH=%%D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
                goto :vcvars_found
            )
            REM Check VS 2022 Professional
            if exist "%%D:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
                set "VCVARS_PATH=%%D:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
                goto :vcvars_found
            )
            REM Check VS 2019 Community
            if exist "%%D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" (
                set "VCVARS_PATH=%%D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
                goto :vcvars_found
            )
        )
    )
)

:vcvars_found

REM Allow override via environment variable
if defined VCVARS64_PATH (
    set "VCVARS_PATH=%VCVARS64_PATH%"
)

REM Check if we found vcvars64.bat
if not defined VCVARS_PATH (
    echo ERROR: Could not find vcvars64.bat. Please ensure Visual Studio is installed.
    echo You can also set the VCVARS64_PATH environment variable to the full path of vcvars64.bat
    exit /b 1
)

echo Using Visual Studio environment: %VCVARS_PATH%
call "%VCVARS_PATH%" x64 >nul 2>&1

if !ERRORLEVEL! NEQ 0 (
    echo ERROR: Failed to initialize Visual Studio environment
    exit /b 1
)

echo.
echo ========================================
echo CommonLibSSE-NG Build Script [%COMPILER%]
echo ========================================
echo.

REM Build order: SE, AE, VR, Flatrim, All
set "PRESETS=release-%COMPILER%-vcpkg-se release-%COMPILER%-vcpkg-ae release-%COMPILER%-vcpkg-vr release-%COMPILER%-vcpkg-flatrim release-%COMPILER%-vcpkg-all"

for %%P in (%PRESETS%) do (
    echo Building preset: %%P
    echo ----------------------------------------
    
    REM Configure preset (capture output)
    echo Configuring build-%%P...
    cmake --preset build-%%P > "%TEMP%\config_%%P.log" 2>&1
    
    if !ERRORLEVEL! NEQ 0 (
        echo [CONFIGURE FAILED] build-%%P - showing errors:
        echo.
        type "%TEMP%\config_%%P.log"
        echo.
        echo Full output saved to: "%TEMP%\config_%%P.log"
        exit /b 1
    )
    del "%TEMP%\config_%%P.log" >nul 2>&1

    REM Build preset (capture output to temp file)
    echo Building...
    cmake --build --preset %%P > "%TEMP%\build_%%P.log" 2>&1
    
    if !ERRORLEVEL! EQU 0 (
        echo [SUCCESS] %%P
        echo.
        del "%TEMP%\build_%%P.log" >nul 2>&1
    ) else (
        echo [BUILD FAILED] %%P - showing errors:
        echo.
        type "%TEMP%\build_%%P.log" | findstr /C:"error C" /C:"error LNK" /C:"FAILED"
        echo.
        echo Full output saved to: "%TEMP%\build_%%P.log"
        exit /b 1
    )
)

echo.
echo ========================================
echo All builds SUCCEEDED
echo ========================================
exit /b 0
