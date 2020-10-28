/*
    Copyright [2020] <Taraimovych Igor>
*/

#include <iostream>
#include <vector>

#include "ps.hpp"

int main(void) {
    std::vector<ps::Process> res;
    res = ps::getAllProcesses();
    for (auto e : res) {
        std::cout.width(7);
        std::cout << e.pid << " " << e.state << std::endl;
    }
    // ps::Process test(1);

    /*std::cout << test.pid << " " << test.comm << " " << test.state << " " <<
    test.ppid << " " <<
        test.pgrp << " " << test.session << " " << test.tty_nr << " " <<
        test.tpgid << " " << test.flags << " " << test.minflt << " " <<
        test.cminflt << " " <<
        test.majflt << " " << test.cmajflt << " " <<
        test.utime << " " << test.stime << " " << test.cutime << " " <<
        test.cstime << " " <<
        test.priority << " " << test.nice << " " <<
        test.num_threads << " " << test.itrealvalue << " " <<
        test.starttime << " " << test.vsize << " " <<
        test.rss << " " << test.rsslim << " " << test.startcode << " " <<
        test.endcode << " " <<
        test.startstack << " " <<
        test.kstkesp << " " << test.kstkeip << " " << test.signal << " " <<
        test.blocked << " " <<
        test.sigignore << " " << test.sigcatch << " " <<
        test.wchan << " " << test.nswap << " " << test.cnswap << " " <<
        test.exit_signal << " " <<
        test.processor << " " <<
        test.rt_priority << " " << test.policy << " " <<
        test.delayacct_blkio_ticks << " " <<
        test.guest_time << " " << test.cguest_time << " " <<
        test.start_data << " " <<
        test.end_data << " " <<
        test.start_brk << " " << test.arg_start << " " <<
        test.arg_end << " " << test.env_start << " " << test.env_end << " " <<
        test.exit_code;*/
    return EXIT_SUCCESS;
}
