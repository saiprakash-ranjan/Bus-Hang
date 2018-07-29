#include <linux/debugfs.h>
#include <linux/module.h>
#include <asm/io.h>

static int bus_hang_mdp(void *data, u64 *val)
{
	void *p = ioremap(0X01a01000, SZ_4K);
	unsigned int a;

	a = __raw_readl((void *)((unsigned long)p + 0x40));

	*val = a;

	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(bus_hang_fops, bus_hang_mdp, NULL, "%llu\n");

static int bus_hang_init(void)
{
	struct dentry *dir;

	dir = debugfs_create_dir("hang", 0);
	if (!dir)
		return -1;

	debugfs_create_file("bus_hang", 0644, dir, NULL, &bus_hang_fops);

	return 0;
}

module_init(bus_hang_init)
