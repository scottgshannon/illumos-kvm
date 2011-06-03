#ifndef __KVM_COALESCED_MMIO_H__
#define __KVM_COALESCED_MMIO_H__

/*
 * KVM coalesced MMIO
 *
 * Copyright (c) 2008 Bull S.A.S.
 *
 *  Author: Laurent Vivier <Laurent.Vivier@bull.net>
 *
 */

/* XXX Linux doesn't define these structures here so why do we? */

typedef struct kvm_coalesced_mmio_zone {
	uint64_t addr;
	uint32_t size;
	uint32_t pad;
} kvm_coalesced_mmio_zone_t;

typedef struct kvm_coalesced_mmio_zone_ioc {
	struct kvm_coalesced_mmio_zone zone;
	int kvmid;
} kvm_coalesced_mmio_zone_ioc_t;

#ifdef CONFIG_KVM_MMIO

#define KVM_COALESCED_MMIO_ZONE_MAX 100

/* for KVM_REGISTER_COALESCED_MMIO / KVM_UNREGISTER_COALESCED_MMIO */

typedef struct kvm_coalesced_mmio_dev {
	struct kvm_io_device dev;
	struct kvm *kvm;
	kmutex_t lock;
	int nb_zones;
	struct kvm_coalesced_mmio_zone zone[KVM_COALESCED_MMIO_ZONE_MAX];
} kvm_coalesced_mmio_dev_t;

extern int kvm_coalesced_mmio_init(struct kvm *);
extern void kvm_coalesced_mmio_free(struct kvm *);
extern int kvm_vm_ioctl_register_coalesced_mmio(struct kvm *,
    struct kvm_coalesced_mmio_zone *);
extern int kvm_vm_ioctl_unregister_coalesced_mmio(struct kvm *,
    struct kvm_coalesced_mmio_zone *);

#else

#error "CONFIG_KVM_MMIO must be suupported"

#endif /* CONFIG_KVM_MMIO */

#endif /* __KVM_COALESCED_MMIO_H__ */