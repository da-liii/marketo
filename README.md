# Marketo

A KDE application for note taking with the power of lightweight markup language.

It is bundled with a separated Markdown editor.

## Features
+ Use **katepart** as the default editor(**cool** vim mode )
+ Partially support **CommonMark**
+ Highlight fenced code using Kate's Syntax Highlighter
+ Live Preview(auto sync between two views)

## Planning
+ Integrated with baloo for search
+ Git support
+ Support blog post generating

## For User

See [Install Guide](https://github.com/sadhen/marketo/wiki/Install-Guide) to install Marketo.

## For Developer

### Dependencies

You need to install [libmdcpp](https://github.com/sadhen/libmdcpp) first.

Also you need to install many other dependencies for compiling. Please see the CMakeLists.txt file for more info.

### Compile

Then follow these instructions:
``` sh
cd /tmp
git clone https://github.com/sadhen/marketo.git
cd marketo
mkdir $HOME/software
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$HOME/software ..
make
make install
```

**NOTE**: `$HOME` is your home directory. The above instructions will install Marketo in `$HOME/software`.

### Run it
``` sh
cd ~/software/bin/
./marknoto # this will launch the note-taking application
./markpado # this will launch the Markdown editor
```
