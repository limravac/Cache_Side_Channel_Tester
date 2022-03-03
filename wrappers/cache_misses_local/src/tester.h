const char* prefix = "/*\n"
" * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.\n"
" *\n"
" * Licensed under the OpenSSL license (the \"License\").  You may not use\n"
" * this file except in compliance with the License.  You can obtain a copy\n"
" * in the file LICENSE in the source distribution or at\n"
" * https://www.openssl.org/source/license.html\n"
" */\n"
"#include <string.h>\n"
"#include <stdlib.h>\n"
"#include <stdio.h>\n"
"#include <unistd.h>\n"
"#include <linux/perf_event.h>\n"
"#include <linux/hw_breakpoint.h>\n"
"#include <sys/ioctl.h>\n"
"#include <asm/unistd.h>\n"
"#include <openssl/crypto.h>"
"int main()\n"
"{\n";
const char* suffix = "};\n"
"    long a_fd, m_fd;\n"
"    long long accesses, misses;\n"
"\n"
"\n"
"    /*initializing and starting perf*/\n"
"    struct perf_event_attr pe;\n"
"    memset(&pe, 0, sizeof(struct perf_event_attr));\n"
"\n"
"    /*group*/\n"
"    pe.type = PERF_TYPE_HW_CACHE;\n"
"    pe.size = sizeof(struct perf_event_attr);\n"
"    pe.config = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16);\n"
"    pe.disabled = 1;\n"
"    pe.exclude_kernel = 1;\n"
"    pe.exclude_hv = 1;\n"
"    a_fd = syscall(__NR_perf_event_open, &pe, 0, -1, -1, 0);\n"
"    if (a_fd < 0)\n"
"        return -1;\n"
"    \n"
"    /*child*/\n"
"    pe.disabled = 0;\n"
"    pe.config = PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16);\n"
"    m_fd = syscall(__NR_perf_event_open, &pe, 0, -1, a_fd, 0);\n"
"\n"
"    /*enable and start perf*/\n"
"    ioctl(a_fd, PERF_EVENT_IOC_RESET, 0);\n"
"    ioctl(a_fd, PERF_EVENT_IOC_ENABLE, 0);\n"
"\n"
"    /*start of section - activity to measure*/\n"
"    printf(\"poop\");\n"
"    /*end of section - activity to measure*/\n"
"\n"
"    /*stopping perf*/\n"
"    ioctl(m_fd, PERF_EVENT_IOC_DISABLE, 0);\n"
"    \n"
"    /*reading outputs and printing them*/\n"
"    read(m_fd, &misses, sizeof(long long));\n"
"    read(a_fd, &accesses, sizeof(long long));\n"
"    printf(\"%lld\\n\", accesses);\n"
"    printf(\"%lld\\n\", misses);\n"
"\n"
"    /*cleanup and exit*/\n"
"    close(m_fd);\n"
"    close(a_fd);\n"
"    return 0;\n"
"}";
