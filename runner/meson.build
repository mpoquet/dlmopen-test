project('dlmopen-test-runner', 'c', default_options : ['c_std=c11'])

base_dep = dependency('base')
dl_dep = meson.get_compiler('c').find_library('dl', required : true)

executable('runner', 'runner.c',
  install: true,
  dependencies: [base_dep, dl_dep],
  c_args: '-DVERSION=@0@'.format(get_option('version'))
)
