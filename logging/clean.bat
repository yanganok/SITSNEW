@echo off
set nowPath=%cd%
cd /
cd %nowPath%

::delete .vs folder
if exist .vs rd /s /q .vs

::delete output folder
if exist output rd /s /q Output

::delete specify file(*.pdb,*.vshost.*)
for /r %nowPath% %%i in (*.pdb,*.vshost.*,*.vspscc,*.user) do (del %%i)

::delete specify folder(obj,bin)
for /r %nowPath% %%i in (obj,bin,output,.vs,Debug,x64,Win32) do (IF EXIST %%i RD /s /q %%i)

echo OK
pause
