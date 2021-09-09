dlmopen-test
============

A tiny repository to test whether dlmopen_ fits my need.

- Load several libraries (at runtime) that have the same C API.
- Call functions from the desired libraries.
- Keep the full memory of the libraries separated from each other (including dependencies).
- Keep the full memory of the libraries separated from the loader process's memory (including shared dependencies).

Conclusion: Yes, it does :). Details on `my blog`_.

.. _dlmopen: https://man7.org/linux/man-pages/man3/dlmopen.3.html
.. _my blog: https://mpoquet.github.io/blog/2021-09-isolated-dynamic-library-loading-with-dlmopen/index.html
