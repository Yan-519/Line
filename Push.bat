@echo off
setlocal

echo =========================
echo       Commit\Push
echo =========================
echo.
 
set "has_changes=0"
for /f "delims=" %%A in ('git status --porcelain') do set "has_changes=1"
if "%has_changes%"=="0" (
    echo No changes found ^(skipping commit options^)
    goto :push_flag
)

set /p "commit_message=Commit message: "

:empty_message
if "%commit_message%"=="" (
    echo.
    echo Commit message cannot be empty.
    set /p "commit_message=Commit message: "

    goto :empty_message
)

echo.
choice /C YN /M "Are you sure you want to commit?"
if errorlevel 2 exit /b 0

echo.
echo Adding files...
git add .
if errorlevel 1 (
    echo Git add failed.
    pause
    exit /b 1
)

echo.
echo Committing...
git commit -m "%commit_message%"
if errorlevel 1 (
    echo Git commit failed.
    pause
    exit /b 1
)

echo.
echo Changes commited successfully.

:push_flag

echo.
choice /C YN /M "Are you sure you want to push?"
if errorlevel 2 exit /b 0

echo.
echo Pushing...
git push

if errorlevel 1 (
    echo.
    choice /C YN /M "Git push failed. Would you like to force push?"
    if errorlevel 2 exit /b 1

    echo.
    echo Force pushing...
    git push --force

    if errorlevel 1 (
        echo Force push failed.
        pause
        exit /b 1
    )
)

echo.
echo Changes pushed successfully.
pause