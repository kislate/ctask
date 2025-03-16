@echo off

REM @echo off：关闭命令回显，使输出更加简洁。
REM echo on：打开命令回显（通常不需要）。
REM：注释行，用于添加注释说明。
REM setlocal：开始本地环境更改，批处理文件结束时会自动恢复原始环境变量。
REM endlocal：结束本地环境更改，恢复原始环境变量。

cmake -G "MinGW Makefiles" .
mingw32-make