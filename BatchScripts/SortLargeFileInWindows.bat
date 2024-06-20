


@echo off
setlocal EnableDelayedExpansion

rem Define the directory
set "DIR=C:\Users\gavi9006\OneDrive - NIQ\V6 Official\"

rem Check if the directory exists
if not exist "%DIR%" (
    echo The directory "%DIR%" does not exist.
    pause
    exit /b
)

rem Use PowerShell to list files greater than 5 MB recursively and sort by size
powershell -command "Get-ChildItem -Path '%DIR%' -Recurse | Where-Object { -not $_.PSIsContainer -and $_.Length -gt 5MB } | Sort-Object Length -Descending | ForEach-Object { '{0:N0} {1}' -f $_.Length, $_.FullName }"

pause

endlocal
