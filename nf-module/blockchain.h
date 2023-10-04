#pragma once

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/errno.h>
//#include <linux/slab.h>
//#include <linux/netfilter.h>
//#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/string.h>
//#include <linux/init.h>
#include <linux/net.h>
#include <linux/netdevice.h>
#include <linux/socket.h>
#include <linux/sockios.h>
//#include <linux/inet.h>
//#include <linux/inetdevice.h>
#include <linux/netdevice.h>
//#include <linux/etherdevice.h>
#include <linux/if_arp.h>
#include <linux/icmp.h>
#include <linux/netlink.h>
#include <linux/mroute.h>
#include <linux/fcntl.h>
//#include <net/checksum.h>
//#include <net/inet_ecn.h>
//#include <net/xfrm.h>
//#include <net/route.h>
//#include <net/sock.h>
//#include <net/ip.h>
//#include <net/tcp.h>
//#include <net/arp.h>
//#include <net/udp.h>
//#include <net/icmp.h>
//#include <net/inetpeer.h>
//#include <net/protocol.h>
//#include <net/flow.h>
#include <asm/types.h>
//#include <asm/uaccess.h>
//#include <linux/zlib.h>



struct coption {
	unsigned char type;
	unsigned char len;
	unsigned char sqn;
	unsigned char unused[5];
	unsigned char hash0[4];
	unsigned char hash1[4];
	unsigned char hash2[4];
	unsigned char hash3[4];
	unsigned char hash4[4];
	unsigned char hash5[4];
	unsigned char hash6[4];
	unsigned char hash7[4];
};

struct cdata {
	unsigned char ident[2];
	unsigned char srcip[4];
	unsigned char dstip[4];
	unsigned char proto;
	unsigned char pubkey[20];
	unsigned char sqn;
};

struct chash{
	unsigned char lhash[4];
	unsigned char rhash[4];
};

int extract_coption(struct iphdr *iph, struct coption *copt);
void fill_cdata(struct cdata *cdat, struct iphdr *iph);
void calculate_hash(unsigned char *hash, struct cdata *cdat, unsigned int len);
void calculate_chash(unsigned char *hash, struct chash *cdat, unsigned int len);
uint32_t calculateCRC32(const void *data, size_t datalen);
void uint32ToBytes(uint32_t value, unsigned char bytes[4]);
void add_coption(struct sk_buff *skb, struct iphdr *iph, struct coption *copt);
void update_coption(struct iphdr *iph, struct coption *copt);
void init_hash(struct coption *opt, struct cdata *data);
void update_hash(struct coption *opt, struct cdata *data, struct chash *lr);

#endif 
