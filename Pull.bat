@echo off

echo =========================
echo          Pull
echo =========================
echo.

choice /C YN /M "Are you sure you want to pull?"
if errorlevel 2 exit /b 0

echo Pulling...
git pull

if errorlevel 1 (
    echo.
    choice /C YN /M "Git pull failed. Would you like to force pull?"
    if errorlevel 2 exit /b 1

    echo.
    echo Force pulling...
    git pull --force

    if errorlevel 1 (
        echo Force pull failed.
        pause
        exit /b 1
    )
)

echo.
echo Changes pulled successfully.
pause