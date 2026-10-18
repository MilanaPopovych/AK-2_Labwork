# Лабораторна робота № 3 ІО-46 Попович Мілана
## Тема: 
Розвертання Linux Kernel в середовищі програмного емулятора Qemu для архітектури процесорів ARM
## Завдання: 
Розвернути програмне середовище, підготувати інструменти (апаратне забезпечення BeagleBone Black). Розвернути ОС (Linux Kernel) в емуляторі QEMU.

---
## Розділи:

[U-boot](https://github.com/MilanaPopovych/AK-2_Labwork/blob/main/lab3/README.md#1-%D0%B2%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BB%D0%B5%D0%BD%D0%BD%D1%8F-%D1%82%D0%B0-%D0%B7%D0%B1%D1%96%D1%80%D0%BA%D0%B0-u-boot) \
[Linux Kernel](https://github.com/MilanaPopovych/AK-2_Labwork/blob/main/lab3/README.md#2-%D0%BE%D1%82%D1%80%D0%B8%D0%BC%D0%B0%D0%BD%D0%BD%D1%8F-%D0%B2%D0%B8%D1%85%D1%96%D0%B4%D0%BD%D0%BE%D0%B3%D0%BE-%D0%BA%D0%BE%D0%B4%D1%83-%D1%8F%D0%B4%D1%80%D0%B0-linux-%D1%82%D0%B0-%D0%BD%D0%B0%D0%BB%D0%B0%D1%88%D1%82%D1%83%D0%B2%D0%B0%D0%BD%D0%BD%D1%8F-%D1%81%D0%B5%D1%80%D0%B5%D0%B4%D0%BE%D0%B2%D0%B8%D1%89%D0%B0-%D1%96%D0%BD%D1%81%D1%82%D1%80%D1%83%D0%BC%D0%B5%D0%BD%D1%82%D0%B0%D1%80%D1%96%D1%8E-%D0%B2-%D0%BE%D0%B1%D0%BE%D0%BB%D0%BE%D0%BD%D1%86%D1%96) \
[BusyBox](https://github.com/MilanaPopovych/AK-2_Labwork/blob/main/lab3/README.md#3-%D0%B2%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BB%D0%B5%D0%BD%D0%BD%D1%8F-%D1%82%D0%B0-%D0%B7%D0%B1%D1%96%D1%80%D0%BA%D0%B0-busybox) \
[QEMU](https://github.com/MilanaPopovych/AK-2_Labwork/blob/main/lab3/README.md#4-%D0%BF%D1%80%D0%BE%D1%88%D0%B8%D0%B2%D0%BA%D0%B0-%D1%82%D0%B0-%D0%B7%D0%B0%D0%B2%D0%B0%D0%BD%D1%82%D0%B0%D0%B6%D0%B5%D0%BD%D0%BD%D1%8F-qemu)

---
## Хід роботи

**Підготовка до завдання**

Встановлення залежностей для збірки (для всіх подальших проєктів) та кореневої папки:
```sh
$ sudo apt install make libncurses5-dev libssl-dev bc bison flex
$ mkdir ~/repos 
```
### 1. Встановлення та збірка U-boot
Команди терміналу:
```sh
$ cd ~/repos
$ git clone https://github.com/u-boot/u-boot.git
$ cd u-boot
$ git tag | grep -v rc | tail -5
$ git checkout v2026.10
$ curl https://patchwork.ozlabs.org/series/130450/mbox/ | git am
$ export PATH=/opt/gcc-arm-8.3-2019.03-x86_64-arm-eabi/bin:$PATH
$ export CROSS_COMPILE=arm-linux-gnueabihf-
$ export ARCH=arm
$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_evm_defconfig
$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j$(nproc)

```
Перевірка результату:
```sh
$ ls -lh MLO u-boot.img
```
Результат збірки U-boot (завантажувач): 

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/e50123e170470a925f72a980334e867f469e14af/lab3/img/Screenshot%20From%202026-10-17%2018-51-32.png" width="700">

Вихідні файли: 
* MLO (завантажувач першого етапу) 
* u-boot.img (завантажувач другого етапу)

### 2. Отримання вихідного коду ядра Linux та налаштування середовища інструментарію в оболонці
Команди терміналу:
```sh
$ cd ~/repos
$ git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
$ cd linux-stable
$ git checkout linux-6.12.y
$ export PATH=/opt/gcc-arm-8.3-2019.03-x86_64-arm-eabi/bin:$PATH
$ export CROSS_COMPILE='ccache arm-eabi-'
$ export ARCH=arm
$ mkdir fragments
$ vim fragments/bbb.cfg
$ ./scripts/kconfig/merge_config.sh \
arch/arm/configs/multi_v7_defconfig fragments/bbb.cfg
$ make -j4 zImage modules am335x-boneblack.dtb
```
Результат:

Вміст файлу *bbb.cfg*:

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/e50123e170470a925f72a980334e867f469e14af/lab3/img/Screenshot%20From%202026-10-17%2019-10-06.png" width="700">

Перевірка створених файлів після збірки: 

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/e50123e170470a925f72a980334e867f469e14af/lab3/img/Screenshot%20From%202026-10-17%2019-13-48.png" width="700">

Вихідні файли:
* arch/arm/boot/zImage
* arch/arm/boot/dts/am335x-boneblack.dtb

### 3. Встановлення та збірка BusyBox
Встановлення крос-компілятора GNU C через менеджер пакетів:
```sh
$ sudo apt install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf -y
```
Конфігурація повнофункціонального BusyBox:
```sh
$ make defconfig
```
При виконанні команди збірки (make -j4) виникла помилка, пов’язана з викликами застарілої функції stime в файлах date.c, rdate.c

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/65431f440c8b2e690ea4175b852bc2555ab3863b/lab3/img/Screenshot%20From%202026-10-17%2015-25-19.png" width="700">

Вирішення: 
```sh
$ sed -i 's/stime(&ts.tv_sec)/clock_settime(CLOCK_REALTIME, \&ts)/g' coreutils/date.c
$ sed -i 's/stime(&remote_time)/clock_settime(CLOCK_REALTIME, \&(struct timespec){remote_time, 0})/g' util-linux/rdate.c
```
Далі запуск компіляції з прапорцем `-fcommon`:
```sh
$ make HOSTCFLAGS="-fcommon" EXTRA_CFLAGS="-fcommon" -j$(nproc)
$ make install
$ mkdir -p _install/{boot,dev,etc\/init.d,lib,proc,root,sys\/kernel\/debug,tmp}
```
Структура init скрипта (`_install/etc/init.d/rcS`):

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/e50123e170470a925f72a980334e867f469e14af/lab3/img/Screenshot%20From%202026-10-17%2016-45-32.png" width="700">

Зробимо його виконуваним:
```sh
$ chmod +x _install/etc/init.d/rcS
```
Зробимо посилання на систему ініціалізації в кореневому каталозі `~/repos/busybox` (щоб ядро могло її запустити):
```sh
$ ln -s bin/busybox _install/init
```
Завантаження та збірка ядра:
```sh
$ cd linux-stable
$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- omap2plus_defconfig
$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j$(nproc) zImage dtbs modules
```
Заповнення каталогу /boot rootfs файлами ядра: 
```sh
$ cd _install/boot
$ cp ~/repos/linux-stable/arch/arm/boot/zImage ~/repos/linux-stable/arch/arm/boot/dts/ti/omap/am335x-boneblack.dtb . ~/repos/linux-stable/System.map . && cp ~/repos/linux-stable/.config ./config
```
Скопіюємо модулі ядра до `lib/modules/$(uname -r)/` у нашій `rootfs`:
```sh
$ cd ~/repos/linux-stable
$ export INSTALL_MOD_PATH=~/repos/busybox/_install
$ export ARCH=arm
$ make modules_install
$ cd -
```
Результати копіювання модулів ядра:

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/114d0646b10894f25526024a5d8a6634eecc4944/lab3/img/Screenshot%20From%202026-10-17%2017-14-03.png" width="700">

Оскільки BusyBox було динамічно злінковано, нам потрібно скопіювати
системні бібліотеки з тулчейна у каталог lib/. Двійковий файл busybox
залежить від libc.so, libm.so та ld-linux.so (який насправді є залежністю від
libc.so). У чому можна впевнитись за допомогою цієї команди:
```sh
$ ${CROSS_COMPILE}readelf -d _install/bin/busybox | grep NEEDED
```
Результат виконання команди (залежності busybox):

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/114d0646b10894f25526024a5d8a6634eecc4944/lab3/img/Screenshot%20From%202026-10-17%2017-17-21.png" width="700">

Але busybox також неявно залежить від libnss.so (виконуючи dlopen()
виклик). Отже, давайте просто встановимо всі бібліотеки тулчейна, щоб
задовольнити всі залежності:
```sh
$ cd _install/lib
$ libc_dir=({CROSS_COMPILE}-gcc -print-sysroot)/lib
$ cp -a $libc_dir/*.so* .
$ cd -
```

Результат виконання команди (встановлення бібліотек toolchain):

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/114d0646b10894f25526024a5d8a6634eecc4944/lab3/img/Screenshot%20From%202026-10-17%2017-35-32.png" width="700">

Конфігурація `/etc`: 
```sh
$ echo 'MODALIAS=.*root:root660@modprobe"MODALIAS"' > \_install/etc/mdev.conf
$ echo 'root:x:0:' > _install/etc/group
$ echo 'root:x:0:0:root:/root:/bin/sh' > _install/etc/passwd
$ echo 'root::10933:0:99999:7:::' > _install/etc/shadow
$ echo "nameserver 8.8.8.8" > _install/etc/resolv.conf
```

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/114d0646b10894f25526024a5d8a6634eecc4944/lab3/img/Screenshot%20From%202026-10-17%2017-39-24.png" width="700">

### 4. Прошивка та завантаження QEMU

Завантаження QEMU: 
```sh
$ sudo apt install qemu-system-arm -y
```
Створення архіву CPIO файлової системи:
```sh
$ cd ~/repos/busybox/_install
$ find . | cpio -o -H newc | gzip > ../rootfs.cpio.gz
$ cd ..
```
Запуск ядра та rootfs у QEMU:
```sh
$ qemu-system-arm -kernel _install/boot/zImage -initrd rootfs.cpio.gz \
-machine virt -nographic -m 512 \
--append "root=/dev/ram0 rw console=ttyAMA0,115200 mem=512M"
```

Результат виконання команди (`kernel log`):

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/e4c22b3b6620e8b20d114d595c2b9ec8104362d2/lab3/img/Screenshot%20From%202026-10-17%2018-05-52.png" width="700">

Команди для перевірки функціональності системи:
```sh
/ # uname -a
/ # ls -l
/ # dmesg | grep init
/ # busybox --help | head -15
/ # poweroff
```

Результат:

<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/e4c22b3b6620e8b20d114d595c2b9ec8104362d2/lab3/img/Screenshot%20From%202026-10-18%2013-55-51.png" width="800">

---

## Висновок
В ході лабораторної роботи було опановано збирання компонентів вбудованої операційної системи та розгортання ядра Linux з 
кореневою файловою системою BusyBox для процесорної архітектури ARM Cortex-A у середовищі емулятора QEMU. 
В результаті було успішно виконано завантаження ядра в емуляторі qemu-system-arm з передачею параметрів ядра та отримано робочий командний рядок оболонки.
