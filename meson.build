project('min-heap', 'c', default_options: ['c_std=gnu99'])

without_example = get_option('without_example')

libheap = library('heap',
    ['src/heap.c'],
    include_directories: ['include'],
    install: true)

libheap_dep = declare_dependency(
    link_with: [libheap],
    include_directories: ['include'])

install_headers('include/heap.h')

if not without_example

executable('heap-example', 
    ['example/main.c'],
    dependencies: [libheap_dep])

endif

