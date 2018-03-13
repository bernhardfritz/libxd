# Installing libxd from source

Assuming you have successfully compiled libxd following the guidelines described [here](compile.md), upon installation, libxd will be available system-wide.

## Linux

---

## macOS

---

#### Installing

Once you have compiled libxd you can install it to your system.

The default install location on macOS would be `/usr/local`. However, you can specify a different location like `../install` using the following command:

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=../install
```

To start the installation use the following command:
```bash
make install
```

> :warning: Existing files will be overwritten.

To uninstall use the following command:
```bash
xargs rm < install_manifest.txt
```

> :warning: This will delete all files that have been added/changed during the installation.

---

## Windows