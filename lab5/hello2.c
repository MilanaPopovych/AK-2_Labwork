// SPDX-License-Identifier: Dual BSD/GPL
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include "hello1.h"


MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Module hello2 (calling print_hello)");
MODULE_LICENSE("Dual BSD/GPL");

static uint howmany = 1;
module_param(howmany, uint, 0444);
MODULE_PARM_DESC(howmany, "К-сть виведень Hello, world!");

static int __init hello2_init(void)
{
	uint i;
	int ret;

	if (howmany > 10) {
		pr_err("Помилка: Параметр howmany більший за 10 (%u)\n", howmany);
		return -EINVAL;
	}
	if (howmany == 0 || (howmany >= 5 && howmany <= 10)) {
		pr_warn("Параметр howmany дорівнює %u\n", howmany);
	}
	for (i = 0; i < howmany; i++) {
		ret = print_hello();
		if (ret) {
			pr_err("Помилка виклику print_hello() на ітерації %u\n", i);
			return ret;
		}
	}
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Goodbye, world!\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
