# Tests
Function - Test code  

`fill_cdata` - `test1_fd.c`  

`extract_coption` - `test1_eo.c`  

`init_hash` - `test1_ih.c`  

`add_coption` -  `test1_ao.c`

`update_hash` - `test1_uh.c`

`update_coption` - `test1_uco.c`

 `test_all.c` - a test function for an entire sequence that is executed on a single router

`test_all_hops.c` - test function for packets passing through multiple routers

## Instructions for use
1. Insert blockchain.ko module: `sudo insmod blockchain.ko`  

2. In `test/Makefile` specify the corresponding test module that we want to test, as well as in `test/build.sh`  

3. View the test result with: `sudo dmesg`
