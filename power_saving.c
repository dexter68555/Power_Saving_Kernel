#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

#define PROC_NAME "PowerSaving"

static int power_saving_enabled = 0;

static int proc_show(struct seq_file *m, void *v) {
    seq_printf(m, "Power Saving: %s\n", power_saving_enabled ? "Enabled" : "Disabled");
    return 0;
}

static ssize_t proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos) {
    char buf[10];

    if (count > 9) {
        return -EINVAL;
    }

    if (copy_from_user(buf, buffer, count)) {
        return -EFAULT;
    }

    buf[count] = '\0';

    if (strncmp(buf, "enable", 6) == 0) {
        power_saving_enabled = 1;
    } else if (strncmp(buf, "disable", 7) == 0) {
        power_saving_enabled = 0;
    } else {
        return -EINVAL;
    }

    return count;
}

static int proc_open(struct inode *inode, struct file *file) {
    return single_open(file, proc_show, NULL);
}

static const struct proc_ops proc_ops = {
    .proc_open = proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
    .proc_write = proc_write,
};

static int __init power_saving_init(void) {
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
    return 0;
}

static void __exit power_saving_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

module_init(power_saving_init);
module_exit(power_saving_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple power-saving control module");