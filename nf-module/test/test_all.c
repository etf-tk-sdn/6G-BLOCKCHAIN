#include "blockchain.h"
#include <linux/skbuff.h>

MODULE_LICENSE("GPL");

void test_all(struct iphdr *iph, struct sk_buff *skb) {
	struct coption *copt;
	struct cdata *cdat;
	struct chash *lr;

	copt=(struct coption*)kmalloc(sizeof(struct coption), GFP_KERNEL);
	cdat=(struct cdata *)kmalloc(sizeof(struct cdata), GFP_KERNEL);
	lr=(struct chash *)kmalloc(sizeof(struct chash), GFP_KERNEL);

	fill_cdata(cdat, iph);
	if (extract_coption(iph, copt)==0) {
		update_hash(copt,cdat, lr);
		update_coption(iph, copt);
	} else {
		init_hash(copt, cdat);
		add_coption(skb, iph, copt);
	}
	iph->check = 0;
	iph->check = ip_fast_csum((unsigned char *)iph, iph->ihl);
	kfree(copt);
	kfree(cdat);
	kfree(lr);
}

void print_packet(struct iphdr *iph) {
	int i;
	printk(KERN_INFO "-----------START OF PACKET-------------\n");
	for (i = 0; i < ntohs(iph->tot_len); i+=4) {
		if (i == 0)
			printk(KERN_INFO "|VER|IHL|TOS|TOTAL_LENGTH|    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));
		if (i == 4)
			printk(KERN_INFO "|IDENTIFIC. |FLAGS|OFFSET|    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));                            
		if (i == 8)
			printk(KERN_INFO "|TTL|PROTO. |HEADER_CSUM |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));
		if (i == 12)
			printk(KERN_INFO "|SOURCE_ADDRESS          |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));                            
		if (i == 16)
			printk(KERN_INFO "|DESTINATION_ADDRESS     |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));   
		if (iph->ihl == 5) {
			if (i == 20 || i==40)
				printk(KERN_INFO "|PAYLOAD                 |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));                
		} else {
			if (i == 20) 
				printk(KERN_INFO "|TYP|LEN|SQN|UNUSED     |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));
			if (i == 24)
				printk(KERN_INFO "|UNUSED                 |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));
			if (i == 28)
				printk(KERN_INFO "|HASH0                  |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));                          
			if (i==32)
				printk(KERN_INFO "|HASH1                  |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));
			if (i==36)
				printk(KERN_INFO "|HASH2                  |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));                          
			if (i==40)
				printk(KERN_INFO "|HASH3                  |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));
			if (i==44)
				printk(KERN_INFO "|HASH4                  |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));
			if (i==48)	
				printk(KERN_INFO "|HASH5                  |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));                          
			if (i==52)
				printk(KERN_INFO "|HASH6                  |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));                          
			if (i==56)
				printk(KERN_INFO "|HASH7                  |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));                          
			if (i==60)
				printk(KERN_INFO "|PAYLOAD                |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));
			if (i==80)
				printk(KERN_INFO "|PAYLOAD                |    %02x%02x%02x%02x\n", *((unsigned char*)iph+i), *((unsigned char*)iph+i+1), *((unsigned char*)iph+i+2), *((unsigned char*)iph+i+3));
			}
	}                                                                                                                                                                                                                      
printk(KERN_INFO "-------------END OF PACKET-------------\n");                  
}


static int __init test_module_init(void) {
	//Uncomment / Comment
	//	Data for packet without options
	unsigned char packet[] = {0x45,0x96,0x68,0xc9,0xf2,0x08,0x00,0x45,0x00,0x00,0x3c,0xd0,0x8b,0x00,0x00,0x80,0x01,0x57,0x94,0xc0,0xa8,0xc8,0xa9,0xc0,0xa8,0xc8,0xa6,0x08,0x00,0x4c,0xb5,0x00,0x01,0x00,0xa6,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69};
	//	Data for packet with options
	//unsigned char packet[] = {0x4f,0x00,0x00,0x64,0xd2,0x34,0x00,0x00,0x40,0x01,0xdc,0xa3,0xc0,0xa8,0xc8,0xa6,0xc0,0xa8,0xc8,0xa9,0x95,0x28,0x03,0x00,0x00,0x00,0x00,0x00,0x9b,0x54,0x97,0xc5,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x00,0x00,0x54,0xb5,0x00,0x01,0x00,0xa6,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69};

	struct iphdr *iph;
	struct sk_buff *skb;
	
	int packet_size = sizeof(packet);

	skb = alloc_skb(ETH_HLEN+packet_size, GFP_KERNEL);
	if (!skb) {
		printk(KERN_ERR "Failed to allocate skb");
		return 0;
	}

	iph = (struct iphdr *)skb_put(skb, sizeof(struct iphdr));
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = htons(sizeof(struct iphdr) + packet_size);
	iph->id = htons(12345);
	iph->frag_off = 0;
	iph->ttl = 128;
	iph->protocol = IPPROTO_ICMP;
	iph->saddr = htonl(0xC0A80101);
	iph->daddr = htonl(0xC0A80102);
	iph->check = 0; 

	memcpy(skb_put(skb, sizeof(packet)), packet, packet_size);
	iph = ip_hdr(skb);

	print_packet(iph);

	test_all(iph, skb);

	print_packet(iph);

	kfree(skb);
	return 0;
}

static void __exit test_module_exit(void) {
	printk(KERN_INFO "End of test");
}


module_init(test_module_init);
module_exit(test_module_exit);

