/*
    Copyright [2020] <Taraimovych Igor>
*/

#include "ps.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace ps {

// Constructor by process id
Process::Process(int32_t process_id) {
    std::ifstream stat("/proc/" + std::to_string(process_id) + "/stat");
    stat >>
        pid >>
        comm >>
        state >>
        ppid >>
        pgrp >>
        session >>
        tty_nr >>
        tpgid >>
        flags >>
        minflt >>
        cminflt >>
        majflt >>
        cmajflt >>
        utime >>
        stime >>
        cutime >>
        cstime >>
        priority >>
        nice >>
        num_threads >>
        itrealvalue >>
        starttime >>
        vsize >>
        rss >>
        rsslim >>
        startcode >>
        endcode >>
        startstack >>
        kstkesp >>
        kstkeip >>
        signal >>
        blocked >>
        sigignore >>
        sigcatch >>
        wchan >>
        nswap >>
        cnswap >>
        exit_signal >>
        processor >>
        rt_priority >>
        policy >>
        delayacct_blkio_ticks >>
        guest_time >>
        cguest_time >>
        start_data >>
        end_data >>
        start_brk >>
        arg_start >>
        arg_end >>
        env_start >>
        env_end >>
        exit_code;
}

// Copy constructor
Process::Process(const Process& other) :
    pid(other.pid),
    comm(other.comm),
    state(other.state),
    ppid(other.ppid),
    pgrp(other.pgrp),
    session(other.session),
    tty_nr(other.tty_nr),
    tpgid(other.tpgid),
    flags(other.flags),
    minflt(other.minflt),
    cminflt(other.cminflt),
    majflt(other.majflt),
    utime(other.utime),
    stime(other.stime),
    cutime(other.cutime),
    cstime(other.cstime),
    priority(other.priority),
    nice(other.nice),
    num_threads(other.num_threads),
    itrealvalue(other.itrealvalue),
    starttime(other.starttime),
    vsize(other.vsize),
    rss(other.rss),
    rsslim(other.rsslim),
    startcode(other.startcode),
    endcode(other.endcode),
    startstack(other.startstack),
    kstkesp(other.kstkesp),
    kstkeip(other.kstkeip),
    signal(other.signal),
    blocked(other.blocked),
    sigignore(other.sigignore),
    sigcatch(other.sigcatch),
    wchan(other.wchan),
    nswap(other.nswap),
    cnswap(other.cnswap),
    exit_signal(other.exit_signal),
    processor(other.processor),
    rt_priority(other.rt_priority),
    policy(other.policy),
    delayacct_blkio_ticks(other.delayacct_blkio_ticks),
    guest_time(other.guest_time),
    cguest_time(other.cguest_time),
    start_data(other.start_data),
    end_data(other.end_data),
    start_brk(other.start_brk),
    arg_start(other.arg_start),
    arg_end(other.arg_end),
    env_start(other.env_start),
    env_end(other.env_end),
    exit_code(other.exit_code) {}

// Standard destructor
Process::~Process() {}

namespace fs = std::filesystem;

// Generates Process objects for each process in procfs.
std::vector<Process> getAllProcesses() {
    std::vector<Process> result;
    for (const auto& entry : fs::directory_iterator("/proc/")) {
        std::string path = entry.path();
        size_t slash_pos = path.find_last_of('/');
        std::string name = path.substr(slash_pos + 1,
            path.size() - slash_pos - 1);
        int32_t pid;
        try {
            pid = std::stoi(name);
            Process proc(pid);
            result.push_back(proc);
        } catch(std::exception& e) {
            continue;
        }
    }
    return result;
}

// Gets an actual command for a process.
// If there is no command, returns process name in parentheses.
std::string Process::getCommand() {
    std::ifstream cmdfile("/proc/" + std::to_string(pid) + "/cmdline");
    std::string result;
    std::getline(cmdfile, result);
    if (result == "") {
        result = "[" + comm.substr(1, comm.size() - 2) + "]";
    }
    return result;
}

// Gets the controlling terminal of the process.
std::string Process::getTty() {
    int32_t major = (tty_nr & (255 << 8)) >> 8;
    int32_t minor = (tty_nr & 255) + ((tty_nr & (65535 << 16)) >> 8);
    std::string res;
    switch (major) {
        case 4:
            res = "tty" + std::to_string(minor);
            break;
        case 136:
            res = "pts/" + std::to_string(minor);
            break;
        case 5:
            res = "pts/ptmx";
            break;
        case 188:
            res = "ttyUSB" + std::to_string(minor);
            break;
        case 166:
            res = "ttyACM" + std::to_string(minor);
            break;
        case 247:
            res = "ttyHSL0";
            break;
        case 248:
            res = "ttyHSL0";
            break;
        default:
            res = "?";
            break;
    }
    return res;
}

}  // namespace ps
