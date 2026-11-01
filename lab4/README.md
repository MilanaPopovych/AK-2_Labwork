# Лабораторна робота № 4 ІО-46 Попович Мілана
## Тема: 
Розроблення модулів Linux Kernel (частина 1)
## Завдання: 
Створити модуль ядра, який динамічно завантажується та вивантажується в систему, та додати параметр howmany до виконуваного файлу. 
Реалізувати роботу зі списком і пам'яттю. 

---
## Розділи:

[Реалізація модуля ядра]() \
[Параметризація]() \
[Зв'язані списки та пам'ять]() \
[Очищення ресурсів]() \
[Збирання]()

---
## Хід роботи

**Підготовка до завдання**

Перед виконанням make, до команд export, які використовувалися для
збирання ядра, додаємо export KDIR=шлях_до_каталогу_ядра
(наприклад, $HOME/repos/linux-stable)
```sh
$ export KDIR=$HOME/repos/linux/stable
```
Перевіряємо встановлення шляхів за допомогою `echo`

Результат виконання команди:
<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/00c207662087ff8e4941261c1cd76fa7ed484237/lab4/img/Screenshot%20From%202026-11-01%2016-44-50.png" width="800">

### 1. Реалізація модуля ядра
На цьому етапі, нам треба модифікувати вихідний файл `hello.c`, прописавши функції ініціалізації (`__init`) та завершення (`__exit`).

Вміст файлу hello.c: 
```c
// SPDX-License-Identifier: Dual BSD/GPL
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_time_node {
	struct list_head list;
	ktime_t time;
};

/* Статична змінна голови списку  */
static LIST_HEAD(hello_list_head);

static uint howmany = 1;
module_param(howmany, uint, S_IRUGO);
/* Опис параметра */
MODULE_PARM_DESC(howmany, "Кількість виведень повідомлення Hello, world!");

static int __init hello_init(void)
{
	uint i;
	struct hello_time_node *ptr; 
	/*Якщо знач. більше 10 -- друкуємо помилку і повертаємо -EINVAL */
	if (howmany > 10) {
		printk(KERN_ERR "Помилка: Параметр howmany більший за 10\n");
		return -EINVAL;	
	}
	/* Якщо знач. 0 або між 5 і 10 -- попередження і вивід */
	if (howmany == 0 || (howmany >= 5 && howmany <= 10)) {
		printk(KERN_WARNING "Параметр howmany дорівнює %u\n", howmany);
	}
	/* Вивід Hello, world! відповідно до значення howmany */
	for (i=0; i < howmany; i++) {
		ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
		/* Перевірка виділення пам'яті */
		if (!ptr) {
			printk(KERN_ERR "Помилка! Не вдалося виділити пам'ять\n");
			struct hello_time_node *md, *tmp;
			list_for_each_entry_safe(md, tmp, &hello_list_head, list) {
			list_del(&md->list);
			kfree(md);
			}
			return -ENOMEM;
		}
		/* Заносимо поточний час ядра у відповідне поле */
		ptr->time = ktime_get(); 
		list_add_tail(&ptr->list, &hello_list_head);
		printk(KERN_INFO "Hello, world!\n");
	}
	return 0;
}

static void __exit hello_exit(void){
	/* Вказівники для поточного ел-та та тимчасового */
	struct hello_time_node *md, *tmp;
	/* Прохід по списку з безпечним вилученням ел-тів */
	list_for_each_entry_safe(md, tmp, &hello_list_head, list) {
		/* Час події в наносек. */
		printk(KERN_INFO "Час події: %lld ns\n", ktime_to_ns(md->time));
		/* Вилучення ел-та зі списку */
		list_del(&md->list);
		/* Звільнення пам'яті */
		kfree(md);
	}
	printk(KERN_INFO "Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);
```

### 2. Параметризація
Команди терміналу:
```sh

```
Результат:

### 3. Зв'язані списки та пам'ять

### 4. Очищення ресурсів

### 5. Збирання

---

## Висновок
В ході лабораторної роботи було успішно розроблено, скомпільовано та протестовано динамічний модуль ядра Linux. 
Закріплено навички роботи з параметрами ядра, їх перевірки та обробкою непридатних значень із поверненням відповідних кодів помилок.
Практично реалізовано динамічне управління пам'яттю у просторі ядра за допомогою функцій kmalloc та kfree, 
відпрацьовано процес крос-компіляції модулів ядра за допомогою системи збирання Kbuild/Makefile та їх перевірки 
увімкнення/вивантаження (insmod/rmmod) у віртуальному середовищі QEMU.
