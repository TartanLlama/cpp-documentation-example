# Run with: source activate.sh

if [ ! -d .my_super_project_x ]; then
    python3 -m venv .my_super_project_x
fi

if [ -z ${VIRTUAL_ENV} ]; then 
    source ./.my_super_project_x/bin/activate
fi
if [ -z ${VIRTUAL_ENV} ]; then 
    exit 1
fi

export DRAWIO="/Applications/draw.io.app/Contents/MacOS/draw.io"

# checking required packages
pip install -q --upgrade pip
pip install -q -r ./requirements.txt
pip install -q -r ./docs/requirements.txt

# Add java to the path
if [[ ":$PATH:" != *"/usr/local/opt/openjdk/bin/:"* ]]; then
  export PATH="/usr/local/opt/openjdk/bin/:$PATH"
fi

cmake .
