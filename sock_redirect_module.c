#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

#include <linux/ip.h>

#include "sock_redirect_module.h"

MODULE_LICENSE("GPL2");
MODULE_AUTHOR("colorfulshark@hotmail.com");


struct nf_hook_ops nfh_ops[] = {
    [0] = {
        .hook = nfh_locout_fn,
        .owner = THIS_MODULE,
        .pf = NFPROTO_IPV4,
        .hooknum = NF_INET_LOCAL_OUT,
        .priority = NF_IP_PRI_FIRST,
    },
};

static unsigned int nfh_locout_fn(unsigned int hooknum,
                   struct sk_buff *skb,
                   const struct net_device *in,
                   const struct net_device *out,
                   int (*okfn)(struct sk_buff *))
{
    u8 *sip;
    u8 *dip;
    struct iphdr *iph;
    LOG("%s\n", __FUNCTION__);
    LOG(out->name);
    iph = ip_hdr(skb);
    sip = (u8 *)&iph->saddr;
    dip = (u8 *)&iph->daddr;
    LOG("saddr: %d.%d.%d.%d\n", sip[0], sip[1], sip[2], sip[3]);
    LOG("daddr: %d.%d.%d.%d\n", dip[0], dip[1], dip[2], dip[3]);


    return NF_ACCEPT;
}



static int mod_init(void)
{
    int err;
    LOG("sock redirect module init\n");
    LOG("prepare to register hook op\n");
    err = nf_register_hooks(nfh_ops, ARRAY_SIZE(nfh_ops));
    if(err < 0)
        goto err_nf_reg_hook;
    return 0;

err_nf_reg_hook:
    LOG("fail to register hook op\n");
    return err;

}

static void mod_exit(void)
{
    LOG("sock redirect module exit\n");
    LOG("prepare to unregister hook op\n");
    nf_unregister_hooks(nfh_ops, ARRAY_SIZE(nfh_ops));
}

module_init(mod_init);
module_exit(mod_exit);
