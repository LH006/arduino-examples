Arduino
==========================

# 즐겨찾기

- [링크1][ESP8266](https://github.com/esp8266/)
- [링크2 "버전"]
- [링크3] ([sources](doc/installing.rst#using-git-version))

# Arduino project
  * ESP8266

# Contents
  * 내용 목록
- 설명문:
  - [내용1](#Contents-1) - 공백표시
  - [내용2](#Contents-2)
  - [내용3](#using-platformio)
  - [내용4](#building-with-make)
- [내용5](#documentation)
- [내용6](#issues-and-support) 

# 예제1)
#### Latest release [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/)


### Contents 1
[내용](#Contents)
* 아아아아아아
- 점 리스트 링크: (https://1.com)
- 점 링크: `https://1.com/index.json`
- 링크: [링크 보이는 글](https://1.com/)

### Contents 2
#### [내용2]
- When using [Arduino IDE](https://www.arduino.cc/en/software), follow [our instructions here](https://arduino-esp8266.readthedocs.io/en/latest/installing.html#using-git-version).
- When using [링크1](https://platformio.org/install), refer to [링크2](https://docs.platformio.org/en/stable/platforms/espressif8266.html#using-arduino-framework-with-staging-version).
---
### [메뉴3]
* [ ] 사각
* [ ] 사각
* [ ] 사각
---
### [메뉴4]
1. 숫자
2. 숫자
3. 숫자
---

[PlatformIO](https://platformio.org?utm_source=arduino-esp8266) is an open source ecosystem for IoT
development with a cross-platform build system, a library manager, and full support
for Espressif (ESP8266) development. It works on the following popular host operating systems: macOS, Windows,
Linux 32/64, and Linux ARM (like Raspberry Pi, BeagleBone, CubieBoard).

- [What is PlatformIO?](https://docs.platformio.org/en/latest/what-is-platformio.html?utm_source=arduino-esp8266)
- [PlatformIO IDE](https://platformio.org/platformio-ide?utm_source=arduino-esp8266)
- [PlatformIO Core](https://docs.platformio.org/en/latest/core.html?utm_source=arduino-esp8266) (command line tool)
- [Advanced usage](https://docs.platformio.org/en/latest/platforms/espressif8266.html?utm_source=arduino-esp8266) -
  custom settings, uploading to SPIFFS, Over-the-Air (OTA), staging version
- [Integration with Cloud and Standalone IDEs](https://docs.platformio.org/en/latest/ide.html?utm_source=arduino-esp8266) -
  Cloud9, Codeanywhere, Eclipse Che (Codenvy), Atom, CLion, Eclipse, Emacs, NetBeans, Qt Creator, Sublime Text, VIM, Visual Studio, and VSCode
- [Project Examples](https://docs.platformio.org/en/latest/platforms/espressif8266.html?utm_source=arduino-esp8266#examples)

### Building with make

[makeEspArduino](https://github.com/plerup/makeEspArduino) is a generic makefile for any ESP8266 Arduino project.
Using make instead of the Arduino IDE makes it easier to do automated and production builds.

### Documentation

Documentation for latest development version: https://arduino-esp8266.readthedocs.io/en/latest/

### Issues and support ###

[ESP8266 Community Forum](https://www.esp8266.com/u/arduinoanswers) is a well-established community for questions and answers about Arduino for ESP8266. Stackoverflow is also an alternative. If you need help, have a "How do I..." type question, have a problem with a 3rd party library not hosted in this repo, or just want to discuss how to approach a problem, please ask there.

If you find the forum useful, please consider supporting it with a donation. <br />
[![Donate](https://img.shields.io/badge/paypal-donate-yellow.svg)](https://www.paypal.com/webscr?cmd=_s-xclick&hosted_button_id=4M56YCWV6PX66)

If you encounter an issue which you think is a bug in the ESP8266 Arduino Core or the associated libraries, or if you want to propose an enhancement, you are welcome to submit it here on Github: https://github.com/esp8266/Arduino/issues.

Please provide as much context as possible, as well as the information requested in the issue template:

- ESP8266 Arduino core version which you are using (you can check it in Boards Manager)
- your sketch code; please wrap it into a code block, see [Github markdown manual](https://help.github.com/articles/basic-writing-and-formatting-syntax/#quoting-code)
- when encountering an issue that happens at run time, attach the serial output. Wrap it into a code block, just like the code.
- for issues that happen at compile time, enable verbose compiler output in the IDE preferences, and attach that output (also inside a code block)
- ESP8266 development board model
- IDE settings (board choice, flash size)
- etc

### Contributing

For minor fixes of code and documentation, please go ahead and submit a pull request.  A gentle introduction to the process can be found [here](https://www.freecodecamp.org/news/a-simple-git-guide-and-cheat-sheet-for-open-source-contributors/).

Check out the list of issues that are easy to fix — [easy issues pending](https://github.com/esp8266/Arduino/issues?q=is%3Aopen+is%3Aissue+label%3A%22level%3A+easy%22). Working on them is a great way to move the project