@ECHO OFF

pushd %~dp0

REM Command file for Sphinx documentation

if "%SPHINXBUILD%" == "" (
	set SPHINXBUILD=sphinx-build
)
set SOURCEDIR=source
set BUILDDIR=sphinx

set READTHEDOCS=True
del Doxyfile
set ORGPATH=%PATH%
set PATH=c:\Program Files\doxygen\bin\;%PATH%
python %SOURCEDIR%\conf.py
set PATH=%ORGPATH%
set READTHEDOCS=False

if "%1" == "help" goto help
if not "%1" == "" goto original

%SPHINXBUILD% >NUL 2>NUL
if errorlevel 9009 (
	echo.
	echo.The 'sphinx-build' command was not found. Make sure you have Sphinx
	echo.installed, then set the SPHINXBUILD environment variable to point
	echo.to the full path of the 'sphinx-build' executable. Alternatively you
	echo.may add the Sphinx directory to PATH.
	echo.
	echo.If you don't have Sphinx installed, grab it from
	echo.https://www.sphinx-doc.org/
	exit /b 1
)

%SPHINXBUILD% -b html -Dbreathe_projects.MySuperProject=%CD%\doxygen\xml %SOURCEDIR% %BUILDDIR% %SPHINXOPTS% %O%
goto end

:original
%SPHINXBUILD% -M %1 %SOURCEDIR% %BUILDDIR% %SPHINXOPTS% %O%
goto end

:help
%SPHINXBUILD% -M help %SOURCEDIR% %BUILDDIR% %SPHINXOPTS% %O%

:end
popd
