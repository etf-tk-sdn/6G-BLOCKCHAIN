#include "blockchain.h"
MODULE_LICENSE("GPL");

static int __init t4_module_init(void) {
	struct coption *copt;
	struct cdata *cdat;
	struct chash  *lr;
	//packet with options (Hash0 calculated)
	unsigned char packet_wo[] = {0x4f,0x00,0x00,0x64,0xd2,0x34,0x00,0x00,0x40,0x01,0xdc,0xa3,0xc0,0xa8,0xc8,0xa6,0xc0,0xa8,0xc8,0xa9,0x95,0x28,0x7F,0x00,0x00,0x00,0x00,0x00,0x9b,0x54,0x97,0xc5,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x00,0x00,0x54,0xb5,0x00,0x01,0x00,0xa6,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69};
	struct iphdr *iph = (struct iphdr*)packet_wo;
	copt = (struct coption *)kmalloc(sizeof(struct coption), GFP_KERNEL);
	cdat = (struct cdata *)kmalloc(sizeof(struct cdata), GFP_KERNEL);
	lr = (struct chash*)kmalloc(sizeof(struct chash), GFP_KERNEL);

	fill_cdata(cdat, iph);
	printk(KERN_INFO "FILL DATA TEST");
	printk(KERN_INFO "Ident:  %02x %02x", cdat->ident[0], cdat->ident[1]); 
	printk(KERN_INFO "SrcIp:  %02x %02x %02x %02x", cdat->srcip[0], cdat->srcip[1], cdat->srcip[2],  cdat->srcip[3]);
	printk(KERN_INFO "DstIp:  %02x %02x %02x %02x", cdat->dstip[0], cdat->dstip[1], cdat->dstip[2], cdat->dstip[3]); 
	printk(KERN_INFO "Proto:  %02x", cdat->proto);
	printk(KERN_INFO "Sqn:    %02x", cdat->sqn); 	

	extract_coption(iph, copt);
	printk(KERN_INFO "Extract option test");
	printk(KERN_INFO "Type:   %02x", copt->type);
	printk(KERN_INFO "Len:    %02x", copt->len);
	printk(KERN_INFO "Sqn:    %02x", copt->sqn);
	printk(KERN_INFO "Unused: %02x %02x %02x %02x %02x", copt->unused[0], copt->unused[1], copt->unused[2], copt->unused[3], copt->unused[4]);
	printk(KERN_INFO "Hash0:  %02x %02x %02x %02x", copt->hash0[0], copt->hash0[1], copt->hash0[2], copt->hash0[3]);
	printk(KERN_INFO "Hash1:  %02x %02x %02x %02x", copt->hash1[0], copt->hash1[1], copt->hash1[2], copt->hash1[3]);
	printk(KERN_INFO "Hash2:  %02x %02x %02x %02x", copt->hash2[0], copt->hash2[1], copt->hash2[2], copt->hash2[3]);
	printk(KERN_INFO "Hash3:  %02x %02x %02x %02x", copt->hash3[0], copt->hash3[1], copt->hash3[2], copt->hash3[3]);
	printk(KERN_INFO "Hash4:  %02x %02x %02x %02x", copt->hash4[0], copt->hash4[1], copt->hash4[2], copt->hash4[3]);
	printk(KERN_INFO "Hash5:  %02x %02x %02x %02x", copt->hash5[0], copt->hash5[1], copt->hash5[2], copt->hash5[3]);
	printk(KERN_INFO "Hash6:  %02x %02x %02x %02x", copt->hash6[0], copt->hash6[1], copt->hash6[2], copt->hash6[3]);
	printk(KERN_INFO "Hash7:  %02x %02x %02x %02x", copt->hash7[0], copt->hash7[1], copt->hash7[2], copt->hash7[3]);  	


	printk(KERN_INFO "Before update: Hash0:  %02x %02x %02x %02x", copt->hash0[0], copt->hash0[1], copt->hash0[2], copt->hash0[3]);  
	update_hash(copt, cdat, lr);	
	
	printk(KERN_INFO "Update hash test");
	printk(KERN_INFO "lhash:  %02x %02x %02x %02x", lr->lhash[0], lr->lhash[1], lr->lhash[2], lr->lhash[3]);
	printk(KERN_INFO "rhash:  %02x %02x %02x %02x", lr->rhash[0], lr->rhash[1], lr->rhash[2], lr->rhash[3]); 

	printk(KERN_INFO "Type:   %02x", copt->type);
	printk(KERN_INFO "Len:    %02x", copt->len);
	printk(KERN_INFO "Sqn:    %02x", copt->sqn);
	printk(KERN_INFO "Unused: %02x %02x %02x %02x %02x", copt->unused[0], copt->unused[1], copt->unused[2], copt->unused[3], copt->unused[4]);
	printk(KERN_INFO "Hash0:  %02x %02x %02x %02x", copt->hash0[0], copt->hash0[1], copt->hash0[2], copt->hash0[3]);
	printk(KERN_INFO "Hash1:  %02x %02x %02x %02x", copt->hash1[0], copt->hash1[1], copt->hash1[2], copt->hash1[3]);  
	printk(KERN_INFO "Hash2:  %02x %02x %02x %02x", copt->hash2[0], copt->hash2[1], copt->hash2[2], copt->hash2[3]);
	printk(KERN_INFO "Hash3:  %02x %02x %02x %02x", copt->hash3[0], copt->hash3[1], copt->hash3[2], copt->hash3[3]); 
	printk(KERN_INFO "Hash4:  %02x %02x %02x %02x", copt->hash4[0], copt->hash4[1], copt->hash4[2], copt->hash4[3]);
	printk(KERN_INFO "Hash5:  %02x %02x %02x %02x", copt->hash5[0], copt->hash5[1], copt->hash5[2], copt->hash5[3]);
	printk(KERN_INFO "Hash6:  %02x %02x %02x %02x", copt->hash6[0], copt->hash6[1], copt->hash6[2], copt->hash6[3]);
	printk(KERN_INFO "Hash7:  %02x %02x %02x %02x", copt->hash7[0], copt->hash7[1], copt->hash7[2], copt->hash7[3]);   

	kfree(copt);
	kfree(cdat);
	kfree(lr);
	return 0;
}

static void __exit t4_module_exit(void) {
printk(KERN_INFO "Exit");
}
module_init(t4_module_init);
module_exit(t4_module_exit);
