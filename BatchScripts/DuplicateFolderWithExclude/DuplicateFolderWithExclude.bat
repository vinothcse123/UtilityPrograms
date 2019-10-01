::INPUTS

set sourcePath="C:\v6Drive\V6Backup\Source\DuplicateFolderWithExclude\Test"


set excludePath=C:\v6Drive\V6Backup\Source\DuplicateFolderWithExclude\Test\f1 C:\v6Drive\V6Backup\Source\DuplicateFolderWithExclude\Test\f2



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

robocopy %sourcePath%  %destinationPath% /MIR /Z  /XF *.iso *.log *.au /XD  %excludePath%
