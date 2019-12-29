
Debian
====================
This directory contains files used to package Intercashd/Intercash-qt
for Debian-based Linux systems. If you compile Intercashd/Intercash-qt yourself, there are some useful files here.

## Intercash: URI support ##


Intercash-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Intercash-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your Intercashqt binary to `/usr/bin`
and the `../../share/pixmaps/Intercash128.png` to `/usr/share/pixmaps`

Intercash-qt.protocol (KDE)

