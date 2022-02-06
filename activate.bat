@echo off
rem Run to activate on MS Windows

if not exist .my_super_project_w (
  python -m venv .my_super_project_w
)

if not defined VIRTUAL_ENV (
  .my_super_project_w\Scripts\activate.bat
)

set DRAWIO=c:\Program Files\draw.io\draw.io.exe

pip install -q --upgrade pip
pip install -q -r ./requirements.txt
pip install -q -r ./docs/requirements.txt

cmake .