#include "blockchain.h"

int extract_coption(struct iphdr *iph, struct coption *copt) {
	unsigned char *iph_bytes = (unsigned char *)iph;
	if (iph->ihl == 15 && *(iph_bytes+20) == 149 && *(iph_bytes+21) == 40) {
		copt->type = *(iph_bytes+20);
		copt->len = *(iph_bytes+21);
		copt->sqn = *(iph_bytes+22);
		memcpy(copt->unused,iph_bytes+23, 5);
		memcpy(copt->hash0, iph_bytes+28, 4);
		memcpy(copt->hash1, iph_bytes+32, 4);
		memcpy(copt->hash2, iph_bytes+36, 4);
		memcpy(copt->hash3, iph_bytes+40, 4);
		memcpy(copt->hash4, iph_bytes+44, 4);
		memcpy(copt->hash5, iph_bytes+48, 4);
		memcpy(copt->hash6, iph_bytes+52, 4);
		memcpy(copt->hash7, iph_bytes+56, 4);
		return 0;
	} else {
	return -1;
	}
}

void fill_cdata(struct cdata *cdat, struct iphdr *iph) {
	unsigned char *iph_bytes = (unsigned char *)iph;
	unsigned char pubkey [20] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10};
	memcpy(cdat->ident, iph_bytes+4,2);
	memcpy(cdat->srcip, iph_bytes+12,4);
	memcpy(cdat->dstip, iph_bytes+16,4);
	cdat->proto = *(iph_bytes+9);
	memcpy(cdat->pubkey, pubkey, 20);

	if(iph->ihl > 5) {
		 cdat->sqn = *(iph_bytes + 20 + 2);
	} else {
		cdat->sqn = 1;
	}
}


uint32_t calculateCRC32(const void *data, size_t datalen) {
	return crc32(0, data, datalen);
}

void uint32ToBytes(uint32_t value, unsigned char bytes[4]) {
	bytes[0] = (value >> 24) & 0xFF; // Most significant byte (MSB)
	bytes[1] = (value >> 16) & 0xFF;
	bytes[2] = (value >> 8) & 0xFF;
	bytes[3] = value & 0xFF;         // Least significant byte (LSB)
}

void add_coption(struct sk_buff *skb, struct iphdr *iph, struct coption *copt){
	skb->tail+=copt->len;
	skb->len+=copt->len;
	iph->ihl+=10;
	iph->tot_len = htons(ntohs(iph->tot_len)+copt->len);
	memmove((unsigned char*)iph+20+copt->len, (unsigned char*)iph+20, ntohs(iph->tot_len)-sizeof(struct iphdr) - copt->len);
	*((unsigned char*)iph+20) = copt->type;
	*((unsigned char*)iph+21) = copt->len;
	*((unsigned char*)iph+22) = copt->sqn;
	memcpy((unsigned char*)iph+23, copt->unused, 5);
	memcpy((unsigned char*)iph+28, copt->hash0, 4);
}

void update_coption(struct iphdr *iph, struct coption *copt) {
	*((unsigned char*)iph+20) = copt->type;
	*((unsigned char*)iph+21) = copt->len;
	*((unsigned char*)iph+22) = copt->sqn;
	memcpy((unsigned char*)iph+23, copt->unused, 5);
	memcpy((unsigned char*)iph+28, copt->hash0, 4);
	memcpy((unsigned char*)iph+32, copt->hash1, 4);
	memcpy((unsigned char*)iph+36, copt->hash2, 4);
	memcpy((unsigned char*)iph+40, copt->hash3, 4);
	memcpy((unsigned char*)iph+44, copt->hash4, 4);
	memcpy((unsigned char*)iph+48, copt->hash5, 4);
	memcpy((unsigned char*)iph+52, copt->hash6, 4);
	memcpy((unsigned char*)iph+56, copt->hash7, 4);
}

void calculate_hash(unsigned char *hash, struct cdata *cdat, unsigned int len) {
	uint32_t hash32 = calculateCRC32(cdat, sizeof(struct cdata));
	uint32ToBytes(hash32, hash);
}

