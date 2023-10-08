#include "blockchain.h"
#include <linux/skbuff.h>

MODULE_LICENSE("GPL");

static int __init t6_module_init(void) {
	unsigned char packet[]={0x45,0x96,0x68,0xc9,0xf2,0x08,0x00,0x45,0x00,0x00,0x3c,0xd0,0x8b,0x00,0x00,0x80,0x01,0x57,0x94,0xc0,0xa8,0xc8,0xa9,0xc0,0xa8,0xc8,0xa6,0x08,0x00,0x4c,0xb5,0x00,0x01,0x00,0xa6,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69};
	struct iphdr *iph;
	struct sk_buff *skb;
	struct coption *copt = &(struct coption){0x95, 0x28, 0x1, {0x00, 0x00, 0x00, 0x00, 0x00}, {0x11, 0x22, 0x33, 0x44}};
	skb = alloc_skb(ETH_HLEN + sizeof(packet), GFP_KERNEL);
	if(!skb) {
		printk(KERN_ERR "Failed to allocate");
	 	return 0;
	}
	iph = (struct iphdr *)skb_put(skb, sizeof(struct iphdr));
	iph->ihl=5;
	iph->version=4;
	iph->tos=0;
	iph->tot_len = htons(sizeof(struct iphdr) + sizeof(packet));
	iph->id = htons(12345);
	iph->frag_off = 0;
	iph->ttl = 64;
	iph->protocol = IPPROTO_ICMP;
	iph->saddr = htonl(0xC0A80101);
	iph->daddr = htonl(0xC0A80102);
	iph->check = 0;

	memcpy(skb_put(skb, sizeof(packet)), packet, sizeof(packet));

	iph = ip_hdr(skb);
	printk(KERN_INFO "IHL before add_coption: %d", iph->ihl);

	add_coption(skb, iph, copt);	
	printk(KERN_INFO "- - - - - - - - - - - - - - - -"); 
	printk(KERN_INFO "IHL after add_coption: %d", iph->ihl); 
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

	printk(KERN_INFO "Length ihl after: %d", iph->ihl); 
	kfree(skb);	

	return 0;
}

static void __exit t6_module_exit(void) {
	printk(KERN_INFO "Exit");
}

module_init(t6_module_init);
module_exit(t6_module_exit);

