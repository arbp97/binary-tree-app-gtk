#!/bin/sh

# This script will create a deb package for btree-view

packageVersion=$(printf "0.1.3" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)")

# Create file structure

mkdir -pv packaging/DEBIAN
mkdir -pv packaging/usr/share/licenses/BTree-View
mkdir -pv packaging/usr/share/pixmaps
mkdir -pv packaging/usr/share/applications
mkdir -pv packaging/usr/share/doc/BTree-View
mkdir -pv packaging/usr/bin


# Copy files to corresponding directories

cp -vf LICENSE packaging/usr/share/licenses/BTree-View
cp -vf res/btree-view.png packaging/usr/share/pixmaps
cp -vf btree-view.desktop packaging/usr/share/applications
cp -vf README.md packaging/usr/share/doc/BTree-View
cp -vf btree-view packaging/usr/bin


# Create control file

echo "Package: btree-view
Version: ${packageVersion}
Architecture: all
Maintainer: arbp97
Depends: libgtk-3-0
Priority: optional
Homepage: https://github.com/arbp97/btree-view
Description: Create and visualize binary trees" > packaging/DEBIAN/control

# Build the package

dpkg-deb --build packaging

# Rename the package

mv packaging.deb BTree-View.deb
