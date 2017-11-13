
static void clar_print_init(size_t test_count, size_t suite_count, const char *suite_names)
{
	(void)suite_names;
	printf("Loaded %zu suites, with %zu tests, starting\n", suite_count, test_count);
}

static void clar_print_shutdown(const double evaluation_duration,
                                size_t test_count, size_t suite_count, size_t error_count, size_t skip_count)
{
	size_t success_count;
	printf("\n\n");
	clar_report_errors();

	if (_clar.verbosity > 1) {
		if (test_count == 0)
			printf("no tests found");
		else {
			printf("\nran %zu [", test_count);
			success_count = test_count - skip_count - error_count;
			if (success_count)
				printf("%zu passed", success_count);
			if (skip_count)
				printf(" %zu skipped", skip_count);
			if (error_count)
				printf(" %zu failed", error_count);
			printf("] in %zu suits", suite_count);
			printf(" in %.4f seconds", evaluation_duration);
		}
		printf("\n");
	}
}

static void clar_print_error(size_t num, const struct clar_error *error)
{
	printf("  %zu) Failure:\n", num);

	printf("%s::%s [%s:%d]\n",
		error->suite,
		error->test,
		error->file,
		error->line_number);

	printf("  %s\n", error->error_msg);

	if (error->description != NULL)
		printf("  %s\n", error->description);

	printf("\n");
	fflush(stdout);
}

static void clar_print_ontest(const char *test_name, size_t test_number, enum cl_test_status status)
{
	if (_clar.verbosity > 1)
		printf("\n  %s [#%zu] ", test_name, test_number);

	switch(status) {
	case CL_TEST_OK: printf("."); break;
	case CL_TEST_FAILURE: printf("F"); break;
	case CL_TEST_SKIP: printf("S"); break;
	}

	fflush(stdout);
}

static void clar_print_onsuite(const char *suite_name, size_t suite_index, size_t tests_in_suite)
{
	if (_clar.verbosity > 0 || _clar.report_suite_names)
		printf("\n%s", suite_name);

	if (_clar.verbosity > 1)
		printf(" [#%zu with %zu tests]", suite_index, tests_in_suite);
}

static void clar_print_onabort(const char *msg, ...)
{
	va_list argp;
	va_start(argp, msg);
	vfprintf(stderr, msg, argp);
	va_end(argp);
}
