#include "blockchain.h"
MODULE_LICENSE("GPL");

static int __init t1_module_init(void) {
	unsigned char packet1[] = {0x45,0x00,0x00,0x3c,0xd0,0x8b,0x00,0x00,0x80,0x01,0x57,0x94,0xc0,0xa8,0xc8,0xa9,0xc0,0xa8,0xc8,0xa6,0x08,0x00,0x4c,0xb5,0x00,0x01,0x00,0xa6,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69};
	struct iphdr *iph = (struct iphdr *) packet1;
	struct cdata *cdat;

	cdat = (struct cdata *)kmalloc(sizeof(struct cdata), GFP_KERNEL); 

	fill_cdata(cdat, iph);
	
	printk(KERN_INFO "Ident:  %02x %02x", cdat->ident[0], cdat->ident[1]);
	printk(KERN_INFO "SrcIp:  %02x %02x %02x %02x", cdat->srcip[0], cdat->srcip[1], cdat->srcip[2],  cdat->srcip[3]);
	printk(KERN_INFO "DstIp:  %02x %02x %02x %02x", cdat->dstip[0], cdat->dstip[1], cdat->dstip[2], cdat->dstip[3]);
	printk(KERN_INFO "Proto:  %02x", cdat->proto);
	printk(KERN_INFO "Sqn:    %02x", cdat->sqn);
	printk(KERN_INFO "PubKey: %02x %02x %02x %02x ... %02x %02x %02x %02x", cdat->pubkey[0], cdat->pubkey[1], cdat->pubkey[2], cdat->pubkey[3], cdat->pubkey[16], cdat->pubkey[17], cdat->pubkey[18], cdat->pubkey[19]);

	kfree(cdat);
	return 0;
}

static void __exit t1_module_exit(void){
	printk(KERN_INFO "Exit");	
}
module_init(t1_module_init);
module_exit(t1_module_exit);
