:: �S�\�[�X�̍s���𐔂���
@echo off
@setlocal enabledelayedexpansion

cd /d "%~dp0"
echo �y�\�[�X�R�[�h�s���z

pushd "%~dp0src"

set hoge=0

for /r %%i in (*.c *.h *.cpp *.hpp *.cxx *.hxx *.inl) do (
	echo %%i
	set lines=
	for /f %%a in ('type %%i ^| find /c /v ""') do (
		set /a lines=%%a
	)
	echo !lines!
	
	set /a hoge+=lines
)

echo %hoge%

pause

goto end

:end











