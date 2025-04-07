# yetch
Yet another Linux system info fetcher 🚀.
Made in C++ to make it blazingly fast.

## Demo
![image](https://github.com/user-attachments/assets/bde7c157-fc23-413a-bb90-046f5fc0bd3f)

## Installing requirements
To make yetch work you will need the `hostname` command, found in the package `inetutils` and the `lsb_release` found in the `lsb-release` package.
So, install both packages with your preferred package manager. Exemple with pacman:
```
sudo pacman -S inetutils lsb-release
```

## Building
```
git clone https://github.com/Yot360/yetch.git
cd yetch
mkdir build
cd build
cmake ..
cmake --build .
```

## Installing 
```
sudo cmake --install .
```
This will install yetch to `/usr/local/bin/yetch` (needs sudo permissions).

## Prebuit binary
You can find prebuilt binaries in the [Actions tab of the repo](https://github.com/Yot360/yetch/actions).
