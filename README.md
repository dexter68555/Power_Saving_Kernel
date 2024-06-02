# Power_Saving_Kernel
This is a Linux Kernel in C that toggle the power saving state.

Explanation
- proc_create: This function creates an entry in the /proc filesystem.
- proc_show: Displays the current power-saving status.
- proc_write: Allows writing to the proc file to enable or disable power saving.
- module_init and module_exit: These macros define the initialization and cleanup functions of the module.

How to install it:
Step 1:
Run the following command.
```sh
make
```

Step 2:
Run the following command.
```sh
sudo insmod power_saving.ko
```

Step 3:
You can check the kernel logs to see if your module loaded correctly.
```sh
dmesg | tail
```

How to use it:
Enabling power saving
```sh
echo "enable" | sudo tee /proc/PowerSaving
```

Disabling power saving
```sh
echo "disable" | sudo tee /proc/PowerSaving
```

Check the current power saving stat
```sh
cat /proc/PowerSaving
```

How to remove the kernel:
Please run the following command to remove the kernel.
```sh
sudo rmmod <the_name_you_used>
make clean
```
