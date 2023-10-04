#include "blockchain.h"
MODULE_LICENSE("GPL");

static int __init t5_module_init(void) {
	struct coption *copt = &(struct coption){0x95, 0x28, 0x80, {0x00, 0x00, 0x00, 0x00, 0x00}, 
	{0x1c, 0xe0, 0x4d, 0xd9}, {0x39, 0x31, 0xec, 0x42}, {0x6d, 0x7b, 0xeb, 0x13}, 
	{0x3e, 0x5c, 0xf8, 0xfd}, {0x59, 0x8e, 0xcb, 0x59}, {0x4b, 0xb9, 0x6d, 0x57},
	{0xe3, 0xe7, 0x37, 0xd3}};
	unsigned char packet_wo[] = {0x4f,0x00,0x00,0x64,0xd2,0x34,0x00,0x00,0x40,0x01,0xdc,0xa3,0xc0,0xa8,0xc8,0xa6,0xc0,0xa8,0xc8,0xa9,0x95,0x28,0x01,0x00,0x00,0x00,0x00,0x00,0x9b,0x54,0x97,0xc5,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x00,0x00,0x54,0xb5,0x00,0x01,0x00,0xa6,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69};
	struct iphdr *iph = (struct iphdr *)packet_wo;
	
	update_coption(iph, copt);
	printk(KERN_INFO "Type:   %02x", *((unsigned char*)iph+20));
	printk(KERN_INFO "Len:    %02x",*((unsigned char*)iph+21));
	printk(KERN_INFO "Sqn:    %02x",*((unsigned char*)iph+22));
	printk(KERN_INFO "Unused: %02x %02x %02x %02x %02x", *((unsigned char*)iph+23), *((unsigned char*)iph+24), *((unsigned char*)iph+25), *((unsigned char*)iph+26), *((unsigned char*)iph+27));
	printk(KERN_INFO "Hash0:  %02x %02x %02x %02x", *((unsigned char*)iph+28), *((unsigned char*)iph+29), *((unsigned char*)iph+30), *((unsigned char*)iph+31));
	printk(KERN_INFO "Hash1:  %02x %02x %02x %02x", *((unsigned char*)iph+32), *((unsigned char*)iph+33), *((unsigned char*)iph+34), *((unsigned char*)iph+35));
	printk(KERN_INFO "Hash2:  %02x %02x %02x %02x", *((unsigned char*)iph+36), *((unsigned char*)iph+37), *((unsigned char*)iph+38), *((unsigned char*)iph+39));
	printk(KERN_INFO "Hash3:  %02x %02x %02x %02x", *((unsigned char*)iph+40), *((unsigned char*)iph+41), *((unsigned char*)iph+42), *((unsigned char*)iph+43));	
	printk(KERN_INFO "Hash4:  %02x %02x %02x %02x", *((unsigned char*)iph+44), *((unsigned char*)iph+45), *((unsigned char*)iph+46), *((unsigned char*)iph+47));
	printk(KERN_INFO "Hash5:  %02x %02x %02x %02x", *((unsigned char*)iph+48), *((unsigned char*)iph+49), *((unsigned char*)iph+50), *((unsigned char*)iph+51));
	printk(KERN_INFO "Hash6:  %02x %02x %02x %02x", *((unsigned char*)iph+52), *((unsigned char*)iph+53), *((unsigned char*)iph+54), *((unsigned char*)iph+55));
	printk(KERN_INFO "Hash7:  %02x %02x %02x %02x", *((unsigned char*)iph+56), *((unsigned char*)iph+57), *((unsigned char*)iph+58), *((unsigned char*)iph+59)); 
	return 0;	
}

static void __exit t5_module_exit(void) {
	printk(KERN_INFO "Exit");
}
module_init(t5_module_init);
module_exit(t5_module_exit);
