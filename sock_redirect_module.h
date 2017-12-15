#ifndef SOCK_REDIRECT_MODULE_H
#define SOCK_REDIRECT_MODULE_H

#define debug 1
#define MOD_TAG "sock_redirect"
#if debug
#define LOG(fmt, args...) \
do{\
    printk("[%s]:", MOD_TAG);\
    printk(fmt, ##args);\
}while(0)

#else
#define LOG(msg)
#endif

static unsigned int nfh_locout_fn(unsigned int hooknum,
                   struct sk_buff *skb,
                   const struct net_device *in,
                   const struct net_device *out,
                   int (*okfn)(struct sk_buff *));

#endif // SOCK_REDIRECT_MODULE_H
