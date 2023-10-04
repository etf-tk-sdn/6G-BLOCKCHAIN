#!/bin/sh

sudo rmmod test1_ih.ko
make
sudo insmod test1_ih.ko
