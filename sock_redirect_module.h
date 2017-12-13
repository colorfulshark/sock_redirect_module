#ifndef SOCK_REDIRECT_MODULE_H
#define SOCK_REDIRECT_MODULE_H

static unsigned int nfh_pre_fn(unsigned int hooknum,
                   struct sk_buff *skb,
                   const struct net_device *in,
                   const struct net_device *out,
                   int (*okfn)(struct sk_buff *));

#endif // SOCK_REDIRECT_MODULE_H
