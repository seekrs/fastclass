
# fastclass

A C program destined to make C++ classes faster following the orthodox canonical class form.

## How to install

First clone the repository:
```bash
git clone https://github.com/Namonay/fastclass.git
cd fastclass
```

Then use `make` to build and/or install the binary:
```bash
# Builds the 'class' binary
make 

# Installs to local path
make install
```

If you want to install to a custom path, you can input it as a make parameter:
```bash
# This is the default path
make install INSTALL_PATH="$HOME/.local/bin"
```

## How to use

The format for using fastclass is: `class [-FLAGS] [FILES] ...`

* `-f` will insert the 42Header in all classes created using NAME and MAIL defines.
* `-p` will insert `std::cout` output for the constructors and destructors.
* `-h` will print this help.

## How to uninstall

You can use `make remove` to delete the binary file located in `INSTALL_PATH`.

## License

(wtfpl)[./LICENSE]