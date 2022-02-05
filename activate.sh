# Run with: source activate.sh

if [ ! -d .catcutifier_x ]; then
    python3 -m venv .catcutifier_x
fi

if [ -z ${VIRTUAL_ENV} ]; then 
    source ./.catcutifier_x/bin/activate
fi
if [ -z ${VIRTUAL_ENV} ]; then 
    exit 1
fi

export DRAWIO="/Applications/draw.io.app/Contents/MacOS/draw.io"

# checking required packages
pip install -q -r ./requirements.txt
pip install -q -r ./docs/requirements.txt

# Add java to the path
if [[ ":$PATH:" != *"/usr/local/opt/openjdk/bin/:"* ]]; then
  export PATH="/usr/local/opt/openjdk/bin/:$PATH"
fi

