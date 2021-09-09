project('dlmopen-test-base', 'c', default_options : ['c_std=c11'])

base_shared = shared_library('base', 'base.c',
  install: true,
  c_args: '-DVERSION=@0@'.format(get_option('version'))
)

pkgc = import('pkgconfig')
pkgc.generate(name: 'base',
    libraries: base_shared,
    version: get_option('version').to_string(),
    description: 'Base library.'
)
