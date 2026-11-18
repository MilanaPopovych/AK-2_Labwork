// SPDX-License-Identifier: Dual BSD/GPL
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Module hello1 (list management)");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_time_node {
	struct list_head list;
	ktime_t time_before;
	ktime_t time_after;
};

/* Статична змінна голови списку  */
static LIST_HEAD(hello_list_head);

int print_hello(void) {
	struct hello_time_node *ptr;

	ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
	if (!ptr) {
		pr_err("Помилка виділення пам'яті\n");
		return -ENOMEM;
	}
	ptr->time_before = ktime_get();
	pr_info("Hello, world!\n");
	ptr->time_after = ktime_get();
	list_add_tail(&ptr->list, &hello_list_head);
	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("Модуль hello1 завантажено\n");
	return 0;
}

static void __exit hello1_exit(void){
	struct hello_time_node *md, *tmp;
	ktime_t delta;

	list_for_each_entry_safe(md, tmp, &hello_list_head, list) {
		delta = ktime_sub(md->time_after, md->time_before);
		pr_info("Час, витрачений на друк: %lld ns\n", ktime_to_ns(delta));
		list_del(&md->list);
		kfree(md);
	}
	pr_info("Модуль hello1 вивантажено\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
