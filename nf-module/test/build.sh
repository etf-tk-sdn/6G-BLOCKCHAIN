#!/bin/sh

sudo rmmod test_all_hops.ko
make
sudo insmod test_all_hops.ko
