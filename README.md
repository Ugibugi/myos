#Kernel test
Mały test bootowalnego kernela ze wsparciem C++

##Budowanie
Do zbudowania binarki wymagane są: 
-i686-elf-g++
-nasm

Dodatkowo do zrobienia obrazu iso potrzebny jest:
-grub-mkrescue

Polecenia do zbudowania

```
make
make iso

```
iso można odpalić w qemu poleceniem

```
qemu-system-i386 -cdrom myos.iso
```
lub

```
./run
```

