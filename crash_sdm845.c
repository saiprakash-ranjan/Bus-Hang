#include <linux/debugfs.h>
#include <linux/module.h>
#include <asm/io.h>

static int crash_mtp(void *data, u64 *val)
{
/* qcom,ssc@5c00000 in msm-4.9 */
	void *p = ioremap(0x5c00000, SZ_4K);
	unsigned int a;

	a = __raw_readl((void *)((unsigned long)p + 0x40));

	*val = a;

	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(crash_fops, crash_mtp, NULL, "%llu\n");

static int crash_init(void)
{
	struct dentry *dir;

	dir = debugfs_create_dir("crash", 0);
	if (!dir)
		return -1;

	debugfs_create_file("crash", 0644, dir, NULL, &crash_fops);

	return 0;
}

module_init(crash_init)
