/*
    Copyright [2020] <Taraimovych Igor>
*/

#ifndef PS_INCLUDE_PS_HPP_
#define PS_INCLUDE_PS_HPP_

#if   defined(__linux) || defined(__linux__)

#elif defined(__APPLE__)

#endif

#include <cstdint>
#include <string>
#include <vector>

namespace ps {

struct Process {
    public:
        // Standard constructor is deprecated
        Process(void) = delete;

        // Constructor by process id
        explicit Process(int32_t pid);

        // Copy constructor
        Process(const Process& other);

        // Standard destructor
        ~Process();

        // Gets an actual command for a process.
        // If there is no command, returns process name in parentheses
        std::string getCommand();

        // Gets the controlling terminal of the process.
        std::string getTty();

        // The process ID.
        int32_t     pid;

        // The filename of the executable, in parentheses.
        std::string comm;

        // Process state
        char        state;

        // The PID of the parent of this process.
        int32_t     ppid;

        // The process group ID of the process.
        int32_t     pgrp;

        // The session ID of the process.
        int32_t     session;

        // The controlling terminal of the process.
        int32_t     tty_nr;

        // The ID of the foreground process group
        // of the controlling terminal of the process.
        int32_t     tpgid;

        // The kernel flags word of the process.
        uint32_t    flags;

        // The number of minor faults the process has made
        // which have not required loading a memory page from disk.
        uint64_t    minflt;

        // The number of minor faults that the process's
        // waited-for children have made.
        uint64_t    cminflt;

        // The number of major faults the process has made
        // which have required loading a memory page from disk.
        uint64_t    majflt;

        // The number of major faults that the process's
        // waited-for children have made.
        uint64_t    cmajflt;

        // Amount of time that this process has been scheduled
        // in user mode, measured in clock ticks.
        uint64_t    utime;

        // Amount of time that this process has been scheduled
        // in kernel mode, measured in clock ticks.
        uint64_t    stime;

        // Amount of time that this process's waited-for children
        // have been scheduled in user mode, measured in clock ticks.
        int64_t     cutime;

        // Amount of time that this process's waited-for children
        // have been scheduled in kernel mode, measured in clock ticks.
        int64_t     cstime;

        // For processes running a
        // real-time scheduling policy (policy below; see
        // sched_setscheduler(2)), this is the negated scheduling
        // priority, minus one; that is, a number in the
        // range -2 to -100, corresponding to real-time priorities
        // 1 to 99.  For processes running under a non-real-time
        // scheduling policy, this is the raw nice
        // value (setpriority(2)) as represented in the kernel.
        // The kernel stores nice values as numbers in the
        // range 0 (high) to 39 (low), corresponding to the
        // user-visible nice range of -20 to 19.
        int64_t     priority;

        // The nice value (see setpriority(2)), a value in the
        // range 19 (low priority) to -20 (high priority).
        int64_t     nice;

        // Number of threads in this process.
        int64_t     num_threads;

        // The time in jiffies before the next SIGALRM is sent
        // to the process due to an interval timer.
        int64_t     itrealvalue;

        // The time the process started after system boot.
        uint64_t    starttime;

        // Virtual memory size in bytes.
        uint64_t    vsize;

        // Resident Set Size: number of pages the process has
        // in real memory.
        int64_t     rss;

        // Current soft limit in bytes on the rss of the process.
        uint64_t    rsslim;

        // The address above which program text can run.
        uint64_t    startcode;

        // The address below which program text can run.
        uint64_t    endcode;

        // The address of the start (i.e., bottom) of the stack.
        uint64_t    startstack;

        // The current value of RSP (stack pointer), as found
        // in the kernel stack page for the process.
        uint64_t    kstkesp;

        // The current RIP (instruction pointer).
        uint64_t    kstkeip;

        // The bitmap of pending signals, displayed as a decimal number.
        uint64_t    signal;

        // The bitmap of blocked signals, displayed as a decimal number.
        uint64_t    blocked;

        // The bitmap of ignored signals, displayed as a decimal number.
        uint64_t    sigignore;

        // The bitmap of caught signals, displayed as a decimal number.
        uint64_t    sigcatch;

        // This is the "channel" in which the process is waiting.
        // It is the address of a location in the kernel
        // where the process is sleeping.
        uint64_t    wchan;

        // Number of pages swapped (not maintained).
        uint64_t    nswap;

        // Cumulative nswap for child processes (not maintained).
        uint64_t    cnswap;

        // Signal to be sent to parent when we die.
        int32_t     exit_signal;

        // CPU number last executed on.
        int32_t     processor;

        // Real-time scheduling priority, a number in the range
        // 1 to 99 for processes scheduled under a real-time
        // policy, or 0, for non-real-time processes.
        uint32_t    rt_priority;

        // Scheduling policy.
        uint32_t    policy;

        // Aggregated block I/O delays, measured in clock ticks (centiseconds).
        uint64_t    delayacct_blkio_ticks;

        // Guest time of the process (time spent running a virtual
        // CPU for a guest operating system), measured in clock ticks.
        uint64_t    guest_time;

        // Guest time of the process's children, measured in clock ticks.
        int64_t     cguest_time;

        // Address above which program initialized and
        // uninitialized (BSS) data are placed.
        uint64_t    start_data;

        // Address below which program initialized and
        // uninitialized (BSS) data are placed.
        uint64_t    end_data;

        // Address above which program heap can be expanded with brk(2).
        uint64_t    start_brk;

        // Address above which program command-line arguments (argv) are placed.
        uint64_t    arg_start;

        // Address below program command-line arguments (argv) are placed.
        uint64_t    arg_end;

        // Address above which program environment is placed.
        uint64_t    env_start;

        // Address below which program environment is placed.
        uint64_t    env_end;

        // The thread's exit status in the form reported by waitpid(2).
        int32_t     exit_code;
};

// Generates Process objects for each process in procfs.
std::vector<Process> getAllProcesses();

}  // namespace ps

#endif  // PS_INCLUDE_PS_HPP_
