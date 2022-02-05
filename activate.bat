@echo off
rem Run to activate on MS Windows

if not exist .catcutifier_w (
  python -m venv .catcutifier_w
)

if not defined VIRTUAL_ENV (
  .catcutifier_w\Scripts\activate.bat
)

set DRAWIO=c:\Program Files\draw.io\draw.io.exe

pip install -q -r ./requirements.txt
pip install -q -r ./docs/requirements.txt
