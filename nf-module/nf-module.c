#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/net.h>
#include <linux/netdevice.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/inet.h>
#include <linux/inetdevice.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/if_arp.h>
#include <linux/icmp.h>
#include <linux/netlink.h>
#include <linux/mroute.h>
#include <linux/fcntl.h>
#include <net/checksum.h>
#include <net/inet_ecn.h>
#include <net/xfrm.h>
#include <net/route.h>
#include <net/sock.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/arp.h>
#include <net/udp.h>
#include <net/icmp.h>
#include <net/inetpeer.h>
#include <net/protocol.h>
#include <net/flow.h>
#include <asm/types.h>
#include <asm/uaccess.h>
#include <linux/zlib.h>
#include <linux/fs.h>
#include "blockchain.h"

static struct nf_hook_ops nfho;

unsigned hook_func(void *priv,
                   struct sk_buff *skb,
                   const struct nf_hook_state *state) {

    struct iphdr *iph;
    struct coption *opt;
    struct cdata *data;
    struct chash *lr;

    if (!skb) {
        return NF_ACCEPT;
    }

    iph = (struct iphdr *)skb_network_header(skb);

    if (!iph) {
        printk(KERN_INFO "No IP header\n");
        return NF_ACCEPT;
    }

    if(iph->protocol == IPPROTO_ICMP) {
	opt = (struct coption *)kmalloc(sizeof(struct coption), GFP_KERNEL);
	data = (struct cdata *)kmalloc(sizeof(struct cdata), GFP_KERNEL);
	lr = (struct chash *)kmalloc(sizeof(struct chash), GFP_KERNEL);

	fill_cdata(data, iph);
	if (extract_coption(iph, opt)==0) {
		update_hash(opt, data, lr);
		update_coption(iph, opt);
	} else {
		init_hash(opt, data);
		add_coption(skb, iph, opt);
	}
	iph->check = 0;
	iph->check = ip_fast_csum((unsigned char *)iph, iph->ihl);
	kfree(data);
	kfree(opt);
	kfree(lr);
    }

    return NF_ACCEPT;
}

static int __init initialize(void) {
    nfho.hook = hook_func;
    nfho.hooknum = NF_INET_POST_ROUTING;
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net,&nfho);
    printk(KERN_INFO "\n=== NF-MODULE INIT ===\n");
    return 0;
}

static void __exit teardown(void) {
    printk(KERN_INFO "\n=== NF-MODULE EXIT ===\n");
    nf_unregister_net_hook(&init_net,&nfho);
}

module_init(initialize);
module_exit(teardown);

MODULE_LICENSE("GPL");
