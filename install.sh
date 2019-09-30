# Install Arduino IDE

if ! [ -x "$(command -v arduino-cli)" ]; then
  echo 'Error: Arduino CLI is not installed...' >&2
  curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
fi

echo 'Arduino: Installing Compiler...' >&2
arduino-cli core install arduino:samd
echo 'Arduino: Installing Board Files...' >&2
arduino-cli core update-index --additional-urls http://arduino.esp8266.com/stable/package_esp8266com_index.json