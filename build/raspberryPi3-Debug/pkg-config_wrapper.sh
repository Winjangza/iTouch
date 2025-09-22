#!/bin/sh
PKG_CONFIG_SYSROOT_DIR=/media/ubuntu/Piyanon/raspberrypi/sysroot
export PKG_CONFIG_SYSROOT_DIR
PKG_CONFIG_LIBDIR=/media/ubuntu/Piyanon/raspberrypi/sysroot/usr/lib/pkgconfig:/media/ubuntu/Piyanon/raspberrypi/sysroot/usr/share/pkgconfig:/media/ubuntu/Piyanon/raspberrypi/sysroot/usr/lib/arm-linux-gnueabihf/pkgconfig
export PKG_CONFIG_LIBDIR
exec pkg-config "$@"
