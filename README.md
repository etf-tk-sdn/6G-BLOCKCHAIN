# Tests
Function - Test code  

`fill_cdata` - `test1_fd.c`  

`extract_coption` - `test1_eo.c`  

`init_hash` - `test1_ih.c`  

`update_hash` - `test1_uh.c`

`update_coption` - `test1_uco.c`

##Instructions for use
1. Insert blockchain.ko module: `sudo insmod blockchain.ko`  

2. In `test/Makefile` specify the corresponding test module that we want to test, as well as in `test/build.sh`  

3. View the test result with: `sudo dmesg`
