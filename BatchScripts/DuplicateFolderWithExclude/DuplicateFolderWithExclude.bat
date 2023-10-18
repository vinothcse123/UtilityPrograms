::INPUTS

::Give some additional space at end of path in sourcePath. If there is space in path then give double quotes. If no space then don't give double quotes - windows 
set sourcePath="C:\Users\gavi9006\OneDrive - VIN\ "


set excludePath="C:\Users\gavi9006\OneDrive - VIN\\f1 C:\Users\gavi9006\OneDrive - VIN\\f2"



@echo off
for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
set "YY=%dt:~2,2%" & set "YYYY=%dt:~0,4%" & set "MM=%dt:~4,2%" & set "DD=%dt:~6,2%"
set "HH=%dt:~8,2%" & set "Min=%dt:~10,2%" & set "Sec=%dt:~12,2%"



set "datestamp=%YYYY%%MM%%DD%" & set "timestamp=%HH%%Min%%Sec%"
set "fullstamp=%YYYY%-%MM%-%DD%_%HH%-%Min%-%Sec%"

echo fullstamp: "%fullstamp%"

set "desdirName=V6_BACKUP_%fullstamp%"

set destinationPath=%desdirName%

mkdir %destinationPath%


echo source path is %sourcePath%
echo destinationPath path is %destinationPath%

robocopy %sourcePath%  "%destinationPath% " /MIR /Z  /XF *.iso *.log *.au /XD  %excludePath%

timeout /t 100
