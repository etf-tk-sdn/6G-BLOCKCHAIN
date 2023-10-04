#!/bin/sh

sudo rmmod test1_uco.ko
make
sudo insmod test1_uco.ko