void calculate_chash(unsigned char *hash, struct chash *cdat, unsigned int len) {
	uint32_t hash32 = calculateCRC32(cdat, sizeof(struct cdata));
	uint32ToBytes(hash32, hash);
}

void init_hash(struct coption *opt, struct cdata *data) {
	unsigned char zeros[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char hash0[4];
	opt->type = 149;
	opt->len = 40;
	opt->sqn = 1;
	memcpy(opt->unused, zeros, 5);
	calculate_hash(hash0, data, sizeof(struct cdata));
	memcpy(opt->hash0, hash0, 4);
}

void update_hash(struct coption *opt, struct cdata *data, struct chash *lr) {
	unsigned char hash0[4], hash1[4], hash2[4], hash3[4], hash4[4], hash5[4], hash6[4], hash7[4];

	opt->sqn+=1;
        if (opt->sqn % 2 == 0) {
      		memcpy(lr->lhash, opt->hash0, 4);
		calculate_hash(hash0, data, sizeof(struct cdata));
               	memcpy(lr->rhash, hash0, 4);
                calculate_chash(hash1, lr, sizeof(struct chash));
                if (opt->sqn % 4 == 0) {
                     	memcpy(lr->lhash, opt->hash1, 4);
                        memcpy(lr->rhash, hash1, 4);
                        calculate_chash(hash2, lr, sizeof(struct chash));
                        if(opt->sqn % 8 == 0) {
                        	memcpy(lr->lhash, opt->hash2,4);
                                memcpy(lr->rhash, hash2, 4);
                                calculate_chash(hash3, lr, sizeof(struct chash));
                                if(opt->sqn % 16 == 0) {
                                	memcpy(lr->lhash, opt->hash3, 4);
                                        memcpy(lr->rhash, hash3, 4);
                                        calculate_chash(hash4, lr, sizeof(struct chash));                                                           
	           		        if (opt->sqn % 32 == 0) {
                                               	memcpy(lr->lhash, opt->hash4, 4);
                                                memcpy(lr->rhash, hash4, 4);                                                                             
                                                calculate_chash(hash5, lr, sizeof(struct chash));                                                        
                                                if (opt->sqn % 64 == 0) {                                                                                     
                                                    	memcpy(lr->lhash, opt->hash5, 4);                    
                                                        memcpy(lr->rhash, hash5, 4);  
                                                        calculate_chash(hash6, lr, sizeof(struct chash));                                                       
                                                        if (opt->sqn % 128 == 0) {                                                                     
                                                               	memcpy(lr->lhash, opt->hash6, 4);                                                   
                                                                memcpy(lr->rhash, hash6, 4);                                                              
                                                                calculate_chash(hash7, lr, sizeof(struct chash));                              
                                                         }
                                                 }
                                         }
                                 }
                         }
                  }
                  memcpy(opt->hash0, hash0, 4);
                  memcpy(opt->hash1, hash1, 4);
                  memcpy(opt->hash2, hash2, 4);
		  memcpy(opt->hash3, hash3, 4);
		  memcpy(opt->hash4, hash4, 4);
		  memcpy(opt->hash5, hash5, 4);
		  memcpy(opt->hash6, hash6, 4);
	          memcpy(opt->hash7, hash7, 4);
	} else { 
		calculate_hash(hash0, data, sizeof(struct cdata));
		memcpy(opt->hash0, hash0, 4);
	}
}

EXPORT_SYMBOL(add_coption);
EXPORT_SYMBOL(update_coption);
EXPORT_SYMBOL(fill_cdata);
EXPORT_SYMBOL(extract_coption);
EXPORT_SYMBOL(calculate_hash);
EXPORT_SYMBOL(calculate_chash);
EXPORT_SYMBOL(uint32ToBytes);
EXPORT_SYMBOL(init_hash);
EXPORT_SYMBOL(update_hash);

MODULE_LICENSE("GPL");   
