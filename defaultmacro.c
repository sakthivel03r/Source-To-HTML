/* Default Macro Present in All Library File in C */

char *Macro[] = {
    /* --- Compiler predefined macros --- */
    "__FILE__", "__LINE__", "__DATE__", "__TIME__", "__func__",
    "__STDC__", "__STDC_VERSION__", "__STDC_HOSTED__",
    "__STDC_NO_THREADS__", "__STDC_NO_ATOMICS__", "__STDC_NO_VLA__",
    "__cplusplus",

    /* --- stddef.h --- */
    "NULL", "offsetof",

    /* --- stdio.h --- */
    "EOF", "SEEK_SET", "SEEK_CUR", "SEEK_END",
    "BUFSIZ", "FILENAME_MAX", "FOPEN_MAX", "TMP_MAX", "L_tmpnam",
    "_IOFBF", "_IOLBF", "_IONBF", "stderr", "stdin", "stdout",

    /* --- stdlib.h --- */
    "EXIT_SUCCESS", "EXIT_FAILURE", "RAND_MAX", "MB_CUR_MAX",

    /* --- errno.h --- */
    "errno", "EDOM", "ERANGE", "EILSEQ",

    /* --- assert.h --- */
    "assert", "NDEBUG",

    /* --- limits.h --- */
    "CHAR_BIT", "SCHAR_MIN", "SCHAR_MAX", "UCHAR_MAX",
    "CHAR_MIN", "CHAR_MAX", "SHRT_MIN", "SHRT_MAX", "USHRT_MAX",
    "INT_MIN", "INT_MAX", "UINT_MAX", "LONG_MIN", "LONG_MAX", "ULONG_MAX",
    "LLONG_MIN", "LLONG_MAX", "ULLONG_MAX",

    /* --- float.h --- */
    "FLT_MIN", "FLT_MAX", "DBL_MIN", "DBL_MAX",
    "FLT_EPSILON", "DBL_EPSILON", "FLT_DIG", "DBL_DIG", "FLT_RADIX",

    /* --- time.h --- */
    "CLOCKS_PER_SEC",

    /* --- threads.h --- */
    "ONCE_FLAG_INIT", "TSS_DTOR_ITERATIONS",

    /* --- signal.h --- */
    "SIG_DFL", "SIG_IGN", "SIG_ERR",
    "SIGINT", "SIGABRT", "SIGSEGV",

    /* --- stdint.h --- */
    "INT8_MIN", "INT8_MAX", "UINT8_MAX",
    "INT16_MIN", "INT16_MAX", "UINT16_MAX",
    "INT32_MIN", "INT32_MAX", "UINT32_MAX",
    "INT64_MIN", "INT64_MAX", "UINT64_MAX",
    "INTPTR_MIN", "INTPTR_MAX", "UINTPTR_MAX",
    "INTMAX_MIN", "INTMAX_MAX", "UINTMAX_MAX",
    "SIZE_MAX", "PTRDIFF_MIN", "PTRDIFF_MAX",

    /* --- math.h --- */
    "HUGE_VAL", "HUGE_VALF", "HUGE_VALL",
    "INFINITY", "NAN",
    "FP_INFINITE", "FP_NAN", "FP_NORMAL", "FP_ZERO", "FP_SUBNORMAL",
    "FP_FAST_FMA",

    /* --- stdbool.h --- */
    "true", "false", "bool", "__bool_true_false_are_defined",

    /* --- complex.h --- */
    "I", "complex", "imaginary"
};
