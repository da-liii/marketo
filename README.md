# KMarkNote

A KDE application for note taking with the power of lightweight markup language.

It is bundled with a Markdown editor named KMarkPad.

## Features
+ Use Katepart as the default editor
+ Support Markdown
+ Live Preview(auto sync between two views)
+ Integrated Terminal at the bottom
+ github-flavored highlight code syntax (using katepart's highlight library)
+ Integrated into baloo's tag system(planning)
+ Git support(planning)
+ Jekyll support(planning)

## Install

### Dependencies

You need to install [libmdcpp](https://github.com/sadhen/libmdcpp) first.

Then install these packages in **Debian Sid**, other distributions should be 
similar:

`g++, qt4-default, kdelibs5-dev, katepart, konsole, git, cmake, extra-cmake-modules`

If you are using Ubuntu:

`g++, qt4-default, kdelibs5-dev, katepart, konsole, git, cmake`

### Compile

Then follow these instructions:
``` sh
cd /tmp
git clone https://github.com/sadhen/KMarkNote.git
cd KMarkNote
mkdir $HOME/software
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$HOME/software ..
make
make install
```

You can also only install the Markdown Editor:
``` sh
cd /tmp
git clone https://github.com/sadhen/KMarkNote.git
cd KMarkNote
mkdir $HOME/software
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$HOME/software ..
make
make install
```

**NOTE**: `$HOME` is your home directory. The above instructions will install KMarkNote in `$HOME/software`.

## Run it
``` sh
cd ~/software/bin/
./kmarknote # this will launch KMarkNote: the note-taking application
./kmarkpad # this will launch KMarkPad: the Markdown editor
```
