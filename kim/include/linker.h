/*
 * Author: Aurelio Colosimo, 2016
 *
 * This file is part of kim-os project: https://github.com/colosimo/kim-os
 * According to kim-os license, you can do whatever you want with it,
 * as long as you retain this notice.
 */

#ifndef _LINKER_H_
#define _LINKER_H_

/* Misc */
#define attr_used __attribute__((used))
#define attr_weak __attribute__((weak))
#define attr_alias(x) __attribute__((alias(x)))
#define attr_noret __attribute__((noreturn))
#define attr_packed __attribute__((packed))
#define attr_pure __attribute__((pure))
#define attr_aligned(x) __attribute__((aligned(x)))
#define attr_unused __attribute__((unused))

/* Sections */
#define attr_sect(x) __attribute__((section(x))) attr_aligned(4) attr_used
#define attr_devs attr_sect("devs")
#define attr_drvs attr_sect("drvs")
#define attr_cli attr_sect("cli")
#define attr_tasks attr_sect("tasks")

extern struct task_t __start_tasks, __stop_tasks;
#define tasks(i) (&((&__start_tasks)[i]))

/* Section Devices: "devs" */
extern struct k_dev_t __start_devs, __stop_devs;
#define devs(i) (&((&__start_devs)[i]))

/* Section Drivers: "drvs" */
extern struct k_drv_t __start_drvs, __stop_drvs;
#define drvs(i) (&((&__start_drvs)[i]))

/* Section Command Line Interface: "cli" */
extern struct cli_cmd_t __start_cli, __stop_cli;
#define cli(i) (&((&__start_cli)[i]))

#endif /* _LINKER_H_ */
