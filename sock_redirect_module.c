#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

#include "sock_redirect_module.h"


#define MOD_TAG "sock_redirect"
#define LOG(msg) printk("[%s]:%s\n", MOD_TAG, msg)

MODULE_LICENSE("GPL3");
MODULE_AUTHOR("colorfulshark@hotmail.com");


struct nf_hook_ops nfh_pre_op = {
    .hook = nfh_pre_fn,
    .owner = THIS_MODULE,
    .pf = NFPROTO_IPV4,
    .hooknum = NF_INET_LOCAL_OUT,
    .priority = NF_IP_PRI_FIRST,
};

static unsigned int nfh_pre_fn(unsigned int hooknum,
                   struct sk_buff *skb,
                   const struct net_device *in,
                   const struct net_device *out,
                   int (*okfn)(struct sk_buff *))
{
    LOG(__FUNCTION__);
    return NF_ACCEPT;
}



static int mod_init(void)
{
    int err;
    LOG("sock redirect module init\n");
    LOG("prepare to register hook op\n");
    err = nf_register_hook(&nfh_pre_op);
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
    nf_unregister_hook(&nfh_pre_op);
}

module_init(mod_init);
module_exit(mod_exit);
