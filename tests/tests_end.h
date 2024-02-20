// #include "tests.h"

int main() {
	#ifdef _WIN32
		// So we can display unicode... windows rly took an L here ngl
		SetConsoleOutputCP(65001);

		// https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			testoutputwidth = csbi.srWindow.Right - csbi.srWindow.Left + 1 - 17 /* width of " PASS " + timing */;
	#endif

	#ifndef STOP_CATCHING_SIGNALS
		// Win32 so simple
		#if defined(_WIN32)
			// https://stackoverflow.com/questions/1992816/how-to-handle-seg-faults-under-windows
			SetUnhandledExceptionFilter(plswork);

		// linux = bruh
		#else
			// https://stackoverflow.com/questions/10202941/segmentation-fault-handling
			struct sigaction sa = {0};
			sigemptyset(&sa.sa_mask);
			sa.sa_flags     = SA_NODEFER;
			sa.sa_sigaction = handler;
			sigaction(SIGSEGV, &sa, NULL); /* ignore whether it works or not */ 
		#endif
	#endif


	if(init) init();

	// Generates the array of funcs that are the tests in the file
	TESTFUNCRET (*testfuncs[])TESTFUNCARGS = { TESTFUNGEN() };

	// Initializes variables for number of total nad failed tests
	int failed = 0;
	int tests = __COUNTER__ - 1;
	
	printf("Executing %d tests.\n", tests);
	for (int i = 0, len = tests; i < len; i ++) {

		// SigSegV Exception handling
		if(!setjmp(owo)) {
			if (testfuncs[i]()) failed ++;
		} else {
			char* subtest = "subtest", * test = "test";
			puts("");
			if(subtests_run) printf(SUBTESTINDENT);
			printf(TERMREDBGBLACK" FATAL ERROR " TERMRESET" Recieved");

			#if defined(_WIN32)
			// Found on lines 1350+ in winnt.h. Pretty self explanatory so no comments needed ~~unlike for linux bruh~~.
			switch (sigthing) {
				case STATUS_FLOAT_DIVIDE_BY_ZERO: printf(TERMREDBOLD " STATUS_FLOAT_DIVIDE_BY_ZERO" TERMRESET); break;
				case STATUS_INTEGER_DIVIDE_BY_ZERO: printf(TERMREDBOLD " STATUS_INTEGER_DIVIDE_BY_ZERO" TERMRESET); break;
				case STATUS_STACK_OVERFLOW: printf(TERMREDBOLD " STATUS_STACK_OVERFLOW" TERMRESET); break;
				case STATUS_ACCESS_VIOLATION: printf(TERMREDBOLD " STATUS_ACCESS_VIOLATION" TERMRESET); break;
				default: printf(TERMREDBOLD" STATUS_UNKNOWN (%X)" TERMRESET, sigthing);
			}
			#else
			// an impressive amount of signals tho ngl
			// Comments taken from https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-sigaction-examine-change-signal-action
			switch (sigthing) {
				case SIGSEGV:   printf(TERMREDBOLD " SIGSEGV (Accessing %p)" TERMRESET, sigaddr); break; // Incorrect access to memory.
				case SIGABRT:   printf(TERMREDBOLD " SIGABRT" TERMRESET); break; // Abnormal termination (sent by abort()).
				case SIGALRM:   printf(TERMREDBOLD " SIGALRM" TERMRESET); break; // A timeout signal (sent by alarm()).
				case SIGBUS:    printf(TERMREDBOLD " SIGBUS" TERMRESET); break; // Bus error (available only when running on MVS™ 5.2 or higher).
				case SIGFPE:    printf(TERMREDBOLD " SIGFPE" TERMRESET); break; // Arithmetic exceptions that are not masked, for example, overflow, division by zero, and incorrect operation.
				case SIGHUP:    printf(TERMREDBOLD " SIGHUP" TERMRESET); break; // A controlling terminal is suspended, or the controlling process ended.
				case SIGILL:    printf(TERMREDBOLD " SIGILL" TERMRESET); break; // Detection of an incorrect function image.
				case SIGINT:    printf(TERMREDBOLD " SIGINT" TERMRESET); break; // Interactive attention.
				case SIGKILL:   printf(TERMREDBOLD " SIGKILL" TERMRESET); break; // A termination signal that cannot be caught or ignored.
				case SIGPIPE:   printf(TERMREDBOLD " SIGPIPE" TERMRESET); break; // A write to a pipe that is not being read.
				case SIGPOLL:   printf(TERMREDBOLD " SIGPOLL" TERMRESET); break; // Pollable event occurred (available only when running on MVS 5.2 or higher).
				case SIGPROF:   printf(TERMREDBOLD " SIGPROF" TERMRESET); break; // Profiling timer expired (available only when running on MVS 5.2 or higher).
				case SIGQUIT:   printf(TERMREDBOLD " SIGQUIT" TERMRESET); break; // A quit signal for a terminal.
				case SIGSYS:    printf(TERMREDBOLD " SIGSYS" TERMRESET); break; // Bad system call issued (available only when running on MVS 5.2 or higher).
				case SIGTERM:   printf(TERMREDBOLD " SIGTERM" TERMRESET); break; // Termination request sent to the program.
				case SIGTRAP:   printf(TERMREDBOLD " SIGTRAP" TERMRESET); break; // Internal for use by dbx or ptrace.
				case SIGURG:    printf(TERMREDBOLD " SIGURG" TERMRESET); break; // High bandwidth data is available at a socket (available only when running on MVS 5.2 or higher).
				case SIGUSR1:   printf(TERMREDBOLD " SIGUSR1" TERMRESET); break; // Intended for use by user applications.
				case SIGUSR2:   printf(TERMREDBOLD " SIGUSR2" TERMRESET); break; // Intended for use by user applications.
				case SIGVTALRM: printf(TERMREDBOLD " SIGVTALRM" TERMRESET); break; // Virtual timer has expired (available only when running on MVS 5.2 or higher).
				case SIGXCPU:   printf(TERMREDBOLD " SIGXCPU" TERMRESET); break; // CPU time limit exceeded (available only when running on MVS 5.2 or higher). If a process runs out of CPU time and SIGXCPU is caught or ignored, a SIGKILL is generated.
				case SIGXFSZ:   printf(TERMREDBOLD " SIGXFSZ" TERMRESET); break; // File size limit exceeded.
				case SIGCHLD:   printf(TERMREDBOLD " SIGCHLD" TERMRESET); break; // An ended or stopped child process (SIGCLD is an alias name for this signal).
				case SIGWINCH:  printf(TERMREDBOLD " SIGWINCH" TERMRESET); break; // Window size has changed (available only when running on MVS 5.2 or higher).
				case SIGSTOP:   printf(TERMREDBOLD " SIGSTOP" TERMRESET); break; // A stop signal that cannot be caught or ignored.
				case SIGTSTP:   printf(TERMREDBOLD " SIGTSTP" TERMRESET); break; // A stop signal for a terminal.
				case SIGTTIN:   printf(TERMREDBOLD " SIGTTIN" TERMRESET); break; // A background process attempted to read from a controlling terminal.
				case SIGTTOU:   printf(TERMREDBOLD " SIGTTOU" TERMRESET); break; // A background process attempted to write to a controlling terminal. 
				case SIGCONT:   printf(TERMREDBOLD " SIGCONT" TERMRESET); break; // https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-sigaction-examine-change-signal-action
				default: 				printf(TERMREDBOLD " SIGUNKNOWN (%X)" TERMRESET, sigthing);
			}
			#endif
			
			
			printf(" on %s %d\n",
				subtests_run ? subtest : test,
				(subtests_run > 0 ? subtests_run : i) + 1);
			subtests_run = 0;
			subtests_passed = 0;
			failed ++;
		}
	}
	if(!failed) printf(TERMGREENBOLD "ALL TESTS PASSED!!" TERMRESET" Nice job bro.");
	else if(failed == tests) printf(TERMREDBOLD "All tests failed. Spectacular." TERMRESET);
	else printf("%d / %d tests passed.", tests - failed, tests);
	printf(" Took " TERMBLUEBOLD "%.2f ms" TERMRESET "\n", tests_totaltime * 1000.0);
	return 0;
}
